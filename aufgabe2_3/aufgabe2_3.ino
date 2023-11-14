const int LDR = A3;
const int ledPins[] = {13, 12, 11, 10};                      // Ein Array für LEDs erstellt
const int numLeds = sizeof(ledPins);                         // Größe des Arrays
const int Amax = 1023;                                       // Maximale Wertebereich des AD-Wandlers ??
const int Umax = 5;                                          // Maximale Wertebereich der Spannung    ??
const int ledMax = 15;                                       // Maximale Wertebereich der LEDs (4 Bit)??


void setup() {
  for (int i = 0; i < numLeds; i++){
    pinMode(ledPins[i], OUTPUT);                             // Pins 10-13 werden als Outputs deklariert
  }
  pinMode(LDR, INPUT);
  Serial.begin(9600);                                       // ??
}

void setLED(int value){
    for (int n=0; n< numLeds; n++) {                         // Zählt Bitstellen und Pinnr. für LED
    if(bitRead(value, n)) digitalWrite(n+10, LOW);    // Wenn Bit an Stelle n 1 ist, schalte LED an
    else digitalWrite(n+10, HIGH);                    // Wenn Bit an Stelle n 0 ist, schalte LED aus
  }
}

void loop() {
  int wert = analogRead(LDR);                                // speichert analogwert von LDR 
  double volt = map(wert, 0, Amax, 0, Umax);                 // umrechnet den wert von (0-Amax) auf (0-Umax) 
  double value = map(wert, 0, Amax, 0, ledMax);              // umrechnet den wert von (0-Amax) auf (0-ledmax) 
  setLED(value);                                             // steuert LED-Helligkeit

  Serial.print(wert, HEX);                                   
  Serial.print("\t");
  Serial.print(volt, 2);
  Serial.println(" V");
  delay(100);                                                // Wiederholt den Vorgang 10 mal pro Sekunde
}
