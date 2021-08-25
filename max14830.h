/* 
 * File:   max14830.h
 * Author: root
 *
 * Created on 24 August 2021, 08:42
 */

#ifndef MAX14830_H
#define	MAX14830_H

#define MAX_UART0_WRITE         0xD8
#define MAX_UART0_READ          0xD9
#define MAX_UART1_WRITE         0xB8
#define MAX_UART1_READ          0xB9
#define MAX_UART2_WRITE         0x58
#define MAX_UART2_READ          0x59
#define MAX_UART3_WRITE         0x38
#define MAX_UART3_READ          0x39

#include "mcc_generated_files/i2c2.h"

#ifdef	__cplusplus
extern "C" {
#endif

void MAX_Initialize();


#ifdef	__cplusplus
}
#endif

#endif	/* MAX14830_H */

