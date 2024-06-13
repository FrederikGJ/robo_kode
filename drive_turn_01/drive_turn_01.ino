#include <Servo.h>  // Inkluderer Servo biblioteket for at kontrollere servo motoren

#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

Servo servo;  // Opretter et servo objekt

unsigned long previousMillisMotor = 0;  // Variabel til at gemme sidste tid motorerne blev opdateret
unsigned long previousMillisServo = 0;  // Variabel til at gemme sidste tid servo blev opdateret

const long intervalMotor = 3000;  // Interval for motor kørsel og stop (i millisekunder)
const long intervalServo = 1500;  // Interval for servo bevægelse (i millisekunder)

bool motorRunning = false;  // Variabel til at gemme motorens tilstand (false = slukket, true = tændt)
bool servoMovingForward = true;  // Variabel til at bestemme servo retning (true = fremad, false = tilbage)

void setup() {
  // Sætter alle motorcontroller pins til output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sætter motorerne til at starte i slukket tilstand
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

  // Tilslutter servo til pin D7 (GPIO13)
  servo.attach(D7);
  servo.write(0);  // Sætter startposition for servo til 0 grader
}

void loop() {
  unsigned long currentMillis = millis();  // Gemmer den nuværende tid i millisekunder

  // Opdater Motorer
  if (currentMillis - previousMillisMotor >= intervalMotor) {
    previousMillisMotor = currentMillis;  // Opdaterer previousMillisMotor til den nuværende tid

    if (motorRunning) {
      // Slukker motorerne
      digitalWrite(ENA, LOW);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(ENB, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    } else {
      // Tænder motorerne
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    motorRunning = !motorRunning;  // Skifter motor tilstand
  }

  // Opdater Servo
  if (currentMillis - previousMillisServo >= intervalServo) {
    previousMillisServo = currentMillis;  // Opdaterer previousMillisServo til den nuværende tid

    if (servoMovingForward) {
      servo.write(45);  // Bevæger servo til 180 grader (fremad)
    } else {
      servo.write(0);  // Bevæger servo tilbage til 0 grader (tilbage)
    }
    servoMovingForward = !servoMovingForward;  // Skifter retning (fra fremad til tilbage eller omvendt)
  }
}
