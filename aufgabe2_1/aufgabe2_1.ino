const int ledPins[] = {13, 12, 11, 10};                 // Ein Array für LEDs erstellt
const int numLeds = sizeof(ledPins);                    // Größe des Arrays
const int dly = 1000;                                   // delay (1 s)


void setup() {
  for (int i = 0; i < numLeds; i++){
    pinMode(ledPins[i], OUTPUT);                        // Pins 10-13 werden als Outputs deklariert 
  }
}


void setLED(int value){
    for (int n=0; n < numLeds; n++) {                    // Zählt Bitstellen und Pinnr. für LED
      if (bitRead(value, n)) digitalWrite(ledPins[n], LOW);   // Wenn Bit an Stelle n = 1, schalte LED an
      else digitalWrite(ledPins[n], HIGH);                    // Wenn Bit an Stelle n = 0, schalte LED aus
  }
}


void loop() {
  for(int count = 0; count < pow(2, numLeds); count++){  // Zählt bis 15 hoch
    setLED(count);                                       // Übergibt die Zahl an die Hilfsfunktion setLED
    delay(dly);                                          // Sekundentakt
  }
}
