/*
 * SiIxxxx <Firmware or Driver>
 *
 * Copyright (C) 2011 Silicon Image Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the
 * GNU General Public License for more details.
*/

//#include <stdio.h>
#include <linux/types.h>
//#include "si_mhl_tx_api.h"


#ifndef __SII_9244_API_H__
#define __SII_9244_API_H__

/* C99 defined data types.  */
typedef char Bool;
typedef    bool    bool_tt;


#define LOW                     0
#define HIGH                    1



// Generic Masks
//==============
#define _ZERO             0x00
#define BIT0                   0x01
#define BIT1                   0x02
#define BIT2                   0x04
#define BIT3                   0x08
#define BIT4                   0x10
#define BIT5                   0x20
#define BIT6                   0x40
#define BIT7                   0x80

/*
// Timers - Target system uses these timers
#define ELAPSED_TIMER               0xFF
#define ELAPSED_TIMER1             0xFE    // For from discovery to MHL est timeout

typedef enum TimerId
{
    TIMER_FOR_MONITORING= 0,        // HalTimerWait() is implemented using busy waiting
    TIMER_POLLING,        // Reserved for main polling loop
    TIMER_2,            // Available
    TIMER_SWWA_WRITE_STAT,
    TIMER_TO_DO_RSEN_CHK,
    TIMER_TO_DO_RSEN_DEGLITCH,
    TIMER_COUNT            // MUST BE LAST!!!!
} timerId_t;
*/
//
// This is the time in milliseconds we poll what we poll.
//
#define MONITORING_PERIOD        50

//#define SiI_DEVICE_ID            0xB0

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern bool    vbusPowerState;
extern uint16_t Int_count;
//------------------------------------------------------------------------------
// Array of timer values
//------------------------------------------------------------------------------
#if 0
extern uint16_t g_timerElapsed;
extern uint16_t g_elapsedTick;
extern uint16_t g_timerElapsedGranularity;

extern uint16_t g_timerElapsed1;
extern uint16_t g_elapsedTick1;
extern uint16_t g_timerElapsedGranularity1;

//extern uint16_t g_timerCounters[TIMER_COUNT];


void     HalTimerSet ( uint8_t index, uint16_t m_sec );
uint8_t     HalTimerExpired ( uint8_t index );

uint16_t    HalTimerElapsed( uint8_t index );
#endif

void        HalTimerWait ( uint16_t m_sec );

///////////////////////////////////////////////////////////////////////////////
//
// AppMhlTxDisableInterrupts
//
// This function or macro is invoked from MhlTx driver to secure the processor
// before entering into a critical region.
//
// Application module must provide this function.
//
extern    void    AppMhlTxDisableInterrupts( void );


///////////////////////////////////////////////////////////////////////////////
//
// AppMhlTxRestoreInterrupts
//
// This function or macro is invoked from MhlTx driver to secure the processor
// before entering into a critical region.
//
// Application module must provide this function.
//
extern    void    AppMhlTxRestoreInterrupts( void );


///////////////////////////////////////////////////////////////////////////////
//
// AppVbusControl
//
// This function or macro is invoked from MhlTx driver to ask application to
// control the VBUS power. If powerOn is sent as non-zero, one should assume
// peer does not need power so quickly remove VBUS power.
//
// if value of "powerOn" is 0, then application must turn the VBUS power on
// within 50ms of this call to meet MHL specs timing.
//
// Application module must provide this function.
//
extern    void    AppVbusControl( bool powerOn );

//====================================================
// VBUS power check for supply or charge
//====================================================
#define     VBUS_POWER_CHK                ENABLE //( DISABLE)

#define    POWER_STATE_D3                3
#define    POWER_STATE_D0_NO_MHL        2
#define    POWER_STATE_D0_MHL            0
#define    POWER_STATE_FIRST_INIT        0xFF

#endif  // __SII_9244_API_H__
