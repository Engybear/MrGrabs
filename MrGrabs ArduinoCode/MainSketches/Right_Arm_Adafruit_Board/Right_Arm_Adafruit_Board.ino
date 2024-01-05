#pragma GCC optimize ("O0")

#include <AX12A.h>

#define DirectionPin  (1u) //TX PIN
#define BaudRate    (1000000u)
#define ID_1  (1u)
#define ID_2  (2u)
#define ID_3  (3u)
#define ID_4  (4u)
#define ID_5  (5u)
#define ID_6  (6u)
#define ID_7  (7u)

#include <Wire.h>
#define Right_Ada_Addr 6
int receivedData = 0;

void setAngleLimits(){ //adjust as needed, 0 - 300 degrees
  ax12a.setAngleLimit(ID_1, 0, 1023);
  ax12a.setAngleLimit(ID_2, 0, 1023);
  ax12a.setAngleLimit(ID_3, 0, 1023);
  ax12a.setAngleLimit(ID_4, 0, 1023);
  ax12a.setAngleLimit(ID_5, 0, 1023);
  ax12a.setAngleLimit(ID_6, 0, 1023);
  ax12a.setAngleLimit(ID_7, 0, 1023);
}
void setVoltageLimits(){ //9~11V
  ax12a.setVoltageLimit(ID_1, 9, 11);
  ax12a.setVoltageLimit(ID_2, 9, 11);
  ax12a.setVoltageLimit(ID_3, 9, 11);
  ax12a.setVoltageLimit(ID_4, 9, 11);
  ax12a.setVoltageLimit(ID_5, 9, 11);
  ax12a.setVoltageLimit(ID_6, 9, 11);
  ax12a.setVoltageLimit(ID_7, 9, 11);
}
void setTorqueOn(){
  ax12a.torqueStatus(ID_1, true);
  ax12a.torqueStatus(ID_2, true);
  ax12a.torqueStatus(ID_3, true);
  ax12a.torqueStatus(ID_4, true);
  ax12a.torqueStatus(ID_5, true);
  ax12a.torqueStatus(ID_6, true);
  ax12a.torqueStatus(ID_7, true);

  ax12a.setEndless(ID_1, false);
  ax12a.setEndless(ID_2, false);
  ax12a.setEndless(ID_3, false);
  ax12a.setEndless(ID_4, false);
  ax12a.setEndless(ID_5, false);
  ax12a.setEndless(ID_6, false);
  ax12a.setEndless(ID_7, false);
}
const int complianceMargin = 15;
void setComplianceMargins(){ //10 degrees within target position
  ax12a.setCMargin(ID_1, complianceMargin, complianceMargin);
  ax12a.setCMargin(ID_2, complianceMargin, complianceMargin);
  ax12a.setCMargin(ID_3, complianceMargin, complianceMargin);
  ax12a.setCMargin(ID_4, complianceMargin, complianceMargin);
  ax12a.setCMargin(ID_5, complianceMargin, complianceMargin);
  ax12a.setCMargin(ID_6, complianceMargin, complianceMargin);
  ax12a.setCMargin(ID_7, complianceMargin, complianceMargin);
}

const int servoSpeed = 100;
void moveToState1(){ //arms stowed away
  //ax12a.moveSpeed(ID_1, 512, servoSpeed);
  ax12a.moveSpeed(ID_2, 872, servoSpeed);
  ax12a.moveSpeed(ID_3, 155, servoSpeed);
  ax12a.moveSpeed(ID_4, 218, servoSpeed);
  ax12a.moveSpeed(ID_5, 800, servoSpeed);
  ax12a.moveSpeed(ID_6, 490, servoSpeed);
  ax12a.moveSpeed(ID_7, 512, servoSpeed);
}
void moveToState2(){ //halfway lift arm up from stowed position
  //ax12a.moveSpeed(ID_1, 512, servoSpeed);
  ax12a.moveSpeed(ID_2, 679, servoSpeed);
  ax12a.moveSpeed(ID_3, 336, servoSpeed);
  ax12a.moveSpeed(ID_4, 218, servoSpeed);
  ax12a.moveSpeed(ID_5, 800, servoSpeed);
  ax12a.moveSpeed(ID_6, 490, servoSpeed);
  ax12a.moveSpeed(ID_7, 512, servoSpeed);
}
void moveToState3(){ //arm fully lifted up from stowed position
  //ax12a.moveSpeed(ID_1, 512, servoSpeed);
  ax12a.moveSpeed(ID_2, 677, servoSpeed);
  ax12a.moveSpeed(ID_3, 336, servoSpeed);
  ax12a.moveSpeed(ID_4, 317, servoSpeed);
  ax12a.moveSpeed(ID_5, 701, servoSpeed);
  ax12a.moveSpeed(ID_6, 488, servoSpeed);
  ax12a.moveSpeed(ID_7, 512, servoSpeed);
}
void moveToState4(){ //arm lower down to rest in front of computer
  //ax12a.moveSpeed(ID_1, 154, servoSpeed);
  ax12a.moveSpeed(ID_2, 692, servoSpeed);
  ax12a.moveSpeed(ID_3, 325, servoSpeed);
  ax12a.moveSpeed(ID_4, 315, servoSpeed);
  ax12a.moveSpeed(ID_5, 701, servoSpeed);
  ax12a.moveSpeed(ID_6, 491, servoSpeed);
  ax12a.moveSpeed(ID_7, 512, servoSpeed);
}
void moveToState5(){ //arm back up to rotate hand for wave preparation
  //ax12a.moveSpeed(ID_1, 512, servoSpeed);
  ax12a.moveSpeed(ID_2, 684, servoSpeed);
  ax12a.moveSpeed(ID_3, 332, servoSpeed);
  ax12a.moveSpeed(ID_4, 500, servoSpeed);
  ax12a.moveSpeed(ID_5, 509, servoSpeed);
  ax12a.moveSpeed(ID_6, 180, servoSpeed);
  ax12a.moveSpeed(ID_7, 512, servoSpeed);
}
void moveToState6(){ //move hand wave left
  //ax12a.moveSpeed(ID_1, 512, servoSpeed);
  ax12a.moveSpeed(ID_2, 685, servoSpeed);
  ax12a.moveSpeed(ID_3, 329, servoSpeed);
  ax12a.moveSpeed(ID_4, 654, servoSpeed);
  ax12a.moveSpeed(ID_5, 361, servoSpeed);
  ax12a.moveSpeed(ID_6, 180, servoSpeed);
  ax12a.moveSpeed(ID_7, 512, servoSpeed);
}
void moveToState7(){ //move hand wave right
  //ax12a.moveSpeed(ID_1, 512, servoSpeed);
  ax12a.moveSpeed(ID_2, 685, servoSpeed);
  ax12a.moveSpeed(ID_3, 328, servoSpeed);
  ax12a.moveSpeed(ID_4, 319, servoSpeed);
  ax12a.moveSpeed(ID_5, 691, servoSpeed);
  ax12a.moveSpeed(ID_6, 181, servoSpeed);
  ax12a.moveSpeed(ID_7, 512, servoSpeed);
}

void setup()
{
  Serial.begin(9600);

  Wire.begin(Right_Ada_Addr);
  Wire.onReceive(receiveEvent);

  ax12a.begin(BaudRate, DirectionPin, &Serial1);
  setTorqueOn();
  setAngleLimits();
  setVoltageLimits();
  setComplianceMargins();
}

//data is receieved in 4 bit length packets
void receiveEvent(int byteCount) {
  // Serial.println("ReceiveEvent");

  receivedData = Wire.read();

  if(receivedData == 5){
    Serial.println("Startup Arm Received");   
  }else if(receivedData == 6){
    Serial.println("Shutdown Arm Received");
  }else if(receivedData == 7){
    Serial.println("Wave Arm Received");
  }else{
    Serial.println("This should not happen");
  }
}

void loop()
{
  if(receivedData == 5){
    moveToState2();
    delay(2000);
    moveToState3();
    delay(2000);
    //moveToState4();
    //delay(2000);
  }else if(receivedData == 6){
    //shutdown
    Serial.println("Shutdown Arm Received");
    moveToState3();
    delay(2000);
    moveToState2();
    delay(2000);
    moveToState1();
  }else if(receivedData == 7){
    //wave
    moveToState5();
    delay(2000);

    int count = 0;
    do{
      moveToState6();
      delay(2000);
      moveToState7();
      delay(2000);
      count++;
    }while(count < 3);
  }
  receivedData = 0;
  delay(10);
}