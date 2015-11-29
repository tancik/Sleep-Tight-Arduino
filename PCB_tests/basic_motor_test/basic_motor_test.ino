//Tests the motor basic functionality. Rotates motor single
//direction at 50%

int motorPin = 5;

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  analogWrite(motorPin, 128);
}
