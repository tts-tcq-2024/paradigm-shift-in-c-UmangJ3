#include <stdio.h>
#include <assert.h>

int checkTemperature(float temperature) {
    return !(temperature < 0 || temperature > 45);
}

int checkSoc(float soc) {
    return !(soc < 20 || soc > 80);
}

int checkChargeRate(float chargeRate) {
    return !(chargeRate > 0.8);
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkTemperature(temperature) && checkSoc(soc) && checkChargeRate(chargeRate);
}

int main() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
}
