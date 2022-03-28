#include <helpers.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    psl("This is running!");
    putl(millis());
    delay(1000);
}
