#include "LedControl.h"
#include <SoftwareSerial.h>


const int DIN_PIN = 7;
const int CS_PIN = 6;
const int CLK_PIN = 5;
int i = 0;
const byte EMOJI[][8] = { // http://xantorohara.github.io/led-matrix-editor/
  {
    B00111100,
    B01111110,
    B11011011,
    B11011011,
    B11111111,
    B10111101,
    B11000011,
    B01111110
  }, {
     B00000000,
    B00100100,
    B00100100,
    B00100100,
    B00000000,
    B01000010,
    B00111100,
    B00000000
  }, // emoji 0~1
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
  }, // left 2~6
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
  } // right 7~11
  ,
  {
    B00111100,
    B01000010,
    B10100101,
    B10011001,
    B10011001,
    B10100101,
    B01000010,
    B00111100
  } // cancle 12
/*
  {
    B00010000,
    B00110000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00111000
  }, {
    B00111000,
    B01000100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111100
  }, {
    B00111000,
    B01000100,
    B00000100,
    B00011000,
    B00000100,
    B00000100,
    B01000100,
    B00111000
  }, {
    B00000100,
    B00001100,
    B00010100,
    B00100100,
    B01000100,
    B01111100,
    B00000100,
    B00000100
  }, {
    B01111100,
    B01000000,
    B01000000,
    B01111000,
    B00000100,
    B00000100,
    B01000100,
    B00111000
  }, {
    B00111000,
    B01000100,
    B01000000,
    B01111000,
    B01000100,
    B01000100,
    B01000100,
    B00111000
  }, {
    B01111100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000
  }, {
    B00111000,
    B01000100,
    B01000100,
    B00111000,
    B01000100,
    B01000100,
    B01000100,
    B00111000
  }, {
    B00111000,
    B01000100,
    B01000100,
    B01000100,
    B00111100,
    B00000100,
    B01000100,
    B00111000
  }, {
    B00111000,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B00111000
  }
*/
};
const int IMAGES_LEN = sizeof(EMOJI) / 8;
LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN); // (DIN, CS, CLK, 1dot) ___DOT___

int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); // ___bluetooth___

void setup() {
  Serial.begin(9600);    
  
  display.shutdown(0, false);
  display.setIntensity(0, 5); // LED 밝기(0~15)
  display.clearDisplay(0); // ___DOT___
  
  bluetooth.begin(9600); // ___bluetooth___
}

void displayImage(const byte* image) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(image[i], 7 - j));
    }
  }
}

char why;
void loop() {
  why = (char)bluetooth.read();
  
  if(why == '1') { // left
    while(why == '1'){
      for(int i = 2; i <= 6 ; i++) {
        displayImage(EMOJI[i]);
        delay(100);
        why = (char)bluetooth.read();
        if(why != '1'){ break;}
      }
      why = (char)bluetooth.read();
    }
  }
  
  if(why == '2') { // right
    while(why == '2') {
      for(int i = 7; i <= 11; i++) {
        displayImage(EMOJI[i]);
        delay(100);
        why = (char)bluetooth.read();
        if(why != '2'){ break;}
      }
      why = (char)bluetooth.read();
    }
  }

  if(why == '3') { // smile
    while(why == '3') {
      why = (char)bluetooth.read();
      displayImage(EMOJI[0]);
      }
  }
  
  if(why == '4') { // kill
    while(why == '4') {
      why = (char)bluetooth.read();
      displayImage(EMOJI[12]);
      }
  }

  
  displayImage(EMOJI[1]); // default 
/*
  if(bluetooth.available())
  {
    char toSend = (char)bluetooth.read();
    Serial.print(toSend);
  }
*/
}
