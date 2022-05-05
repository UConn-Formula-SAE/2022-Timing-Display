


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




void setup() {
  // put your setup code here, to run once:
  pinMode(CAL_IN, INPUT);
  pinMode(CAL_A, OUTPUT);
  pinMode(CAL_B, OUTPUT);
  pinMode(CAL_C, OUTPUT);
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(DEBUG_LED, HIGH); 
  SerialUSB.begin(115200);
  while(!SerialUSB);
  SerialUSB.println("Connected");
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
     
  }
}

int cal_pos = 0;
int last;
void loop() {
  // put your main code here, to run repeatedly:
  if (cal_pos){
    last = cal_pos;
  }
  cal_pos = check_cal();
  if (cal_pos != last){
    SerialUSB.println(cal_pos);
  }
  
}
