/*
  Blink - modifiziert, Aufgabenblatt 1, 1.4 Tasterabfrage 
*/

const int buttonPin = 2;  // Der Pin, an dem der Taster angeschlossen ist
int buttonState = 0;      // Speichert den aktuellen Zustand des Tasters
int lastButtonState = 0;  // Speichert den vorherigen Zustand des Tasters

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // LED-Pin als Ausgang
  pinMode(buttonPin, INPUT);    // Taster-Pin als Eingang
}


// Funktion um die LED blinken zu lassen
void blinkLED(int delayTime) {
  digitalWrite(LED_BUILTIN, HIGH); // LED einschalten
  delay(delayTime);               // Halte die LED eingeschaltet
  digitalWrite(LED_BUILTIN, LOW);  // LED ausschalten
  delay(delayTime);               // Halte die LED ausgeschaltet
}


// loop der ständig den Tasterzustand checkt und die Blinkfrequenz entsprechend reguliert
void loop() {
  buttonState = digitalRead(buttonPin); // Den aktuellen Tasterzustand auslesen

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // Taster wurde gedrückt, LED mit 2 Hz blinken
      blinkLED(500);  // 2 Hz (Halbe Periode = 500 ms)
    } else {
      // Taster wurde losgelassen, LED mit 1 Hz blinken
      blinkLED(1000); // 1 Hz (Halbe Periode = 1000 ms)
    }
  }

  lastButtonState = buttonState; // Den vorherigen Tasterzustand aktualisieren
}
