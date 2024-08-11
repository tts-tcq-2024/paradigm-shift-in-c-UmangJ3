#include <stdio.h>
#include <assert.h>
#include "battery_checker.h"
#include "messages.h"

Language currentLanguage = ENGLISH;

const float SOC_UPPER_LIMIT = 80.0;
const float SOC_LOWER_LIMIT = 20.0;
const float TEMP_UPPER_LIMIT = 45.0;
const float TEMP_LOWER_LIMIT = 0.0;
const float CHARGE_RATE_UPPER_LIMIT = 0.8;
const float TOLERANCE = 0.05;  // 5% tolerance

void printMessage(const char* message) {
    printf("%s\n", message);
}

const char* getMessage(Message msg) {
    switch (currentLanguage) {
        case ENGLISH: return msg.english;
        case GERMAN: return msg.german;
        default: return msg.english;
    }
}

int isWithinRange(float value, float lower, float upper) {
    return (value >= lower && value <= upper);
}

void checkAndPrintWarning(float value, float lower, float upper, Messages msg) {
    if (value < lower + upper * TOLERANCE) {
        printMessage(getMessage(msg.lowWarning));
    } else if (value > upper - upper * TOLERANCE) {
        printMessage(getMessage(msg.highWarning));
    }
}

int checkValue(float value, float lower, float upper, Messages msg) {
    if (!isWithinRange(value, lower, upper)) {
        printMessage(getMessage(msg.outOfRange));
        return 0;
    }
    checkAndPrintWarning(value, lower, upper, msg);
    return 1;
}

int checkChargeRate(float chargeRate) {
    Messages chargeRateMessages = messages[2];
    if (chargeRate > CHARGE_RATE_UPPER_LIMIT) {
        printMessage(getMessage(chargeRateMessages.outOfRange));
        return 0;
    }
    if (chargeRate > CHARGE_RATE_UPPER_LIMIT - CHARGE_RATE_UPPER_LIMIT * TOLERANCE) {
        printMessage(getMessage(chargeRateMessages.highWarning));
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkValue(temperature, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, messages[0]) &&
           checkValue(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, messages[1]) &&
           checkChargeRate(chargeRate);
}



void runTests() {

    currentLanguage = ENGLISH;
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));

    assert(!batteryIsOk(50.0, 70.0, 0.7));
    assert(!batteryIsOk(25.0, 85.0, 0.7));
    assert(!batteryIsOk(25.0, 70.0, 0.9));

    assert(batteryIsOk(45.0, 70.0, 0.7));
    assert(batteryIsOk(0.0, 70.0, 0.7));
    assert(batteryIsOk(25.0, 80.0, 0.7));
    assert(batteryIsOk(25.0, 20.0, 0.7));
    assert(batteryIsOk(25.0, 70.0, 0.8));
    
    assert(batteryIsOk(TEMP_LOWER_LIMIT + TEMP_UPPER_LIMIT * TOLERANCE - 0.1, 70.0, 0.7));
    assert(batteryIsOk(TEMP_UPPER_LIMIT - TEMP_UPPER_LIMIT * TOLERANCE + 0.1, 70.0, 0.7));
    assert(batteryIsOk(25.0, SOC_LOWER_LIMIT + SOC_UPPER_LIMIT * TOLERANCE - 0.1, 0.7));
    assert(batteryIsOk(25.0, SOC_UPPER_LIMIT - SOC_UPPER_LIMIT * TOLERANCE + 0.1, 0.7));
    
    currentLanguage = GERMAN;
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));

    assert(!batteryIsOk(50.0, 70.0, 0.7));
    assert(!batteryIsOk(25.0, 85.0, 0.7));
    assert(!batteryIsOk(25.0, 70.0, 0.9));

    assert(batteryIsOk(45.0, 70.0, 0.7));
    assert(batteryIsOk(0.0, 70.0, 0.7));
    assert(batteryIsOk(25.0, 80.0, 0.7));
    assert(batteryIsOk(25.0, 20.0, 0.7));
    assert(batteryIsOk(25.0, 70.0, 0.8));
    
    assert(batteryIsOk(TEMP_LOWER_LIMIT + TEMP_UPPER_LIMIT * TOLERANCE - 0.1, 70.0, 0.7));
    assert(batteryIsOk(TEMP_UPPER_LIMIT - TEMP_UPPER_LIMIT * TOLERANCE + 0.1, 70.0, 0.7));
    assert(batteryIsOk(25.0, SOC_LOWER_LIMIT + SOC_UPPER_LIMIT * TOLERANCE - 0.1, 0.7));
    assert(batteryIsOk(25.0, SOC_UPPER_LIMIT - SOC_UPPER_LIMIT * TOLERANCE + 0.1, 0.7));
    

    
}
