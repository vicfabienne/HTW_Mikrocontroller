#include <Wire.h>
const int MPU = 0x68;                   // I2C-Adresse des MPU-6050
const int PWR = 0x6B;                   // Registeradresse für das PWR_MGMT_1-Register (Powermanagement) --> 1 --> sleep
const int ACC = 0x1C;                   // Registeradresse für das ACCEL_CONFIG-Register --> 0, Empfindlichkeit des Sensors
const int del = 100;                    // delay in ms
int x, y, z;                            // Variablen für die Beschleunigung

void setup() {
  Serial.begin(9600);                   // Initialisiert die serielle Kommunikation
  // Initialisiert den MPU-6050
  Wire.begin();                         // Startet die I2C Kommunikation
  Wire.beginTransmission(MPU);
  Wire.write(PWR);                      // Adresse des PWR_MGMT_1 Registers
  Wire.write(0x00);                     // Setzt das PWR_MGMT_1 Register auf 0 (wecke den MPU-6050 auf)
  Wire.endTransmission();
  
  Wire.beginTransmission(MPU);
  Wire.write(ACC);                      // Adresse des ACCEL_CONFIG Registers
  Wire.write(0x10);                     // Setzt das ACCEL_CONFIG Register auf 0x10 (8g Empfindlichkeit)
  Wire.endTransmission();
}

/** 
  * zum lesen der Beschleunigungsdaten von der X-,Y- und Z achse des MPU
  * Parameter über "call by reference" übergeben, da wir nicht mit festen werten arbeiten, sondern mit veränderlichen, die auch außerhalb der Funktion verfügbar sein sollen
  * In dem Fall werden sie hier gespeichert, um dann in Loop über die Serielle Schnittstelle ausgegeben werden zu können

*/
void getAccel(int *x, int *y, int *z) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);                      // Starte die Leseoperation ab der X-Achse
  Wire.endTransmission(false);          //setzt stop Parameter falsch zur Erhaltung einer wiederholten Startbedingung für die nächsten Leseoperationen 
  Wire.requestFrom(MPU, 6, true);      //fordert 6 Bytes Daten vom MPU-6050 an und wartet auf die Daten.


  // Verfahren hier: 
  //  Byte from I2C bus lesen, byte um 8 bit nach links verschieben um "platz für das nächste byte" zu schaffen, bitwise OR kombinieren, durch 4.095 teilen
  *x = (Wire.read() << 8 | Wire.read())/4.095;  // Teilt durch 4.095, um die Rohdaten in g umzurechnen
  *y = (Wire.read() << 8 | Wire.read())/4.095;
  *z = (Wire.read() << 8 | Wire.read())/4.095;
  delay(del);
}

void loop() {
  getAccel(&x, &y, &z);
    Serial.print("X=");
    Serial.print(x);
    Serial.print(" Y=");
    Serial.print(y);
    Serial.print(" Z=");
    Serial.println(z);
}
