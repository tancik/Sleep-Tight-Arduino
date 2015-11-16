int motorPin = 5;
int directionPin = 8;
int onOffPin = 3; // the pin value needs to be changed

int onOffState = 0;
bool direction = true;

void setup() {
  Serial.begin(9600);
  
  pinMode(motorPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(onOffPin, INPUT);

  //setPwmFrequency(motorPin, 256);
  digitalWrite(directionPin, HIGH);
}

void loop() {
  // check to see if there is a change in switch states
  if (onOffState != digitalRead(onOffPin)) {
    onOffState = digitalRead(onOffPin);
    
  }
  if (analogRead(A0) > 1020){
    digitalWrite(directionPin,LOW); 
  } else if (analogRead(A0) < 10) {
    digitalWrite(directionPin,HIGH); 
  }
  analogWrite(motorPin, 128);
  Serial.println(analogRead(A1));
}

void motorControl(int state) {
  if (state == 0) {
    digitalWrite(directionPin, LOW);
  }
    
}
