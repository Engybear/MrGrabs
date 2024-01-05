#include <Wire.h>
#define Left_Ada_Addr 5
#define Right_Ada_Addr 6

//RIGHT MOTOR
const int Motor1_Speed = A3; //orange - PWM2
const int Motor1_Dir = D3; //yellow - DIR2

//LEFT MOTOR
const int Motor2_Speed = A2; //green - PWM1 
const int Motor2_Dir = D2; //black - DIR1

#include <ArduinoBLE.h>
BLEService mainService("19B10010-E8F2-537E-4F6C-D104768A1214"); // create service
BLEByteCharacteristic buttonCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLEWrite | BLERead | BLENotify); // allow remote device to write button presses
BLEByteCharacteristic speedCharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLEWrite | BLERead | BLENotify); // allow remote device to write speed slider value

//global speed value of motors + directions
int gCurSpeed1 = 0;
int gCurSpeed2 = 0;
int gSliderSpeed = 0;
bool curDir1 = HIGH; //HIGH = forward direction
bool curDir2 = HIGH; //HIGH = forward direction

//bool conditions for movement direction
bool movingBack = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //start up BLE
  if(!BLE.begin()){
    Serial.println("Bluetooth startup failed");
    while(1);
  }

  //attach characteristics to main service
  BLE.setLocalName("MrGrabs");
  BLE.setAdvertisedService(mainService);
  mainService.addCharacteristic(buttonCharacteristic);
  mainService.addCharacteristic(speedCharacteristic);
  BLE.addService(mainService);

  //prep characteristics with interrupt handlers for button presses / slider updates
  buttonCharacteristic.writeValue(0);
  speedCharacteristic.writeValue(0);
  buttonCharacteristic.setEventHandler(BLEWritten, buttonValueHandler);
  speedCharacteristic.setEventHandler(BLEWritten, speedValueHandler);
  
  //advertist BLE service to public
  BLE.advertise();

  Wire.begin(); //setup as Main central for I2C

  //setup Adafruit boards as peripherals
  Wire.beginTransmission(Left_Ada_Addr);
  Wire.endTransmission();
  Wire.beginTransmission(Right_Ada_Addr);
  Wire.endTransmission();

  //setup motor control pins
  pinMode(Motor1_Speed, OUTPUT);
  pinMode(Motor1_Dir, OUTPUT);
  pinMode(Motor2_Speed, OUTPUT);
  pinMode(Motor2_Dir, OUTPUT);

  //initilize speed and direction to 0
  analogWrite(Motor1_Speed,gCurSpeed1);
  digitalWrite(Motor1_Dir,curDir1);
  analogWrite(Motor2_Speed,gCurSpeed2);
  digitalWrite(Motor2_Dir,curDir2);

}

/* Smooth Speed Changer function; used without flip to change speed, 
                                  used with flip twice, to decrement to 0, change direction pin, and then increment to desired negative direction value
 * curSpeed1 : current speed of Motor1
 * newSpeed1 : desired speed of Motor1
 * curSpeed2 : current speed of Motor2
 * newSpeed2 : desired speed of MOtor2
 * boolflip1 : Motor1's direction pin needs to flip
 * boolflip2 : Motor2's direction pin needs to flip
 */ 
void changeSpeedSmooth(int curSpeed1, int newSpeed1, int curSpeed2, int newSpeed2, bool flip1, bool flip2){
  // Serial.print("Updating Speed: ");
  // Serial.print(curSpeed1);
  // Serial.print(" -> ");
  // Serial.print(newSpeed1);
  // Serial.print(" / ");
  // Serial.print(curSpeed2);
  // Serial.print(" -> ");
  // Serial.print(newSpeed2);
  // Serial.print(" / flips: ");
  // Serial.print(flip1);
  // Serial.print(" / ");
  // Serial.println(flip2);

  int i = curSpeed1, j = curSpeed2;
  while(i != newSpeed1 || j != newSpeed2){
    if(i < newSpeed1) i++;
    else if(i > newSpeed1) i--;
    if(j < newSpeed2) j++;
    else if(j > newSpeed2) j--; 

    analogWrite(Motor1_Speed, i);
    analogWrite(Motor2_Speed, j);
    
    delay(10); 
    //delay is used to slow down the update of the speed to the motors 
    //this is to ensure we don't immediately jump from 0 to max speed and fry our motor controller
  }

  //update direction pins on flip condition
  if(flip1) digitalWrite(Motor1_Dir, curDir1);
  if(flip2) digitalWrite(Motor2_Dir, curDir2);
  delay(10);

  // Serial.print("Directions: ");
  // Serial.print(curDir1);
  // Serial.print(" , ");
  // Serial.println(curDir2);
  
  //update global speed values
  gCurSpeed1 = newSpeed1;
  gCurSpeed2 = newSpeed2;
}

bool armWave = true; //boolean to alternative between which arm will wave

void buttonValueHandler(BLEDevice central, BLECharacteristic buttonCharacteristic){ //will run when we receive a button press from the app
  byte data;
  int buttonValue = (int)(*buttonCharacteristic.value()); //receive the value being transmitted to us as an int

  switch (buttonValue){ //hardcoded cases based on which button was pressed
    case 1: //Move forwards
      //goal: Motor1_Speed = gSliderSpeed, Motor2_Speed = gSliderSpeed
      Serial.println("Move Forwards");

      curDir1 = HIGH;
      curDir2 = HIGH;

      if(movingBack){ //if moving back, we need to flip before moving forward
        changeSpeedSmooth(gCurSpeed1, 0, gCurSpeed2, 0, true, true);
        changeSpeedSmooth(gCurSpeed1, gSliderSpeed, gCurSpeed2, gSliderSpeed, false, false);

      }
      else{ //if turning left or turning right or moving forward, simply adjust speed on both motors
        changeSpeedSmooth(gCurSpeed1, gSliderSpeed, gCurSpeed2, gSliderSpeed, false, false);
      }

      movingBack = false;
      break;

    case 2: //Move backwards
      //goal: Motor1_Speed = -gSliderSpeed, Motor2_Speed = -gSliderSpeed
      Serial.println("Move Back");

      curDir1 = LOW;
      curDir2 = LOW;
      if(!movingBack){ //if turning left or turning right or moving forward, we need to flip before moving back
        changeSpeedSmooth(gCurSpeed1, 0, gCurSpeed2, 0, true, true);
        changeSpeedSmooth(gCurSpeed1, gSliderSpeed, gCurSpeed2, gSliderSpeed, false, false);

      }
      else{ //if moving back, simply adjust speed on both motors
        changeSpeedSmooth(gCurSpeed1, gSliderSpeed, gCurSpeed2, gSliderSpeed, false, false);
      }

      movingBack = true;
      break;

    case 3: //Turn left
      //goal: Motor1_Speed = 0, Motor2_Speed = gSliderSpeed 
      Serial.println("Turn Left");

      curDir1 = HIGH;
      curDir2 = HIGH;
      
      if(movingBack){ //if moving back, we need to flip before moving forward
        changeSpeedSmooth(gCurSpeed1, 0, gCurSpeed2, 0, true, true);
        changeSpeedSmooth(gCurSpeed1, 0, gCurSpeed2, gSliderSpeed, false, false);
      }
      else{ //if turning left or turning right or moving forward, simply adjust speed on both motors
        //increment to new speed
        changeSpeedSmooth(gCurSpeed1, 0, gCurSpeed2, gSliderSpeed, false, false);
      }

      movingBack = false;
      break;

    case 4: //Turn right
      //goal: Motor1_Speed = gSliderSpeed, Motor2_Speed = 0
      Serial.println("Turn Right");

      curDir1 = HIGH;
      curDir2 = HIGH;
      
      if(movingBack){ //if moving back, we need to flip before moving forward
        changeSpeedSmooth(gCurSpeed1, 0, gCurSpeed2, 0, true, true);
        changeSpeedSmooth(gCurSpeed1, gSliderSpeed, gCurSpeed2, 0, false, false);
      }
      else{ //if turning left or turning right or moving forward, simply adjust speed on both motors
        //increment to new speed
        changeSpeedSmooth(gCurSpeed1, gSliderSpeed, gCurSpeed2, 0, false, false);
      }

      movingBack = false;
      break;
    
    case 5: //Startup Arm
      //goal: have arm move from stable position to active position
      data = 5; //send byte protocol for arm startup to both arms
      Serial.println("Startup Arm");
      
      Wire.beginTransmission(Left_Ada_Addr);
      Wire.write(data);
      Wire.endTransmission();

      Wire.beginTransmission(Right_Ada_Addr);
      Wire.write(data);
      Wire.endTransmission();
      break;

    case 6: //Shutdown Arm
      //goal: have arm move from active position to stable position
      data = 6; //send byte protocol for arm shutdown to both arms
      Serial.println("Shutdown Arm");

      Wire.beginTransmission(Left_Ada_Addr);
      Wire.write(data);
      Wire.endTransmission();

      Wire.beginTransmission(Right_Ada_Addr);
      Wire.write(data);
      Wire.endTransmission();
      break;

    case 7: //Wave Arm
      //goal: have arm move from active position to wave, then back to active position
      //alternative which arm waves
      data = 7; //send byte protocol for arm wave to alternating arms
      Serial.println("Wave Arm");

      if(armWave){
        Wire.beginTransmission(Left_Ada_Addr);
        Wire.write(data);
        Wire.endTransmission();
      }else{
        Wire.beginTransmission(Right_Ada_Addr);
        Wire.write(data);
        Wire.endTransmission();
      }
      armWave = !armWave;
      break;

    default: //oh boi, this should not happen
       Serial.println("BUTTON VALUE ERROR");
      break;
  }
}

void speedValueHandler(BLEDevice central, BLECharacteristic speedCharacteristic){ //will run when the slider is updated to a new value on the app
  const float ratio = 255/50; //the slider operates from 0 to 50; convert to 0 to 255 for analog values
  int speedValue = (int)(*speedCharacteristic.value()); //read the value of the slider as an int
  gSliderSpeed = (speedValue * ratio);

  if(speedValue == 0) changeSpeedSmooth(gCurSpeed1, 0, gCurSpeed2, 0, false, false); //if speed is set to 0, update both motors to be 0, else wait for button press
                                                                                     //we only update the speed here if it's being set to 0
  
  // Serial.print("Updating Speed:");
  // Serial.println(gSliderSpeed);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  BLE.poll(); //poll for interrupt events

  //also poll the ultrasonic sensors here, if they detect an object that's too close
}