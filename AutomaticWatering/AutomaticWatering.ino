#include <TimeLib.h>

const int motorInput1 = 10;    // Motor driver input 1
const int motorInput2 = 11;    // Motor driver input 2
const int en = 9;              // Enable pin for motor driver
const int led1 = 7;            // LED indicator

unsigned long previousMillis = 0;
const long pumpInterval = 24 * 60 * 60 * 1000;  // 24 hours in milliseconds

void setup() {
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(led1, OUTPUT);
  
  Serial.begin(9600);  
  setTime(16, 10, 0, 7, 2, 2024);  // Set initial time (16:10:00 on Feb 7, 2024)
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if it's 16:10:00
  if (hour() == 16 && minute() == 10 && second() == 0) {
    // Check if a day has passed
    if (currentMillis - previousMillis >= pumpInterval) {
      previousMillis = currentMillis;

      Serial.println("Water pump activated at 16:10:00");

      // Run motor for 50 seconds
      analogWrite(en, 255);
      digitalWrite(motorInput1, HIGH);
      digitalWrite(motorInput2, LOW);
      digitalWrite(led1, HIGH);
      delay(50000);  // 50 seconds ON

      // Turn off motor
      digitalWrite(motorInput1, LOW);
      digitalWrite(motorInput2, LOW);
      analogWrite(en, 0);
      digitalWrite(led1, LOW);
    }
  }

  // Continuous on-off cycling every 6 seconds
  analogWrite(en, 255);
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(led1, HIGH);
  Serial.println("Water pump ON");
  delay(6000);  

  analogWrite(en, 0);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(led1, LOW);
  Serial.println("Water pump OFF");
  delay(6000);
}
