#include <Servo.h>                         // Inkluderer Servo biblioteket for at kontrollere servo motoren

Servo servo;                               // Opretter en servo objekt

#define LED1 D1                            // Definerer LED1 som værende tilsluttet NodeMCU pin D1

unsigned long previousMillisLED = 0;       // Variabel til at gemme sidste tid LED blev opdateret
unsigned long previousMillisServo = 0;     // Variabel til at gemme sidste tid servo blev opdateret

const long intervalLED = 500;              // Interval for LED blink (i millisekunder)
const long intervalServo = 1500;           // Interval for servo bevægelse (i millisekunder)

bool ledState = LOW;                       // Variabel til at gemme LED tilstand (LOW = slukket, HIGH = tændt)
bool servoMovingForward = true;            // Variabel til at bestemme servo retning (true = fremad, false = tilbage)

void setup() {
  pinMode(LED1, OUTPUT);                   // Sætter LED1 pin som output
  servo.attach(2);                         // Tilslutter servo til pin D4 (GPIO2)
  servo.write(0);                          // Sætter startposition for servo til 0 grader
}

void loop() {
  unsigned long currentMillis = millis();  // Gemmer den nuværende tid i millisekunder

  // Opdater LED
  if (currentMillis - previousMillisLED >= intervalLED) {
    previousMillisLED = currentMillis;     // Opdaterer previousMillisLED til den nuværende tid
    ledState = !ledState;                  // Skifter LED tilstand (fra tændt til slukket eller omvendt)
    digitalWrite(LED1, ledState);          // Opdaterer LED til den nye tilstand
  }

  // Opdater Servo
  if (currentMillis - previousMillisServo >= intervalServo) {
    previousMillisServo = currentMillis;   // Opdaterer previousMillisServo til den nuværende tid

    if (servoMovingForward) {
      servo.write(180);                    // Bevæger servo til 180 grader (fremad)
    } else {
      servo.write(0);                      // Bevæger servo tilbage til 0 grader (tilbage)
    }
    servoMovingForward = !servoMovingForward; // Skifter retning (fra fremad til tilbage eller omvendt)
  }
}
