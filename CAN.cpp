#include "CAN.h"

void CAN_setup() {
    
    #if MAX_DATA_SIZE > 8
    /*
     * To compatible with MCP2515 API,
     * default mode is CAN_CLASSIC_MODE
     * Now set to CANFD mode.
     */
    CAN.setMode(CAN_NORMAL_MODE);
    #endif


    while (CAN_OK != CAN.begin(CAN_1000KBPS)) {            
        SerialUSB.println(F("CAN init fail, retry..."));
        delay(100);
    }
    SerialUSB.println(F("CAN init ok!"));
}

CANFrame CAN_receive() {

    CANFrame frame;
    // check if data coming
    if (CAN_MSGAVAIL != CAN.checkReceive()) {
        SerialUSB.println("No data received");
        frame.empty = true;
        return frame;
    }
    
    // read data, len: data length, buf: data buf
    CAN.readMsgBuf(&frame.len, frame.cdata);

    frame.canId = CAN.getCanId();
    frame.isExtended = CAN.isExtendedFrame();
    frame.isRemoteRequest = CAN.isRemoteRequest();

    return frame;
}

void CAN_send(CANFrame frame) {
    CAN.sendMsgBuf(frame.canId, frame.isExtended, frame.len, frame.cdata);
}

CANFrame::CANFrame() {
  this->isExtended = false;
  this->isRemoteRequest = false;
  this->cdata = {0};
  this->empty = false;
  
 }

CANFrame::CANFrame(uint32_t canId, uint8_t len, byte cdata[MAX_DATA_SIZE]) {
  this->canId = canId;
  this->len = len;
  for (int i = 0; i < MAX_DATA_SIZE; i++) {
    this->cdata[i] = cdata[i];
  }
  this->isExtended = false;
  this->isRemoteRequest = false;
  this->empty = false;
}

void CANFrame::toString(char* outputBuffer) {
      int n;
      /* Displayed type:
       *
       * 0x00: standard data frame
       * 0x02: extended data frame
       * 0x30: standard remote frame
       * 0x32: extended remote frame
       */
      uint8_t type = (isExtended << 0) | (isRemoteRequest << 1);
      static const byte type2[] = {0x00, 0x02, 0x30, 0x32};
      n += sprintf(outputBuffer + n, "[%08lX](%02X) ", (unsigned long)canId, type2[type]);
 
      for (int i = 0; i < len; i++) {
          n += sprintf(outputBuffer + n, "%02X ", cdata[i]);
      }
}
