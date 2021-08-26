#include "max14830.h"

void CLK_CONFIG_Init(uint8_t UART);
void UARTS_Mode_Init(uint8_t UART);
void GPIO_Init();

void MAX_Init()
{
    int x=0;
    CLK_CONFIG_Init(MAX_UART0_WRITE);
    CLK_CONFIG_Init(MAX_UART1_WRITE);
    CLK_CONFIG_Init(MAX_UART2_WRITE);
    CLK_CONFIG_Init(MAX_UART3_WRITE);
    
    UARTS_Mode_Init(MAX_UART0_WRITE);
    UARTS_Mode_Init(MAX_UART1_WRITE);
    UARTS_Mode_Init(MAX_UART2_WRITE);
    UARTS_Mode_Init(MAX_UART3_WRITE);
    
    GPIO_Init();
            
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
}

void CLK_CONFIG_Init(uint8_t UART)
{
    maxWriteByte(MAX_UART0_WRITE, MAX14830_PLLCONFIG , 0x01);       //PreDIV0=1
    int x=0;
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(UART, MAX14830_BRGCONFIG, 0x00);         
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(UART, MAX14830_DIVLSB, 0x02);                      //Div1=1
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(UART, MAX14830_DIVMSB, 0x00);           
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(MAX_UART0_WRITE, MAX14830_CLKSOURCE, 0x0A);        //PLLBypass=1, CrystalEn=1
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}

}

void UARTS_Mode_Init(uint8_t UART)
{
    maxWriteByte(MAX_UART0_WRITE, MAX14830_MODE1 , 0x00);
    int x=0;
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
//    maxWriteByte(MAX_UART0_WRITE, MAX14830_MODE2 , 0x02);
//    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
//    maxWriteByte(MAX_UART0_WRITE, MAX14830_MODE2 , 0x00);
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(UART, MAX14830_LCR , 0x03);                        //LCR setup 8 bit word, 1 stop bit, no parity
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}             //StopBits=1, Length0=1
//    maxWriteByte(MAX_UART0_WRITE, MAX14830_RXTIMEOUT , 0x00);
//    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
//    maxWriteByte(MAX_UART0_WRITE, MAX14830_HDPLXDELAY , 0x00);
//    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
//    maxWriteByte(MAX_UART0_WRITE, MAX14830_IRDA , 0x00);
//    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}

}

void GPIO_Init()
{
    maxWriteByte(MAX_UART1_WRITE, MAX14830_GPIOCONFG, 0x08);
}