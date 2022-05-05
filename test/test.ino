#include <AS1115.h>

#define CAL_IN 27
#define CAL_A 28
#define CAL_B 29
#define CAL_C 30

AS1115 disp = AS1115(0x00);

void setup() {
  // put your setup code here, to run once:
  pinMode(CAL_IN, INPUT);
  pinMode(CAL_A, OUTPUT);
  pinMode(CAL_B, OUTPUT);
  pinMode(CAL_C, OUTPUT);
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


void display_cal(){
  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  while (starttime - endtime <= 1000){
     int cal_pos = check_cal();
     disp
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
}
