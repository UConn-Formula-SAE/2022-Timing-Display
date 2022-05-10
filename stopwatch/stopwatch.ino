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

AS1115 disp;
int timer_ms;
int prev_time;
bool timer_paused;
int debug_light_timer = 0;
int debug_light_display_time = 200;
int debug_light_off_time = 1000;
int cal_pos;

void setup(void) {

  pinMode(CAL_IN, INPUT);
  pinMode(CAL_A, OUTPUT);
  pinMode(CAL_B, OUTPUT);
  pinMode(CAL_C, OUTPUT);
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(DEBUG_LED, HIGH); 
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
  timer_ms = 0;
  prev_time = millis();
  timer_paused = false;
  debug_light_timer = 0;
}

void splitInt(int num, int* outputDigits, int len) {
  for (int i = 0; i < len; i++) {
    outputDigits[i] = 0;
  }  
  for (int i = len - 1; i >= 0; i--) {
    outputDigits[i] = num % 10;
    num = num / 10;
    if (num < 1) return;
  }
}

int check_cal(){
  int cal_pos = 1;
  for (int i = 0; i < 8; i++) {
        digitalWrite(CAL_A, i & 1 ? HIGH : LOW);
        digitalWrite(CAL_B,  i & 2 ? HIGH : LOW);
        digitalWrite(CAL_C,  i & 4 ? HIGH : LOW);
        if (digitalRead(CAL_IN) == HIGH){
          cal_pos = i + 2;
        }
  }
  return cal_pos;
}

void loop(void) {
  int current_time = millis();
  if (digitalRead(SWS1)) {
    timer_paused = !timer_paused;
  }
  if (!timer_paused) {
    timer_ms += current_time - prev_time;
  }
  debug_light_timer += current_time - prev_time;
  prev_time = current_time;
  if (debug_light_timer > debug_light_off_time + debug_light_display_time) {
    digitalWrite(DEBUG_LED, LOW);
    debug_light_timer = 0;
  } else if (debug_light_timer > debug_light_off_time) {
    digitalWrite(DEBUG_LED, HIGH);
  }
  byte digit;
  int displayValues[4];
  int timer_hundreth_secs = timer_ms / 10;
  splitInt(timer_hundreth_secs, displayValues, 4);
  SerialUSB.print("Displaying ");
  for(digit=0; digit<=3; digit++) {
    disp.digitWrite(digit, displayValues[digit]);
  }
  SerialUSB.print(timer_hundreth_secs, HEX);
  SerialUSB.println("");
  int new_cal_pos = check_cal();
  if (cal_pos != new_cal_pos) {
    cal_pos = new_cal_pos;
    disp.digitWrite(4, 12); // 12 = hex C
    disp.digitWrite(5, 10); // 13 = hex A
    disp.digitWrite(6, 0); 
    disp.digitWrite(7, cal_pos); 
  } 

}
