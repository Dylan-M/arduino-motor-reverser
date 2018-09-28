/*
 * Auto-reverse circuit for DC motors with dual control switches
 * With code based on Adafruit Arduino - Lesson 15. Bi-directional Motor
 */

#define DEBUG 1

int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int switchPinA = 7;
int switchPinB = 6;
boolean reverse;
boolean enableSwitchPinA;
boolean enableSwitchPinB;

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPinA, INPUT_PULLUP);
  pinMode(switchPinB, INPUT_PULLUP);
  reverse = false;
  enableSwitchPinA = true;
  enableSwitchPinB = false;
}

void loop()
{
  if (enableSwitchPinA) {
    checkSwitchPinA();
  }
  if (enableSwitchPinB) {
    checkSwitchPinB();
  }
  #ifdef DEBUG
    Serial.print(F("Reverse: "));
    Serial.println(reverse);
    Serial.print(F("Pin A: "));
    Serial.println(enableSwitchPinA);
    Serial.print(F("Pin B: "));
    Serial.println(enableSwitchPinB);
    Serial.flush();
  #endif
  setMotor(reverse);
}

void setMotor(boolean reverse)
{
  analogWrite(enablePin, 255);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
}

void stopMotor()
{
  analogWrite(enablePin, 0);
  digitalWrite(in1Pin, false);
  digitalWrite(in2Pin, false);
}

void checkSwitchPinA() {
  if (digitalRead(switchPinA) == HIGH && digitalRead(switchPinB) == LOW) {
    stopMotor();
    #ifdef DEBUG
      Serial.println(F("Executing Switch Pin A"));
      Serial.flush();
    #endif
    enableSwitchPinA = false;
    enableSwitchPinB = true;
    delay(random(3,7) * 1000);
    reverse = ! reverse;
  }
}

void checkSwitchPinB() {
  if (digitalRead(switchPinB) == HIGH && digitalRead(switchPinA) == LOW) {
    stopMotor();
    #ifdef DEBUG
      Serial.println(F("Executing Switch Pin B"));
      Serial.flush();
    #endif
    enableSwitchPinA = true;
    enableSwitchPinB = false;
    delay(random(3,7) * 1000);
    reverse = ! reverse;
  }
}
