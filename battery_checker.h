#ifndef BATTERY_CHECKER_H
#define BATTERY_CHECKER_H
#include "messages.h"
typedef enum { ENGLISH, GERMAN } Language;

extern Language currentLanguage;

void printMessage(const char* message);
const char* getMessage(Message msg);
int isWithinRange(float value, float lower, float upper);
void checkAndPrintWarning(float value, float lower, float upper, Messages msg);
int checkValue(float value, float lower, float upper, Messages msg);
int checkChargeRate(float chargeRate);
int batteryIsOk(float temperature, float soc, float chargeRate);
void runTests();

#endif
