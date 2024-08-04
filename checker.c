#include <stdio.h>
#include <assert.h>

typedef enum { ENGLISH, GERMAN } Language;
Language currentLanguage = ENGLISH;

const float SOC_UPPER_LIMIT = 80.0;
const float SOC_LOWER_LIMIT = 20.0;
const float TEMP_UPPER_LIMIT = 45.0;
const float TEMP_LOWER_LIMIT = 0.0;
const float CHARGE_RATE_UPPER_LIMIT = 0.8;
const float TOLERANCE = 0.05;  // 5% tolerance

void printMessage(const char* englishMsg, const char* germanMsg) {
    if (currentLanguage == ENGLISH) {
        printf("%s\n", englishMsg);
    } else {
        printf("%s\n", germanMsg);
    }
}

int isWithinRange(float value, float lower, float upper) {
    return (value >= lower && value <= upper);
}

void checkAndPrintWarning(float value, float lower, float upper, const char* lowWarningEng, const char* lowWarningGer, const char* highWarningEng, const char* highWarningGer) {
    if (value < lower + upper * TOLERANCE) {
        printMessage(lowWarningEng, lowWarningGer);
    } else if (value > upper - upper * TOLERANCE) {
        printMessage(highWarningEng, highWarningGer);
    }
}

int checkTemperature(float temperature) {
    if (!isWithinRange(temperature, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT)) {
        printMessage("Temperature is out of range!", "Temperatur ist außerhalb des Bereichs!");
        return 0;
    }
    checkAndPrintWarning(temperature, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, "Warning: Temperature nearing lower limit", "Warnung: Temperatur nähert sich dem unteren Grenzwert", "Warning: Temperature nearing upper limit", "Warnung: Temperatur nähert sich dem oberen Grenzwert");
    return 1;
}

int checkSoc(float soc) {
    if (!isWithinRange(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT)) {
        printMessage("State of Charge is out of range!", "Ladezustand ist außerhalb des Bereichs!");
        return 0;
    }
    checkAndPrintWarning(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "Warning: State of Charge nearing lower limit", "Warnung: Ladezustand nähert sich dem unteren Grenzwert", "Warning: State of Charge nearing upper limit", "Warnung: Ladezustand nähert sich dem oberen Grenzwert");
    return 1;
}

int checkChargeRate(float chargeRate) {
    if (chargeRate > CHARGE_RATE_UPPER_LIMIT) {
        printMessage("Charge Rate is too high!", "Laderate ist zu hoch!");
        return 0;
    }
    if (chargeRate > CHARGE_RATE_UPPER_LIMIT - CHARGE_RATE_UPPER_LIMIT * TOLERANCE) {
        printMessage("Warning: Charge Rate nearing upper limit", "Warnung: Laderate nähert sich dem oberen Grenzwert");
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkTemperature(temperature) && checkSoc(soc) && checkChargeRate(chargeRate);
}

int main() {
    currentLanguage = ENGLISH;
    assert(batteryIsOk(25.0, 70.0, 0.7));
    assert(!batteryIsOk(50.0, 85.0, 0.9));

    currentLanguage = GERMAN;
    assert(batteryIsOk(25.0, 70.0, 0.7));
    assert(!batteryIsOk(50.0, 85.0, 0.9));
    return 0;
}
