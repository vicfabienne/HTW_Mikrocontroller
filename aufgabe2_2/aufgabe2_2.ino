const int ledPins[] = {13, 12, 11, 10};                     // Ein Array für LEDs erstellt
const int numLeds = sizeof(ledPins);                        // Größe des Arrays
const int button = 2;
const int dly = 50;                                         // delay 
int laststate = HIGH;
int actstate = HIGH;
int count = 0;


void setup() {                                              // Pins 10-13 werden als Outputs deklariert
  for (int i = 0; i < numLeds; i++){
    pinMode(ledPins[i], OUTPUT); 
    digitalWrite(ledPins[i], HIGH);                         // alle LED's werden auf aus gesetzt                         
  }
  pinMode(button, INPUT);
}

void setLED(int value) {
  for (int n = 0; n < numLeds; n++) {                      // Zählt Bitstellen und Pinnr. für LED
    bool isBitSet = bitRead(value, n);                     // Prüft, ob das Bit an der Position n gesetzt ist
    digitalWrite(ledPins[n], isBitSet ? LOW : HIGH);       // Schaltet die LED basierend auf dem Bit-Zustand
  }
}

void loop() {
 actstate = digitalRead(button);                              // speichert aktuelle Schalterzustand                            
  if (actstate == HIGH && laststate == LOW) laststate = HIGH;
    if (actstate == LOW && laststate == HIGH) {
      count++;
      setLED(count);
      laststate = LOW;
  }
  delay(dly);
}
