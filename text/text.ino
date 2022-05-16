#include <Wire.h>
#include <AS1115.h>
#include "text.h"
#define CAN_MOSI (PA04)
#define CAN_MISO (PA05)
#define CAN_CS (PA06)
#define CAN_SCLK (PA07)
#define SEG_SDI (PA08)
#define SEG_SCK (PA09)
#define DEBUG_LED (PA10)
#define SWS1 (PA15)
#define SWS2 (PA16)
#define CAN_INT (PA17)
#define CAL_IN (PA18)
#define CAL_A (PA19)
#define CAL_B (PA20)
#define CAL_C (PA21)


byte counter = 0;
AS1115 disp;

void setup(void) {
  
  pinMode(PA10, OUTPUT);
  
  SerialUSB.begin(115200);
  SerialUSB.print("Initializing AS1115...");
  digitalWrite(PA10, HIGH);
  disp = AS1115(0x03);
  disp.begin();
  disp.setIntensity(0xff);
  disp.setFont(FONT_HEX);
  disp.setDecode(DECODE_ALL_RAW);
  
  byte shift = 1;
  for(int i = 0; i < 8; i++) {
    shift = 1;
    for(int j = 0; j < 8; j++) {
      disp.digitWrite(i, shift);
      shift = shift <<1;
//      shift = shift | 1;
      delay(50);
    }
  }
  disp.digitWrite(0, RAW_U);
  disp.digitWrite(1, RAW_C);
  disp.digitWrite(2, RAW_O);
  disp.digitWrite(3, RAW_n);
  disp.digitWrite(4, RAW_F);
  disp.digitWrite(5, RAW_S);
  disp.digitWrite(6, RAW_A);
  disp.digitWrite(7, RAW_E);
  SerialUSB.println("done.");
}

void loop(void) {
//  byte digit;
//   
//  SerialUSB.print("Displaying ");
//  for(digit=0; digit<=7; digit++) {
//    disp.digitWrite(digit, counter);
//    SerialUSB.print(counter, HEX);
//  }
//  SerialUSB.println("");
//  counter++;
//  if(counter == 0x0A){
//    counter = 0;
//  }

//  disp.digitWrite(0, RAW_0);
//  disp.digitWrite(1, RAW_1);
//  disp.digitWrite(2, RAW_2);
//  disp.digitWrite(3, RAW_3);
//  disp.digitWrite(4, RAW_4);
//  disp.digitWrite(5, RAW_5);
//  disp.digitWrite(6, RAW_6);
//  disp.digitWrite(7, RAW_7);
//  delay(3000);
//  disp.digitWrite(0, RAW_8);
//  disp.digitWrite(1, RAW_9);
//  disp.digitWrite(2, RAW_A);
//  disp.digitWrite(3, RAW_B);
//  disp.digitWrite(4, RAW_C);
//  disp.digitWrite(5, RAW_D);
//  disp.digitWrite(6, RAW_E);
//  disp.digitWrite(7, RAW_F);
//  delay(2300);
  
  digitalWrite(PA10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(PA10, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  delay(500);
}
