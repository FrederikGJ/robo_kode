 #include <Servo.h>

Servo servo;

#define LED1 D1 // Led in NodeMCU at pin D1

unsigned long previousMillisLED = 0;        // variabel til at gemme sidste tid LED blev opdateret
unsigned long previousMillisServo = 0;      // variabel til at gemme sidste tid servo blev opdateret

const long intervalLED = 500;               // interval for LED blink (i millisekunder)
const long intervalServo = 1500;            // interval for servo bevægelse (i millisekunder)

bool ledState = LOW;                        // variabel til at gemme LED tilstand
bool servoMovingForward = true;             // variabel til at bestemme servo retning

void setup() {
  Serial.begin(115200);                     // Start seriel kommunikation for debug
  pinMode(LED1, OUTPUT);                    // LED1 D1 pin som output
  servo.attach(2);                          // D4
  servo.write(0);                           // start position for servo
}

void loop() {
  unsigned long currentMillis = millis();   // gem nuværende tid

  // Opdater LED
  if (currentMillis - previousMillisLED >= intervalLED) {
    previousMillisLED = currentMillis;
    ledState = !ledState;                   // skift LED tilstand
    digitalWrite(LED1, ledState);           // opdater LED
    Serial.print("LED state: ");
    Serial.println(ledState);               // Print LED tilstand for debug
  }

  // Opdater Servo
  if (currentMillis - previousMillisServo >= intervalServo) {
    previousMillisServo = currentMillis;

    if (servoMovingForward) {
      servo.write(180);                     // bevæg servo fremad
      Serial.println("Servo moving to 180"); // Print servo position for debug
    } else {
      servo.write(0);                       // bevæg servo tilbage
      Serial.println("Servo moving to 0");   // Print servo position for debug
    }
    servoMovingForward = !servoMovingForward;  // skift retning
  }
}
