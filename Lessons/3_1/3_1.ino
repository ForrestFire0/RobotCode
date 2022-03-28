#include <helpers.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    volatile int howMany = 0;
    howMany = getNumber();
    putl(howMany);
}

__attribute__((noinline)) int getNumber() {
    return 10;
}
