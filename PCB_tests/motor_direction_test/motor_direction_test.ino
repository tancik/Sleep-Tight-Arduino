// Tests the motor's ability to rotate in a direction
//Switch direction after 2 seconds

const int motorPin = 5;
const int directionPin = 9;
const int waitTime = 2000; //default is 2 seconds

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
}

void loop() {
  //Initial direction dependent on second param.
  digitalWrite(directionPin, HIGH);
  analogWrite(motorPin, 128);
  delay(waitTime);

  //Change motor direction
  digitalWrite(directionPin, LOW);
  analogWrite(motorPin, 128);
  delay(waitTime);
}
