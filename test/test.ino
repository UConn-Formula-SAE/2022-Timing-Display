#include <Wire.h>
#include <AS1115.h>

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
  disp.setDecode(DECODE_ALL_FONT);
  disp.digitWrite(0, 0);
  disp.digitWrite(1, 1);
  disp.digitWrite(2, 2);
  disp.digitWrite(3, 3);
  disp.digitWrite(4, 4);
  disp.digitWrite(5, 5);
  disp.digitWrite(6, 6);
  disp.digitWrite(7, 7);
  SerialUSB.println("done.");
}

void loop(void) {
  byte digit;
   
  SerialUSB.print("Displaying ");
  for(digit=0; digit<=7; digit++) {
    disp.digitWrite(digit, counter);
    SerialUSB.print(counter, HEX);
  }
  SerialUSB.println("");
  counter++;
  if(counter == 0x0A){
    counter = 0;
  }
  
  digitalWrite(PA10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(PA10, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  delay(500);
}
