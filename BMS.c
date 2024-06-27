#include <stdio.h>
#include "BMS.h"

const char* getStatusMessage(BatteryStatus status) 
{
  switch (status) 
  {
    case TEMPERATURE_LOW: return "Temperature too low!";
    case TEMPERATURE_HIGH: return "Temperature too high!";
    case SOC_LOW: return "State of Charge too low!";
    case SOC_HIGH: return "State of Charge too high!";
    case CHARGE_RATE_HIGH: return "Charge Rate too high!";
    default: return "Battery is OK.";
  }
}

BatteryStatus evaluateBattery(float temperature, float soc, float chargeRate) 
{
  if (isTemperatureOutOfRange(temperature)) 
  {
    return TEMPERATURE_LOW;
  }
  if (isSocOutOfRange(soc)) 
  {
    return SOC_LOW;
  }
  if (isChargeRateOutOfRange(chargeRate)) 
  {
    return CHARGE_RATE_HIGH;
  }
  return OK;
}

int isTemperatureOutOfRange(float temperature) 
{
  return (temperature < 0 || temperature > 45);
}

int isSocOutOfRange(float soc) 
{
  return (soc < 20 || soc > 80);
}

int isChargeRateOutOfRange(float chargeRate) 
{
  return (chargeRate > 0.8);
}

int batteryIsOk(float temperature, float soc, float chargeRate) 
{
  BatteryStatus status = evaluateBattery(temperature, soc, chargeRate);
  printf("%s\n", getStatusMessage(status));
  return status == OK;
}
