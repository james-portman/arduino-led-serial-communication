// LED to communicate
// arduino A, main receiver


#define RED_N_SIDE 4
#define GREEN_N_SIDE 3
#define BLUE_N_SIDE 3

#define RED_P_SIDE 10
#define GREEN_P_SIDE 8
#define BLUE_P_SIDE 2

void setup() {
  pinMode(RED_P_SIDE,OUTPUT);
}


void setBackwards(int posPin, int negPin) {
  // Apply reverse voltage, charge up the pin and led capacitance
  pinMode(negPin,OUTPUT);
  pinMode(posPin,OUTPUT);
  digitalWrite(negPin,HIGH);
  digitalWrite(posPin,LOW);
}

void isolate(int negPin) {
  // Isolate the pin 2 end of the diode
  pinMode(negPin,INPUT);
  digitalWrite(negPin,LOW);  // turn off internal pull-up resistor  
}

unsigned int measure(int posPin, int negPin) {
  setBackwards(posPin,negPin);
  isolate(negPin);
  unsigned int j;
  // Count how long it takes the diode to bleed back down to a logic zero
  for (j = 0; j < 30000; j++) {
    if ( digitalRead(negPin)==0) break;
  }
  return j;
}


unsigned int measureAll(int redNeg, int greenNeg, int blueNeg) {
  unsigned int j;
  
  // Count how long it takes the diodes to bleed back down to a logic zero
  for (j = 0; j < 30000; j++) {
    int rNow,gNow,bNow = 1;
    rNow = digitalRead(redNeg);
    gNow = digitalRead(greenNeg);
    bNow = digitalRead(blueNeg);
    if (rNow == gNow == bNow == 0) { break; }
  }
  return j;
}


void switchOn(int posPin, int negPin) {
  digitalWrite(posPin,HIGH);
  digitalWrite(negPin,LOW);
  pinMode(posPin,OUTPUT);
  pinMode(negPin,OUTPUT);
}

void switchOnFor(int posPin, int ms) {
  digitalWrite(posPin,HIGH);
  delay(ms);
  digitalWrite(posPin,LOW);
}

void loop() {

  unsigned int j = measure(BLUE_P_SIDE, BLUE_N_SIDE);
  unsigned int inverse = 30000 - j;
  
  switchOnFor(RED_P_SIDE,inverse/100);
  delay(j/100);

}
