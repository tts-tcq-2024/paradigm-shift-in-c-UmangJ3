#include <stdio.h>
#include "BMS.h"

const char* getStatusMessage(BatteryStatus status) {
    static const char* statusMessages[] = {
        [TEMPERATURE_LOW] = "Temperature too low!",
        [TEMPERATURE_HIGH] = "Temperature too high!",
        [SOC_LOW] = "State of Charge too low!",
        [SOC_HIGH] = "State of Charge too high!",
        [CHARGE_RATE_HIGH] = "Charge Rate too high!",
        [OK] = "Battery is OK."
    };

    if (status < 0 || status >= sizeof(statusMessages) / sizeof(statusMessages[0])) {
        return "Unknown status";
    }

    return statusMessages[status];
}

BatteryStatus evaluateTemperature(float temperature) {
    if (temperature < 0) {
        return TEMPERATURE_LOW;
    } else if (temperature > 45) {
        return TEMPERATURE_HIGH;
    }
    return OK;
}

BatteryStatus evaluateSoc(float soc) {
    if (soc < 20) {
        return SOC_LOW;
    } else if (soc > 80) {
        return SOC_HIGH;
    }
    return OK;
}

BatteryStatus evaluateChargeRate(float chargeRate) {
    if (chargeRate > 0.8) {
        return CHARGE_RATE_HIGH;
    }
    return OK;
}

BatteryStatus getFirstNonOkStatus(BatteryStatus statuses[], int size) {
    for (int i = 0; i < size; i++) {
        if (statuses[i] != OK) {
            return statuses[i];
        }
    }
    return OK;
}

BatteryStatus evaluateBatteryStatus(float temperature, float soc, float chargeRate) {
    BatteryStatus statuses[] = {
        evaluateTemperature(temperature),
        evaluateSoc(soc),
        evaluateChargeRate(chargeRate)
    };
    return getFirstNonOkStatus(statuses, sizeof(statuses) / sizeof(statuses[0]));
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    return evaluateBatteryStatus(temperature, soc, chargeRate) == OK;
}
