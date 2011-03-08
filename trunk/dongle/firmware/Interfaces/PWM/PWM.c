/**************************************************************************
 *  Copyright (C) 2008 - 2010 by Simon Qian                               *
 *  SimonQian@SimonQian.com                                               *
 *                                                                        *
 *  Project:    Versaloon                                                 *
 *  File:       PWM.c                                                     *
 *  Author:     SimonQian                                                 *
 *  Versaion:   See changelog                                             *
 *  Purpose:    PWM header file                                           *
 *  License:    See license                                               *
 *------------------------------------------------------------------------*
 *  Change Log:                                                           *
 *      YYYY-MM-DD:     What(by Who)                                      *
 *      2011-03-06:     created(by SimonQian)                             *
 **************************************************************************/

#include "app_cfg.h"
#if INTERFACE_PWM_EN

#include "interfaces.h"
#include "PWM.h"

static uint16_t pwm0_cycle = 0;
static uint16_t pwm_buff[512], pwm0_cur_rate = 0;

RESULT pwm_init(uint8_t index)
{
	switch (index)
	{
	case 0:
		return ERROR_OK;
	case 1:
		SYNCSWPWM_IN_TIMER_INIT();
		return ERROR_OK;
	default:
		return ERROR_FAIL;
	}
}

RESULT pwm_fini(uint8_t index)
{
	switch (index)
	{
	case 0:
		SYNCSWPWM_PORT_ODPP_FINI();
		SYNCSWPWM_OUT_TIMER_FINI();
		return ERROR_OK;
	case 1:
		SYNCSWPWM_IN_TIMER_FINI();
		return ERROR_OK;
	default:
		return ERROR_FAIL;
	}
}

RESULT pwm_config(uint8_t index, uint16_t kHz, uint8_t pushpull, uint8_t polarity)
{
	switch (index)
	{
	case 0:
		SYNCSWPWM_OUT_TIMER_INIT(polarity);
		if (pushpull)
		{
			SYNCSWPWM_PORT_PP_INIT();
		}
		else
		{
			SYNCSWPWM_PORT_OD_INIT();
		}
		
		pwm0_cycle = SYNCSWPWM_OUT_TIMER_MHZ * 1000 / kHz;
		SYNCSWPWM_OUT_TIMER_SetCycle(pwm0_cycle);
		if (pwm0_cur_rate)
		{
			SYNCSWPWM_OUT_TIMER_SetRate(pwm0_cur_rate * pwm0_cycle / 0xFFFF);
		}
		return ERROR_OK;
	case 1:
		return ERROR_OK;
	default:
		return ERROR_FAIL;
	}
}

RESULT pwm_out(uint8_t index, uint16_t count, uint16_t *rate)
{
	uint16_t i;
	
	switch (index)
	{
	case 0:
		if ((count > dimof(pwm_buff)) || (NULL == rate))
		{
			return ERROR_FAIL;
		}
		
		pwm0_cur_rate = rate[count - 1];
		for (i = 0; i < count; i++)
		{
			pwm_buff[i] = rate[i] * pwm0_cycle / 0xFFFF;
		}
		SYNCSWPWM_OUT_TIMER_DMA_INIT(count, pwm_buff);
		SYNCSWPWM_OUT_TIMER_DMA_WAIT();
		return ERROR_OK;
	default:
		return ERROR_FAIL;
	}
}

RESULT pwm_in(uint8_t index, uint16_t count, uint16_t *rate)
{
	uint32_t dly;
	
	switch (index)
	{
	case 1:
		if ((count > dimof(pwm_buff) / 2) || (NULL == rate))
		{
			return ERROR_FAIL;
		}
		
		SYNCSWPWM_IN_TIMER_DMA_INIT(count, pwm_buff, pwm_buff + count);
		dly = 0xFFFFFFFF;
		SYNCSWPWM_IN_TIMER_RISE_DMA_WAIT(dly);
		if (dly)
		{
			memcpy(rate, pwm_buff, 4 * count);
		}
		return dly ? ERROR_OK : ERROR_FAIL;
	default:
		return ERROR_FAIL;
	}
}

#endif