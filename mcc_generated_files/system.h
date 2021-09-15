/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    system.h

  @Summary:
    This is the system.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
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

#ifndef _XTAL_FREQ
#define _XTAL_FREQ  24000000UL
#endif

#include "xc.h"
#include "stdint.h"

#ifndef SYSTEM_H
#define	SYSTEM_H

struct ExtKey{
uint8_t 	un8ExtKeyboardAttached;
uint8_t 	un8KeyInExt;
uint8_t 	un8FreezePicture;
uint8_t 	un8ArrowButtonMode;
uint8_t 	un8ArrowButtonMode_temp;
uint16_t 	un16MenuTimer;
uint8_t 	un8AEMode;
uint8_t		un8SettingBrightness;
uint8_t		un8FocusLocked;
uint8_t		un8FocusMode;
uint8_t		un8MemoryMode;
uint8_t		un8CurrentHCursor;
uint8_t		un8CurrentVCursor;
uint16_t	un16Cursor1;
uint16_t	un16Cursor2;
uint16_t	un16Cursor3;
uint16_t	un16Cursor4;
uint16_t	un16GridX;
uint16_t	un16GridY;
uint8_t		un8TurnMenuOff;
uint8_t 	un8ExtKBMenuMode;
};

struct CameraVars //CameraFCB_H11
{
uint8_t		un8WideDynamicRange;
uint8_t 	un8DisplayBrightnessLevel;
uint8_t 	un8BrightnessCompensationSelection;
uint8_t 	un8CompensationLevel;
uint8_t		un8DeFog;
uint8_t 	un8ColorHue;
uint8_t		un8InfraredMode;
uint8_t		un8NoiseReduction;

// 			Lens Control Variables
uint16_t	un16ZoomPosition;
uint8_t		un8FocusNearLimit;
uint16_t	un16FocusPosition;
uint8_t		un8DZoomMode;
uint8_t		un8ZoomModeNIZT;
uint8_t		un8AFSensitivity;
//uint8_t		un8DigitalZoom;
uint8_t		un8AFMode;
uint8_t		un8FocusMode;
uint8_t		un8LowContrastDetection;
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
uint8_t		un8HighResolution;
uint8_t		un8WD;
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
uint8_t		un8AutoICRAlarm;
uint8_t		un8AutoICR;
uint8_t		un8Keylock;
uint8_t		un8Power;
uint8_t		uint8Stabilizer;
uint8_t		uint8StabilizerHold;
uint8_t		un8ICR;
uint8_t		un8Freeze;
uint8_t		un8LRReverse;
uint8_t		un8PrivacyZone;
uint8_t		un8Mute;
uint8_t		un8TitleDisplay;
uint8_t		un8Display;
uint8_t		un8PictureEffectMode;
uint8_t		un8GammaMode;
uint16_t	un16CameraID;
uint8_t		un8Memory;
uint8_t		un8ICRProvided;
uint8_t		un8Stabilizer;
uint8_t		un8System;

// 			Camera Enlargement Functions
uint8_t		un8DigitalZoom;
uint8_t		un8AFActicationTime;
uint8_t		n8AFIntervalTime;
uint8_t		un8SpotAEPositionX;
uint8_t		un8SpotAEPositionY;
uint8_t 	un8MD;
uint8_t 	un8ColorGain;
uint8_t 	un8AdvancedPrivacy;
uint8_t 	un8PictureFlipProvided;
uint8_t 	un8AEResponse;
uint8_t 	un8Gamma;
uint8_t 	un8HighSensitivityMode;
uint8_t 	un8NRLevel;
uint8_t 	un8ChromaSuppress;
uint8_t 	un8GainLimit;
//uint8_t		un8AutoSlowShutterLimit;
//uint8_t		un8DZoomLimit;
uint8_t 	un8PictureFlip;
uint8_t 	un8DigitalZoomOn;
uint16_t 	CAMERA_ZOOM_LEVEL_MAX;
// RELOCATE TODO
uint8_t		un8AutomaticExposure;

uint8_t		un8TestByte;
}; //Camera;

struct System
{
uint8_t		un8LightLevel;
uint8_t 	un8SoundOn;
uint8_t 	un8LightOn;
uint8_t		un8CrossHairOn;
uint8_t		un8CrossHairSize;
uint8_t		un8CrossHairColor;
uint8_t 	un8DisplayRevision;
uint8_t		un8HPD;
uint8_t 	un8SystemVideoFormat;
uint8_t 	un8CameraPatch;
uint8_t 	un8RecallFactorySettings;
uint8_t		un8RecallFactorySettingsSure;
uint8_t		un8SCurveType;
uint8_t		un8Calibrated;
float 		fDx;
uint16_t 	cDiff;
uint8_t		un8InternalKeyPadLocked;
uint8_t		un8USBDeviceAttached;

struct 		CameraVars Camera;
struct 		ExtKey ExtKeyVars;

uint8_t		un8LenseDiopter;
float		fScreenHeight;
float		fScreenWidth;
uint16_t	un16ScreenDiagonalSize;
uint8_t		un8LockExternalKeypad;
//uint8_t		un8LockInternalKeypad;

uint8_t		un8LastDefault;

uint8_t 	un8CurrentMenuOption;
uint8_t 	un8LastMenuOption;

//RTC_TimeTypeDef TimeStructure;
//RTC_DateTypeDef DateStructure;

uint8_t		un8OSD_ON;

uint8_t		un8WhiteBalance;
uint8_t		un8MeasurementUnits;
uint8_t		un8UART1_Switch;

uint8_t 	un8Overview;

uint16_t	un16CameraOffsetX;
uint16_t	un16CameraOffsetY;
uint8_t		un8EngineeringMenu;
uint8_t		NUMBER_OF_MENU_LINES;

uint8_t		un8RemapFootswitch;

uint8_t		un8MemoryValidByte;


};

//struct CameraVars Camera;
//struct System SystemVars;

#define VIDEO_FORMAT_1080P_25HZ	4
#define VIDEO_FORMAT_1080P_30HZ	5
#define VIDEO_FORMAT_1080P_50HZ	0
#define VIDEO_FORMAT_1080P_60HZ	1
#define  VIDEO_FORMAT_720P_50HZ	2
#define  VIDEO_FORMAT_720P_60HZ	3
#define  VIDEO_FORMAT_720P_29HZ 8
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */
void SYSTEM_Initialize(void);
#endif	/* SYSTEM_H */
/**
 End of File
*/