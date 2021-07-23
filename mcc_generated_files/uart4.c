/**
  FTDIUART Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart4.c

  @Summary
    This is the generated source file for the FTDIUART driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for FTDIUART. 
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
#include "uart4.h"

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
#define FTDIUART_CONFIG_TX_BYTEQ_LENGTH (8+1)
#define FTDIUART_CONFIG_RX_BYTEQ_LENGTH (8+1)

/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

*/

static uint8_t txQueue[FTDIUART_CONFIG_TX_BYTEQ_LENGTH];
static uint8_t rxQueue[FTDIUART_CONFIG_RX_BYTEQ_LENGTH];

void (*FTDIUART_TxDefaultInterruptHandler)(void);
void (*FTDIUART_RxDefaultInterruptHandler)(void);

/**
  Section: Driver Interface
*/

void FTDIUART_Initialize(void)
{
    IEC5bits.U4TXIE = 0;
    IEC5bits.U4RXIE = 0;

    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    U4MODE = (0x8008 & ~(1<<15));  // disabling UART ON bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U4STA = 0x00;
    // BaudRate = 115200; Frequency = 12000000 Hz; U4BRG 25; 
    U4BRG = 0x19;
    // ADMADDR 0; ADMMASK 0; 
    U4ADMD = 0x00;
    
    txHead = txQueue;
    txTail = txQueue;
    rxHead = rxQueue;
    rxTail = rxQueue;
   
    rxOverflowed = false;

    FTDIUART_SetTxInterruptHandler(&FTDIUART_Transmit_CallBack);

    FTDIUART_SetRxInterruptHandler(&FTDIUART_Receive_CallBack);

    IEC5bits.U4RXIE = 1;
    
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U4MODEbits.UARTEN = 1;   // enabling UART ON bit
    U4STAbits.UTXEN = 1;
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
*/

void FTDIUART_SetTxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler == NULL)
    {
        FTDIUART_TxDefaultInterruptHandler = &FTDIUART_Transmit_CallBack;
    }
    else
    {
        FTDIUART_TxDefaultInterruptHandler = interruptHandler;
    }
} 

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U4TXInterrupt ( void )
{
    (*FTDIUART_TxDefaultInterruptHandler)();

    if(txHead == txTail)
    {
        IEC5bits.U4TXIE = 0;
    }
    else
    {
        IFS5bits.U4TXIF = 0;

        while(!(U4STAbits.UTXBF == 1))
        {
            U4TXREG = *txHead++;

            if(txHead == (txQueue + FTDIUART_CONFIG_TX_BYTEQ_LENGTH))
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

void __attribute__ ((weak)) FTDIUART_Transmit_CallBack ( void )
{ 

}

void FTDIUART_SetRxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler == NULL)
    {
        FTDIUART_RxDefaultInterruptHandler = &FTDIUART_Receive_CallBack;
    }
    else
    {
        FTDIUART_RxDefaultInterruptHandler = interruptHandler;
    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U4RXInterrupt( void )
{
    (*FTDIUART_RxDefaultInterruptHandler)();

    IFS5bits.U4RXIF = 0;
	
    while((U4STAbits.URXDA == 1))
    {
        *rxTail = U4RXREG;

        // Will the increment not result in a wrap and not result in a pure collision?
        // This is most often condition so check first
        if ( ( rxTail    != (rxQueue + FTDIUART_CONFIG_RX_BYTEQ_LENGTH-1)) &&
             ((rxTail+1) != rxHead) )
        {
            rxTail++;
        } 
        else if ( (rxTail == (rxQueue + FTDIUART_CONFIG_RX_BYTEQ_LENGTH-1)) &&
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

void __attribute__ ((weak)) FTDIUART_Receive_CallBack(void)
{
//    if (FTDIUART_IsRxReady() == 1) { 
//        rxChar = FTDIUART_Read();
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

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U4ErrInterrupt( void )
{
    if ((U4STAbits.OERR == 1))
    {
        U4STAbits.OERR = 0;
    }
    
    IFS5bits.U4ERIF = 0;
}

/**
  Section: UART Driver Client Routines
*/

uint8_t FTDIUART_Read( void)
{
    uint8_t data = 0;

    while (rxHead == rxTail )
    {
    }
    
    data = *rxHead;

    rxHead++;

    if (rxHead == (rxQueue + FTDIUART_CONFIG_RX_BYTEQ_LENGTH))
    {
        rxHead = rxQueue;
    }
    return data;
}

void FTDIUART_Write( uint8_t byte)
{
    while(FTDIUART_IsTxReady() == 0)
    {
    }

    *txTail = byte;

    txTail++;
    
    if (txTail == (txQueue + FTDIUART_CONFIG_TX_BYTEQ_LENGTH))
    {
        txTail = txQueue;
    }

    IEC5bits.U4TXIE = 1;
}

bool FTDIUART_IsRxReady(void)
{    
    return !(rxHead == rxTail);
}

bool FTDIUART_IsTxReady(void)
{
    uint16_t size;
    uint8_t *snapshot_txHead = (uint8_t*)txHead;
    
    if (txTail < snapshot_txHead)
    {
        size = (snapshot_txHead - txTail - 1);
    }
    else
    {
        size = ( FTDIUART_CONFIG_TX_BYTEQ_LENGTH - (txTail - snapshot_txHead) - 1 );
    }
    
    return (size != 0);
}

bool FTDIUART_IsTxDone(void)
{
    if(txTail == txHead)
    {
        return (bool)U4STAbits.TRMT;
    }
    
    return false;
}


/*******************************************************************************

  !!! Deprecated API !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/

static uint8_t FTDIUART_RxDataAvailable(void)
{
    uint16_t size;
    uint8_t *snapshot_rxTail = (uint8_t*)rxTail;
    
    if (snapshot_rxTail < rxHead) 
    {
        size = ( FTDIUART_CONFIG_RX_BYTEQ_LENGTH - (rxHead-snapshot_rxTail));
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

static uint8_t FTDIUART_TxDataAvailable(void)
{
    uint16_t size;
    uint8_t *snapshot_txHead = (uint8_t*)txHead;
    
    if (txTail < snapshot_txHead)
    {
        size = (snapshot_txHead - txTail - 1);
    }
    else
    {
        size = ( FTDIUART_CONFIG_TX_BYTEQ_LENGTH - (txTail - snapshot_txHead) - 1 );
    }
    
    if(size > 0xFF)
    {
        return 0xFF;
    }
    
    return size;
}

unsigned int __attribute__((deprecated)) FTDIUART_ReadBuffer( uint8_t *buffer ,  unsigned int numbytes)
{
    unsigned int rx_count = FTDIUART_RxDataAvailable();
    unsigned int i;
    
    if(numbytes < rx_count)
    {
        rx_count = numbytes;
    }
    
    for(i=0; i<rx_count; i++)
    {
        *buffer++ = FTDIUART_Read();
    }
    
    return rx_count;    
}

unsigned int __attribute__((deprecated)) FTDIUART_WriteBuffer( uint8_t *buffer , unsigned int numbytes )
{
    unsigned int tx_count = FTDIUART_TxDataAvailable();
    unsigned int i;
    
    if(numbytes < tx_count)
    {
        tx_count = numbytes;
    }
    
    for(i=0; i<tx_count; i++)
    {
        FTDIUART_Write(*buffer++);
    }
    
    return tx_count;  
}

FTDIUART_TRANSFER_STATUS __attribute__((deprecated)) FTDIUART_TransferStatusGet (void )
{
    FTDIUART_TRANSFER_STATUS status = 0;
    uint8_t rx_count = FTDIUART_RxDataAvailable();
    uint8_t tx_count = FTDIUART_TxDataAvailable();
    
    switch(rx_count)
    {
        case 0:
            status |= FTDIUART_TRANSFER_STATUS_RX_EMPTY;
            break;
        case FTDIUART_CONFIG_RX_BYTEQ_LENGTH:
            status |= FTDIUART_TRANSFER_STATUS_RX_FULL;
            break;
        default:
            status |= FTDIUART_TRANSFER_STATUS_RX_DATA_PRESENT;
            break;
    }
    
    switch(tx_count)
    {
        case 0:
            status |= FTDIUART_TRANSFER_STATUS_TX_FULL;
            break;
        case FTDIUART_CONFIG_RX_BYTEQ_LENGTH:
            status |= FTDIUART_TRANSFER_STATUS_TX_EMPTY;
            break;
        default:
            break;
    }

    return status;    
}

uint8_t __attribute__((deprecated)) FTDIUART_Peek(uint16_t offset)
{
    uint8_t *peek = rxHead + offset;
    
    while(peek > (rxQueue + FTDIUART_CONFIG_RX_BYTEQ_LENGTH))
    {
        peek -= FTDIUART_CONFIG_RX_BYTEQ_LENGTH;
    }
    
    return *peek;
}

bool __attribute__((deprecated)) FTDIUART_ReceiveBufferIsEmpty (void)
{
    return (FTDIUART_RxDataAvailable() == 0);
}

bool __attribute__((deprecated)) FTDIUART_TransmitBufferIsFull(void)
{
    return (FTDIUART_TxDataAvailable() == 0);
}

uint16_t __attribute__((deprecated)) FTDIUART_StatusGet (void)
{
    return U4STA;
}

unsigned int __attribute__((deprecated)) FTDIUART_TransmitBufferSizeGet(void)
{
    if(FTDIUART_TxDataAvailable() != 0)
    { 
        if(txHead > txTail)
        {
            return((txHead - txTail) - 1);
        }
        else
        {
            return((FTDIUART_CONFIG_TX_BYTEQ_LENGTH - (txTail - txHead)) - 1);
        }
    }
    return 0;
}

unsigned int __attribute__((deprecated)) FTDIUART_ReceiveBufferSizeGet(void)
{
    if(FTDIUART_RxDataAvailable() != 0)
    {
        if(rxHead > rxTail)
        {
            return((rxHead - rxTail) - 1);
        }
        else
        {
            return((FTDIUART_CONFIG_RX_BYTEQ_LENGTH - (rxTail - rxHead)) - 1);
        } 
    }
    return 0;
}

void __attribute__((deprecated)) FTDIUART_Enable(void)
{
    U4MODEbits.UARTEN = 1;
    U4STAbits.UTXEN = 1;
}

void __attribute__((deprecated)) FTDIUART_Disable(void)
{
    U4MODEbits.UARTEN = 0;
    U4STAbits.UTXEN = 0;
}
