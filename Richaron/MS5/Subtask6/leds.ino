
void leds_on() {
    for (int i = 0; i < 6; i++) {
        leds[i] = CRGB(100, 100, 100);
    }
    FastLED.show();
}

void leds_set(CRGB c) {
    for (int i = 0; i < 6; i++) {
        leds[i] = c;
    }
    FastLED.show();
}

void leds_off() {
    for (int i = 0; i < 6; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
}

void leds_flash(byte i) {
    for (byte I = 0; I < i; I++) {
        leds_on();
        delay(50);
        leds_off();
        delay(50);
    }
}

void leds_flash(byte i, CRGB c) {
    for (byte I = 0; I < i; I++) {
        leds_set(c);
        delay(50);
        leds_off();
        delay(50);
    }
}

void party(byte i) {
    for (byte I = 0; I < i; I++) {
        leds[(I + 0) % 6] = CRGB::Red;
        leds[(I + 1) % 6] = CRGB::Yellow;
        leds[(I + 2) % 6] = CRGB::Green;
        leds[(I + 3) % 6] = CRGB::Blue;
        leds[(I + 4) % 6] = CRGB::Purple;
        leds[(I + 5) % 6] = CRGB::Pink;
        FastLED.show();
        delay(150);
    }
}
