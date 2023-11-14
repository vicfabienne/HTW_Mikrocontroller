const int ledPins[] = {13, 12, 11, 10};                     //Ein Array für LEDs erstellt//Array f
const int numLeds = sizeof(ledPins);                        //Größe des Arrays
const int button = 2;
const int del = 50;                                         //delay 
int laststate = HIGH;
int actstate = HIGH;
int count = 0;


void setup() {                                              //Pins 10-13 werden als Outputs deklariert
  for (int i = 0; i < numLeds-1; i++){
    pinMode(ledPins[i], OUTPUT); 
    digitalWrite(ledPins[i], HIGH);                           
  }
  pinMode(button, INPUT);
}


/*void setLED(int value) {                                    //nimmt eine ganze Zahl als Parameter
  for (int i = 0; i < numLeds; i++){                        //Zählt Bitstellen und Pinnr. für LED
  if(bitRead(value, i)) digitalWrite(10+i, LOW) ;            //Wenn Bit an Stelle n 1 ist, schalte LED an
    else digitalWrite(10+i, HIGH);                          //Wenn Bit an Stelle n 0 ist, schalte LED aus
    }
}*/


void setLED(int value) {
  for (int n = 0; n < numLeds-1; n++) {                       // Zählt Bitstellen und Pinnr. für LED
    bool isBitSet = bitRead(value, n);                 // Prüft, ob das Bit an der Position n gesetzt ist
    digitalWrite(ledPins[n], isBitSet ? LOW : HIGH);       // Schaltet die LED basierend auf dem Bit-Zustand
  }
}


void loop() {
 actstate=digitalRead(button);                              //speichert aktuelle Schalterzustand                            
  if (actstate==HIGH && laststate==LOW) laststate=HIGH;
  if (actstate==LOW && laststate==HIGH) {
    count++;
    setLED(count);
    laststate=LOW;
  }
  delay(del);
}
