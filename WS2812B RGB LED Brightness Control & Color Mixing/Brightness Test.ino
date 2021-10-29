#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

int Pot = A0;
int PotVal = 0;
int OutVal = 0;


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
  PotVal = analogRead(Pot);
  Serial.println(OutVal);
  OutVal = map(PotVal, 0, 1023, 0, 255);

  analogWrite(NUM_LEDS, OutVal);
  

  FastLED.setBrightness(OutVal);
  
  leds[0] = CRGB(255, 255, 255); 
  FastLED.show();
}
