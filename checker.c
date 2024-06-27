#include <assert.h>
#include "BMS.h"

void testBatteryStatus() 
{
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0.0));
  assert(!batteryIsOk(-1, 50, 0.5));
  assert(!batteryIsOk(25, 19, 0.5));
  assert(!batteryIsOk(25, 50, 0.9));
  assert(batteryIsOk(0, 20, 0.8));
  assert(batteryIsOk(45, 80, 0.8));
}

int main() 
{
  testBatteryStatus();
  return 0;
}
