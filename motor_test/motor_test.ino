int motorPin = 5;
int directionPin = 8;
float VHigh = 5;
float minPosition = 0.01;
float maxPosition = 0.9 * VHigh;
int wiperPin = 0;
int onSwitch = 6;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(onSwitch,INPUT);

  //setPwmFrequency(motorPin, 256);
  //digitalWrite(directionPin, HIGH);
}

void loop() {
  if (digitalRead(onSwitch) && analogRead(wiperPin)>=minPosition){
    delay(1000);
    if(digitalRead(onSwitch)){
      bool returnval=Tighten(motorPin,wiperPin,onSwitch, directionPin);
      if (returnval){
        TurnOff(motorPin,wiperPin);
      }
    }
  if(!digitalRead(onSwitch)&& analogRead(wiperPin)<=maxPosition){
    TurnOff(motorPin,wiperPin);
  }
  }
 
  
  
}

void TurnOff(int motorPin, int wiperPin){
  digitalWrite(directionPin,LOW);
  digitalWrite(motorPin,255);
  while(analogRead(wiperPin)<maxPosition){
    delay(1);
  }
  digitalWrite(motorPin, 0);
}
bool Tighten(int motorPin, int wiperPin, int switchPin, int directionPin){
  digitalWrite(directionPin, HIGH);
  if (analogRead(wiperPin)>=minPosition){
    analogWrite(motorPin,128);
  }
  while (digitalRead(switchPin)&& analogRead(wiperPin)>=minPosition){
    delay(1);
  }
  if(!digitalRead(switchPin)){
    analogWrite(motorPin,0);
    return true;
  }
  else{
    analogWrite(motorPin,0);
    return false;
  }
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
