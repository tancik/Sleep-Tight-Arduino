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
