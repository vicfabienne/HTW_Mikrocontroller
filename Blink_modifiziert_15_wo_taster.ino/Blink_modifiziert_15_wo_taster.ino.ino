/*
  Blink - modifiziert, Aufgabenblatt 1, 1.5 Lauflicht ohne Taster, kontinuierliches Licht

  // time tracking ist unnötig
*/

const int ledPins[] = {10, 11, 12, 13}; // Pins für die LEDs
int currentLED = 0; // Index der aktuellen LED
unsigned long previousMillis = 0; // Speichert die Zeit des letzten LED-Wechsels
const long interval = 250; // Intervall zwischen den LED-Wechseln (0,25 Sekunden)

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT); // LED-Pins als Ausgänge
  }
}

void loop() {
  unsigned long currentMillis = millis(); // Aktuelle Zeit auslesen

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Zeit für den nächsten LED-Wechsel aktualisieren

    int currentLED = 0; // Index der aktuellen LED
    digitalWrite(ledPins[currentLED], LOW); // Vorherige LED ausschalten
    currentLED = (currentLED + 1) % 4; // Nächste LED auswählen
    digitalWrite(ledPins[currentLED], HIGH); // Aktuelle LED einschalten

    
  }
}
