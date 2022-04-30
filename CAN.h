#include "Arduino.h"
#include <SPI.h>

#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
static mcp2518fd CAN(SPI_CS_PIN); // Set CS pin

// To TEST MCP2518FD CAN2.0 data transfer
#define MAX_DATA_SIZE 8
// To TEST MCP2518FD CANFD data transfer, uncomment below lines
// #undef  MAX_DATA_SIZE
// #define MAX_DATA_SIZE 64

#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
static mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#define MAX_DATA_SIZE 8
#endif

class CANFrame {
  
    public:
      CANFrame();
      CANFrame(uint32_t canId, uint8_t len, byte cdata[MAX_DATA_SIZE]);
      uint32_t canId;
      bool isExtended;
      bool isRemoteRequest;
      uint8_t len;
      byte cdata[MAX_DATA_SIZE];
      bool empty; // set to true if no data was received
      void toString(char* outputBuffer);
  
};

void CAN_setup();
CANFrame CAN_receive();
void CAN_send(CANFrame frame);
