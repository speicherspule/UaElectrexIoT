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
#define SAMPLEFREQ 1000 //Sample Frequency
#define SUCCESS 0
#define ERROR_FREQUENCY -1

void InitUart(void);
void SendData(void);
//void timer3_handler();
int8_t Timer3_Init(uint16_t);
void init_timer2(int);

unsigned char startByte = 0xAA;


unsigned char id27 = 0x1B;
unsigned char id28 = 0x1C;
unsigned char checksum = 0;


int main(int argc, char** argv) {
    TRISAbits.TRISA3 = 0; // Led4 as output
    PORTAbits.RA3 = 0; //Off Initial State Led4 
    
    InitUart();
    SendData(); 
            
    
}
void SendData(void){
    
    PutChar(startByte);
    PutChar(0x35);
    
    PutChar(0x01);
    PutChar(0x01);
    PutChar(0x00);
    
    PutChar(0x02);
    PutChar(0x01);
    PutChar(0x02);
    
    PutChar(0x03);
    PutChar(0x01);
    PutChar(0x01);
    
    uint16_t i;
    for (i = 4; i < 14; i++) {
        PutChar(i);
        PutChar(0x01);
        PutChar(0x01);
        checksum = checksum + i + 0x01 + 0x01;
    }

    PutChar(0x0E);
    PutChar(0x01);
    PutChar(0x01);
    
    PutChar(0x17);
    PutChar(0x01);
    PutChar(0x07);    

    PutChar(0x1B);
    PutChar(0x02);
    PutChar(0x01);
    PutChar(0xAA);

    PutChar(0x1C);
    PutChar(0x02);
    PutChar(0x01);
    PutChar(0xAA);
    
    checksum = checksum + 0x01 + 0x01 + 0x00 + 0x02 + 0x01 + 0x02 + 0x03 + 0x01 + 0x01 + 0x0E + 0x01 + 0x01 + 0x17 + 0x01 + 0x07 + 0x1B + 0x02 + 0x01 + 0xAA + 0x1C + 0x02 + 0x01 + 0xAA;
    PutChar(checksum);
    
}
void InitUart(void){
    
    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
       PORTAbits.RA3 = 1; // If Led active error initializing UART
       while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
}

int8_t Timer3_Init(uint16_t freq)
{
    // Set timer
    T3CONbits.ON = 0; // Stop timer
    IFS0bits.T3IF=0; // Reset interrupt flag
    IPC3bits.T3IP=5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration if interrupts are used ***
    IEC0bits.T3IE = 0; // Disable T3 interrupts
    // Timer period configuration
    T3CONbits.TCKPS = 0b111; //Divide by 16 pre-scaler
    T3CONbits.TCS = 0;
    //PR3=PBCLOCK/(freq*16); // Range 40MHz/16 = 2.56MHz; 2.56MHz/100Hz=25000; 2.56MHz/500Hz=5000)
    PR3=64000;
    //printf("Timer3_Init: PR3=%u\n\r",PBCLOCK/(freq*16));
    TMR3=0;
    IEC0bits.T3IE = 1; // Disable T3 interrupts
    T3CONbits.TON=1; // Start the timer
    return SUCCESS;
}   

void init_timer2(int frequency)
{
    T2CON   = 0x0;      // Disable timer 2 when setting it up
    TMR2    = 0;        // Set timer 2 counter to 0
    IEC0bits.T2IE = 0;  // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
    PR2 = SYSCLK / 2 / frequency / 32;

    // Set up the pre-scaler
    T2CONbits.TCKPS = 0b101; // Pre-scale of 8

    IFS0bits.T2IF = 0;  // Clear interrupt flag for timer 2
    IPC2bits.T2IP = 3;  // Interrupt priority 3
    IPC2bits.T2IS = 1;  // Sub-priority 1
    IEC0bits.T2IE = 1;  // Enable Timer 2 Interrupt

    // Turn on timer 2
    T2CONbits.TON   = 1;
}