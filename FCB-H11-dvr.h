// Defines

// USART
#define CAMERA_UART_BUFFER_SIZE			200


//	Camera Settings Limits

#define CAMERA_ZOOM_SPEED_MAX			7
//#define CAMERA_ZOOM_LEVEL_MAX			0x6000



#define CAMERA_ZOOM_LEVEL_MIN			0x0000

#define CAMERA_FOCUS_AUTO				0x00
#define CAMERA_FOCUS_MANUAL				0x01

#include "stdint.h"
/*
struct CameraFCB_H11
{

uint8_t		un8WideDynamicRange;
uint8_t		un8DeFog;
uint8_t		un8InfraredMode;

// 			Lens Control Variables
uint16_t	un16ZoomPosition;
uint8_t		un8FocusNearLimit;
uint16_t	un16FocusPosition;
uint8_t		un8AFMode;
uint8_t		un8FocusMode;
uint8_t		un8GammaMemoryRecall;
uint8_t		un8FocusCommand;
uint8_t		un8ZoomCommand;

//			Camera Control Variables
uint8_t		un8R_Gain;
uint8_t		un8B_Gain;
uint8_t		un8OnePushRES;
uint8_t		un8WBMode;
uint8_t		un8ApertureGain;
uint8_t		un8ExposureMode;
uint8_t		un8SpotAE;
uint8_t		un8BackLight;
uint8_t		un8ExposureComp;
uint8_t		un8SlowShutter;
uint8_t		un8Shutterposition;
uint8_t		un8Irisposition;
uint8_t		un8Gainposition;
uint8_t		un8BrightPosition;
uint8_t		un8ExposureCompposition;

// 			Camera Other Variables
uint8_t		un8AutoICR;
uint8_t		un8Keylock;
uint8_t		un8Power;
uint8_t		un8ICR;
uint8_t		un8Freeze;
uint8_t		un8Mute;
uint8_t		un8PictureEffectMode;
uint8_t		un8GammaMode;
uint16_t	un16CameraID;
uint8_t		un8Memory;
uint8_t		un8System;

// 			Camera Enlargement Functions
uint8_t		un8DigitalZoom;
uint8_t		un8AFActicationTime;
uint8_t		n8AFIntervalTime;
uint8_t		un8SpotAEPositionX;
uint8_t		un8SpotAEPositionY;
uint8_t		un8AutoSlowShutterLimit;
uint8_t		un8DZoomLimit;

uint8_t		un8TestByte;



};
*/

#define 	CAMERA_READ_OK	 				0
#define 	CAMERA_CMD_ACK					1
#define 	CAMERA_CMD_COMPLETE 			2
#define 	CAMERA_INQUIRY_RETURN 			3
#define 	CAMERA_BLOCK_INQUIRY_RETURN    	3	//Make the same for now.
#define 	CAMERA_ERROR_MESSAGE			5
#define 	CAMERA_UNKNOWN_ERROR			6
#define 	CAMERA_TIMEOUT_ERROR 			7
#define 	CAMERA_BROADCAST_CMD_RETURN		8
#define 	CAMERA_NETWORK_CHANGE_RETURN	9

#define 	CAMERA_SYNTAX_ERROR				10
#define 	CAMERA_CMD_BUFFER_FULL			11
#define 	CAMERA_CMD_CANCELLED			12
#define 	CAMERA_NO_SOCKET				13
#define 	CAMERA_CMD_NOT_EXECUTABLE		14

//	CAMERA AUTO EXPOSURE MODES
#define 	CAM_AE_FULL_AUTO 		0x00
#define 	CAM_AE_MANUAL			0x03
#define 	CAM_AE_SHUTTER_PRIORITY	0x0A
#define 	CAM_AE_IRIS_PRIORITY	0x0B
#define 	CAM_AE_BRIGHT_MODE		0x0D
#define 	CAM_AE_SPOT_LIGHT_MODE	0x10

//	CAMERA SHUTTER LIMITS
#define 	CAMERA_SHUTTER_MIN		0x01
#define 	CAMERA_SHUTTER_MAX		0x0F
#define 	CAMERA_IRIS_MIN			0x05
#define 	CAMERA_IRIS_MAX			0x11
#define 	CAMERA_GAIN_MIN			0x00
#define 	CAMERA_GAIN_MAX			0x0F
#define 	CAMERA_BRIGHT_MIN		0x00
#define 	CAMERA_BRIGHT_MAX		0x0E
#define 	CAMERA_EXP_COMP_MIN		0x00
#define 	CAMERA_EXP_COMP_MAX		0x0E
#define 	CAMERA_APERATURE_MIN	0x00
#define 	CAMERA_APERATURE_MAX	0x0F


//  Focus Limits


//	Wide Dynamic Range
#define 	CAMERA_WDR_OFF 			0x00
#define 	CAMERA_WDR_WD 			0x01
#define		CAMERA_WDR_VE			0x02




//void	DebugPrintHex(uint8_t *un8String,uint8_t un8Termination);



void	CameraBufferReset(void);
void    CamUARTWriteString(char *szString);
uint8_t	un8CameraAddressSet(void);
uint8_t	un8CameraIFClear(void);
uint8_t	un8CameraPowerOn(void);
uint8_t un8CameraPowerOff(void);
uint8_t	un8CameraStopZoom(void);
uint8_t	un8CameraStartTeleZoom(uint8_t un8ZoomSpeed);
uint8_t	un8CameraStartWideZoom(uint8_t un8ZoomSpeed);
uint8_t	un8CameraStopFocus(void);
uint8_t	un8CameraStartTeleFocus(uint8_t un8ZoomSpeed);
uint8_t	un8CameraStartWideFocus(uint8_t un8ZoomSpeed);
uint8_t	un8CameraReadFocusPosition(void);
uint8_t	un8CameraZoomDirect(uint16_t unZoomLevel);
uint8_t	un8CameraFocusDirect(uint32_t unFoucsPosition);
uint8_t	un8CameraAutoFocus(void);
uint8_t	un8CameraManualFocus(void);
uint8_t	un8CameraShutterDirect(uint8_t);
uint8_t	un8CameraIrisDirect(uint32_t unIrisPosition);
uint8_t	un8CameraGainDirect(uint32_t unGain);
uint8_t	un8CameraBrightnessDirect(uint8_t unBrightness);
uint8_t	un8CameraExposureCompReset(void);
uint8_t	un8CameraExposureCompDirect(uint8_t unExposureCompPosition);
uint8_t	un8CameraApertureDirect(uint8_t unApertureGain);
uint8_t	un8CameraGammaSetNormal(void);
uint8_t	un8CameraGammaSetCinema1(void);
uint8_t	un8CameraGammaSetCinema2(void);
uint8_t	un8CameraFreezeOn(void);
uint8_t	un8CameraFreezeOff(void);
uint8_t	un8CameraPictureEffectNegative(void);
uint8_t	un8CameraPictureEffectBW(void);
uint8_t	un8CameraMemoryReset(uint32_t unMemoryNumber);
uint8_t	un8CameraMemorySet(uint32_t unMemoryNumber);
uint8_t	un8CameraMemoryRecall(uint32_t unMemoryNumber);
uint8_t	un8CameraCustom(void);
uint8_t	un8CameraSetResolutionHD50(void);
uint8_t	un8CameraPictureEffectOff(void);
uint8_t	un8CameraSetResolutionHD60(void);
uint8_t	un8CameraWriteReg(uint8_t unRegister, uint8_t unValue);
uint8_t	u8CameraReadReg(uint8_t unRegister,uint8_t *un8RecValue);
uint8_t	un8CameraReadSystem(void);
uint8_t	un8ReadCamera(char *szCameraReadString);
void	DelayMS(uint32_t un32Delay);
void	CameraStringCopy(char *szString1, char *szString2);
void	CameraHardReset(void);
uint8_t	un8InitCamera(void);
uint8_t	un8CameraInfraredMode(uint8_t un8OnOff);
uint8_t	un8CameraWideDynamicRange(uint8_t un8WD);
uint8_t	un8CameraNoiseReduction(uint8_t un8NR_Value);


uint8_t	un8CameraSetVideoFormat(uint8_t un8VideoStandard);
uint8_t	un8OSDOn(void);
uint8_t	un8OSDOff(void);
uint8_t	un8OSDWrite(uint8_t un8Line,uint8_t un8Position,char *szString);
uint8_t	un8OSDBrowseItem(void);
uint8_t	un8CameraSaveMemSetting (uint8_t un8Memory);
uint8_t	un8CameraRecallMemSetting (uint8_t un8Memory);
uint8_t	un8CameraResetMemSetting (uint8_t un8Memory);

uint8_t	un8CameraAutomaticExposureSetup(uint8_t un8AESetting);
uint8_t	un8CameraReadZoomPosition(void);
void 	CameraGPIOInit(void);

uint8_t	un8CameraExposureCompensationDirect(uint8_t un8EC);
uint8_t un8ExposureCompensationOn(void);

uint8_t	un8CameraExposureCompON(void);
uint8_t	un8CameraFlipLR(void);
uint8_t	un8CameraUnFlipLR(void);
uint8_t un8OnePushWhiteBalanceOn(void);
uint8_t un8OnePushWhiteBalanceTrigger(void);

void	Camera12VOff(void);
void	Camera12VOn(void);

uint8_t un8AutoWhiteBalanceOn(void);


uint8_t	CAM_AdjustModeCMD(void);
uint8_t	CAM_ReleaseProtection(void);
uint8_t	un16CameraWriteRegister(uint16_t unRegister,uint8_t un8Data);
uint8_t	un16CameraReadRegister(uint16_t unRegister,uint8_t *un8RecValue);
uint8_t	CAM_LockProtection(void);
uint8_t	CAM_QuitAdjustModeCMD(void);
uint8_t	CAM_VersionInq(void);
uint16_t Get_Camera_Type(void);

