#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(3, 0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(4 , 1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(3, 2, NEO_GRB + NEO_KHZ800);

enum colors {
  RED = 0xff0000,
  BLUE = 0x0000ff,
  GREEN = 0x00ff00,
  WHITE = 0x7f7f7f,
};

void setup() {
  strip0.begin();
  strip1.begin();
  strip2.begin();
}

void demo() {
  for (int i = 0; i < 255; i += 32) {
    for (int j = 0; j < 4; j++) {
      strip0.setPixelColor(j, RED); // red
      strip1.setPixelColor(j, GREEN); // green
      strip2.setPixelColor(j, BLUE); // blue
    }
    strip0.show();
    strip1.show();
    strip2.show();
    delay(300); // don't run as fast as possible
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip0.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip0.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip0.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<4; i++) {
      strip0.setPixelColor(i, c);
      strip1.setPixelColor(i, c);
      strip2.setPixelColor(i, c);
      strip0.show();
      strip1.show();
      strip2.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<4; i++) {
      strip0.setPixelColor(i, Wheel((i+j) & 255));
      strip1.setPixelColor(i, Wheel((i+j) & 255));
      strip2.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip0.show();
    strip1.show();
    strip2.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< 0; i++) {
      strip0.setPixelColor(i, Wheel(((i * 256 / 4) + j) & 255));
      strip1.setPixelColor(i, Wheel(((i * 256 / 4) + j) & 255));
      strip2.setPixelColor(i, Wheel(((i * 256 / 4) + j) & 255));
    }
    strip0.show();
    strip1.show();
    strip2.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < 4; i=i+3) {
        strip0.setPixelColor(i+q, c);    //turn every third pixel on
        strip1.setPixelColor(i+q, c);    //turn every third pixel on
        strip2.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip0.show();
      strip1.show();
      strip2.show();

      delay(wait);

      for (int i=0; i < 4; i=i+3) {
        strip0.setPixelColor(i+q, 0);        //turn every third pixel off
        strip1.setPixelColor(i+q, 0);        //turn every third pixel off
        strip2.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < 4; i=i+3) {
          strip0.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
          strip1.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
          strip2.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip0.show();
        strip1.show();
        strip2.show();

        delay(wait);

        for (int i=0; i < 4; i=i+3) {
          strip0.setPixelColor(i+q, 0);        //turn every third pixel off
          strip1.setPixelColor(i+q, 0);        //turn every third pixel off
          strip2.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

void loop() {
  demo();
  // Some example procedures showing how to display to the pixels:
  colorWipe(RED, 50); // Red
  colorWipe(GREEN, 50); // Green
  colorWipe(BLUE, 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(WHITE, 50); // White
  theaterChase(RED, 50); // Red
  theaterChase(BLUE, 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}
