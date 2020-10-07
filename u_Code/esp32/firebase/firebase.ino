#include <WiFi.h>
#include "FirebaseESP32.h"

#define RXD2 16
#define TXD2 17

//UART StateMachine states
typedef enum {WaitingStartByte, Framelength, Payload, CheckSum, Value} state_machine_t;
state_machine_t data_state_s;
unsigned char incomingByte, length_data, checksum_recv, checksum_calc = 0, id, length_value, value;
unsigned char bufferpayload[128];
int pos = 0, j = 0, k = 0, p = 0, value_int = 0, v = 0, conn = 0,ackFlag = 0,askForValues=0,receiveConfig=0;

const char* ssid = "MEO-669FB0";
const char* password = "830a647f8d";

FirebaseData firebaseData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  connectWifi();
  Firebase.begin("https://uaelectrex.firebaseio.com/", "foNqcyMz6gMfd0rewXHQ281QM3U6CtMYFt1BG31T");
}

void loop() {
  data_SM();
}

void connectWifi() {
  Serial.print("Connecting...");
  // Let us connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".......");
  Serial.println("WiFi Connected....IP Address:");
  Serial.println(WiFi.localIP());
}

void data_SM(void) {
  
  switch (data_state_s) {

    case WaitingStartByte:    //Waits for start byte
      checksum_calc = 0;

      if (Serial2.available() > 0) {
        incomingByte = Serial2.read();
        //Serial.println(incomingByte);
        if (incomingByte == 170) {    //If received byte is startbyte         
          data_state_s = Framelength;   //Goes to next State
        }
      }
      break;

    case Framelength:

      if (Serial2.available() > 0) {
        length_data = Serial2.read();    //Stores Frame Length Value
        //Serial.println(length_data);
        data_state_s = Payload;         //Goes to next State

      }

      break;

    case Payload:

      if (Serial2.available() > 0) {

        bufferpayload[pos] = Serial2.read();    //reads byte of payload to buffer
        //Serial.println(bufferpayload[pos]);
        checksum_calc += bufferpayload[pos];   //calculate checksum

        if (pos == (length_data - 1)) { //Last value of frame
          pos = 0;                    //Puts position back to zero
          data_state_s = CheckSum;    //Goes to next state
        }
        else {
          pos++;                      //If its not last value of frame
          data_state_s = Payload;     //Goes to payload again
        }
      }


      break;

    case CheckSum:
      //Serial.println("checksum state");
      if (Serial2.available() > 0) {
        checksum_recv = Serial2.read();    //Receives checksum from uart.
      }


      if (checksum_recv == checksum_calc) { //If received checksum = calculated checksum
        handlepayload();                    //Valid Payload
        
        data_state_s = WaitingStartByte;
      }

      else {
        sendNotValidACK();     //If received checksum != calculated checksum send wrong ACK
  
        data_state_s = WaitingStartByte;    //Back to waiting for inital frame
      }

      break;

    default:
      data_state_s = WaitingStartByte;
      break;
  }
}

void handlepayload(void) {
  
  FirebaseJson json;
  
  int i = 0;

  while (i < length_data) {            //Percorre o buffer todo
    value_int = 0;

    id = bufferpayload[i];
    
    if((id >=1 && id <= 22)){ // checks if any of the id received 
      receiveConfig = 1;      // was config values
    }

    i++;
    length_value = bufferpayload[i];
    i++;
    k = i;

    while (k < (i + length_value)) {

      if (v == 0 && length_value > 1) {           //if length_value > 1
        value_int = (int)(bufferpayload[k] * 256); //only supports 1 or 2 byte payload
        v++;
      }
      else {
        value_int += (int)(bufferpayload[k]);
      }
      k++;
    }
    v = 0;
    i = k;
    
  json.set(String(id),value_int);
  }
  
  if(receiveConfig == 1 && askForValues == 1){
    sendValidACK();
    receiveConfig = 0;
    askForValues = 0;
  }
 
  Firebase.updateNode(firebaseData,"/maquinas/-MG48BCQC-_-kHIUnpki",json);
  
   
}

void askConfigFiles(void){
  Serial2.write(0xAA);
  Serial2.write(0x03);
  
  Serial2.write(0x01);
  Serial2.write(0x01);
  Serial2.write(0x01);
  
  Serial2.write(0x03);
}

void sendValidACK(void){
  Serial2.write(0xAA);
  Serial2.write(0x03);
  
  Serial2.write(0x02);
  Serial2.write(0x01);
  Serial2.write(0x01);
  
  Serial2.write(0x04);
}

void sendNotValidACK(void){
  Serial2.write(0xAA);
  Serial2.write(0x03);
  
  Serial2.write(0x02);
  Serial2.write(0x01);
  Serial2.write(0x00);
  
  Serial2.write(0x03);
}
