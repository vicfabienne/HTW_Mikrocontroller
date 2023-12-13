#include <Wire.h>
const int MPU = 0x68;     // I2C-Adresse des MPU-6050
const int PWR = 0x6B;     // Registeradresse für das PWR_MGMT_1-Register
const int ACC = 0x1C;     // Registeradresse für das ACCEL_CONFIG-Register
const int S1 = 2;         // Pin für Taste S1
const int S2 = A2;        // Pin für Taste S2
const int StatusLED = 10; // Pin für Status-LED
const int AlarmLED = 12;  // Pin für Alarm-LED
const int Buzzer = 3;     // Pin für den Signalton
const int del = 100;      // delay in ms
const int Threshold = 150;// Schranke für die Alarm-Auslösung
int X, Y, Z;              // Beschleunigungsvariablen
int Xcal, Ycal, Zcal;     // Kalibrierungswerte
bool AlarmAktiv = false;  // Alarmstatus

void setup() {
  Wire.begin();                   // Start dee I2C-Kommunikation
  Serial.begin(9600);             // Initialisiererung der seriellen Kommunikation
  pinMode(S1, INPUT);             
  pinMode(S2, INPUT);             
  pinMode(StatusLED, OUTPUT);           
  pinMode(AlarmLED, OUTPUT);      
  pinMode(Buzzer, OUTPUT);
 
  Wire.beginTransmission(MPU);    // Initialisiere den MPU-6050
  Wire.write(PWR);                // Registeradresse 0x6B
  Wire.write(0x00);               // Weckruf des Sensors
  Wire.endTransmission();

  Wire.beginTransmission(MPU);    // Initialisiere den MPU-6050
  Wire.write(ACC);                // Registeradresse 0x1C
  Wire.write(0x00);               // Empfindlichkeit auf 2g gesetzt
  Wire.endTransmission();

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);                           // Starte mit dem Register ACCEL_XOUT_H
  Wire.endTransmission(false);                // Beende Übertragung
  Wire.requestFrom(MPU, 6, true);             // Lese 6 Register (für jede Achse 2)
  Xcal = (Wire.read() << 8 | Wire.read());    // x-Wert
  Ycal = (Wire.read() << 8 | Wire.read());    // y-Wert
  Zcal = (Wire.read() << 8 | Wire.read());    // z-Wert 
 
}
void getAccel(int* X, int* Y, int* Z) {        // Call by Referenz durch Zeiger
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);                            // Starte mit dem Register ACCEL_XOUT_H
  Wire.endTransmission(false);                 // stop = false, zur Erhaltung einer wiederholten Startbedingung für die nächsten Leseoperationen
  Wire.requestFrom(MPU, 6, true);              // fordert 6 Bytes Daten vom MPU-6050 an und wartet auf die Daten.
  *X = (Wire.read() << 8 | Wire.read());       // x-Wert
  *Y = (Wire.read() << 8 | Wire.read());       // y-Wert
  *Z = (Wire.read() << 8 | Wire.read());       // z-Wert 
}

void loop() {
  if (!digitalRead(S1)) AlarmAktiv = true;  // Mit Drücken Taster 2 Alarm aktiviert
  if (!digitalRead(S2)) AlarmAktiv = false; // Mit Drücken Taster 2 Alarm deaktiviert
  
  if (AlarmAktiv) {
    digitalWrite(StatusLED, LOW);        // Status-LED aktivieren
    noTone(Buzzer);
    getAccel(&X, &Y, &Z);
    X = abs(Xcal - X);
    Y = abs(Ycal - Y);
    Z = abs(Zcal - Z);
    if (X >= Threshold || Y >= Threshold || Z >= Threshold) {
      digitalWrite(AlarmLED, LOW);      // Alarm-LED einschalten
      digitalWrite(Buzzer, LOW);        // Signalton einschalten   
    }
    Serial.print("X=");
    Serial.print(X);
    Serial.print(" Y=");
    Serial.print(Y);
    Serial.print(" Z=");
    Serial.println(Z);
    delay(del);
  }
  else{
    digitalWrite(StatusLED, HIGH);     // Status-LED ausschalten
    digitalWrite(AlarmLED, HIGH);      // Alarm-LED ausschalten
    digitalWrite(Buzzer, HIGH);        // Signalton ausschalten
  }
}
