#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
int LED_PIN = 3;
int LEDS = 57;
int FLOWTIME = 20;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.setBrightness(100); // Set the strips brightness

  strip.begin(); // Prepars the datapin for neopixel commands
  strip.show(); // Turns off all the leds

}

void loop() {
  rainbowCycle(5);
}

// Rainbowlight
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*1; j++) {
    for(i=0; i< 58; i++) {
      strip.setPixelColor(strip.numPixels() - i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }

    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
