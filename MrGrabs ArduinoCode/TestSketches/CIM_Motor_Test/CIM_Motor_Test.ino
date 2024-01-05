const int PWM1 = A2;
const int DIR1 = D2;

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM1,OUTPUT);
}

bool swap = HIGH;
void loop() {
  // put your main code here, to run repeatedly:
  int val = 0;
  for(val = 0; val < 255; val++){
    analogWrite(PWM1,val);
    delay(10);
  }
  for(val = 255; val > 0; val--){
    analogWrite(PWM1,val);
    delay(10);
  }
  delay(100);
  swap = !swap;
  if(val == 0) digitalWrite(DIR1, swap);

}
