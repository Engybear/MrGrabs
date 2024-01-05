#include <Wire.h>

#define Slave_Addr_1 5
#define Slave_Addr_2 6

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); //setup this as master

  Wire.beginTransmission(Slave_Addr_1); //register slave address
  Wire.endTransmission();

  Wire.beginTransmission(Slave_Addr_2); //register slave address
  Wire.endTransmission();

  Serial.begin(9600);
  Serial.println("Master Startup");

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  Serial.println("Sending request for data 1");

  Wire.requestFrom(Slave_Addr_1,sizeof(byte));
  byte response;
  while(Wire.available()){
    response = Wire.read();
  }
  Serial.println(response);

  Serial.println("Sending request for data 2");

  Wire.requestFrom(Slave_Addr_2,sizeof(byte));
  while(Wire.available()){
    response = Wire.read();
  }
  Serial.println(response);

}
