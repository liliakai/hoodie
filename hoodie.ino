
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(3, 0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(4 , 1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(3, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  strip0.begin();
  strip1.begin();
  strip2.begin();
}

void loop() {
  for (int i = 0; i < 255; i += 32) {
    for (int j = 0; j < 4; j++) {
      strip0.setPixelColor(j, i,0,0); // red
      strip1.setPixelColor(j, 0,i,0); // green
      strip2.setPixelColor(j, 0,0,i); // blue
    }
    strip0.show();
    strip1.show();
    strip2.show();
    delay(300); // don't run as fast as possible
  }
}
