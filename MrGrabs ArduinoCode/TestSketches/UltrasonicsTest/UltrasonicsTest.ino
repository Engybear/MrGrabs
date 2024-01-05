//digital pins used as 
const int H_TRIG_1 = D2;
const int H_ECHO_1 = D3;
const int H_TRIG_2 = D4;
const int H_ECHO_2 = D5;
const int H_TRIG_3 = D6;
const int H_ECHO_3 = D7;
const int H_TRIG_4 = D8;
const int H_ECHO_4 = D9;

void setup() {
  // put your setup code here, to run once:

  pinMode(H_TRIG_1,OUTPUT);
  pinMode(H_ECHO_1,INPUT);
  pinMode(H_TRIG_2,OUTPUT);
  pinMode(H_ECHO_2,INPUT);
  pinMode(H_TRIG_3,OUTPUT);
  pinMode(H_ECHO_3,INPUT);
  pinMode(H_TRIG_4,OUTPUT);
  pinMode(H_ECHO_4,INPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  float distance1, distance2, distance3, distance4;
  distance1 = getDistance(H_TRIG_1,H_ECHO_1);
  // distance2 = getDistance(H_TRIG_2,H_ECHO_2);
  // distance3 = getDistance(H_TRIG_3,H_ECHO_3);
  // distance4 = getDistance(H_TRIG_4,H_ECHO_4);

  Serial.print("Distance from Sensor1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Distance from Sensor2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.print("Distance from Sensor3: ");
  Serial.print(distance3);
  Serial.println(" cm");
  Serial.print("Distance from Sensor4: ");
  Serial.print(distance4);
  Serial.println(" cm");
  
  delay(100);
}

float getDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW); // prep trig pin
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); // send out signal
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); // turn off trig pin

  unsigned long duration = pulseIn(echoPin, HIGH); // time how long it takes to get back the pulse

  //speed of sound = 343 m/s = 0.0343 cm/ms
  //divide by 2 to account for distance traveled to objetc and back
  float distance = (duration * 0.0343) / 2;

  //if(distance > 400 || distance < 2) return 0;
  
  return distance;
}

