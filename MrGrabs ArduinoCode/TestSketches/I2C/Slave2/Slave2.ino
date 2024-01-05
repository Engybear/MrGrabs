#include <Wire.h>

#define Slave_Addr_2 6

byte data = 20;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(Slave_Addr_2); //setup this as slave

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
