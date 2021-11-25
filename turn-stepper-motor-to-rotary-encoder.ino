#include <pt.h>
#include <FastLED.h>
//
#define inputA 6
#define inputB 7
#define LED 13

// How many leds in your strip?
#define NUM_LEDS 12
#define LED_PIN 4
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

// Define the array of leds
CRGB leds[NUM_LEDS];

int led_counter = 0;
int old_led_counter = 0;

int AState = 0;
int AoldState = 0;
//
int BState = 0;
int BoldState = 0;
int b = 0;
int bb = 0;
int counter = 0;
//
int change_count = 0;
int old_position = 0;

//
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(inputA, INPUT);
  pinMode(inputB, INPUT);
  pinMode(LED, OUTPUT);
  AoldState = digitalRead(inputA);
  BoldState = digitalRead(inputB);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS ); // GRB ordering is typical

}

void process_led_counter(int new_position) {
  int position_change = new_position - old_position;
  Serial.print("position_change");
  Serial.println(position_change);

  if (position_change >= 2 ) {
    if (led_counter < 11) {
      old_led_counter = led_counter;
      led_counter++;
    }
    else {
      old_led_counter = led_counter;
      led_counter = 0;
    }

  }
  if (position_change <= -2 ) {
    if (led_counter > 0) {
      old_led_counter = led_counter;
      led_counter--;
    }
    else {
      old_led_counter = led_counter;
      led_counter = 11;
    }

  }
  leds[led_counter] = CRGB::Red;
  // Now turn the LED off, then pause
  leds[old_led_counter] = CRGB::Black;
  FastLED.show();
  Serial.print("now led counter is : ");
  Serial.println(led_counter);
  if (change_count > 2) {
    old_position = new_position;
    change_count = 0;
  } else {
    change_count++;
  }
}
//

//
void loop() {
  AState = digitalRead(inputA); // Reads the "current" state of the inputA
  BState = digitalRead(inputB);
  // If the previous and the current state of the inputA are different, that means a Pulse has occured
  if (AState != AoldState) {
    if (BState != AState ) {
      Serial.println("counter value:");
      counter++;
      Serial.println(counter);
      process_led_counter(counter);
    }
  }
  if (BState != BoldState) {
    if (BState != AState ) {
      Serial.println("counter value:");
      counter--;
      Serial.println(counter);
      process_led_counter(counter);
    }
  }
  AoldState = AState; // Updates the previous state of the inputA with the current state
  BoldState = BState;

}
