#define BLYNK_TEMPLATE_ID "TMPL5V8No8mX-"
#define BLYNK_TEMPLATE_NAME "Control DC motor"
#define BLYNK_DEVICE_NAME "motorcontroller"  // You can set this to any name you like

#include <Servo.h>  // Include Servo library for controlling the servo motor
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define WIFI_SSID "WIFI_FREE"  // Replace "WIFI_FREE" with your WiFi SSID
#define WIFI_PASS ""  // If your WiFi has no password, leave this empty

#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

Servo servo;  // Create a Servo object

unsigned long previousMillisServo = 0;  // Variable to store the last time the servo was updated
const long intervalServo = 1500;  // Interval for servo movement (in milliseconds)

bool motorRunning = false;  // Variable to store motor state (false = off, true = on)
bool servoMovingForward = true;  // Variable to determine servo direction (true = forward, false = backward)

// Authentication token
char auth[] = "KC7dMzJcI8w_CnAZxe_b9qJM_kIyiMYI";

void setup() {
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, WIFI_SSID, WIFI_PASS);

  // Set all motor controller pins to output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set motors to start in off state
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

  // Attach servo to pin D7 (GPIO13)
  servo.attach(D7);
  delay(1000);  // Give some time for the servo to initialize
  servo.write(0);  // Set start position for servo to 0 degrees
}

void loop() {
  Blynk.run();

  // Handle servo movement
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisServo >= intervalServo) {
    previousMillisServo = currentMillis;  // Update previousMillisServo to the current time

    if (servoMovingForward) {
      servo.write(180);  // Move servo to 180 degrees (forward)
    } else {
      servo.write(0);  // Move servo back to 0 degrees (backward)
    }
    servoMovingForward = !servoMovingForward;  // Toggle direction
  }
}

// Function to control the motor
BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    // Turn on the motors (forward)
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    // Turn off the motors
    digitalWrite(ENA, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  motorRunning = !motorRunning;  // Toggle motor state
}

// Function to control the motor backward
BLYNK_WRITE(V2) {
  int value = param.asInt();
  if (value == 1) {
    // Turn on the motors (backward)
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else {
    // Turn off the motors
    digitalWrite(ENA, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  motorRunning = !motorRunning;  // Toggle motor state
}
