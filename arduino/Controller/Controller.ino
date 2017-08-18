#include "PinChangeInterrupt.h"
#include "TimerOne.h"
#include <Servo.h>

/*
    Controller

    This sketch reads input from an RC receiver and writes the input to an ESC, a servo, and a raspberry pi.

    The circuit:
    * RC receiver steering on pin 2
    * RC receiver ESC on pin 3
    * RC servo on pin 10
    * RC ESC on pin 9
*/

unsigned int debug_counter=0;

// choose a valid PinChangeInterrupt pin of your Arduino board  
#define STEERING_INPUT_PIN 2
#define ENGINE_INPUT_PIN 3
#define STEERING_OUTPUT_PIN 10
#define ENGINE_OUTPUT_PIN 9

volatile unsigned long engine_input = 0;
volatile unsigned long steering_input = 0;
unsigned long steer_pin_time = 0;
unsigned long engine_pin_time = 0;

unsigned long lastMillis = 0;
const long interval = 0;

Servo steer;  // servo object to control the servo
Servo engine; // servo object to control the ESC

void setup()
{
  // start serial output to raspberry
  Serial.begin(115200);

  steer.attach(STEERING_OUTPUT_PIN);
  engine.attach(ENGINE_OUTPUT_PIN);
  
  // set pins to input with a pullup
  pinMode(ENGINE_INPUT_PIN, INPUT_PULLUP);
  pinMode(STEERING_INPUT_PIN, INPUT_PULLUP);

  // attach the new PinChangeInterrupts and enable event functions
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENGINE_INPUT_PIN), timeEngineInput, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(STEERING_INPUT_PIN), timeSteeringInput, CHANGE);
}

void loop_()
{
  if (millis() - lastMillis >= interval) {
    lastMillis = millis();
    Serial.print("steer:");
    Serial.print(steering_input, DEC);
    Serial.print(" engine:");
    Serial.println(engine_input, DEC);
  }
  steer.writeMicroseconds(steering_input);
  engine.writeMicroseconds(engine_input);
}

void loop()
{
  if (millis() - lastMillis >= interval) {
    lastMillis = millis();
    Serial.print("steer:");
    Serial.print(debug_counter);
    Serial.print(" engine:");
    Serial.println(debug_counter);
    debug_counter++;
  }
  
  steer.writeMicroseconds(steering_input);
  engine.writeMicroseconds(engine_input);
}

void timeEngineInput(void)
{
  if (digitalRead(ENGINE_INPUT_PIN) == HIGH) {
    engine_pin_time = micros();
  } else {
    engine_input = micros() - engine_pin_time;
  }
}

void timeSteeringInput(void)
{
  if (digitalRead(STEERING_INPUT_PIN) == HIGH) {
    steer_pin_time = micros();
  } else {
    steering_input =  micros() - steer_pin_time;
  }
}
