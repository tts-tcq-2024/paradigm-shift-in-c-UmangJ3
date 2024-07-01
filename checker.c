#include <assert.h>
#include "BMS.h"

void testBatteryStatus() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0.0));
}

int main() {
  testBatteryStatus();
  return 0;
}
