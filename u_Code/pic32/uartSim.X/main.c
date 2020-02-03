/* 
 * File:   main.c
 * Author: pedroluzeiro
 *
 * Created on January 10, 2020, 11:14 AM
 * 
 * Sends in loop a hard-coded demo frame 
 * calculate checksum and compares it to the received checksum
 * FRAME:
 * START BYTE | LENGTH | ID | LENGTH | VALUE | ID | lENGTH |    VALUE   | CHECKSUM
 * 0xAA         7        27     2      0x3E7   28      1     0X00 - 0xFF      
 */

//Includes
#include "../CommonFiles/ConfigBits/config_bits.h" // NOTE!! Must precede project file includes
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "../CommonFiles/Uart/uart.h" // NOTE!! Must precede project file includes

/*
 * DeFINES 
 */
#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz
#define SAMPLEFREQ 100 //Sample Frequency
#define SUCCESS 0
#define ERROR_FREQUENCY -1
/*
 Prototypes
 */
void InitUart(void);
int8_t Timer3_Init(uint16_t freq);

int i = 0;
unsigned char startByte = 0xAA;
unsigned char length_frame = 7;

uint8_t id27 = 27;
uint8_t id28 = 28;
uint8_t length_value = 1;
uint8_t length_value_2 = 2;
uint16_t value27 = 0;
uint16_t value28 = 255;
uint8_t checksum,ack;
uint8_t data[] = {0x03,0xE7};

int main(int argc, char** argv) {
        
    TRISAbits.TRISA3 = 0; // Led 4 as output
    TRISCbits.TRISC1 = 0; // LED 5 as output
        
    Timer3_Init(SAMPLEFREQ); //Start Timer3
    InitUart();     //Start Uart
    int i = 0;
    
    
    while(1){
        
        int o;
        
        for (o = 0; o < 2; o++) {             
            while(IFS0bits.T3IF==0);        // Wait for timer interrupt flag
            IFS0bits.T3IF=0;                //Clears timer flag
        }
        

        PutChar(startByte);
        PutChar(length_frame);
        
        /*
        PutChar(id27);
        PutChar(length_value);
        PutChar(value27);
        */
        
        PutChar(id27);
        PutChar(length_value_2);
        PutChar(data[0]);
        PutChar(data[1]);
        
        PutChar(id28);
        PutChar(length_value);
        PutChar(value28);
        
        //checksum = id27+length_value+value27+id28+length_value+value28;
        checksum = id27+length_value_2+data[0]+data[1]+id28+length_value+value28;
        PutChar(checksum);
               
        if(i == 0){
            value27++;
            value28--;
            if(value27 == 255)
            {
                i=1;
            }
        }
        else{
            value27--;
            value28++;
            if(value27 == 0){
                i=0;
            }
        }
        
        
        
             
       
        while ( GetChar(&ack) != UART_SUCCESS );   //Receive ACK byte
        
        if(ack != 0xAB){       //Wrong ACK byte
                                    //Sends again (not implemented)
            //LEDS to debug
             PORTCbits.RC1 = 1;     
             PORTAbits.RA3 = 0; 
             
        }
        else{                       //Correct ACK byte
                                    //Sends next frame
            //LEDS to debug
            PORTAbits.RA3 = 1;
            PORTCbits.RC1 = 0;
        }
              
        
    }
    return (EXIT_SUCCESS);
}

void  InitUart(void){
    
    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
       PORTAbits.RA3 = 1; // If Led active error initializing UART
       while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
}

int8_t Timer3_Init(uint16_t freq)
{
    if(freq < 100 || freq > 500)
        return ERROR_FREQUENCY;
    // Set timer
    T3CONbits.ON = 0; // Stop timer
    IFS0bits.T3IF=0; // Reset interrupt flag
    IPC3bits.T3IP=5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration if interrupts are used ***
    IEC0bits.T3IE = 0; // Disable T3 interrupts
    // Timer period configuration
    T3CONbits.TCKPS = 4; //Divide by 16 pre-scaler
    PR3=PBCLOCK/(freq*16); // Range 40MHz/16 = 2.56MHz; 2.56MHz/100Hz=25000; 2.56MHz/500Hz=5000)
    printf("Timer3_Init: PR3=%u\n\r",PBCLOCK/(freq*16));
    TMR3=0;
    
    T3CONbits.TON=1; // Start the timer
    return SUCCESS;
}   