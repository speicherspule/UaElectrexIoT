/* 
 * File:   main.c
 * Author: pedro
 *
 * Created on 7 de Maio de 2020, 15:20
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
#define SUCCESS 0
#define ERROR_FREQUENCY -1

/*
 * 
 */
void sortAndStore(uint16_t);
void printAll(void);
void InitUart(void);
void SendData(void);
int8_t Timer3_Init(void);
int8_t Timer2_Init(void);
uint32_t GetTime(void);


unsigned char startByte = 0xAA;
unsigned char frame_length = 0x08;
unsigned char value_length_1 = 0x01;
unsigned char value_length_2 = 0x02;
unsigned char id27 = 0x1B;
unsigned char id28 = 0x1C;
unsigned char checksum = 0;
unsigned char value[] = {0x03,0xE7};
unsigned char ack; 

uint16_t data[21] = {0};
uint16_t missedPackets = 0;
uint16_t timer = 0;
uint16_t count = 0,mean =0 ; 
uint32_t sum = 0;
uint8_t max=25,min=5;

int main(int argc, char** argv) {
    
    TRISAbits.TRISA3 = 0; // Led4 as output
    PORTAbits.RA3 = 0; //Off Initial State Led4
  
    InitUart();
    Timer3_Init();
    Timer2_Init();

    int c;
    //while(1){
        
        int i,j=0;
        missedPackets = 0;
        
        for (i = 0; i < 250000; i++) {
        
        while ((GetChar(&ack) == UART_SUCCESS));
     
        ack = 0;
        TMR3 = 0x00;
        IFS0bits.T3IF=0; // Reset interrupt flag
        SendData();
        
        while ((GetChar(&ack) != UART_SUCCESS)){
            if(IFS0bits.T3IF == 1){
                ack = 0;
                break;
            }      
        }
        
        if(ack == 0xAC){
            timer = TMR3;
            sortAndStore(timer);
        }
        
        else{
            missedPackets++;
            int n;
            
            for (n = 0; n < 4; n++) {              
                while(IFS0bits.T3IF == 0);
                IFS0bits.T3IF=0; // Reset interrupt flag
            }
        }

        while(IFS0bits.T2IF == 0);
        IFS0bits.T2IF=0; // Reset interrupt flag

        }
        
        printAll();
        

    //}
return (EXIT_SUCCESS);
}

void sortAndStore(uint16_t timer){
    
    timer = ((timer * 256) / 40000);
    
    count = count + 1;
    sum = sum + timer; 
    
    if(timer <= 5){
        
        if(timer < min){
            min = timer;           
        }

        data[0]++; 
    }
    
    if(timer > 5 && timer <= 6){
        data[1]++; 
    }   
    
    if(timer > 6 && timer <= 7){
        data[2]++; 
    }      
    
    if(timer > 7 && timer <= 8){
        data[3]++; 
    }
    if(timer > 8 && timer <= 9){
        data[4]++; 
    }
    if(timer > 9 && timer <= 10){
        data[5]++; 
    }
    
    if(timer > 10 && timer <= 11){
        data[6]++; 
    }
    if(timer > 11 && timer <= 12){
        data[7]++; 
    }
    if(timer > 12 && timer <= 13){
        data[8]++; 
    }
    
    if(timer > 13 && timer <= 14){
        data[9]++; 
    }
    
    if(timer > 14 && timer <= 15){
        data[10]++; 
    } 
    
    if(timer > 15 && timer <= 16){
        data[11]++; 
    }
    
     if(timer > 16 && timer <= 17){
        data[12]++; 
    } 
    
    if(timer > 17 && timer <= 18){
        data[13]++; 
    }
    
    if(timer > 18 && timer <= 19){
        data[14]++; 
    }
    
    if(timer > 19 && timer <= 20){
        data[15]++; 
    }
    
    if(timer > 20 && timer <= 21){
        data[16]++; 
    }
    
    if(timer >  21 && timer <= 22){
        data[17]++; 
    }

    if(timer > 22 && timer <= 23){
        data[18]++; 
    }
    
    if(timer > 23 && timer <= 24){
        data[19]++; 
    }
    
    if(timer > 24 && timer <= 25){
        data[20]++; 
    }
    if(timer > 25){
        data[21]++;
        
        if(timer > max){
            max = timer;           
        }        
    }     
    
}
void printAll(void){
    int k;
    for (k = 0; k < 22; k++) {
        printf("%i \n",data[k]);
    }
    mean = sum/count;
    
    printf("Missed packets %i \n",missedPackets);
    printf("Mean %i \n",mean);
    printf("Max %i \n",max);
    printf("Min %i \n",min);
    
}
void SendData(void){
    
    unsigned char startByte = 0xAA;
    unsigned char frame_length = 0x08;
    unsigned char value_length_1 = 0x01;
    unsigned char value_length_2 = 0x02;

    unsigned char id27 = 0x1B;
    unsigned char id28 = 0x1C;


    PutChar(startByte);
    PutChar(frame_length);
    
    PutChar(id27);
    PutChar(value_length_2);
    PutChar(value[0]);
    PutChar(value[1]);
    
    PutChar(id28);
    PutChar(value_length_2);
    PutChar(value[0]);
    PutChar(value[1]);

    
    checksum = (id27 + value_length_2 + value[0] + value[1] + id28 + value_length_2 + value[0] + value[1]);  
    PutChar(checksum);
    //printf("%u",checksum);
}

void InitUart(void){
    
    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
       PORTAbits.RA3 = 1; // If Led active error initializing UART
       while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
}

int8_t Timer3_Init(void)
{
    // Set timer
    T3CONbits.TON = 0; // Start the timer
    
    IFS0bits.T3IF=0; // Reset interrupt flag
    IEC0bits.T3IE = 1; // Disable T3 interrupts
    
    // Timer period configuration

    T3CONbits.TCKPS = 7; //Divide by 256 pre-scaler
    T3CONbits.TCS = 0;
    
    PR3=0xFFFF;
    TMR3=0;
    
    T3CONbits.TON=1; // Start the timer

    
    return SUCCESS;
} 

int8_t Timer2_Init(void)
{
    // Set timer
    T2CONbits.TON= 0; // Stop the timer
    
    IFS0bits.T2IF=0; // Reset interrupt flag
    IEC0bits.T2IE = 1; // Disable T3 interrupts
    
    // Timer period configuration
    T2CONbits.T32 = 0; // 16 bit timer operation
    T2CONbits.TCKPS = 7; //Divide by 256 pre-scaler
    T2CONbits.TCS = 0;
    
    PR2 = 312; // 500hz - 1ms
    // PR2=7812; // 20hz - 50ms
    TMR2=0; 
    
    T2CONbits.TON = 1;		// enable timer   

    return SUCCESS;

}  

uint32_t GetTime(void){
    return TMR3;
}



