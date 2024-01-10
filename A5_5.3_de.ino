#include <TimerOne.h>


const int BLINK = 12; //  Blink LED
const int TASTER = 2; // Tasterm zum counter zurücksetzen 


volatile unsigned long count = 0;   // counter der vom Interrupt aktualisiert werden soll


void ISR_count(){                      // ISRs akzeptieren keine Parameter! 
  // counter hochzählen
  count = count + 1;
}


void resetCount(){
  // reset countvalue - no return since count is a global Variable
  count = 0;
}

void ISR_taster(){
  resetCount();
  Serial.println(count,DEC);
}

void setup() {

  // Input/Output  
  pinMode(BLINK, OUTPUT);

  // turn Serialterminal on
  Serial.begin(9600);

  // Interuptfunktion, abhängig von Timer 
  Timer1.initialize(1000);           // Interrupt aller 1ms
  Timer1.attachInterrupt(ISR_count);     // interruptdauer je nach LDR Wert
  attachInterrupt(0, ISR_taster, CHANGE);     // Interruptfunktion für das Tastendrücken, 0 --> externer Interrupt(muss normalerweise über Funktion angesteuert werden)
}

// RISING: sofort bei button klick --> 0 
// FALLING: sofort bei button klick --> 0
// CHANGE: sofort bei button klick --> 0
// --> zumindest in WokWi konnte ich spontan keinen Unterschied feststellen


void loop() {
  if (count == 2000){
    Serial.println(count,DEC); // bug oder wokwi weirdness? ohne die serial prints funktioniert es nicht so gut? 
    digitalWrite(BLINK, !digitalRead(BLINK)); // toggle LED
  }

}

// Funktion der Progresmms: 1. leuchten nach 4s, dann: Taste drücken, 4s warten, toggle. Nächster toggle erst wenn wieder Taste gedrückt wird
