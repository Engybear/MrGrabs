#include <AX12A.h>

#define DirectionPin  (1u) //TX PIN
#define BaudRate    (1000000u)
#define ID    (1u)
#define ID_6  (6u)


void setup()
{
 ax12a.begin(BaudRate, DirectionPin, &Serial1);
 ax12a.setEndless(ID, ON);
 ax12a.setEndless(ID_6, ON);
 
}

void loop()
{
    // ax12a.ledStatus(ID, ON);
    // ax12a.turn(ID, LEFT, 200);
    // delay(2000);
  
    // ax12a.ledStatus(ID, OFF);
    // ax12a.turn(ID, RIGHT, 200);
    // delay(2000);

    int pos = 512;
    digitalWrite(DirectionPin, HIGH);
    ax12a.ledStatus(ID_6, ON);
    ax12a.turn(ID_6, LEFT, 200);
    delay(2000);

    digitalWrite(DirectionPin, LOW);
    pos = ax12a.readPosition(ID_6);
    Serial.println(pos);

    digitalWrite(DirectionPin, HIGH);
    ax12a.ledStatus(ID_6, OFF);
    ax12a.turn(ID_6, RIGHT, 200);
    delay(2000);

    digitalWrite(DirectionPin, LOW);
    pos = ax12a.readPosition(ID_6);
    Serial.println(pos);
}