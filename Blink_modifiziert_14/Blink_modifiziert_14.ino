/*
  Blink - modifiziert, Aufgabenblatt 1, 1.4 Tasterabfrage 

  Achtung! In Zukunft muss die ganze Logik umgekehrt sein, da das Modul mit dem Multi-purpose shield nach umgekehrter Logik funktioniert
*/

const int buttonPin = 2;  // Der Pin, an dem der Taster angeschlossen ist

// viel zu kompliziert, absolut unnötig
// int buttonState = 0;      // Speichert den aktuellen Zustand des Tasters
// int lastButtonState = 0;  // Speichert den vorherigen Zustand des Tasters

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // LED-Pin als Ausgang
  pinMode(buttonPin, INPUT);    // Taster-Pin als Eingang
}


// Funktion um die LED blinken zu lassen
void blinkLED(int delayTime) {
  
}


// loop der ständig den Tasterzustand checkt und die Blinkfrequenz entsprechend reguliert
void loop() {
  // taster abfragen  
  if(digitalRead(buttonPin)) delayTme = 500; // Taster gedrückt --> 1Hz
    else delayTime = 250;                     // Taster nicht gedrückt --> 2 Hz
  
  digitalWrite(LED_BUILTIN, HIGH); // LED einschalten
  delay(delayTime);               // Halte die LED eingeschaltet
  digitalWrite(LED_BUILTIN, LOW);  // LED ausschalten
  delay(delayTime);               // Halte die LED ausgeschaltet
}
