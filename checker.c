#include <assert.h>
#include "BMS.h"

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0.0));
  return 0;
}
