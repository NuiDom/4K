/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ128GB204
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart.h"
#include "mcc_generated_files/i2c2.h"

#define SLAVE_I2C_GENERIC_RETRY_MAX           100
#define SLAVE_I2C_GENERIC_DEVICE_TIMEOUT      50   // define slave timeout 

#define MAX_UART0_WRITE     0xD8
#define MAX_UART0_READ      0xD9
#define MAX_UART1_WRITE     0xB8
#define MAX_UART1_READ      0xB9
#define MAX_UART2_WRITE     0x58
#define MAX_UART2_READ      0x59
#define MAX_UART3_WRITE     0x38
#define MAX_UART3_READ      0x39

#define MAX_PLL_CONFIG_REG  0x1A
#define MAX_BRG_CONFIG_REG  0x1B
#define MAX_DIVLSB_REG      0x1C
#define MAX_DIVMSB_REG     0x1D
#define MAX_CLK_SOURCE_REG  0x1E

void CREATE_BUFFER(uint16_t dataAddress, uint8_t data);
void MAX_Initialize();

uint8_t writeBuffer[3];
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    MAX_Initialize();
    
    int x=0;
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(MAX_UART0_WRITE, 0x10, 0xFF);
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    int y=0;
    for(y=0; y<=130;y++){
    maxWriteByte(MAX_UART0_WRITE, 0x00, 0x41);
    for(x=0;x<500;x++){int y=0; for(y=0;y<500;y++){;}}
    }
//    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
//    maxReadByte(MAX_UART0_WRITE, MAX_UART0_READ, 0x09);
//    CamUART_Write('d');
    while (1)
    {
//        CamUART_Write('d');
    }
    
    return 1;
}

void CREATE_BUFFER(uint16_t dataAddress, uint8_t data)
{
    
    
    
    writeBuffer[0] = (dataAddress >> 8);                // high address
    writeBuffer[1] = (uint8_t)(dataAddress);            // low low address
    
        // data to be written
    writeBuffer[2] = data;
    
}

/**
 End of File
*/

void MAX_Initialize()
{
    maxWriteByte(MAX_UART0_WRITE, MAX_PLL_CONFIG_REG, 0x01);        //set MAX PllConfig reg
    int x=0;
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(MAX_UART0_WRITE, MAX_BRG_CONFIG_REG, 0x00);        //set MAX BEGConfig reg
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(MAX_UART0_WRITE, MAX_DIVLSB_REG, 0x02);        //set MAX 
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(MAX_UART0_WRITE, MAX_DIVMSB_REG, 0x00);        //set MAX 
    for(x=0;x<1000;x++){int y=0; for(y=0;y<500;y++){;}}
    maxWriteByte(MAX_UART0_WRITE, MAX_CLK_SOURCE_REG, 0x08);        //set MAX CLKSource reg
}