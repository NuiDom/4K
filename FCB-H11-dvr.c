////
////	Module	 	:
////
////	Description :
////
////	Inputs		:
////
////	Returns		:
////
////	Rev 1.0	Date: / /14 - Inital Release
////
////	Notes		:	1) 	For commands we currectly do not the complete contect of the reply.
////						We check for ACK and CMD_COMPLETE.
//////---------------------------------------------------------------------------------------//
//#include "USART.h"
#include "FCB-H11-dvr.h"
//#include "AshDefines.h"
////#include "SystemTiming.h"
#include <string.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart.h"
#include "timer.h"
//#include "Debug.h"
//#include "DebugUart.h"
//#include "FPGA.h"
//#include "RTC.h"
////#include "AD9889b.h"
//#include "Sound.h"
#include <stdio.h>
#include <ctype.h>
//#include "USB3_Interface.h"
//
//
//uint8_t	un8CameraMirrorLR(void);
//uint8_t	un8CameraUnMirrorLR(void);
//
//uint8_t	un8CameraSetResolutionHD25(void);
//uint8_t	un8CameraSetResolutionHD30(void);
//uint8_t	un8OSDOn(void);
//uint8_t	un8OSDOff(void);
//
//extern struct 	System SystemVars;
//#define CAMERA_RESPONCE_TIMEOUT 5000000
//
//void	DebugPrintHex(uint8_t *un8String,uint8_t un8Termination);
//
//// Public Vars
//char 		szCameraResponse[CAMERA_UART_BUFFER_SIZE] = {'\0'};
//uint8_t		un8CameraResponseReceived=FALSE;
//uint16_t 	un16CameraUSARTCharCount=0;
//
//// Public Vars
//char 		szUSB3Response[USB3_UART_BUFFER_SIZE] = {'\0'};
//uint8_t		un8USB3ResponseReceived=FALSE;
//uint16_t 	un16USB3USARTCharCount=0;
//
//// 	USART IRQ
////	Each time a Char is Received this function is called and USART Status Register has the USART3->SR & USART_FLAG_RXNE
//void 	USART1_IRQHandler(void)
//{
//uint8_t	u8CharRecieved;
//
//    if (U1STAbits.URXDA !=0)
//	{
//    	u8CharRecieved = CamUART_Read();
//
//		szCameraResponse[un16CameraUSARTCharCount] 	= u8CharRecieved;
//    	szCameraResponse[un16CameraUSARTCharCount+1] 	= '\0';
//
//    	un16CameraUSARTCharCount++;
//    	if(un16CameraUSARTCharCount>=CAMERA_UART_BUFFER_SIZE) // OverRun!!!
//	    	un16CameraUSARTCharCount=0;
//
//    		// Camera uses 0xFF as terminator string
//    	if( u8CharRecieved== 0xFF )
//    	    un8CameraResponseReceived=TRUE;
//    	    
//
//	}
//}
//
//void	USB3BufferReset(void)
//{
//uint8_t	un8Loop;
//
//		un8USB3ResponseReceived=FALSE;
//    	un16USB3USARTCharCount=0;
//
//    	for(un8Loop=0;un8Loop<100;un8Loop++)
//    		szUSB3Response[un8Loop]='L';
//}
//
//void	CameraBufferReset(void)
//{
//uint8_t	un8Loop;
//
//		un8CameraResponseReceived=FALSE;
//    	un16CameraUSARTCharCount=0;
//
//    	for(un8Loop=0;un8Loop<100;un8Loop++)
//    		szCameraResponse[un8Loop]='L';
//}
//
void CamUARTWriteString(char *szString)
{
int     nCurrentChar=0;
char	cChar;

        for(nCurrentChar=0;nCurrentChar<20;nCurrentChar++)
        	{
        	cChar=szString[nCurrentChar];
          	CamUART_Write(cChar);
          	// Loop until the end of transmission
          	while(U1STAbits.TRMT==0);
            if((uint8_t)cChar==0xFF) break;
          	
          	}
}
//
//
//uint8_t	un8CameraStopFocus(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x08;
//		szComString[4]=0x00;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){		// Check for ACK
//			SelectUSB3UART();
//			return(un8Status);
//			DebugWriteString("\r\nERROR ACK - un8CameraStopFocus(void)");
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD un8CameraStopFocus(void):");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraStartTeleFocus(uint8_t un8FocusSpeed)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x08;
//		szComString[4]=0x20+un8FocusSpeed;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){				// Check for ACK
//			SelectUSB3UART();
//			DebugWriteString("\r\nERROR ACK - un8CameraTeleFocus(void)");
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD un8CameraTeleFocus(void)");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraStartWideFocus(uint8_t un8FocusSpeed)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x08;
//		szComString[4]=0x30+un8FocusSpeed;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){				// Check for ACK
//			SelectUSB3UART();
//			DebugWriteString("\r\nERROR ACK un8CameraWideFocus(void)");
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)	{		// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD un8CameraWideFocus(void)");
//			DebugPrintCameraHex(szReadString,0xFF);
//				return(un8Status);
//				}
//
//		return(CAMERA_READ_OK);
//}
//
//
////---------------------------------------------------------------------------------------//
////
////	Function 	:
////
////	Description :
////
////	Inputs		:
////
////
////	Returns		:
////
////	Rev 1.0	Date: / /14 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t	un8CameraAddressSet(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//
//		// Fill the command string
//		szComString[0]=0x88;
//		szComString[1]=0x30;
//		szComString[2]=0x01;
//		szComString[3]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)				// Check for Broadcast Return
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//
//}
////---------------------------------------------------------------------------------------//
////
////	Function 	:
////
////	Description :
////
////	Inputs		:
////
////
////	Returns		:
////
////	Rev 1.0	Date: / /14 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t	un8CameraIFClear(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		// Fill the command string
//		szComString[0]=0x88;
//		szComString[1]=0x01;
//		szComString[2]=0x00;
//		szComString[3]=0x01;
//		szComString[4]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_BROADCAST_CMD_RETURN)				// Check for Broadcast Return
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//
//}
//
//
//uint8_t	un8CameraFlipLR(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x66;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		un8CameraMirrorLR();
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_BROADCAST_CMD_RETURN)				// Check for Broadcast Return
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//
//}
//
//uint8_t	un8CameraUnFlipLR(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x66;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		un8CameraUnMirrorLR();
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_BROADCAST_CMD_RETURN)				// Check for Broadcast Return
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//
//}
//
//uint8_t	un8CameraMirrorLR(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x61;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_BROADCAST_CMD_RETURN)				// Check for Broadcast Return
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//
//}
//
//uint8_t	un8CameraUnMirrorLR(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x61;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_BROADCAST_CMD_RETURN)				// Check for Broadcast Return
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//
//}
//
////---------------------------------------------------------------------------------------//
////
////	Function 	:
////
////	Description :
////
////	Inputs		:
////
////
////	Returns		:
////
////	Rev 1.0	Date: / /14 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t	un8CameraPowerOn(void)
//{
//char	szComString[20];
//char	szReadString[20];
//uint8_t un8Status;
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x00;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
////---------------------------------------------------------------------------------------//
////
////	Function 	:
////
////	Description :
////
////	Inputs		:
////
////
////	Returns		:
////
////	Rev 1.0	Date: / /14 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t un8CameraPowerOff(void)
//{
//char	szComString[20];
//char	szReadString[20];
//uint8_t un8Status;
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x00;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//
//}
////---------------------------------------------------------------------------------------//
////
////	Function 	: CameraRecallMemSetting
////
////	Description :
////
////	Inputs		: None
////
////	Returns		: Void
////
////	Rev 1.0	Date: 26/11/13 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t	un8CameraRecallMemSetting (uint8_t un8Memory)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3F;
//		szComString[4]=0x02;
//		szComString[5]=un8Memory;
//		szComString[6]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){		// Check for ACK
//			SelectUSB3UART();
//			return(un8Status);
//			DebugWriteString("\r\nERROR ACK - un8CameraRecallMemSetting");
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD - un8CameraRecallMemSetting");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//
//}
//uint8_t	un8CameraSaveMemSetting (uint8_t un8Memory)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3F;
//		szComString[4]=0x01;
//		szComString[5]=un8Memory;
//		szComString[6]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){		// Check for ACK
//			SelectUSB3UART();
//			return(un8Status);
//						}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD - un8CameraRecallMemSetting");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//
//}
//
//uint8_t	un8CameraResetMemSetting (uint8_t un8Memory)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3F;
//		szComString[4]=0x00;
//		szComString[5]=un8Memory;
//		szComString[6]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){		// Check for ACK
//			SelectUSB3UART();
//			return(un8Status);
//			DebugWriteString("\r\nERROR ACK - un8CameraRecallMemSetting");
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD - un8CameraRecallMemSetting");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//
//}
//
////---------------------------------------------------------------------------------------//
////
////	Function 	: CameraStopZoom(void)
////
////	Description :
////
////	Inputs		: None
////
////	Returns		: Void
////
////	Rev 1.0	Date: 26/11/13 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t	un8CameraStopZoom(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x07;
//		szComString[4]=0x00;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){		// Check for ACK
//			SelectUSB3UART();
//			return(un8Status);
//			DebugWriteString("\r\nERROR ACK - un8CameraStopZoom(void)");
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD un8CameraStopZoom(void):");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//}
////---------------------------------------------------------------------------------------//
////
////	Function 	: CameraStartTeleZoom
////
////	Description :
////
////	Inputs		: ucZoomSpeed
////				  0 ( Low ) - 7 ( High )
////
////	Returns		: Void
////
////	Rev 1.0	Date : 26/11/13 - Inital Release
////
////---------------------------------------------------------------------------------------//
uint8_t	un8CameraStartTeleZoom(uint8_t un8ZoomSpeed)
{
char	szComString[20];
uint8_t un8Status;
char	szReadString[20];

//		CameraBufferReset();

		// Fill the command string
		szComString[0]=0x81;
		szComString[1]=0x01;
		szComString[2]=0x04;
		szComString[3]=0x07;
		szComString[4]=0x20+un8ZoomSpeed;
		szComString[5]=0xFF;

		// Write the command
		CamUARTWriteString(szComString);

		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){				// Check for ACK
//			SelectUSB3UART();
//			DebugWriteString("\r\nERROR ACK - un8CameraTeleZoom(void)");
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD un8CameraTeleZoom(void)");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}

		return(CAMERA_READ_OK);
}
//---------------------------------------------------------------------------------------//
//
//	Function 	: CameraStartWideZoom
//
//	Description :
//
//	Inputs		: ucZoomSpeed
//				  0 ( Low ) - 7 ( High )
//
//	Returns		: Void
//
//	Rev 1.0	Date: 26/11/13 - Inital Release
//
//---------------------------------------------------------------------------------------//
//uint8_t	un8CameraStartWideZoom(uint8_t un8ZoomSpeed)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x07;
//		szComString[4]=0x30+un8ZoomSpeed;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){				// Check for ACK
//			SelectUSB3UART();
//			DebugWriteString("\r\nERROR ACK un8CameraWideZoom(void)");
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)	{		// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD un8CameraWideZoom(void)");
//			DebugPrintCameraHex(szReadString,0xFF);
//				return(un8Status);
//				}
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraDigitalZoomLimit(uint8_t un8DigitalZoomLimit)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x26;
//		szComString[4]=un8DigitalZoomLimit;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){				// Check for ACK
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)			// Check for CMD_COMPLETE
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
////---------------------------------------------------------------------------------------//
////
////	Function 	: CameraZoomDirect(unsigned int unZoomLevel)
////
////	Description :
////
////	Inputs		: unZoomLevel
////				  0x0000 to 0x4000 Optical Zoom
////
////
////	Returns		: Void
////
////	Rev 1.0	Date : 26/11/13 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t	un8CameraZoomDirect(uint16_t unZoomLevel)
//{
//char	szComString[20];
//uint8_t  p, q, r, s;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)(unZoomLevel >> 12);
//		q = (unsigned char)((unZoomLevel & 0x0F00) >> 8);
//		r = (unsigned char)((unZoomLevel & 0x00F0) >> 4);
//		s = (unsigned char)(unZoomLevel & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x47;
//		szComString[4]=p;
//		szComString[5]=q;
//		szComString[6]=r;
//		szComString[7]=s;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)			// Check for CMD_COMPLETE
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraFocusDirect(uint32_t unFoucsPosition)
//{
//char	szComString[20];
//unsigned char  p, q, r, s;
//uint8_t un8Status;
//char	szReadString[40];
//
//		CameraBufferReset();
//
//		p = (unsigned char)(unFoucsPosition >> 12);
//		q = (unsigned char)((unFoucsPosition & 0x0F00) >> 8);
//		r = (unsigned char)((unFoucsPosition & 0x00F0) >> 4);
//		s = (unsigned char)(unFoucsPosition & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x48;
//		szComString[4]=p;
//		szComString[5]=q;
//		szComString[6]=r;
//		szComString[7]=s;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)			// Check for CMD_COMPLETE
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraAutoFocus(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x38;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraManualFocus(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x38;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraShutterDirect(uint8_t un8ShutterPosition)
//{
//char	szComString[20];
//unsigned char  p, q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)((un8ShutterPosition & 0x00F0) >> 4);
//		q = (unsigned char)(un8ShutterPosition & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x4A;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=p;
//		szComString[7]=q;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraIrisDirect(uint32_t unIrisPosition)
//{
//char	szComString[20];
//unsigned char  p, q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)((unIrisPosition & 0x00F0) >> 4);
//		q = (unsigned char)(unIrisPosition & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x4B;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=p;
//		szComString[7]=q;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraGainDirect(uint32_t unGain)
//{
//char	szComString[20];
//unsigned char  p, q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)((unGain & 0x00F0) >> 4);
//		q = (unsigned char)(unGain & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x4C;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=p;
//		szComString[7]=q;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD COMPLETE");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraBrightnessDirect(uint8_t unBrightness)
//{
//char	szComString[20];
//unsigned char  p, q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)((unBrightness & 0x00F0) >> 4);
//		q = (unsigned char)(unBrightness & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x4D;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=p;
//		szComString[7]=q;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){				// Check for ACK
//			SelectUSB3UART();
//			DebugWriteString("\r\nERROR CMD Ack BR : ");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD COMPLETE BR");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraExposureCompReset(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x0E;
//		szComString[4]=0x00;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraExposureCompON(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3E;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraExposureCompOFF(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3E;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//
//uint8_t	un8CameraExposureCompDirect(uint8_t un8ExposureCompPosition)
//{
//char	szComString[20];
//unsigned char  p, q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		p = (unsigned char)((un8ExposureCompPosition & 0x00F0) >> 4);
//		q = (unsigned char)(un8ExposureCompPosition & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x4E;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=p;
//		szComString[7]=q;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraApertureDirect(uint8_t un8ApertureGain)
//{
//char	szComString[20];
//unsigned char  p, q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)((un8ApertureGain & 0x00F0) >> 4);
//		q = (unsigned char)(un8ApertureGain & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x42;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=p;
//		szComString[7]=q;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraGammaSetNormal(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x5B;
//		szComString[4]=0x00;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraGammaSetCinema1(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x5B;
//		szComString[4]=0x01;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraGammaSetCinema2(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x5B;
//		szComString[4]=0x02;
//
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraFreezeOn(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x62;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraFreezeOff(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x62;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraPictureEffectNegative(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x63;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)			// Check for CMD_COMPLETE
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraPictureEffectBW(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x63;
//		szComString[4]=0x04;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)			// Check for CMD_COMPLETE
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraMemoryReset(uint32_t unMemoryNumber)
//{
//char	szComString[20];
//uint8_t p;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)(unMemoryNumber & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3F;
//		szComString[4]=0x00;
//		szComString[5]=p;
//		szComString[6]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraMemorySet(uint32_t unMemoryNumber)
//{
//char	szComString[20];
//unsigned char  p;
//uint8_t un8Status;
//char	szReadString[20];
//
//		p = (unsigned char)(unMemoryNumber & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3F;
//		szComString[4]=0x01;
//		szComString[5]=p;
//		szComString[6]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraMemoryRecall(uint32_t unMemoryNumber)
//{
//char	szComString[20];
//unsigned char  p;
//uint8_t un8Status;
//char	szReadString[20];
//
//		p = (unsigned char)(unMemoryNumber & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3F;
//		szComString[4]=0x02;
//		szComString[5]=p;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraCustom(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3F;
//		szComString[4]=0x01;
//		szComString[5]=0x7F;
//		szComString[6]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	un8CameraSetResolutionHD50(void)
//{
//		un8CameraWriteReg(0x70,0x12);
//
//		return(CAMERA_READ_OK);
//
//}
//uint8_t	un8CameraPictureEffectOff(void)
//{
//char	szComString[20];
//uint8_t	un8Status;
//char	szReadString[200];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x63;
//		szComString[4]=0x00;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE)			// Check for CMD_COMPLETE
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//}
//
///*uint8_t	un8CameraSetResolutionHD60(void)
//{
//		un8CameraWriteReg(0x70,0x02);
//		return(CAMERA_READ_OK);
//}
//*/
//
///*
//uint8_t	un8CameraSetResolutionHD25(void)
//{
//		un8CameraWriteReg(0x72,0x08);
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraSetResolutionHD30(void)
//{
//		un8CameraWriteReg(0x72,0x06);
//		return(CAMERA_READ_OK);
//}
//*/
//
//uint8_t	un8CameraWriteReg(uint8_t unRegister, uint8_t unValue)
//{
//char	szComString[20];
//uint8_t p,q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		p = (unsigned char)((unValue & 0x00F0) >> 4);
//		q = (unsigned char)(unValue & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x24;
//		szComString[4]=unRegister;
//		szComString[5]=p;
//		szComString[6]=q;
//		szComString[7]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)			// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//}
//uint8_t	u8CameraReadReg(uint8_t unRegister,uint8_t *un8RecValue)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szLString[20];
////char	szDebugString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x04;
//		szComString[3]=0x24;
//		szComString[4]=unRegister;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szLString);
//		SelectUSB3UART();
//
////		DebugWriteString("\r\n Camera read reg : ");
////		DebugPrintCameraHex(szLString,0xff);
//
//		*un8RecValue=(szLString[2]<<4);
//		*un8RecValue+=szLString[3];
//
//
//		return(un8Status);
//
//}
//
////---------------------------------------------------------------------------------------//
////
////	Function 	:	un8ReadCamera
////
////	Description :	Reads a Response from the camera with a timeout
////
////					ACK Response
////
////	Inputs		:	Pointer to buffer for camera response string
////
////	Returns		:	The return can be - 	CAMERA_TIMEOUT_ERROR, CAMERA_CMD_ACK,
////											CAMERA_CMD_COMPLETE, CAMERA_INQUIRY_RETURN,
////											CAMERA_BLOCK_INQUIRY_RETURN,
////											CAMERA_ERROR_MESSAGE, CAMERA_UNKNOWN_ERROR
////
////					The camera USART string is stored in szCameraReadString
////
////	Rev 1.0	Date: 	10/01/14 - Inital Release
////					Louis Ryan
////
////---------------------------------------------------------------------------------------//
//uint8_t	un8ReadCamera(char *szCameraReadString)
//{
//uint32_t	un32CameraReadTimeoutMS=CAMERA_RESPONCE_TIMEOUT;
//uint32_t	un32CameraResponseTime=0;
////char	szDebugBuffer[200];
//
//	// Wait for Camera Response
//	do{
//		DelayUS(1);
//		// If no response within timeout then return error
//		if(un32CameraResponseTime++ >= un32CameraReadTimeoutMS){
//			CameraBufferReset();
//			return( CAMERA_TIMEOUT_ERROR );
//			}
//	}while(un8CameraResponseReceived == FALSE);
//
//	//	Copy the string for calling function
//	CameraStringCopy(szCameraReadString,szCameraResponse);
//
//	// Reset the UART Buffer - There should be no more data until we ask for some
//	CameraBufferReset();
//
//	// Check which kind of response
//
//	//	Is it a Command Acknowledge Response?
//	if(szCameraReadString[1]==0x41){
//		return(CAMERA_CMD_ACK);
//		}
//
//	//	Is it a Command Complete Response?
//	if(szCameraReadString[1]==0x51){
//		return(CAMERA_CMD_COMPLETE);
//		}
//
//	//	Is it a Camera Inquiry Response?
//	if(szCameraReadString[1]==0x50){
//		return(CAMERA_INQUIRY_RETURN);
//		}
//
//	//	Is it a Block Inquiry Response?
//	if(szCameraReadString[15]==0xFF){
//		szCameraReadString[15]=0xFE;
//		return(CAMERA_BLOCK_INQUIRY_RETURN);
//		}
//
//	//	Is it a Camera Broadcast CMD Response?
//		if(szCameraReadString[0]==0x88){
//			return(CAMERA_BROADCAST_CMD_RETURN);
//			}
//
//	//	Is it a Camera Error Response?
//	if((szCameraReadString[1]==0x60) ||(szCameraReadString[1]==0x61)){
//		switch(szCameraReadString[2]){
//			case 0x02 : return(CAMERA_SYNTAX_ERROR); break;
//			case 0x03 : return(CAMERA_CMD_BUFFER_FULL); break;
//			case 0x04 : return(CAMERA_CMD_CANCELLED); break;
//			case 0x05 : return(CAMERA_NO_SOCKET); break;
//			case 0x41 : return(CAMERA_CMD_NOT_EXECUTABLE); break;
//			default   : return(CAMERA_ERROR_MESSAGE);
//			}
//   		}
//
//	//	Is it a Camera Broadcast CMD Response?
//	if(szCameraReadString[1]==0x38){
//		return(CAMERA_NETWORK_CHANGE_RETURN);
//		}
//
////	DebugWriteString("\r\nCAMERA_UNKNOWN_ERROR: ");
////	DebugPrintCameraHex(szCameraReadString,0xFF);
//	// If it is not any of the above
//	return( CAMERA_UNKNOWN_ERROR );
//}
//
//
//
//void	CameraStringCopy(char *szString1, char *szString2)
//{
//uint8_t un8Loop;
//
//		for(un8Loop=0;un8Loop<20;un8Loop++){
//			szString1[un8Loop]=szString2[un8Loop];
//			}
//}
//
////void	CameraHardReset(void)
////{
////		// Reset Camera
////		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
////		GPIO_SetBits(GPIOA, GPIO_Pin_7);
////}
//
//
//
//uint8_t	un8CameraAutomaticExposureSetup(uint8_t un8AESetting)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x39;
//		szComString[4]=un8AESetting;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR AE MODE CMD ");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
///* Change Resolution
////un8Status=un8CameraSetResolutionHD60();
//		if(un8Status!=CAMERA_READ_OK)
//			DebugPrintCameraStatus("ERROR",__FILE__,__LINE__,un8Status);
//
//		//CameraSetResolutionHD50();
//		//CameraSetResolutionHD60();
//
//		un8CameraPowerOff();
//		un8CameraPowerOn();
//		CameraHardReset();
//
//		*/
//
//
//
//
//
//uint8_t	un8OSDBrowseItem(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x73;
//		szComString[4]=0x13;
//		szComString[5]=0x00;
//		szComString[6]=0x00;
//		szComString[7]=0x00;
//		szComString[8]=0x01;
//		szComString[9]=0x00;
//		szComString[10]=0x00;
//		szComString[11]=0x00;
//		szComString[12]=0x00;
//		szComString[13]=0x00;
//		szComString[14]=0x00;
//		szComString[15]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD OSD ON");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8OSDOn(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x74;
//		szComString[4]=0x2F;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD OSD ON");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8OSDOff(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x74;
//		szComString[4]=0x3F;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD OSD OFF");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8OSDWrite(uint8_t un8Line,uint8_t un8Position,char *szString)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//uint8_t un8Loop;
//
//
//		for(un8Loop=0;un8Loop<10;un8Loop++)
//			szComString[5+un8Loop]=0x36;
//
//		for(un8Loop=0;un8Loop<10;un8Loop++){
//			if(szString[un8Loop]=='\0')
//				break;
//			else
//				if(szString[un8Loop]>='A' && szString[un8Loop]<='Z')
//					szComString[5+un8Loop]=szString[un8Loop]-'A';
//				else
//					switch(szString[un8Loop]){
//						case '0' : szComString[5+un8Loop] = 0x27; break;
//						case '1' : szComString[5+un8Loop] = 0x1E; break;
//						case '2' : szComString[5+un8Loop] = 0x1F; break;
//						case '3' : szComString[5+un8Loop] = 0x20; break;
//						case '4' : szComString[5+un8Loop] = 0x21; break;
//						case '5' : szComString[5+un8Loop] = 0x22; break;
//						case '6' : szComString[5+un8Loop] = 0x23; break;
//						case '7' : szComString[5+un8Loop] = 0x24; break;
//						case '8' : szComString[5+un8Loop] = 0x25; break;
//						case '9' : szComString[5+un8Loop] = 0x26; break;
//						case ' ' : szComString[5+un8Loop] = 0x36; break;
//
//						default  : szComString[5+un8Loop] = 0x1C; break;
//						}
//			}
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x73;
//		if(un8Position==0)
//			szComString[4]=0x20+un8Line;
//		else
//			szComString[4]=0x30+un8Line;
//
//		szComString[15]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD WriteOSD");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		return(CAMERA_READ_OK);
//}
//
//
//
//uint8_t	un8CameraInfraredMode(uint8_t un8OnOff)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x01;
//
//		if(un8OnOff==ON)
//			szComString[4]=0x02;
//		else
//			szComString[4]=0x03;
//
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD OSD OFF");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraWideDynamicRange(uint8_t un8WD)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3D;
//
//		switch(un8WD){
//			case CAMERA_WDR_WD : szComString[4]=0x02; break;
//			case CAMERA_WDR_OFF: szComString[4]=0x03; break;
//			case CAMERA_WDR_VE : szComString[4]=0x06; break;
//			}
//
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD OSD OFF");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
//
//
//uint8_t	un8CameraNoiseReduction(uint8_t un8NR_Value)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x53;
//
//		szComString[4]=0x00 + un8NR_Value;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD OSD OFF");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
////void 	CameraGPIOInit(void)
////{
////GPIO_InitTypeDef GPIO_InitStructure;
////
////  		// GPIOB clock enable
////  		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
////
////	  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7, GPIO_Pin_6;
////    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
////	    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
////	    GPIO_Init(GPIOA, &GPIO_InitStructure);
////
////	    }
//
//
////uint8_t	un8CameraSetVideoFormat(uint8_t un8VideoStandard)
////{
////uint8_t un8Status;
////
////
////		CameraBufferReset();
////
////		switch(un8VideoStandard){
////
////			case VIDEO_FORMAT_1080P_25HZ	: 		un8Status=un8CameraWriteReg(0x72,0x08);
////													break;
////
////			case VIDEO_FORMAT_1080P_30HZ	:  		un8Status=un8CameraWriteReg(0x72,0x06);
////													break;
////
////			case VIDEO_FORMAT_1080P_50HZ	:  		un8Status=un8CameraWriteReg(0x72,0x14);
////													break;
////
////			case VIDEO_FORMAT_1080P_60HZ	:  		un8Status=un8CameraWriteReg(0x72,0x13);
////													break;
////
////			case VIDEO_FORMAT_720P_50HZ		:  		un8Status=un8CameraWriteReg(0x72,0x0C);
////													break;
////
////			case VIDEO_FORMAT_720P_60HZ	 	:  		un8Status=un8CameraWriteReg(0x72,0x09);
////													break;
////
////			case VIDEO_FORMAT_720P_29HZ	 	:  		un8Status=un8CameraWriteReg(0x72,0x0E);
////													break;
////
////			default : DebugPrintStatus("ERROR CameraSetVideoStandard - Unknown Standard",__FILE__,__LINE__,0x00);
////			}
////
////	return(un8Status);
////}
//
//uint8_t	un8CameraShowVideoFormat(uint8_t un8VideoStandard)
//{
////uint8_t un8Status;
//
//		CameraBufferReset();
//
//		switch(un8VideoStandard){
//
//			case 0x08 : DebugWriteString("VIDEO_FORMAT_1080P_25HZ");
//													break;
//
//			case 0x06 : DebugWriteString("VIDEO_FORMAT_1080P_30HZ");
//													break;
//
//			case 0x14 : DebugWriteString("VIDEO_FORMAT_1080P_50HZ");
//													break;
//
//			case 0x13 : DebugWriteString("VIDEO_FORMAT_1080P_60HZ");
//													break;
//
//			case 0x0C : DebugWriteString("VIDEO_FORMAT_720P_50HZ");
//													break;
//
//			case 0x09 : DebugWriteString("VIDEO_FORMAT_720P_60HZ");
//													break;
//
//			case 0x0E : DebugWriteString("VIDEO_FORMAT_720P_29HZ");
//													break;
//
//			default : DebugPrintStatus("ERROR CameraShowVideoStandard - Unknown Standard",__FILE__,__LINE__,0x00);
//			}
//
//	return(0);
//}
//
//
//
//uint8_t	un8CameraReadZoomPosition(void)
//{
//char	szComString[20];
//char	szCameraReadString[20];
//uint8_t	un8CameraReadStatus;
//
//		CameraBufferReset();
//
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x04;
//		szComString[3]=0x47;
//		szComString[4]=0xFF;
//
//		// Write the camera command
//		USARTWriteCamera(szComString);
//
//		// Read the camera
//		un8CameraReadStatus = un8ReadCamera(szCameraReadString);
//		SelectUSB3UART();
//		if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
//			return(un8CameraReadStatus);
//
//		SystemVars.Camera.un16ZoomPosition		= 	szCameraReadString[2]<<12;
//		SystemVars.Camera.un16ZoomPosition		+=	szCameraReadString[3]<<8;
//		SystemVars.Camera.un16ZoomPosition		+=	szCameraReadString[4]<<4;
//		SystemVars.Camera.un16ZoomPosition		+=	szCameraReadString[5]<<0;
//
//		return( CAMERA_READ_OK );
//}
//
//uint8_t	un8CameraReadFocusPosition(void)
//{
//char	szComString[20];
//char	szCameraReadString[20];
//uint8_t	un8CameraReadStatus;
//
//		CameraBufferReset();
//
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x04;
//		szComString[3]=0x48;
//		szComString[4]=0xFF;
//
//		// Write the camera command
//		USARTWriteCamera(szComString);
//
//		// Read the camera
//		un8CameraReadStatus = un8ReadCamera(szCameraReadString);
//		SelectUSB3UART();
//		if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
//			return(un8CameraReadStatus);
//
//		SystemVars.Camera.un16FocusPosition		= 	szCameraReadString[2]<<12;
//		SystemVars.Camera.un16FocusPosition		+=	szCameraReadString[3]<<8;
//		SystemVars.Camera.un16FocusPosition		+=	szCameraReadString[4]<<4;
//		SystemVars.Camera.un16FocusPosition		+=	szCameraReadString[5]<<0;
//
//		return( CAMERA_READ_OK );
//}
//
//uint8_t	un8CameraReadSystem(void)
//{
//char	szComString[20];
//char	szCameraReadString[20];
//
//uint8_t	un8CameraReadStatus;
//
//		CameraBufferReset();
//
//		// Read Lens Control System
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x7E;
//		szComString[3]=0x7E;
//		szComString[4]=0x00;
//		szComString[5]=0xFF;
//
//		// Write the camera command
//		USARTWriteCamera(szComString);
//
//		// Read the camera
//		un8CameraReadStatus = un8ReadCamera(szCameraReadString);
//		if( un8CameraReadStatus != CAMERA_BLOCK_INQUIRY_RETURN )
//			{
//			SelectUSB3UART();
//			return(un8CameraReadStatus);
//			}
//
//		SystemVars.Camera.un16ZoomPosition		= 	szCameraReadString[2]<<12;
//		SystemVars.Camera.un16ZoomPosition		+=	szCameraReadString[3]<<8;
//		SystemVars.Camera.un16ZoomPosition		+=	szCameraReadString[4]<<4;
//		SystemVars.Camera.un16ZoomPosition		+=	szCameraReadString[5]<<0;
//		SystemVars.Camera.un8FocusNearLimit	=	szCameraReadString[6]<<4;
//		SystemVars.Camera.un8FocusNearLimit	+=	szCameraReadString[7]<<0;
//		SystemVars.Camera.un16FocusPosition	= 	szCameraReadString[8]<<12;
//		SystemVars.Camera.un16FocusPosition	+=	szCameraReadString[9]<<8;
//		SystemVars.Camera.un16FocusPosition	+=	szCameraReadString[10]<<4;
//		SystemVars.Camera.un16FocusPosition	+=	szCameraReadString[11]<<0;
//		SystemVars.Camera.un8AFMode	    	= 	szCameraReadString[13]>>3;
//		//SystemVars.Camera.un8FocusMode	    	= 	szCameraReadString[13] & 0x01;
//		//SystemVars.Camera.un8FocusMode	    	= 	szCameraReadString[13] & 0x01;
//		SystemVars.Camera.un8GammaMemoryRecall	=	(szCameraReadString[14]>>3) & 0x01;
//		SystemVars.Camera.un8FocusCommand		= 	(szCameraReadString[14]>>2) & 0x01;
//		SystemVars.Camera.un8ZoomCommand		= 	szCameraReadString[14] & 0x01;
//
//		// Read Camera Control System
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x7E;
//		szComString[3]=0x7E;
//		szComString[4]=0x01;
//		szComString[5]=0xFF;
//
//		// Write the camera command
//		USARTWriteCamera(szComString);
//
//		// Read the camera
//		un8CameraReadStatus = un8ReadCamera(szCameraReadString);
//		if( un8CameraReadStatus != CAMERA_BLOCK_INQUIRY_RETURN )
//			{
//			SelectUSB3UART();
//			return(un8CameraReadStatus);
//			}
//
//		//	Camera Control Variables
//		SystemVars.Camera.un8R_Gain			=	szCameraReadString[2]<<4;
//		SystemVars.Camera.un8R_Gain			+=	szCameraReadString[3];
//		SystemVars.Camera.un8B_Gain			=	szCameraReadString[4]<<4;
//		SystemVars.Camera.un8B_Gain			+=	szCameraReadString[5];
//		//SystemVars.Camera.un8OnePushRES		=	szCameraReadString[6]<<3; //????
//		SystemVars.Camera.un8WBMode			=	szCameraReadString[6] & 0x03;
//		SystemVars.Camera.un8ApertureGain		=	szCameraReadString[7];
//		SystemVars.Camera.un8ExposureMode		=	szCameraReadString[8];
//		SystemVars.Camera.un8SpotAE			=	(szCameraReadString[9]<<3) & 0x01;
//		SystemVars.Camera.un8BackLight			=	(szCameraReadString[9]<<2) & 0x01;
//		SystemVars.Camera.un8ExposureComp		=	(szCameraReadString[9]<<1) & 0x01;
//		SystemVars.Camera.un8SlowShutter		=	(szCameraReadString[9]<<0) & 0x01;
//		SystemVars.Camera.un8Shutterposition 	=	szCameraReadString[10];
//		//SystemVars.Camera.un8Irisposition		=	szCameraReadString[11];
//		//SystemVars.Camera.un8Gainposition		=	szCameraReadString[12];
//		SystemVars.Camera.un8BrightPosition 	=	szCameraReadString[14]; // Brightness Changed to Exposure Comp
//		SystemVars.Camera.un8ExposureCompposition=	szCameraReadString[14];
//
//		// Read 'Other' System
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x7E;
//		szComString[3]=0x7E;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the camera command
//		USARTWriteCamera(szComString);
//
//		// Read the camera
//		un8CameraReadStatus = un8ReadCamera(szCameraReadString);
//		if( un8CameraReadStatus != CAMERA_BLOCK_INQUIRY_RETURN )
//			{
//			SelectUSB3UART();
//			return(un8CameraReadStatus);
//			}
//
//		SystemVars.Camera.un8AutoICR			=	(szCameraReadString[2]<<2) & 0x01;
//		SystemVars.Camera.un8Keylock			=	(szCameraReadString[2]<<1) & 0x01;
//		SystemVars.Camera.un8Power				=	(szCameraReadString[2]<<0) & 0x01;
//		SystemVars.Camera.un8ICR				=	(szCameraReadString[3]<<4) & 0x01;
//		SystemVars.Camera.un8Freeze			=	(szCameraReadString[3]<<3) & 0x01;
//		SystemVars.Camera.un8Mute				=	(szCameraReadString[4]<<4) & 0x01;
//		SystemVars.Camera.un8PictureEffectMode = 	szCameraReadString[5];
//		SystemVars.Camera.un8GammaMode			=	szCameraReadString[6];
//		SystemVars.Camera.un16CameraID			=	szCameraReadString[8]<<12;
//		SystemVars.Camera.un16CameraID			+=	szCameraReadString[8]<<8;
//		SystemVars.Camera.un16CameraID			+=	szCameraReadString[9]<<4;
//		SystemVars.Camera.un16CameraID			+=	szCameraReadString[10]<<0;
//		SystemVars.Camera.un8Memory			=	(szCameraReadString[12]<<4) & 0x01;
//		SystemVars.Camera.un8System			=	(szCameraReadString[12]<<0) & 0x01;
//
//		// Read Enlargement Function System
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x7E;
//		szComString[3]=0x7E;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the camera command
//		USARTWriteCamera(szComString);
//
//		// Read the camera
//		un8CameraReadStatus = un8ReadCamera(szCameraReadString);
//		if( un8CameraReadStatus != CAMERA_BLOCK_INQUIRY_RETURN )
//			{
//			SelectUSB3UART();
//			return(un8CameraReadStatus);
//			}
//
//		// Camera Enlargement Functions
//		SystemVars.Camera.un8DigitalZoom			=	szCameraReadString[2]<<4;
//		SystemVars.Camera.un8DigitalZoom			+=	szCameraReadString[3];
//		SystemVars.Camera.un8AFActicationTime		=	szCameraReadString[4]<<4;
//		SystemVars.Camera.un8AFActicationTime		+=	szCameraReadString[5];
//		SystemVars.Camera.n8AFIntervalTime			=	szCameraReadString[6]<<4;
//		SystemVars.Camera.n8AFIntervalTime			+=	szCameraReadString[7];
//		SystemVars.Camera.un8SpotAEPositionX		=	szCameraReadString[8];
//		SystemVars.Camera.un8SpotAEPositionY		=	szCameraReadString[9];
////		SystemVars.Camera.un8AutoSlowShutterLimit	=	szCameraReadString[13];
////		SystemVars.Camera.un8DZoomLimit			=	szCameraReadString[14];
//
//		SelectUSB3UART();
//		return( CAMERA_READ_OK );
//}
//
//
//
//uint8_t	un8CameraRestrictOutputON(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x50;
//
//		szComString[4]=0x03;  // 0x02 for ON
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR restrict Output ON");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t	un8CameraRestrictOutput(void)
//{
//char	szComString[20];
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x20;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=0x80;
//		szComString[7]=0x10;
//		szComString[8]=0x10;
//		szComString[9]=0x80;
//		szComString[10]=0x10;
//		szComString[11]=0x55;
//		szComString[12]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			{
//			SelectUSB3UART();
//			return(un8Status);
//			}
//
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR restrict Output");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//		return(CAMERA_READ_OK);
//}
//
////---------------------------------------------------------------------------------------//
////
////	Function 	:
////
////	Description :
////
////	Inputs		:
////
////
////	Returns		:
////
////	Rev 1.0	Date: / /14 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t un8ExposureCompensationOn(void)
//{
//char	szComString[20];
//char	szReadString[20];
//uint8_t un8Status;
//
//		CameraBufferReset();
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x3E;
//		szComString[4]=0x02;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//
//		return(CAMERA_READ_OK);
//
//}
//
//uint8_t	un8CameraExposureCompensationDirect(uint8_t un8EC)
//{
//char	szComString[20];
//unsigned char  p, q;
//uint8_t un8Status;
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		p = (unsigned char)((un8EC & 0x00F0) >> 4);
//		q = (unsigned char)(un8EC & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x4E;
//		szComString[4]=0x00;
//		szComString[5]=0x00;
//		szComString[6]=p;
//		szComString[7]=q;
//		szComString[8]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status!=CAMERA_CMD_ACK){
//		SelectUSB3UART();// Check for ACK
//			DebugWriteString("\r\nERROR CMD Ack EC");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//		if(un8Status!=CAMERA_CMD_COMPLETE){			// Check for CMD_COMPLETE
//			DebugWriteString("\r\nERROR CMD COMPLETE EC");
//			DebugPrintCameraHex(szReadString,0xFF);
//			return(un8Status);
//			}
//
//
//
//		return(CAMERA_READ_OK);
//}
//
////---------------------------------------------------------------------------------------//
////
////	Function 	:
////
////	Description :
////
////	Inputs		:
////
////
////	Returns		:
////
////	Rev 1.0	Date: / /14 - Inital Release
////
////---------------------------------------------------------------------------------------//
//uint8_t un8OnePushWhiteBalanceOn(void)
//{
//char	szComString[20];
//char	szReadString[20];
//uint8_t un8Status;
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x35;
//		szComString[4]=0x03;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t un8AutoWhiteBalanceOn(void)
//{
//char	szComString[20];
//char	szReadString[20];
//uint8_t un8Status;
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x35;
//		szComString[4]=0x00;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//uint8_t un8OnePushWhiteBalanceTrigger(void)
//{
//char	szComString[20];
//char	szReadString[20];
//uint8_t un8Status;
//
//		CameraBufferReset();
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x04;
//		szComString[3]=0x10;
//		szComString[4]=0x05;
//		szComString[5]=0xFF;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		// Read the Response
//		un8Status=un8ReadCamera(szReadString);
//		SelectUSB3UART();
//
//		if(un8Status!=CAMERA_CMD_ACK)				// Check for ACK
//			return(un8Status);
//
//		return(CAMERA_READ_OK);
//}
//
//
////void	Camera12VOff(void)
////{
////
////		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
////
////}
////void	Camera12VOn(void)
////{
////		GPIO_SetBits(GPIOA, GPIO_Pin_6);
////}
//
//
//
//uint8_t	un8InitCamera(void)
//{
//uint8_t	un8Status;
//uint8_t un8Timeout;
//uint8_t un8BeepTimer=0;
//uint8_t	un8RecValue;
//char	szBuffer[40];
//
//
//		DebugWriteString("\r\n\r\n**********Starting up Camera**********");
//
//		DebugWriteString("\r\n\r\nCamera Buffer Reset");
//		CameraBufferReset();
//
//		DebugWriteString("\r\n\r\nCamera Hard Reset");
//		CameraHardReset();
//
//		DelayMiliSeconds(10);
//		DebugWriteString("\r\n\r\nCamera IF Clear");
//		un8CameraIFClear();
//
//		un8Status=un8CameraIFClear();
//		if(un8Status!=CAMERA_NETWORK_CHANGE_RETURN)
//			DebugPrintCameraStatus("ERROR",__FILE__,__LINE__,un8Status);
//
//		DebugWriteString("\r\n\r\nCamera Powrer On");
//		un8Status=un8CameraPowerOn();
//		if(un8Status!=CAMERA_READ_OK)
//			DebugPrintCameraStatus("ERROR",__FILE__,__LINE__,un8Status);
//
//		DebugWriteString("\r\n\r\nCamera Address Set");
//		un8Status=un8CameraAddressSet();
//		if(un8Status!=CAMERA_READ_OK)
//			DebugPrintCameraStatus("ERROR",__FILE__,__LINE__,un8Status);
//
//
//		// Do these while waiting for camera
//		nFPGAConfig();
//		RTC_Config();
//
////		un8Status = un8AD9889B_Startup();
//		if(un8Status!=CAMERA_READ_OK)
//			DebugPrintStatus("ERROR",__FILE__,__LINE__,un8Status);
//
//
//		DebugWriteString("\r\n\r\nWait for Camera Ready");
//		un8Timeout=0;	// Max times to try before giving up;
//		do{
//			DelayMiliSeconds(20);
//			un8Status=un8CameraPictureEffectOff();
//			DebugWriteString(".");
//			un8BeepTimer++;
//
//			if(un8BeepTimer>=20){
//				DoneSound();
//				un8BeepTimer=0;
//				}
//
//		}while((un8Status!=CAMERA_READ_OK) && (un8Timeout++ <=200));
//
//
//		if(un8Status!=CAMERA_READ_OK)
//			DebugPrintCameraStatus("ERROR - Given up on waiting for camera to boot",__FILE__,__LINE__,un8Status);
//
//		un8Status=un8CameraWriteReg(0x74,0x01);
//		if(un8Status!=CAMERA_READ_OK)
//			DebugPrintCameraStatus("ERROR - Writing to 0x74 Register",__FILE__,__LINE__,un8Status);
//
//		un8Status=u8CameraReadReg(0x74,&un8RecValue);
//		sprintf(szBuffer,"\r\nReg 0x74 = %d",un8RecValue);
//		DebugWriteString(szBuffer);
//
//	//	DelayMiliSeconds(100);	// Need delay for HDMI Chip - Read V-Sync???
//
//		DebugWriteString("\r\n\r\n***********Camera Startup Complete**********\r\n\r\n");
//
////		GPIO_WriteBit(GPIOA,GPIO_Pin_2,1);		// Set Reset to 1
//
//		return(CAMERA_READ_OK);
//}
//
//
//uint8_t	CAM_AdjustModeCMD(void)
//{
//	char	szComString[20];
//	char	szReadString[20];
//	uint8_t un8Status;
//
//			CameraBufferReset();
//
//			szComString[0]=0x81;
//			szComString[1]=0x01;
//			szComString[2]=0x7F;
//			szComString[3]=0x01;
//			szComString[4]=0x7F;
//			szComString[5]=0xFF;
//
//			// Write the camera command
//			USARTWriteCamera(szComString);
//			un8Status=un8ReadCamera(szReadString);
//			if(un8Status==CAMERA_CMD_ACK)
//			{
//				DebugWriteString("\r\nCAM_AdjustModeCMD_ACK");
//			}
//			else
//			{
//				DebugWriteString("\r\nCAM_AdjustModeCMD_NACK");
//			}
//
//			un8Status=un8ReadCamera(szReadString);
//			if(un8Status==CAMERA_CMD_COMPLETE)
//			{
//				DebugWriteString("\r\nCAM_AdjustModeCMD_COMPLETE");
//			}
//			else
//			{
//				DebugWriteString("\r\nCAM_AdjustModeCMD_N_COMPLETE");
//			}
//
//			SelectUSB3UART();
//			//if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
//			//	return(un8CameraReadStatus);
//
//			return(un8Status);
//}
//
//uint8_t	CAM_ReleaseProtection(void)
//{
//	char	szComString[20];
//	char	szReadString[20];
//	uint8_t un8Status;
//
//			CameraBufferReset();
//
//			szComString[0]=0x81;
//			szComString[1]=0x01;
//			szComString[2]=0x7F;
//			szComString[3]=0x7F;
//			szComString[4]=0x02;
//			szComString[5]=0x00;
//			szComString[6]=0x00;
//			szComString[7]=0x01;
//			szComString[8]=0x00;
//			szComString[9]=0x01;
//			szComString[10]=0xFF;
//
//			// Write the camera command
//			USARTWriteCamera(szComString);
//
//
//			un8Status=un8ReadCamera(szReadString);
//			if(un8Status==CAMERA_CMD_ACK)
//			{
//				DebugWriteString("\r\nCAM_ReleaseProtection_ACK");
//			}
//			else
//			{
//				DebugWriteString("\r\nCAM_ReleaseProtection_NACK");
//			}
//
//			un8Status=un8ReadCamera(szReadString);
//			if(un8Status==CAMERA_CMD_COMPLETE)
//			{
//				DebugWriteString("\r\nCAM_ReleaseProtection_COMPLETE");
//			}
//			else
//			{
//				DebugWriteString("\r\nCAM_ReleaseProtection_N_COMPLETE");
//			}
//				SelectUSB3UART();
//			//if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
//			//	return(un8CameraReadStatus);
//
//
//
//			return(un8Status);
//}
//
//uint8_t	un16CameraWriteRegister(uint16_t unRegister,uint8_t un8Data)
//{
//char	szComString[20];
//uint8_t un8Status;
//uint8_t rs,u,v,x,y;
////char	szDebugString[20];
//char	szReadString[20];
//
//		CameraBufferReset();
//
//		rs = (unsigned char)((unRegister>> 8) & 0xFF);
//		x = (unsigned char)((unRegister & 0x00F0) >> 4);
//		y = (unsigned char)(unRegister & 0x000F);
//
//		u = (unsigned char)((un8Data & 0x00F0) >> 4);
//		v = (unsigned char)(un8Data & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x7F;
//		szComString[3]=0x7F;
//		szComString[4]=0x02;
//		szComString[5]=rs;
//		szComString[6]=x;
//		szComString[7]=y;
//		szComString[8]=u;
//		szComString[9]=v;
//		szComString[10]=0xFF;
//		//szComString[11]=0x0;
//		//szComString[12]=0x0;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status==CAMERA_CMD_ACK)
//		{
//			DebugWriteString("\r\nun16CameraWriteRegister_CAMERA_CMD_ACK");
//		}
//		else {
//			DebugWriteString("\r\nun16CameraWriteRegister_CAMERA_CMD_NACK");
//		}
//
//		un8Status=un8ReadCamera(szReadString);
//		if(un8Status==CAMERA_CMD_COMPLETE)
//		{
//			DebugWriteString("\r\nun16CameraWriteRegister_CMD_COMPLETE");
//		}
//		else
//		{
//			DebugWriteString("\r\nun16CameraWriteRegister_CMD_ncomp");
//		}
//		//un8Status=un8ReadCameraReg(szLString);
//
//		SelectUSB3UART();
//
//		return(un8Status);
//}
//
//uint8_t	un16CameraReadRegister(uint16_t unRegister,uint8_t *un8RecValue)
//{
//char	szComString[20];
//uint8_t un8Status;
//uint8_t rs,x,y;
//char	szLString[20];
////char	szDebugString[20];
//
//		CameraBufferReset();
//
//		rs = (unsigned char)((unRegister>> 8) & 0xFF);
//		x = (unsigned char)((unRegister & 0x00F0) >> 4);
//		y = (unsigned char)(unRegister & 0x000F);
//
//		// Fill the command string
//		szComString[0]=0x81;
//		szComString[1]=0x09;
//		szComString[2]=0x7F;
//		szComString[3]=0x7F;
//		szComString[4]=0x01;
//		szComString[5]=rs;
//		szComString[6]=x;
//		szComString[7]=y;
//		szComString[8]=0xFF;
//		//szComString[9]=0x0;
//		//szComString[10]=0x0;
//
//		// Write the command
//		USARTWriteCamera(szComString);
//
//		un8Status=un8ReadCamera(szLString);
//		//un8Status=un8ReadCamera(szReadString);
//		if (un8Status==CAMERA_INQUIRY_RETURN)
//		{
//			*un8RecValue = szLString[5] + (szLString[4] << 4);
//			//DebugWriteString("\r\nCAMERA_INQUIRY_RETURN");
//			return(un8Status);
//		}
//		if(un8Status==CAMERA_CMD_ACK)
//		{
//			DebugWriteString("\r\nun16CameraReadRegister_CAMERA_CMD_ACK");
//		}
//		else {
//			DebugWriteString("\r\nun16CameraReadRegister_CAMERA_CMD_NACK");
//		}
//
//		//un8Status=un8ReadCamera(szReadString);
//		un8Status=un8ReadCamera(szLString);
//		if (un8Status==CAMERA_INQUIRY_RETURN)
//				{
//					*un8RecValue = szLString[5] + (szLString[4] << 4);
//					DebugWriteString("\r\nCAMERA_INQUIRY_RETURN");
//					return(un8Status);
//				}
//		if(un8Status==CAMERA_CMD_COMPLETE)
//		{
//			DebugWriteString("\r\nun16CameraReadRegister_CMD_COMPLETE");
//		}
//		else
//		{
//			DebugWriteString("\r\nun16CameraReadRegister_CMD_ncomp");
//		}
//		SelectUSB3UART();
//
//		*un8RecValue = szLString[5] + (szLString[4] << 4);
//
//		return(un8Status);
//}
//
//uint8_t	CAM_LockProtection(void)
//{
//	char	szComString[20];
//	char	szReadString[20];
//	uint8_t un8Status;
//		CameraBufferReset();
//
//		szComString[0]=0x81;
//		szComString[1]=0x01;
//		szComString[2]=0x7F;
//		szComString[3]=0x7F;
//		szComString[4]=0x02;
//		szComString[5]=0x00;
//		szComString[6]=0x00;
//		szComString[7]=0x01;
//		szComString[8]=0x00;
//		szComString[9]=0x00;
//		szComString[10]=0xFF;
//
//		// Write the camera command
//		USARTWriteCamera(szComString);
//		un8Status=un8ReadCamera(szReadString);
//
//			SelectUSB3UART();
//		//if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
//		//	return(un8CameraReadStatus);
//
//		return(un8Status);
//}
//
//uint8_t	CAM_QuitAdjustModeCMD(void)
//{
//	char	szComString[20];
//	char	szReadString[20];
//	uint8_t un8Status;
//
//			CameraBufferReset();
//
//			szComString[0]=0x81;
//			szComString[1]=0x01;
//			szComString[2]=0x7F;
//			szComString[3]=0x00;
//			szComString[4]=0x7F;
//			szComString[5]=0xFF;
//
//			// Write the camera command
//			USARTWriteCamera(szComString);
//			un8Status=un8ReadCamera(szReadString);
//
//
//				SelectUSB3UART();
//			//if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
//			//	return(un8CameraReadStatus);
//
//			return(un8Status);
//}
//
//uint8_t	CAM_VersionInq(void)
//{
//	char	szComString[20];
//	char	szReadString[20];
//	uint8_t un8Status;
//	uint8_t un8ROM_Rev;
//			CameraBufferReset();
//
//			szComString[0]=0x81;
//			szComString[1]=0x09;
//			szComString[2]=0x00;
//			szComString[3]=0x02;
//			szComString[4]=0xFF;
//
//			// Write the camera command
//			USARTWriteCamera(szComString);
//			un8Status=un8ReadCamera(szReadString);
//			if (un8Status != CAMERA_INQUIRY_RETURN) {
//				SelectUSB3UART();
//				return( un8Status );
//			}
//
//			un8ROM_Rev=szReadString[6];
//				SelectUSB3UART();
//			//if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
//			//	return(un8CameraReadStatus);
//
//			return( un8ROM_Rev );
//}
//
//uint16_t Get_Camera_Type(void)
//{
//	char	szComString[20];
//	char	szReadString[20];
//	uint16_t camera_id;
//
//	uint8_t un8Status;
//
//			CameraBufferReset();
//
//			szComString[0]=0x81;
//			szComString[1]=0x09;
//			szComString[2]=0x04;
//			szComString[3]=0x22;
//			szComString[4]=0xFF;
//
//			// Write the camera command
//			USARTWriteCamera(szComString);
//
//			// Read the camera
//			un8Status = un8ReadCamera(szReadString);
//			SelectUSB3UART();
////			if( un8CameraReadStatus != CAMERA_INQUIRY_RETURN )
////				return(un8CameraReadStatus);
//
//			DebugWriteString("\r\nCAM_ID: ");
//			DebugPrintCameraHex(szReadString,0xFF);
//			DebugWriteString("\r\n");
//
//			camera_id = szReadString[7];
//			camera_id += szReadString[6] << 8;
//
//			return( camera_id );// return the lower half of the camera id
//}
//

