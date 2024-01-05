#include <Wire.h>

#define Slave_Addr_1 5

byte data = 12;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(Slave_Addr_1); //setup this as slave

  Wire.onRequest(requestEvent);

  Serial.begin(9600);
}

void requestEvent(){
  Wire.write(data);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
}
