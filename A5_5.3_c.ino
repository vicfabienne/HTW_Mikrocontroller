#include <TimerOne.h>

const int BLINK = 12; //  Blink LED

volatile unsigned long count = 0;   // counter der vom Interrupt aktualisiert werden soll


void ISR_count(){                      // ISRs akzeptieren keine Parameter! 
  // counter hochzählen
  count = count + 1;
}


void resetCount(){
  // reset countvalue - no return since count is a global Variable
  count = 0;
}


void setup() {

  // Input/Output  
  pinMode(BLINK, OUTPUT);

  // turn Serialterminal on
  Serial.begin(9600);

  // Interuptfunktion, abhängig von Timer 
  Timer1.initialize(1000);           // Interrupt aller 1ms
  Timer1.attachInterrupt(ISR_count);     // interruptdauer je nach LDR Wert
}


void loop() {
  if (count == 2000){
    digitalWrite(BLINK, !digitalRead(BLINK)); // toggle LED every 4s
    resetCount();
  }

}
