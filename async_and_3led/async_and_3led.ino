#include <Servo.h>                         // Inkluderer Servo biblioteket for at kontrollere servo motoren

Servo servo;                               // Opretter en servo objekt

#define LED1_PIN D1                        // Definerer LED1 som værende tilsluttet NodeMCU pin D1 (GPIO5)
#define LED2_PIN D0                        // Definerer LED2 som værende tilsluttet NodeMCU pin GPIO16 (D0)
#define LED3_PIN D3                        // Definerer LED3 som værende tilsluttet NodeMCU pin GPIO0 (D3)

unsigned long previousMillisLED = 0;       // Variabel til at gemme sidste tid LED blev opdateret
unsigned long previousMillisServo = 0;     // Variabel til at gemme sidste tid servo blev opdateret
unsigned long previousMillisExtraLED1 = 0; // Variabel til at gemme sidste tid ekstra LED1 blev opdateret
unsigned long previousMillisExtraLED2 = 0; // Variabel til at gemme sidste tid ekstra LED2 blev opdateret

const long intervalLED = 500;              // Interval for LED blink (i millisekunder)
const long intervalServo = 1500;           // Interval for servo bevægelse (i millisekunder)
const long intervalExtraLED1 = 500;       // Interval for ekstra LED1 blink (i millisekunder)
const long intervalExtraLED2 = 500;       // Interval for ekstra LED2 blink (i millisekunder)

bool ledState = LOW;                       // Variabel til at gemme LED tilstand (LOW = slukket, HIGH = tændt)
bool extraLED1State = LOW;                 // Variabel til at gemme ekstra LED1 tilstand (LOW = slukket, HIGH = tændt)
bool extraLED2State = LOW;                 // Variabel til at gemme ekstra LED2 tilstand (LOW = slukket, HIGH = tændt)
bool servoMovingForward = true;            // Variabel til at bestemme servo retning (true = fremad, false = tilbage)

void setup() {
  pinMode(LED1_PIN, OUTPUT);               // Sætter LED1 pin som output
  pinMode(LED2_PIN, OUTPUT);               // Sætter LED2 pin som output
  pinMode(LED3_PIN, OUTPUT);               // Sætter LED3 pin som output

  servo.attach(2);                         // Tilslutter servo til pin D4 (GPIO2)
  servo.write(0);                          // Sætter startposition for servo til 0 grader
}

void loop() {
  unsigned long currentMillis = millis();  // Gemmer den nuværende tid i millisekunder

  // Opdater LED1
  if (currentMillis - previousMillisLED >= intervalLED) {
    previousMillisLED = currentMillis;     // Opdaterer previousMillisLED til den nuværende tid
    ledState = !ledState;                  // Skifter LED tilstand (fra tændt til slukket eller omvendt)
    digitalWrite(LED1_PIN, ledState);      // Opdaterer LED1 til den nye tilstand
  }

    // Opdater ekstra LED1
  if (currentMillis - previousMillisExtraLED1 >= intervalExtraLED1) {
    previousMillisExtraLED1 = currentMillis; // Opdaterer previousMillisExtraLED1 til den nuværende tid
    extraLED1State = !extraLED1State;        // Skifter ekstra LED1 tilstand (fra tændt til slukket eller omvendt)
    digitalWrite(LED2_PIN, extraLED1State);  // Opdaterer ekstra LED1 til den nye tilstand
  }

  // Opdater ekstra LED2
  if (currentMillis - previousMillisExtraLED2 >= intervalExtraLED2) {
    previousMillisExtraLED2 = currentMillis; // Opdaterer previousMillisExtraLED2 til den nuværende tid
    extraLED2State = !extraLED2State;        // Skifter ekstra LED2 tilstand (fra tændt til slukket eller omvendt)
    digitalWrite(LED3_PIN, extraLED2State);  // Opdaterer ekstra LED2 til den nye tilstand
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
