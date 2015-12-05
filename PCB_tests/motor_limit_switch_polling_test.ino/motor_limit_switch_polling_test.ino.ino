//Tests the loop polling of the limit switch to stop the motor.

const int motorPin = 5;
const int motorStopPin = 3;

bool state = 1;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(motorStopPin, INPUT);
}

void loop() {
  if (digitalRead(motorStopPin) == HIGH) {
    state = 0;
  }
  if (state) {
    analogWrite(motorPin, 128);
  }
  else {
    analogWrite(motorPin, 0);
  }
}




//void loop() {
//  bool motorStopState = digitalRead(motorStopPin);
//  if (motorStopState == 0 && state == 1) {
//    analogWrite(motorPin, 128);
//  }
//  else {
//    analogWrite(motorPin, 0);
//    state = 0;
//  }
//  Serial.println(state);
//}

