/* CAN Loopback Example
 * This example sends a message once a second and receives that message
 *   no CAN bus is required.  This example will test the functionality 
 *   of the protocol controller, and connections to it.
 *   
 *   Written By: Cory J. Fowler - October 5th 2016
*/

#include <SPI.h>
#include <mcp_can.h>

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

// CAN TX Variables
unsigned long prevTX = 0;                                        // Variable to store last execution time
const unsigned int invlTX = 1000;                                // One second interval constant
byte data[] = {0xAA, 0x55, 0x01, 0x10, 0xFF, 0x12, 0x34, 0x56};  // Generic CAN data to send

// CAN RX Variables
long unsigned int rxId;
unsigned char len;
unsigned char rxBuf[8];

// Serial Output String Buffer
char msgString[128];

// CAN0 INT and CS
#define CAN0_INT CAN_INT
MCP_CAN CAN0(CAN_CS);


void setup()
{
  SerialUSB.begin(115200);  // CAN is running at 500,000BPS; 115,200BPS is SLOW, not FAST, thus 9600 is crippling.
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK)
    SerialUSB.println("MCP2515 Initialized Successfully!");
  else
    SerialUSB.println("Error Initializing MCP2515...");
  
  // Since we do not set NORMAL mode, we are in loopback mode by default.
  //CAN0.setMode(MCP_NORMAL);

  pinMode(CAN0_INT, INPUT);                           // Configuring pin for /INT input
  
  SerialUSB.println("MCP2515 Library Loopback Example...");
    delay(5000);
}

void loop()
{
  if(!digitalRead(CAN0_INT))                          // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);              // Read data: len = data length, buf = data byte(s)
    
    if((rxId & 0x80000000) == 0x80000000)             // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    SerialUSB.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){            // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      SerialUSB.print(msgString);
    } else {
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        SerialUSB.print(msgString);
      }
    }
        
    SerialUSB.println();
  }
  
  if(millis() - prevTX >= invlTX){                    // Send this at a one second interval. 
    prevTX = millis();
    byte sndStat = CAN0.sendMsgBuf(0x102, 8, data);

    if(sndStat == CAN_OK)
      SerialUSB.println("Message Sent Successfully!");
    else
      SerialUSB.println("Error Sending Message...");

  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
