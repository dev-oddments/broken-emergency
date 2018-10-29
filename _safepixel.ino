#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

const int JOY_X = A1; // analog
const int JOY_Y = A3; // analog ___ JOY ___

void setup() {
  //while (!Serial);
  Serial.begin(9600);
  Serial.println("16x8 LED Mini Matrix Test");
  
  matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 },
  alert_bmp[] = 
  {
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00011000,
    B00011000 },
  left_bmp[] =
  {
    B00011001,
    B00110011,
    B01100110,
    B11001100,
    B11001100,
    B01100110,
    B00110011,
    B00011001 },
  right_bmp[] =
  {
    B10011000,
    B11001100,
    B01100110,
    B00110011,
    B00110011,
    B01100110,
    B11001100,
    B10011000 };

void loop() {
  int joy_x = analogRead(JOY_X);                           // 변수 X에 아날로그 1번핀에 입력되는 신호를 대입
  int joy_y = analogRead(JOY_Y);                           // 변수 Y에 아날로그 0번핀에 입력되는 신호를 대입
  Serial.write(joy_x);
  
  if(joy_x < 100) { // DOWN
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    for (int8_t x=7; x>=-70; x--) {
      matrix.clear();
      matrix.drawBitmap(0, 8, alert_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      
      matrix.setCursor(x,0);
      matrix.print("WARNING! **");
      matrix.writeDisplay();
      
      joy_x = analogRead(JOY_X); 
      if(joy_x > 100){break;}
      
      delay(100);
    }
  }
  
  if(joy_x > 1000) { // UP
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    for (int8_t x=7; x>=-40; x--) {
      matrix.clear();
      matrix.drawBitmap(0, 8, smile_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      
      matrix.setCursor(x,0);
      matrix.print("Thanks!");
      matrix.writeDisplay();
      
      joy_x = analogRead(JOY_X); 
      if(joy_x < 1000){break;}
      
      delay(100);
    }
      while(joy_x > 1000){
        matrix.clear();
        matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(750);
        
        matrix.clear();
        matrix.drawBitmap(0, 8, smile_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(750);

        joy_x = analogRead(JOY_X); 
        if(joy_x < 1000){break;} 
        delay(100);
    }
  }

  if(joy_y > 1000) { // right
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    for (int8_t x=-64; x<=0; x++) {
      matrix.clear();
      matrix.drawBitmap(0, 8, right_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      
      matrix.setCursor(x,0);
      matrix.print(">>>>>>>>>>>>>>");
      matrix.writeDisplay();
      
      joy_y = analogRead(JOY_Y); 
      if(joy_y < 1000){break;}
      
      delay(100);
    }
  }

  if(joy_y <100) { // left
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    for (int8_t x=0; x>=-64; x--) {
      matrix.clear();
      matrix.drawBitmap(0, 8, left_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      
      matrix.setCursor(x,0);
      matrix.print("<<<<<<<<<<<<<<<");
      matrix.writeDisplay();
      
      joy_y = analogRead(JOY_Y); 
      if(joy_y > 100){break;}
      
      delay(100);
    }
  }
  
  if(joy_x > 400 && joy_x < 600 && joy_y > 400 && joy_y < 600) {
    matrix.setTextSize(2);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    for (int8_t x=0; x>=-110; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("SAFEPIXEL");
      matrix.writeDisplay();
      if(joy_x < 400 || joy_x > 600 || joy_y < 400 || joy_y > 600){break;}
      joy_x = analogRead(JOY_X); 
      joy_y = analogRead(JOY_Y);      
      delay(100);
    }
    while(joy_x > 400 && joy_x < 600 && joy_y > 400 && joy_y < 600){
      matrix.clear();
      matrix.drawRect(0,0, 8,16, LED_ON);
      matrix.fillRect(2,2, 4,12, LED_ON);
      matrix.writeDisplay();  // write the changes we just made to the display
      delay(500);

      if(joy_x < 400 || joy_x > 600 || joy_y < 400 || joy_y > 600){break;}
      joy_x = analogRead(JOY_X); 
      joy_y = analogRead(JOY_Y);  
    }
  }
}
