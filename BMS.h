#ifndef BMS_H
#define BMS_H

typedef enum 
{
  OK,
  TEMPERATURE_LOW,
  TEMPERATURE_HIGH,
  SOC_LOW,
  SOC_HIGH,
  CHARGE_RATE_HIGH
} BatteryStatus;

const char* getStatusMessage(BatteryStatus status);
BatteryStatus evaluateBattery(float temperature, float soc, float chargeRate);
int batteryIsOk(float temperature, float soc, float chargeRate);

int isTemperatureOutOfRange(float temperature);
int isSocOutOfRange(float soc);
int isChargeRateOutOfRange(float chargeRate);

#endif // BMS_H
