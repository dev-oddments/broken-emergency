#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define NUM_MATRICES 3
Adafruit_8x8matrix matrix[NUM_MATRICES];

const int JOY_X = A1; // analog
const int JOY_Y = A3; // analog ___ JOY __
int boot_flag = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  for(uint8_t m=0; m<NUM_MATRICES; m++) {
    matrix[m].begin(0x70 + m);
    matrix[m].clear();
    matrix[m].setTextSize(1);
    matrix[m].setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix[m].setRotation(1);

  }
  
}

static const uint8_t PROGMEM
  default_sign[][24] = {                 // Mouth animation frames
  { 0B11111111, 0B11111111, 0B11111111, // Mouth position A
    0B10000000, 0B00000000, 0B00000001,
    0B10111111, 0B11111111, 0B11111101,
    0B10100000, 0B00000000, 0B00000101,
    0B10100000, 0B00000000, 0B00000101,
    0B10111111, 0B11111111, 0B11111101,
    0B10000000, 0B00000000, 0B00000001,
    0B11111111, 0B11111111, 0B11111111 } },
  left_sign[][8] = {    // Eye animation frames
  {
    B00011000,
    B00110001,
    B01100011,
    B11000110,
    B11000110,
    B01100011,
    B00110001,
    B00011000
  },{
    B00110001,
    B01100011,
    B11000110,
    B10001100,
    B10001100,
    B11000110,
    B01100011,
    B00110001
  },{
    B01100011,
    B11000110,
    B10001100,
    B00011000,
    B00011000,
    B10001100,
    B11000110,
    B01100011
  },{
    B11000110,
    B10001100,
    B00011000,
    B00110001,
    B00110001,
    B00011000,
    B10001100,
    B11000110
  },{
    B10001100,
    B00011000,
    B00110001,
    B01100011,
    B01100011,
    B00110001,
    B00011000,
    B10001100
  }, },
  
  right_sign[][8] = {    // Eye animation frames
  {
    B00011000,
    B10001100,
    B11000110,
    B01100011,
    B01100011,
    B11000110,
    B10001100,
    B00011000
  },{
    B10001100,
    B11000110,
    B01100011,
    B00110001,
    B00110001,
    B01100011,
    B11000110,
    B10001100
  },{
    B11000110,
    B01100011,
    B00110001,
    B00011000,
    B00011000,
    B00110001,
    B01100011,
    B11000110
  },{
    B01100011,
    B00110001,
    B00011000,
    B10001100,
    B10001100,
    B00011000,
    B00110001,
    B01100011
  },{
    B00110001,
    B00011000,
    B10001100,
    B11000110,
    B11000110,
    B10001100,
    B00011000,
    B00110001
  } },
  progress_sign[][8] = {    // Eye animation frames
  {
    B11111111,
    B10000001,
    B10111101,
    B10100101,
    B10100101,
    B10111101,
    B10000001,
    B11111111
  },{
    B00000000,
    B01111110,
    B01000010,
    B01011010,
    B01011010,
    B01000010,
    B01111110,
    B00000000
  }, {
    B10000001,
    B01111110,
    B01100110,
    B01011010,
    B01011010,
    B01100110,
    B01111110,
    B10000001
  } },
  alert_sign[][24] = {    // Eye animation frames
  { 
    0B00011000, 0B00000000, 0B00000000,
    0B00011000, 0B01000010, 0B01000010,
    0B00011000, 0B00100100, 0B00100100,
    0B00011000, 0B00011000, 0B00011000,
    0B00011000, 0B00011000, 0B00011000,
    0B00000000, 0B00100100, 0B00100100,
    0B00011000, 0B01000010, 0B01000010,
    0B00011000, 0B00000000, 0B00000000 
  }, {
    0B00000000, 0B00011000, 0B00000000,
    0B01000010, 0B00011000, 0B01000010,
    0B00100100, 0B00011000, 0B00100100,
    0B00011000, 0B00011000, 0B00011000,
    0B00011000, 0B00011000, 0B00011000,
    0B00100100, 0B00000000, 0B00100100,
    0B01000010, 0B00011000, 0B01000010,
    0B00000000, 0B00011000, 0B00000000 
  }, {
    0B00000000, 0B00000000, 0B00011000, 
    0B01000010, 0B01000010, 0B00011000,
    0B00100100, 0B00100100, 0B00011000, 
    0B00011000, 0B00011000, 0B00011000, 
    0B00011000, 0B00011000, 0B00011000,
    0B00100100, 0B00100100, 0B00000000, 
    0B01000010, 0B01000010, 0B00011000, 
    0B00000000, 0B00000000, 0B00011000
  }, {
    0B00000000, 0B00011000, 0B00000000,
    0B01000010, 0B00011000, 0B01000010,
    0B00100100, 0B00011000, 0B00100100,
    0B00011000, 0B00011000, 0B00011000,
    0B00011000, 0B00011000, 0B00011000,
    0B00100100, 0B00000000, 0B00100100,
    0B01000010, 0B00011000, 0B01000010,
    0B00000000, 0B00011000, 0B00000000 
  } };
  
void loop() {
  if(boot_flag == 0){
    boot();
  }
  int joy_x = analogRead(JOY_X);                           // 변수 X에 아날로그 1번핀에 입력되는 신호를 대입
  int joy_y = analogRead(JOY_Y);                           // 변수 Y에 아날로그 0번핀에 입력되는 신호를 대입

  if(joy_y < 100) { // left
    leftSign();
  }
  if(joy_y > 1000) { // left
    rightSign();
  }
  if(joy_x > 400 && joy_x < 600 && joy_y > 400 && joy_y < 600) {
    defaultSign();
  }
  if(joy_x < 100) {
    alertSign();
  }
//  leftSign();
//  delay(500);
//  delay(500);
}

void scroll(char* text) {
  int scrollPositions = (strlen(text) * 4) + 4;
  int joy_x = analogRead(JOY_X); 
  int joy_y = analogRead(JOY_Y);
  for (int x=scrollPositions / 2; x>=-scrollPositions; x--) {
   for(uint8_t m=0; m<NUM_MATRICES; m++) {
    matrix[m].clear();
    matrix[m].setCursor((x - (m * 8)), 0);
    matrix[m].print(text);
    matrix[m].writeDisplay();
    joy_x = analogRead(JOY_X); 
    joy_y = analogRead(JOY_Y); 
    if(joy_x < 400 || joy_x > 600 || joy_y < 400 || joy_y > 600){break;}     
   }
   delay(30);
  }

}

void boot() {
  boot_flag = 1;
  scroll("SAFEPIXEL**");

}


void defaultSign() {
  for(uint8_t i=0; i<3; i++) {
    matrix[i].clear();
    matrix[i].drawBitmap(i * -8, 0, default_sign[0], 24, 8, LED_ON);
    matrix[i].writeDisplay();
  }
}



void leftSign() {
  for(int x = 0; x < 5; x++) {
    delay(100);
    matrix[0].clear();
    matrix[0].drawBitmap(0, 0, left_sign[x], 8, 8, LED_ON);
    matrix[0].writeDisplay();
    matrix[1].clear();
    matrix[1].drawBitmap(0, 0, left_sign[(x+3)%5], 8, 8, LED_ON);
    matrix[1].writeDisplay();
    matrix[2].clear();
    matrix[2].drawBitmap(0, 0, progress_sign[1], 8, 8, LED_ON);
    matrix[2].writeDisplay();
  }
}

void rightSign() {
  for(int x = 0; x < 5; x++) {
    delay(100);
    matrix[0].clear();
    matrix[0].drawBitmap(0, 0, progress_sign[1], 8, 8, LED_ON);
    matrix[0].writeDisplay();
    matrix[1].clear();
    matrix[1].drawBitmap(0, 0, right_sign[(x+3)%5], 8, 8, LED_ON);
    matrix[1].writeDisplay();
    matrix[2].clear();
    matrix[2].drawBitmap(0, 0, right_sign[x], 8, 8, LED_ON);
    matrix[2].writeDisplay();
  }
}

void alertSign() {
  for(int x = 0; x < 4; x++){
    delay(400);
    for(uint8_t i=0; i<3; i++) {
      matrix[i].clear();
      matrix[i].drawBitmap(i * -8, 0, alert_sign[x], 24, 8, LED_ON);
      matrix[i].writeDisplay();
    }
  }
}
