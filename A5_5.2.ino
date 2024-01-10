#include <TimerOne.h>

// LED Pin 12 --> default Blinken mit 1Hz
// LDR: Wert von AD Wandler --> input für ISR, je nach Wert, wird die Hauptfunktion für eine equivalente Länge in ms unterrbrochen

const int BLINK = 12; // LDR abhängige LED  
const int LDR = A3; // Input für LDR wert

void delay_ms(unsigned int ms) {  // Verzögerungsfunktion 
    while (ms--)                  // Wiederholen entsprechend d. Parameters
    delayMicroseconds(1000);      // Jeweils 1ms warten

}

void ISR_wait(){                      // ISRs akzeptieren keine Parameter! 
  // LDR wert lesen
  int ldrwert = analogRead(LDR);
  delay_ms(ldrwert);
}

void setup() {

  // Input/Output
  pinMode(LDR, INPUT);  
  pinMode(BLINK, OUTPUT);

  // turn Serialterminal on
  Serial.begin(9600);

  // Interuptfunktion, abhängig von Timer 
  Timer1.initialize(1000000);           // Interrupt aller 1s
  Timer1.attachInterrupt(ISR_wait);     // interruptdauer je nach LDR Wert
}


void loop() {

  // standard blinken 1Hz - Aber abhängig von LDR value, da je nach LDR wert, der delay um entsprechende Dauer verlängert wird
  digitalWrite(BLINK, !digitalRead(BLINK));
  Serial.println(ldrwert,DEC);            // print statement nicht in ISR da das die Funktion verzögert
  delay(500);
  digitalWrite(BLINK, !digitalRead(BLINK));
  delay(500);
}
