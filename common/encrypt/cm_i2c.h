// CryptoMemory I2C Header File
//
// This library is used in all of the low level hardware interface for I2C communications.
//
// Revision Date      Changes
// -------- --------- -----------------------------------------------------------------
//    0.1   26 Oct 04 First Release

// Protect Library against multiple inclusion
#ifndef CM_I2C_H
#define CM_I2C_H

// -------------------------------------------------------------------------------------------------
// Other includes required by this header file
// -------------------------------------------------------------------------------------------------

#include "cm_lib.h"

#ifdef USE_ORI_DRIVER /*LZ : we use new i2c driver on st5100*/
// -------------------------------------------------------------------------------------------------
// I/O Port Grouping
//
// Note: the "PORTx" in the header is the last address in the group of three port address
//
// -------------------------------------------------------------------------------------------------
#define IO_PORT_IN  (-2)
#define IO_PORT_DIR (-1)
#define IO_PORT_OUT (0)

// -------------------------------------------------------------------------------------------------
// Macros
// -------------------------------------------------------------------------------------------------

// Define control of the secure memory in terms of the pins defined in CM_PORT_CFG
//
#define CM_CLK_PD     (*(volatile unsigned char *)(CM_PORT_CFG.ucClockPort+IO_PORT_DIR))
#define CM_CLK_PO     (*(volatile unsigned char *)(CM_PORT_CFG.ucClockPort+IO_PORT_OUT))
#define CM_CLK_PIN    (CM_PORT_CFG.ucClockPin)
#define CM_CLK_OUT    CM_CLK_PD|=(1<<CM_CLK_PIN)
#define CM_CLK_LO     CM_CLK_PO&=~(1<<CM_CLK_PIN)
#define CM_CLK_HI     CM_CLK_PO|=(1<<CM_CLK_PIN)

#define CM_DATA_PI    (*(volatile unsigned char *)(CM_PORT_CFG.ucDataPort+IO_PORT_IN))
#define CM_DATA_PD    (*(volatile unsigned char *)(CM_PORT_CFG.ucDataPort+IO_PORT_DIR))
#define CM_DATA_PO    (*(volatile unsigned char *)(CM_PORT_CFG.ucDataPort+IO_PORT_OUT))
#define CM_DATA_PIN   (CM_PORT_CFG.ucDataPin)
#define CM_DATA_OUT   CM_DATA_PD|=(1<<CM_DATA_PIN)
#define CM_DATA_IN    CM_DATA_PD&=~(1<<CM_DATA_PIN)
#define CM_DATA_HI    CM_DATA_PO|=(1<<CM_DATA_PIN)
#define CM_DATA_LO    CM_DATA_PO&=~(1<<CM_DATA_PIN)
#define CM_DATA_RD    (CM_DATA_PI&(1<<CM_DATA_PIN))
#define CM_DATA_BIT   ((CM_DATA_PI>>CM_DATA_PIN)&1)

#define CM_DETECT_PI  (*(volatile unsigned char *)(CM_PORT_CFG.ucCardSensePort+IO_PORT_IN))
#define CM_DETECT_PD  (*(volatile unsigned char *)(CM_PORT_CFG.ucCardSensePort+IO_PORT_DIR))
#define CM_DETECT_PIN (CM_PORT_CFG.ucCardSensePin)
#define CM_DETECT_POL (CM_PORT_CFG.ucCardSensePolarity)
#define CM_DETECT_IN  CM_DETECT_PD&=~(1<<CM_DETECT_PIN)
#define CM_DETECT_RD  CM_DETECT_PI&(1<<CM_DETECT_PIN)

#define CM_POWER_PD  (*(volatile unsigned char *)(CM_PORT_CFG.ucPowerPort+IO_PORT_DIR))
#define CM_POWER_PO  (*(volatile unsigned char *)(CM_PORT_CFG.ucPowerPort+IO_PORT_OUT))
#define CM_POWER_PIN (CM_PORT_CFG.ucPowerPin)
#define CM_POWER_POL (CM_PORT_CFG.ucPowerPolarity)
#define CM_POWER_OUT CM_POWER_PD|=(1<<CM_POWER_PIN)
#define CM_POWER_HI  CM_POWER_PO|=(1<<CM_POWER_PIN)
#define CM_POWER_LO  CM_POWER_PO&=~(1<<CM_POWER_PIN)

#define CM_DIR_INIT   CM_CLK_PD|=(1<<CM_CLK_PIN);CM_DATA_PD|=(1<<CM_DATA_PIN)

#define CM_TIMER      (CM_PORT_CFG.ucDelayCount)
#define CM_START_TRIES (CM_PORT_CFG.ucStartTries)

// -------------------------------------------------------------------------------------------------
// Macros that replace small common function
// -------------------------------------------------------------------------------------------------

#define CM_CLOCKHIGH  cm_Delay(1);(CM_CLK_HI);cm_Delay(1)
#define CM_CLOCKLOW   cm_Delay(1);(CM_CLK_LO);cm_Delay(1)
#define CM_CLOCKCYCLE cm_Delay(1);(CM_CLK_LO);cm_Delay(2);(CM_CLK_HI);cm_Delay(1)
#else
//#include "stpio.h"

#if 0
#define	ClockOut()		SET_PIO_PIN(PIO_PORT(3), 4, STPIO_OUT)
#define Clocklow(void)	STPIO_SET_PIN(PIO_PORT(3), 4, 0)
#define ClockHigh(void)	STPIO_SET_PIN(PIO_PORT(3), 4, 0)
#define DataOut(void)	SET_PIO_PIN(PIO_PORT(3), 2, STPIO_OUT)
#define DataIn(void)	SET_PIO_PIN(PIO_PORT(3), 2, STPIO_IN)
#define Datalow(void)	STPIO_SET_PIN(PIO_PORT(3), 2, 0)
#define DataHigh(void)	STPIO_SET_PIN(PIO_PORT(3), 2, 1)
#define DataRd(void)	STPIO_GET_PIN(3, 2)

#else
void ClockOut(void);
void ClockLow(void);
void ClockHigh(void);
void DataOut(void);
void DataIn(void);
void Datalow(void);
void DataHigh(void);
uchar DataRd(void);
#endif
/*
void cm_InitI2c(STPIO_Handle_t PioHanle,
				STPIO_BitMask_t SclMask,
				STPIO_BitMask_t SdaMask);*/
void cm_InitI2c(void);
void cm_TermI2c(void);

// -------------------------------------------------------------------------------------------------
// I/O Port Grouping
//
// Note: the "PORTx" in the header is the last address in the group of three port address
//
// -------------------------------------------------------------------------------------------------
#define IO_PORT_IN  (-2)
#define IO_PORT_DIR (-1)
#define IO_PORT_OUT (0)

// -------------------------------------------------------------------------------------------------
// Macros
// -------------------------------------------------------------------------------------------------

// Define control of the secure memory in terms of the pins defined in CM_PORT_CFG
//
#define CM_CLK_PD
#define CM_CLK_PO
#define CM_CLK_PIN
#define CM_CLK_OUT    ClockOut()
#define CM_CLK_LO     ClockLow()
#define CM_CLK_HI     ClockHigh()

#define CM_DATA_PI
#define CM_DATA_PD
#define CM_DATA_PO
#define CM_DATA_PIN
#define CM_DATA_OUT   DataOut()
#define CM_DATA_IN    DataIn()
#define CM_DATA_HI    DataHigh()
#define CM_DATA_LO    Datalow()
#define CM_DATA_RD    DataRd()
#define CM_DATA_BIT

#define CM_DETECT_PI
#define CM_DETECT_PD
#define CM_DETECT_PIN
#define CM_DETECT_POL
#define CM_DETECT_IN
#define CM_DETECT_RD

#define CM_POWER_PD
#define CM_POWER_PO
#define CM_POWER_PIN
#define CM_POWER_POL
#define CM_POWER_OUT
#define CM_POWER_HI
#define CM_POWER_LO

#define CM_DIR_INIT

#define CM_TIMER      (CM_PORT_CFG.ucDelayCount)
#define CM_START_TRIES (CM_PORT_CFG.ucStartTries)

// -------------------------------------------------------------------------------------------------
// Macros that replace small common function
// -------------------------------------------------------------------------------------------------

#define CM_CLOCKHIGH  cm_Delay(1);(CM_CLK_HI);cm_Delay(1)
#define CM_CLOCKLOW   cm_Delay(1);(CM_CLK_LO);cm_Delay(1)
#define CM_CLOCKCYCLE cm_Delay(1);(CM_CLK_LO);cm_Delay(2);(CM_CLK_HI);cm_Delay(1)


#endif

// -------------------------------------------------------------------------------------------------
// Low Level Function Prototypes
// -------------------------------------------------------------------------------------------------

// Placeholder function that always returns TRUE
uchar cm_TRUE(void);

// Placeholder function that always returns SUCCESS
uchar cm_SUCCESS(void);

// Card Detect
uchar cm_CardDetect(void);

// Power On Functions
void cm_FullPowerOn(void);
void cm_PowerOn(void);

// Power Off Functions
void cm_FullPowerOff(void);
void cm_PowerOff(void);

// Send Command
uchar cm_SendCommand(puchar pucCommandBuffer);

// Receive Data
uchar cm_ReceiveData(puchar pucReceiveData, uchar ucLength);

// Send Data
uchar cm_SendData(puchar pucSendData, uchar ucLength);

// Random
void cm_RandGen(puchar pucRandomData);

// Wait Clock
void cm_WaitClock(uchar ucLoop);

// Send Command Byte
uchar cm_SendCmdByte(uchar ucCommand);

// end of multiple inclusion protection
#endif
