// Tests the electrical current reading from the motor controller

const int motorPin = 5;
const int motorFeedbackPin = A0;

int motorFeedback = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(motorFeedbackPin, INPUT);
}

void loop() {
  analogWrite(motorPin, 128);
  motorFeedback = analogRead(motorFeedbackPin);
  Serial.println(motorFeedback);
}
