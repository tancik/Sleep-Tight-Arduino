//Tests the motor basic functionality of the motor to hit either
//limit switch and reverse direction.

//pin constants
const int motorPin = 5;
const int motorInterruptPin = 3;
const int switchPollingPin = 4;
const int directionPin = 9;

//potentially variable parameters
const int motorSpeed = 50;

//flags and global states
volatile bool motorLimitFlag = false;
bool lastLimitSwitchState = false;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(motorInterruptPin, OUTPUT);
  pinMode(switchPollingPin, INPUT);
  pinMode(directionPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motorInterruptPin), reverseMotor, RISING);
}

void loop() {
  getPollingSwitchState();
  if (motorLimitFlag) {
    //if the the motor hit a switch, first stop the motor,
    //get the current direction, and switch. Once done,
    //power the motor back on
//    analogWrite(motorPin, 0);
    bool currentDirection = digitalRead(directionPin);
    digitalWrite(directionPin, !currentDirection);
    analogWrite(motorPin, motorSpeed);
    motorLimitFlag = false;
  }
  else {
    analogWrite(motorPin, motorSpeed);
  }
}

void getPollingSwitchState() {
  //Check the limit switch by polling. If the limit switch
  //is HIGH, change the global "motorLimitFlag" variable
  //to reflect the need to stop and/or reverse the motor.
  bool switchState = digitalRead(switchPollingPin);
  if (switchState && !lastLimitSwitchState) {
    motorLimitFlag = true;
  }
  lastLimitSwitchState = switchState;
}

void reverseMotor() {
  motorLimitFlag = true;
}

