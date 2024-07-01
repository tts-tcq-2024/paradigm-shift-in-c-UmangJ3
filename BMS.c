#include <stdio.h>
#include "BMS.h"

const char* getStatusMessage(BatteryStatus status) {
    // Define a lookup table for status messages
    static const char* statusMessages[] = {
        [TEMPERATURE_LOW] = "Temperature too low!",
        [TEMPERATURE_HIGH] = "Temperature too high!",
        [SOC_LOW] = "State of Charge too low!",
        [SOC_HIGH] = "State of Charge too high!",
        [CHARGE_RATE_HIGH] = "Charge Rate too high!",
        [OK] = "Battery is OK."
    };

    // Validate the status and return the corresponding message
    if (status < 0 || status >= sizeof(statusMessages) / sizeof(statusMessages[0])) {
        return "Unknown status"; // Handle unexpected status
    }

    return statusMessages[status];
}

BatteryStatus evaluateBattery(float temperature, float soc, float chargeRate) {
    int temperatureOutOfRange = isTemperatureOutOfRange(temperature);
    int socOutOfRange = isSocOutOfRange(soc);
    int chargeRateOutOfRange = isChargeRateOutOfRange(chargeRate);
    BatteryStatus status = OK;

    if (temperatureOutOfRange && (socOutOfRange || chargeRateOutOfRange)) {
        status = TEMPERATURE_LOW;
    } else if (!temperatureOutOfRange && socOutOfRange) {
        status = SOC_LOW;
    } else if (!temperatureOutOfRange && chargeRateOutOfRange) {
        status = CHARGE_RATE_HIGH;
    }
    return status;
}

int isTemperatureOutOfRange(float temperature) {
    return (temperature < 0 || temperature > 45);
}

int isSocOutOfRange(float soc) {
    return (soc < 20 || soc > 80);
}

int isChargeRateOutOfRange(float chargeRate) {
    return (chargeRate > 0.8);
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    BatteryStatus status = evaluateBattery(temperature, soc, chargeRate);
    return status == OK;
}
