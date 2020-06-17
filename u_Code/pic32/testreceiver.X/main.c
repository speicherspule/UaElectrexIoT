/* 
 * File:   main.c
 * Author: pedro
 *
 *
 * 
 * Created on 5 de Junho de 2020, 16:32
 */


/*
 *  This code implements a state machine that receives the data from the gateway.
 *  It deals with the configuration request (global variable askForValuesFlag = 1) 
 *  from the gateway and receives the ACK frame.
 *  If the ACK is valid, it makes an global ackFlag (shared memory) = 1, if not, = 0. 
 *
 */

//Includes
#include "../CommonFiles/ConfigBits/config_bits.h" // NOTE!! Must precede project file includes
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "../CommonFiles/Uart/uart.h" // NOTE!! Must precede project file includes

//Defines
#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz


//prototypes
void InitUart(void);
void receiveUart(void);
void handle(void);
void sendConfig(void);
void sendValidACK(void);
void sendNotValidACK(void);

//config variables
unsigned char startByte = 0xAA;
unsigned char length_frame_3 = 3;
uint8_t length_value = 1;
uint8_t value1 = 0x02;
uint8_t checksum;

//UART StateMachine states
typedef enum {WaitingStartByte, Framelength, Payload, CheckSum, Value} state_machine_t;
state_machine_t data_state_s;

unsigned char incomingByte, length_data, checksum_recv, checksum_calc = 0, id, length_value, value_sm;
unsigned char bufferpayload[128];
int rcv_data = 0;
int pos = 0;
uint8_t ackFlag,askForValuesFlag;
int h = 0;
/*
 * 
 */
int main(int argc, char** argv) {
    
    InitUart();
    while(1){
        receiveUart(); 
    }
    return (EXIT_SUCCESS);
}

void receiveUart(void){

  switch (data_state_s) {

    case WaitingStartByte:    //Waits for start byte

        checksum_calc = 0;
        
        while (GetChar(&incomingByte) != UART_SUCCESS );

        if (incomingByte == 170) {    //If received byte is startbyte
          data_state_s = Framelength;   //Goes to next State
        }
  
    break;

    case Framelength:
       
        while ( GetChar(&length_data) != UART_SUCCESS );
        data_state_s = Payload;         //Goes to next State

      break;

    case Payload:
      
        
        while ( GetChar(&bufferpayload[pos]) != UART_SUCCESS );
  
        checksum_calc += bufferpayload[pos];   //calculate checksum

        if (pos == (length_data - 1)) { //Last value of frame
          pos = 0;                    //Puts position back to zero
          data_state_s = CheckSum;    //Goes to next state
        }
        else {
          pos++;                      //If its not last value of frame
          data_state_s = Payload;     //Goes to payload again
        }

      break;

    case CheckSum:
        while ( GetChar(&checksum_recv) != UART_SUCCESS );

        if (checksum_recv == checksum_calc) { //If received checksum = calculated checksum
            
            handle();                           //Valid Payload
            data_state_s = WaitingStartByte;
        }

      else {              
        data_state_s = WaitingStartByte;    //Back to waiting for inital frame
      }

      break;

    default:
      data_state_s = WaitingStartByte;
      break;
  }    
}

void handle(void){
    uint16_t i = 0,v = 0,k = 0,value_int = 0,ackFlag = 0;
    
    while (i < length_data) {            //Percorre o buffer todo
       
        value_int = 0;
    
        id = bufferpayload[i];
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
    }
    
       if((id == 0x01) && (value_int == 0x01))      //ask for config files ID=0x01 && Value =0x01
       {
        printf("Recebi pedido");
        askForValuesFlag = 1;
        sendConfig();  // test
        
       }
       
       if((id == 0x02) && (value_int == 0x00))      //ask for config files ID=0x01 && Value =0x01
       {
           printf("Recebi not ack");
           ackFlag = 0;
       }  
        
       if((id == 0x02) && (value_int == 0x01))      //ask for config files ID=0x01 && Value =0x01
       {           
           printf("Recebi ack %i",h);
           ackFlag = 1;
           h++;
       }  

}

void sendValidACK(void){
    PutChar(0xAA);
    PutChar(0x03);
    
    PutChar(0x02);
    PutChar(0x01);
    PutChar(0x01);
    
    PutChar(0x04);
}

void sendNotValidACK(void){
    PutChar(0xAA);
    PutChar(0x03);
    
    PutChar(0x02);
    PutChar(0x01);
    PutChar(0x00);
    
    PutChar(0x03);
}

void sendConfig(void){

    int m;
    for (m = 4; m < 16; m++) {
    PutChar(startByte);
    PutChar(length_frame_3);    
    PutChar(m);
    PutChar(length_value);
    PutChar(value1);
    checksum = m+length_value+value1;
    PutChar(checksum);
    }
}

void InitUart(void){
    
    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
       PORTAbits.RA3 = 1; // If Led active error initializing UART
       while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
}