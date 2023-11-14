const int red=5;
const int green=6;
const int blue=9;

int num;
String cmd;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  analogWrite(red, 255);          // warum analogWrite und nicht digital write? 
  analogWrite(green, 255);
  analogWrite(blue, 255);
  Serial.begin(9600); // ??
  Serial.print("Farbe");
  Serial.print("\t");
  Serial.println("Farbanteil");
}


void loop() {
  
  while (Serial.available()==0) {} // ??


  cmd = Serial.readStringUntil(' ');
  num = Serial.parseInt();
  num = 255-constrain(num, 0, 255);
    
  if(cmd == "off")  {                                //Wenn off eingegeben wird, geht die LED aus
    analogWrite(red,255);
    analogWrite(green,255);
    analogWrite(blue,255);
  }
  
  if(cmd == "red"){                                 //Wert für Rotanteil
    analogWrite(red,num);
  }

  if(cmd == "green"){                               //Wert für Grünanteil
    analogWrite(green,num);
  }

  if(cmd == "blue"){                                 //Wert für Blauanteil
    analogWrite(blue,num);
  }    
}
