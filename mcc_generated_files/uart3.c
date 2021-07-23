/**
  FrontFaceUART Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart3.c

  @Summary
    This is the generated source file for the FrontFaceUART driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for FrontFaceUART. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ128GB204
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
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
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "xc.h"
#include "uart3.h"

/**
  Section: Data Type Definitions
*/

/** UART Driver Queue Status

  @Summary
    Defines the object required for the status of the queue.
*/

static uint8_t * volatile rxTail;
static uint8_t *rxHead;
static uint8_t *txTail;
static uint8_t * volatile txHead;
static bool volatile rxOverflowed;

/** UART Driver Queue Length

  @Summary
    Defines the length of the Transmit and Receive Buffers

*/

/* We add one extra byte than requested so that we don't have to have a separate
 * bit to determine the difference between buffer full and buffer empty, but
 * still be able to hold the amount of data requested by the user.  Empty is
 * when head == tail.  So full will result in head/tail being off by one due to
 * the extra byte.
 */
#define FrontFaceUART_CONFIG_TX_BYTEQ_LENGTH (8+1)
#define FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH (8+1)

/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

*/

static uint8_t txQueue[FrontFaceUART_CONFIG_TX_BYTEQ_LENGTH];
static uint8_t rxQueue[FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH];

void (*FrontFaceUART_TxDefaultInterruptHandler)(void);
void (*FrontFaceUART_RxDefaultInterruptHandler)(void);

/**
  Section: Driver Interface
*/

void FrontFaceUART_Initialize(void)
{
    IEC5bits.U3TXIE = 0;
    IEC5bits.U3RXIE = 0;

    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    U3MODE = (0x8008 & ~(1<<15));  // disabling UART ON bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U3STA = 0x00;
    // BaudRate = 115200; Frequency = 12000000 Hz; U3BRG 25; 
    U3BRG = 0x19;
    // ADMADDR 0; ADMMASK 0; 
    U3ADMD = 0x00;
    
    txHead = txQueue;
    txTail = txQueue;
    rxHead = rxQueue;
    rxTail = rxQueue;
   
    rxOverflowed = false;

    FrontFaceUART_SetTxInterruptHandler(&FrontFaceUART_Transmit_CallBack);

    FrontFaceUART_SetRxInterruptHandler(&FrontFaceUART_Receive_CallBack);

    IEC5bits.U3RXIE = 1;
    
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U3MODEbits.UARTEN = 1;   // enabling UART ON bit
    U3STAbits.UTXEN = 1;
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
*/

void FrontFaceUART_SetTxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler == NULL)
    {
        FrontFaceUART_TxDefaultInterruptHandler = &FrontFaceUART_Transmit_CallBack;
    }
    else
    {
        FrontFaceUART_TxDefaultInterruptHandler = interruptHandler;
    }
} 

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U3TXInterrupt ( void )
{
    (*FrontFaceUART_TxDefaultInterruptHandler)();

    if(txHead == txTail)
    {
        IEC5bits.U3TXIE = 0;
    }
    else
    {
        IFS5bits.U3TXIF = 0;

        while(!(U3STAbits.UTXBF == 1))
        {
            U3TXREG = *txHead++;

            if(txHead == (txQueue + FrontFaceUART_CONFIG_TX_BYTEQ_LENGTH))
            {
                txHead = txQueue;
            }

            // Are we empty?
            if(txHead == txTail)
            {
                break;
            }
        }
    }
}

void __attribute__ ((weak)) FrontFaceUART_Transmit_CallBack ( void )
{ 

}

void FrontFaceUART_SetRxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler == NULL)
    {
        FrontFaceUART_RxDefaultInterruptHandler = &FrontFaceUART_Receive_CallBack;
    }
    else
    {
        FrontFaceUART_RxDefaultInterruptHandler = interruptHandler;
    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U3RXInterrupt( void )
{
    (*FrontFaceUART_RxDefaultInterruptHandler)();

    IFS5bits.U3RXIF = 0;
	
    while((U3STAbits.URXDA == 1))
    {
        *rxTail = U3RXREG;

        // Will the increment not result in a wrap and not result in a pure collision?
        // This is most often condition so check first
        if ( ( rxTail    != (rxQueue + FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH-1)) &&
             ((rxTail+1) != rxHead) )
        {
            rxTail++;
        } 
        else if ( (rxTail == (rxQueue + FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH-1)) &&
                  (rxHead !=  rxQueue) )
        {
            // Pure wrap no collision
            rxTail = rxQueue;
        } 
        else // must be collision
        {
            rxOverflowed = true;
        }
    }
}

void __attribute__ ((weak)) FrontFaceUART_Receive_CallBack(void)
{
//    if (FrontFaceUART_IsRxReady() == 1) { 
//        rxChar = FrontFaceUART_Read();
//        static int i = 0;
//
//        rxBuffer[i] = rxChar;
//        i++;
//        if (rxChar == '\n') {
//            new_command = true;
//            i = 0;
//        }
//    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U3ErrInterrupt( void )
{
    if ((U3STAbits.OERR == 1))
    {
        U3STAbits.OERR = 0;
    }
    
    IFS5bits.U3ERIF = 0;
}

/**
  Section: UART Driver Client Routines
*/

uint8_t FrontFaceUART_Read( void)
{
    uint8_t data = 0;

    while (rxHead == rxTail )
    {
    }
    
    data = *rxHead;

    rxHead++;

    if (rxHead == (rxQueue + FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH))
    {
        rxHead = rxQueue;
    }
    return data;
}

void FrontFaceUART_Write( uint8_t byte)
{
    while(FrontFaceUART_IsTxReady() == 0)
    {
    }

    *txTail = byte;

    txTail++;
    
    if (txTail == (txQueue + FrontFaceUART_CONFIG_TX_BYTEQ_LENGTH))
    {
        txTail = txQueue;
    }

    IEC5bits.U3TXIE = 1;
}

bool FrontFaceUART_IsRxReady(void)
{    
    return !(rxHead == rxTail);
}

bool FrontFaceUART_IsTxReady(void)
{
    uint16_t size;
    uint8_t *snapshot_txHead = (uint8_t*)txHead;
    
    if (txTail < snapshot_txHead)
    {
        size = (snapshot_txHead - txTail - 1);
    }
    else
    {
        size = ( FrontFaceUART_CONFIG_TX_BYTEQ_LENGTH - (txTail - snapshot_txHead) - 1 );
    }
    
    return (size != 0);
}

bool FrontFaceUART_IsTxDone(void)
{
    if(txTail == txHead)
    {
        return (bool)U3STAbits.TRMT;
    }
    
    return false;
}


/*******************************************************************************

  !!! Deprecated API !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/

static uint8_t FrontFaceUART_RxDataAvailable(void)
{
    uint16_t size;
    uint8_t *snapshot_rxTail = (uint8_t*)rxTail;
    
    if (snapshot_rxTail < rxHead) 
    {
        size = ( FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH - (rxHead-snapshot_rxTail));
    }
    else
    {
        size = ( (snapshot_rxTail - rxHead));
    }
    
    if(size > 0xFF)
    {
        return 0xFF;
    }
    
    return size;
}

static uint8_t FrontFaceUART_TxDataAvailable(void)
{
    uint16_t size;
    uint8_t *snapshot_txHead = (uint8_t*)txHead;
    
    if (txTail < snapshot_txHead)
    {
        size = (snapshot_txHead - txTail - 1);
    }
    else
    {
        size = ( FrontFaceUART_CONFIG_TX_BYTEQ_LENGTH - (txTail - snapshot_txHead) - 1 );
    }
    
    if(size > 0xFF)
    {
        return 0xFF;
    }
    
    return size;
}

unsigned int __attribute__((deprecated)) FrontFaceUART_ReadBuffer( uint8_t *buffer ,  unsigned int numbytes)
{
    unsigned int rx_count = FrontFaceUART_RxDataAvailable();
    unsigned int i;
    
    if(numbytes < rx_count)
    {
        rx_count = numbytes;
    }
    
    for(i=0; i<rx_count; i++)
    {
        *buffer++ = FrontFaceUART_Read();
    }
    
    return rx_count;    
}

unsigned int __attribute__((deprecated)) FrontFaceUART_WriteBuffer( uint8_t *buffer , unsigned int numbytes )
{
    unsigned int tx_count = FrontFaceUART_TxDataAvailable();
    unsigned int i;
    
    if(numbytes < tx_count)
    {
        tx_count = numbytes;
    }
    
    for(i=0; i<tx_count; i++)
    {
        FrontFaceUART_Write(*buffer++);
    }
    
    return tx_count;  
}

FrontFaceUART_TRANSFER_STATUS __attribute__((deprecated)) FrontFaceUART_TransferStatusGet (void )
{
    FrontFaceUART_TRANSFER_STATUS status = 0;
    uint8_t rx_count = FrontFaceUART_RxDataAvailable();
    uint8_t tx_count = FrontFaceUART_TxDataAvailable();
    
    switch(rx_count)
    {
        case 0:
            status |= FrontFaceUART_TRANSFER_STATUS_RX_EMPTY;
            break;
        case FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH:
            status |= FrontFaceUART_TRANSFER_STATUS_RX_FULL;
            break;
        default:
            status |= FrontFaceUART_TRANSFER_STATUS_RX_DATA_PRESENT;
            break;
    }
    
    switch(tx_count)
    {
        case 0:
            status |= FrontFaceUART_TRANSFER_STATUS_TX_FULL;
            break;
        case FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH:
            status |= FrontFaceUART_TRANSFER_STATUS_TX_EMPTY;
            break;
        default:
            break;
    }

    return status;    
}

uint8_t __attribute__((deprecated)) FrontFaceUART_Peek(uint16_t offset)
{
    uint8_t *peek = rxHead + offset;
    
    while(peek > (rxQueue + FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH))
    {
        peek -= FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH;
    }
    
    return *peek;
}

bool __attribute__((deprecated)) FrontFaceUART_ReceiveBufferIsEmpty (void)
{
    return (FrontFaceUART_RxDataAvailable() == 0);
}

bool __attribute__((deprecated)) FrontFaceUART_TransmitBufferIsFull(void)
{
    return (FrontFaceUART_TxDataAvailable() == 0);
}

uint16_t __attribute__((deprecated)) FrontFaceUART_StatusGet (void)
{
    return U3STA;
}

unsigned int __attribute__((deprecated)) FrontFaceUART_TransmitBufferSizeGet(void)
{
    if(FrontFaceUART_TxDataAvailable() != 0)
    { 
        if(txHead > txTail)
        {
            return((txHead - txTail) - 1);
        }
        else
        {
            return((FrontFaceUART_CONFIG_TX_BYTEQ_LENGTH - (txTail - txHead)) - 1);
        }
    }
    return 0;
}

unsigned int __attribute__((deprecated)) FrontFaceUART_ReceiveBufferSizeGet(void)
{
    if(FrontFaceUART_RxDataAvailable() != 0)
    {
        if(rxHead > rxTail)
        {
            return((rxHead - rxTail) - 1);
        }
        else
        {
            return((FrontFaceUART_CONFIG_RX_BYTEQ_LENGTH - (rxTail - rxHead)) - 1);
        } 
    }
    return 0;
}

void __attribute__((deprecated)) FrontFaceUART_Enable(void)
{
    U3MODEbits.UARTEN = 1;
    U3STAbits.UTXEN = 1;
}

void __attribute__((deprecated)) FrontFaceUART_Disable(void)
{
    U3MODEbits.UARTEN = 0;
    U3STAbits.UTXEN = 0;
}
