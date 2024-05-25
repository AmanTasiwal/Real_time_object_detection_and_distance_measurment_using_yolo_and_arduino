// constants won't change
const int TRIG_PIN = 6;             // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = 7;             // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int BUZZER_PIN = 3;           // Arduino pin connected to Piezo Buzzer's pin
const int DISTANCE_THRESHOLD = 50;  // centimeters

// variables will change:
float duration_us, distance_cm;

#include <Servo.h>
Servo s1;

const int Tx = 1;
const int Rx = 0;
#include<SoftwareSerial.h>
SoftwareSerial bluetooth(Tx, Rx);

void setup() {
  // Serial.begin (9600);         // initialize serial port
  bluetooth.begin (9600);
  pinMode(TRIG_PIN, OUTPUT);    // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);     // set arduino pin to input mode
  pinMode(BUZZER_PIN, OUTPUT);  // set arduino pin to output mode
  // put your setup code here, to run once:
  s1.attach(9);
}

void loop() {

  for (int angle = 0; angle <=90 ; angle++) {
    s1.write(angle);
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(ECHO_PIN, HIGH);
    // calculate the distance
    distance_cm = 0.017 * duration_us;
    if (distance_cm < DISTANCE_THRESHOLD) {
      digitalWrite(BUZZER_PIN, HIGH);  // turn on Piezo Buzzer
      bluetooth.write("A");
    } else {
      digitalWrite(BUZZER_PIN, LOW);  // turn off Piezo Buzzer
    }
    delay(100);  // Adjust this delay to control the speed of rotation
  }

  // // Rotate anti-clockwise
  for (int angle = 90; angle >= 0; angle--) {
    s1.write(angle);
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(ECHO_PIN, HIGH);
    // calculate the distance
    distance_cm = 0.017 * duration_us;
    if (distance_cm < DISTANCE_THRESHOLD) {
      digitalWrite(BUZZER_PIN, HIGH);  // turn on Piezo Buzzer
      bluetooth.write("A");
    } else {
      digitalWrite(BUZZER_PIN, LOW);  // turn off Piezo Buzzer
    }
    delay(100);  // Adjust this delay to control the speed of rotation
  }
}
