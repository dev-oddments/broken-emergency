
const int JOY_push = 3;
const int JOY_X = 1; // analog
const int JOY_Y = 0; // analog ___ JOY ___
int count = 0;
void setup() {
  Serial.begin(9600);              //Starting serial communication
  pinMode(JOY_push, INPUT); // ___ JOY ___
}
  
void loop() {
  int joy_push = digitalRead(JOY_push);                       // 변수 push에 디지털 3번핀에 입력되는 신호를 대입
  int joy_x = analogRead(JOY_X);                           // 변수 X에 아날로그 1번핀에 입력되는 신호를 대입
  int joy_y = analogRead(JOY_Y);                           // 변수 Y에 아날로그 0번핀에 입력되는 신호를 대입
  if(joy_x < 100) { // left
    Serial.write("1");
    count = 1;
  }

  if(joy_x > 1000) { // right
    Serial.write("2");
    count = 1;
  }

  if(joy_y > 1000) { // smile
    Serial.write("3");
    count = 1;
  }

  if(joy_y <100) { // kill
    Serial.write("4");
    count = 1;
  }
  if(joy_x > 400 && joy_x < 600 && joy_y > 400 && joy_y < 600) {
    if(count == 1) {
      Serial.write("0");
      count = 0;
    }
  }
  //if(joy_push == 0) {
    //Serial.write("9");
    //count = 0;
  //}
  delay(100);
}
