// LED Pin 10 --> Periodendauer von 1s blinken (500ms an, 500ms aus)
 // LED Pin 12 --> Periodendauer abhängig von LDR an Pin A3
 // LDR: Wert von AD Wandler *2 --> Millisekunden (Bsp.: 748 gemessen, LED: 748ms an, 748ms aus)

const int CONSTANTBLINK = 10; // konstant blinkende LED (pink)
const int DYNAMICBLINK = 12; // LDR abhängige LED  
const int LDR = A3; // Input für LDR wert

void setup() {

  // Input/Output
  pinMode(LDR, INPUT);  
  pinMode(CONSTANTBLINK, OUTPUT);
  pinMode(DYNAMICBLINK, OUTPUT);

  // turn Serialterminal on
  Serial.begin(9600);
  
}

/** 
 * LED togglen durch millis() 
 * @param waittime int, Wert für die gewünschte Periodendauer in ms 
 * @param led int, PIN für die zu toggelnde LED
 * @param toggletime long, Variable zum speichern der Togglezeit der LED
 */
void LEDtoggle(int waittime, int led, unsigned long *toggletime) {
  Serial.println(waittime,DEC);
  Serial.println(led, DEC);
  Serial.println(*toggletime,DEC);

  if(millis() >= *toggletime) { 
    digitalWrite(led, !digitalRead(led));
    *toggletime = millis() + waittime;
  }

}
/** 
 * Periodendauer in ms für blink LED berechnen, abhängig von Ausgabewertes eines Lichtwiderstandes
 */
int getPDfromLDR(int ldrpin) {
  int ldrWert = analogRead(ldrpin);                              // speichert analogwert von LDR
  Serial.println(ldrWert, DEC);                               // ausgabe LDR Wert (sanity check purpose)                          
  // umrechnung LDR Wert 
  int dynamicLEDPeriodendauer = ldrWert * 2;

  return dynamicLEDPeriodendauer;
}

void loop() {

  // Zeitwert speicherung
  static unsigned long nexttoggleLEDconstant = 0;               // nächster Zeitpunkt konstant blinkende LED toggle
  static unsigned long nexttoggleLEDdynamic = 0;                // nächster Zeitpunkt LDR abhängige LED toggle

  // konstant blinkende LED  
  LEDtoggle(1000,CONSTANTBLINK,&nexttoggleLEDconstant);

  // LDR abhängige LED 
  int dynamicLEDPeriodendauer = getPDfromLDR(LDR);             // Abfrage LDR Wert
  LEDtoggle(dynamicLEDPeriodendauer, DYNAMICBLINK, &nexttoggleLEDdynamic); // toggeln der LED
}
