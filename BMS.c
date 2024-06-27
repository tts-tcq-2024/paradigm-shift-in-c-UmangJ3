#include <stdio.h>
#include <assert.h>

typedef enum 
{
  OK,
  TEMPERATURE_LOW,
  TEMPERATURE_HIGH,
  SOC_LOW,
  SOC_HIGH,
  CHARGE_RATE_HIGH
} BatteryStatus;

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
  if (temperature < 0) 
  {
    return TEMPERATURE_LOW;
  } 
  else if (temperature > 45) 
  {
    return TEMPERATURE_HIGH;
  } 
  else if (soc < 20) 
  {
    return SOC_LOW;
  } 
  else if (soc > 80) 
  {
    return SOC_HIGH;
  } 
  else if (chargeRate > 0.8) 
  {
    return CHARGE_RATE_HIGH;
  }
  return OK;
}

int batteryIsOk(float temperature, float soc, float chargeRate) 
{
  BatteryStatus status = evaluateBattery(temperature, soc, chargeRate);
  printf("%s\n", getStatusMessage(status));
  return status == OK;
}

void testBatteryStatus() 
{
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0.0));
  assert(!batteryIsOk(-1, 50, 0.5));
  assert(!batteryIsOk(25, 19, 0.5));
  assert(!batteryIsOk(25, 50, 0.9));
  
}

int main() 
{
  testBatteryStatus();
  return 0;
}
