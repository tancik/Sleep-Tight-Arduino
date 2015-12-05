//Tests the motor limit switch Arduino interrupt functionality to
//stop the motor.

const int motorPin = 5;
const int motorInterruptPin = 3;

volatile bool state = 1;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(motorInterruptPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motorInterruptPin), reverseMotor, RISING);
}

void loop() {
  if (state == 1) {
    analogWrite(motorPin, 128);
  }
  else {
    analogWrite(motorPin, 0);
  }
  Serial.println(state);
}

void reverseMotor() {
  state = 0;
}

