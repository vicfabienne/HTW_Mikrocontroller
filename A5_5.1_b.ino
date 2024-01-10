#include <TimerOne.h>

// LED Pin 10 --> Periodendauer von 1s blinken, interrupt funktion
 // LED Pin 12 --> Periodendauer abhängig von LDR an Pin A3, mit delay statt mit millis
 // LDR: Wert von AD Wandler *2 --> Millisekunden (Bsp.: 748 gemessen, LED: 748ms an, 748ms aus)

const int CONSTANTBLINK = 10; // konstant blinkende LED (pink)
const int DYNAMICBLINK = 12; // LDR abhängige LED  
const int LDR = A3; // Input für LDR wert

void ISR_constantLEDblink(){                                                         // Interruptserviceroutine wird vom interrupt controller aufgerufen        
  digitalWrite(CONSTANTBLINK, !digitalRead(CONSTANTBLINK));                 // LED toggel
}

void setup() {

  // Input/Output
  pinMode(LDR, INPUT);  
  pinMode(CONSTANTBLINK, OUTPUT);
  pinMode(DYNAMICBLINK, OUTPUT);

  // turn Serialterminal on
  Serial.begin(9600);

  // Interrupt setting
  Timer1.initialize (1000000); // Timer 1 für 1s Verzögerung initialisieren
  Timer1.attachInterrupt (ISR_constantLEDblink); // Interrupt-Funktion für das Blinken festlegen
}


void loop() {

  // LDR abhängige LED 
  int ldrWert = analogRead(LDR);                                            // speichert analogwert von LDR
  Serial.println(ldrWert, DEC);                                             // ausgabe LDR Wert (sanity check purpose)                          
  digitalWrite(DYNAMICBLINK, !digitalRead(DYNAMICBLINK));
  delay(ldrWert);
  digitalWrite(DYNAMICBLINK, !digitalRead(DYNAMICBLINK));
  delay(ldrWert);
}
