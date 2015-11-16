#include <elapsedMillis.h>;
elapsedMillis elapsedTime;
int motorPin = 5;
int directionPin = 8;
int onOffPin = 3; // the pin value needs to be changed
int maxPosition=700;
int onOffState = 0;
//bool direction = true;
int minPosition = 10;
bool motorRunning = false;
bool waiting = false;
int waitTime = 1000;


void setup() {
  Serial.begin(9600);
  
  pinMode(motorPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(onOffPin, INPUT);
  digitalWrite(directionPin, HIGH);
  analogWrite(motorPin,0);
}

void loop() {
  // check to see if there is a change in switch states
  if(motorRunning &&(analogRead(A0)>maxPosition || analogRead(A0)<minPosition)){
    analogWrite(motorPin,0);
    motorRunning =false;
  }
  if (onOffState != digitalRead(onOffPin)) {
    onOffState = digitalRead(onOffPin);
    if (onOffState && analogRead(A0)>maxPosition){
      waiting=true;
      elapsedTime=0;     
    }
    else if(!onOffState && analogRead(A0)<minPosition){
      waiting = false;
      digitalWrite(directionPin,LOW);
      analogWrite(motorPin,255); 
      motorRunning=true;    
    }
  }
  if (waiting && elapsedTime>waitTime){
    waiting=false;
    digitalWrite(directionPin, HIGH);
    analogWrite(motorPin,122);
    motorRunning = true;
  }

}

