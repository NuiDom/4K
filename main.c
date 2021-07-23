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
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/uart2.h"
#include "mcc_generated_files/uart3.h"
#include "mcc_generated_files/uart4.h"
#include "mcc_generated_files/i2c2.h"

#define SLAVE_I2C_GENERIC_RETRY_MAX           100
#define SLAVE_I2C_GENERIC_DEVICE_TIMEOUT      50   // define slave timeout 

void CREATE_BUFFER(uint16_t dataAddress, uint8_t data);

uint8_t writeBuffer[3];
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
//         #define MCHP24AA512_RETRY_MAX       100  // define the retry count
//            #define MCHP24AA512_ADDRESS         0x50 // slave device address
//            #define MCHP24AA512_DEVICE_TIMEOUT  50   // define slave timeout 
//
//
//            uint8_t MCHP24AA512_Read(
//                                            uint16_t address,
//                                            uint8_t *pData,
//                                            uint16_t nCount)
//            {
//                I2C2_MESSAGE_STATUS status;
//                uint8_t     writeBuffer[3];
//                uint16_t    retryTimeOut, slaveTimeOut;
//                uint16_t    counter;
//                uint8_t     *pD;
//
//                pD = pData;
//
//                for (counter = 0; counter < nCount; counter++)
//                {
//
//                    // build the write buffer first
//                    // starting address of the EEPROM memory
//                    writeBuffer[0] = (address >> 8);                // high address
//                    writeBuffer[1] = (uint8_t)(address);            // low low address
//
//                    // Now it is possible that the slave device will be slow.
//                    // As a work around on these slaves, the application can
//                    // retry sending the transaction
//                    retryTimeOut = 0;
//                    slaveTimeOut = 0;
//
//                    while(status != I2C2_MESSAGE_FAIL)
//                    {
//                        // write one byte to EEPROM (2 is the count of bytes to write)
//                        I2C2_MasterWrite(    writeBuffer,
//                                                2,
//                                                MCHP24AA512_ADDRESS,
//                                                &status);
//
//                        // wait for the message to be sent or status has changed.
//                        while(status == I2C2_MESSAGE_PENDING)
//                        {
//                            // add some delay here
//
//                            // timeout checking
//                            // check for max retry and skip this byte
//                            if (slaveTimeOut == MCHP24AA512_DEVICE_TIMEOUT)
//                                return (0);
//                            else
//                                slaveTimeOut++;
//                        }
//
//                        if (status == I2C2_MESSAGE_COMPLETE)
//                            break;
//
//                        // if status is  I2C2_MESSAGE_ADDRESS_NO_ACK,
//                        //               or I2C2_DATA_NO_ACK,
//                        // The device may be busy and needs more time for the last
//                        // write so we can retry writing the data, this is why we
//                        // use a while loop here
//
//                        // check for max retry and skip this byte
//                        if (retryTimeOut == MCHP24AA512_RETRY_MAX)
//                            break;
//                        else
//                            retryTimeOut++;
//                    }
//
//                    if (status == I2C2_MESSAGE_COMPLETE)
//                    {
//
//                        // this portion will read the byte from the memory location.
//                        retryTimeOut = 0;
//                        slaveTimeOut = 0;
//
//                        while(status != I2C2_MESSAGE_FAIL)
//                        {
//                            // write one byte to EEPROM (2 is the count of bytes to write)
//                            I2C2_MasterRead(     pD,
//                                                    1,
//                                                    MCHP24AA512_ADDRESS,
//                                                    &status);
//
//                            // wait for the message to be sent or status has changed.
//                            while(status == I2C2_MESSAGE_PENDING)
//                            {
//                                // add some delay here
//
//                                // timeout checking
//                                // check for max retry and skip this byte
//                                if (slaveTimeOut == MCHP24AA512_DEVICE_TIMEOUT)
//                                    return (0);
//                                else
//                                    slaveTimeOut++;
//                            }
//
//                            if (status == I2C2_MESSAGE_COMPLETE)
//                                break;
//
//                            // if status is  I2C2_MESSAGE_ADDRESS_NO_ACK,
//                            //               or I2C2_DATA_NO_ACK,
//                            // The device may be busy and needs more time for the last
//                            // write so we can retry writing the data, this is why we
//                            // use a while loop here
//
//                            // check for max retry and skip this byte
//                            if (retryTimeOut == MCHP24AA512_RETRY_MAX)
//                                break;
//                            else
//                                retryTimeOut++;
//                        }
//                    }
//
//                    // exit if the last transaction failed
//                    if (status == I2C2_MESSAGE_FAIL)
//                    {
//                        return(0);
//                        break;
//                    }
//
//                    pD++;
//                    address++;
//
//                }
//                return(1);
//
//            }
    CREATE_BUFFER(0xFF00, 0xA3);
    uint8_t *pData = &writeBuffer[0];
    uint8_t     *pD;
    uint8_t sendData = &pD;
    I2C2_MESSAGE_STATUS status;
    
    I2C2_MasterWrite(pData, 3, 0x50, &status);
    int x=0;
    for(x=0;x<4800;x++){int y=0; for(y=0;y<2000;y++){;}}
    I2C2_MasterWrite(pData, 2, 0x50, &status);
//    for(x=0;x<4800;x++){int y=0; for(y=0;y<2000;y++){;}}
    I2C2_MasterRead(pD, 0, 0x50, &status);
    
    for(x=0;x<4800;x++){int y=0; for(y=0;y<2000;y++){;}}
    I2C1CON1bits.SCLREL = 1; // release clock 
    CamUART_Write((uint8_t)pD);

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

