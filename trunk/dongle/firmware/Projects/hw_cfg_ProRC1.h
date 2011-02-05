/**************************************************************************
 *  Copyright (C) 2008 - 2010 by Simon Qian                               *
 *  SimonQian@SimonQian.com                                               *
 *                                                                        *
 *  Project:    Versaloon                                                 *
 *  File:       hw_cfg_ProRC1.h                                           *
 *  Author:     SimonQian                                                 *
 *  Versaion:   See changelog                                             *
 *  Purpose:    hardware configuration file for Pro Version RC1           *
 *  License:    See license                                               *
 *------------------------------------------------------------------------*
 *  Change Log:                                                           *
 *      YYYY-MM-DD:     What(by Who)                                      *
 *      2008-11-07:     created(by SimonQian)                             *
 *      2008-11-22:     rewrite GPIO_Dir(by SimonQian)                    *
 **************************************************************************/

#ifndef HSE_VALUE
#define HSE_VALUE						((uint32_t)12000000)
#endif

#define _SYS_FREQUENCY					72		// in MHz
#define _SYS_FLASH_VECTOR_TABLE_SHIFT	FLASH_LOAD_OFFSET // From board_defs.mk

/****************************** Power ******************************/
#define PWREXT_EN_PORT					GPIOB
#define PWREXT_EN_PIN					GPIO_PIN_8

#define PWREXT_INIT()					PWREXT_DISABLE()
#define PWREXT_ENABLE()					do{\
											GPIO_ClrPins(PWREXT_EN_PORT, PWREXT_EN_PIN);\
											GPIO_SetMode(PWREXT_EN_PORT, PWREXT_EN_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define PWREXT_DISABLE()				GPIO_SetMode(PWREXT_EN_PORT, PWREXT_EN_PIN, GPIO_MODE_IN_FLOATING)

/****************************** Global Output ******************************/
#define GLOBAL_OUTPUT_ENABLE_PORT		GPIOB
#define GLOBAL_OUTPUT_ENABLE_PIN		GPIO_PIN_1

#define GLOBAL_OUTPUT_INIT()			do{\
											GLOBAL_OUTPUT_DISABLE();\
											GPIO_SetMode(GLOBAL_OUTPUT_ENABLE_PORT, GLOBAL_OUTPUT_ENABLE_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define GLOBAL_OUTPUT_ENABLE()			GPIO_ClrPins(GLOBAL_OUTPUT_ENABLE_PORT, GLOBAL_OUTPUT_ENABLE_PIN)
#define GLOBAL_OUTPUT_DISABLE()			GPIO_SetPins(GLOBAL_OUTPUT_ENABLE_PORT, GLOBAL_OUTPUT_ENABLE_PIN)

/****************************** DelayTimer ******************************/
#define DELAYTIMER_MAXDELAY_US			200000

#define DELAYTIMER_INIT()				do{\
											SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;\
											SysTick->CTRL |= SysTick_CLKSource_HCLK;\
											SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;\
											SysTick->VAL = 0;\
										} while (0)

#define DELAYTIMER_DelayUS_Start(us)	do{\
											SysTick->LOAD = (us) * _SYS_FREQUENCY;\
											SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;\
										} while (0)
#define DELAYTIMER_DelayUS_IsReady()	(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
#define DELAYTIMER_DelayUS_End()		do{\
											SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;\
											SysTick->VAL = 0;\
										} while (0)

#define DELAYTIMER_DelayUS(us)			do{\
											DELAYTIMER_DelayUS_Start(us);\
											while (!DELAYTIMER_DelayUS_IsReady());\
											DELAYTIMER_DelayUS_End();\
										} while (0)

/****************************** SW ******************************/
#define SW_PORT							GPIOB
#define SW_PIN							GPIO_PIN_11
#define SW_DIR_PORT						GPIOB
#define SW_DIR_PIN						GPIO_PIN_12
#define SW_PULL_PORT					GPIOA
#define SW_PULL_PIN						GPIO_PIN_2
#define SW_RST_PORT						GPIOB
#define SW_RST_PIN						GPIO_PIN_10
#define SW_RST_DIR_PORT					GPIOA
#define SW_RST_DIR_PIN					GPIO_PIN_0
#define SW_RST_PULL_PORT				GPIOA
#define SW_RST_PULL_PIN					GPIO_PIN_15
#define SYNCSW_IN_PORT					GPIOB
#define SYNCSW_IN_PIN					GPIO_PIN_4
#define SYNCSW_OUT_PORT					GPIOB
#define SYNCSW_OUT_PIN					GPIO_PIN_5
#define SYNCSW_DIR_PORT					GPIOA
#define SYNCSW_DIR_PIN					GPIO_PIN_1

#define SW_PULL_INIT()					do{\
											GPIO_ClrPins(SW_PULL_PORT, SW_PULL_PIN);\
											GPIO_SetMode(SW_PULL_PORT, SW_PULL_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SW_PULL_SET()					GPIO_SetPins(SW_PULL_PORT, SW_PULL_PIN)
#define SW_PULL_CLR()					GPIO_ClrPins(SW_PULL_PORT, SW_PULL_PIN)

#define SW_DIR_INIT()					do{\
											SW_SETINPUT_PD();\
											GPIO_SetMode(SW_DIR_PORT, SW_DIR_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SW_SETINPUT()					SW_SETINPUT_PU()
#define SW_SETINPUT_PU()				do{\
											SW_PULL_SET();\
											GPIO_SetMode(SW_PORT, SW_PIN, GPIO_MODE_IPU);\
											GPIO_ClrPins(SW_DIR_PORT, SW_DIR_PIN);\
										}while(0)
#define SW_SETINPUT_PD()				do{\
											SW_PULL_CLR();\
											GPIO_SetMode(SW_PORT, SW_PIN, GPIO_MODE_IPD);\
											GPIO_ClrPins(SW_DIR_PORT, SW_DIR_PIN);\
										}while(0)
#define SW_SETOUTPUT()					do{\
											GPIO_SetPins(SW_DIR_PORT, SW_DIR_PIN);\
											GPIO_SetMode(SW_PORT, SW_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SW_SETOUTPUT_OD()				SW_SETOUTPUT()
#define SW_SET()						GPIO_SetPins(SW_PORT, SW_PIN)
#define SW_CLR()						GPIO_ClrPins(SW_PORT, SW_PIN)
#define SW_GET()						GPIO_GetInPins(SW_PORT, SW_PIN)

#define SW_RST_PULL_INIT()				do{\
											GPIO_ClrPins(SW_RST_PULL_PORT, SW_RST_PULL_PIN);\
											GPIO_SetMode(SW_RST_PULL_PORT, SW_RST_PULL_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SW_RST_PULL_SET()				GPIO_SetPins(SW_RST_PULL_PORT, SW_RST_PULL_PIN)
#define SW_RST_PULL_CLR()				GPIO_ClrPins(SW_RST_PULL_PORT, SW_RST_PULL_PIN)

#define SW_RST_DIR_INIT()				do{\
											SW_RST_SETINPUT_PD();\
											GPIO_SetMode(SW_RST_DIR_PORT, SW_RST_DIR_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SW_RST_SETINPUT_PU()			do{\
											SW_RST_PULL_SET();\
											GPIO_SetMode(SW_RST_PORT, SW_RST_PIN, GPIO_MODE_IPU);\
											GPIO_ClrPins(SW_RST_DIR_PORT, SW_RST_DIR_PIN);\
										}while(0)
#define SW_RST_SETINPUT_PD()			do{\
											SW_RST_PULL_CLR();\
											GPIO_SetMode(SW_RST_PORT, SW_RST_PIN, GPIO_MODE_IPD);\
											GPIO_ClrPins(SW_RST_DIR_PORT, SW_RST_DIR_PIN);\
										}while(0)
#define SW_RST_SETOUTPUT()				do{\
											GPIO_SetPins(SW_RST_DIR_PORT, SW_RST_DIR_PIN);\
											GPIO_SetMode(SW_RST_PORT, SW_RST_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SW_RST_SET()					GPIO_SetPins(SW_RST_PORT, SW_RST_PIN)
#define SW_RST_CLR()					GPIO_ClrPins(SW_RST_PORT, SW_RST_PIN)
#define SW_RST_GET()					GPIO_GetInPins(SW_RST_PORT, SW_RST_PIN)

#define SYNCSW_DIR_INIT()				do{\
											SYNCSW_SETINPUT();\
											GPIO_SetMode(SYNCSW_IN_PORT, SYNCSW_IN_PIN, GPIO_MODE_IPU);\
											GPIO_SetMode(SYNCSW_DIR_PORT, SYNCSW_DIR_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SYNCSW_SETINPUT()				do{\
											GPIO_SetMode(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_ClrPins(SYNCSW_DIR_PORT, SYNCSW_DIR_PIN);\
										}while(0)
#define SYNCSW_SETOUTPUT()				do{\
											GPIO_SetPins(SYNCSW_DIR_PORT, SYNCSW_DIR_PIN);\
											GPIO_SetMode(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SYNCSW_SET()					GPIO_SetPins(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN)
#define SYNCSW_CLR()					GPIO_ClrPins(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN)
#define SYNCSW_GET()					GPIO_GetInPins(SYNCSW_IN_PORT, SYNCSW_IN_PIN)

/***************************** STM8_SWIM ******************************/
#define SWIM_PORT_INIT_GPIO()			do{\
											GPIO_SetMode(SYNCSW_IN_PORT, SYNCSW_IN_PIN, GPIO_MODE_IPD);\
											GPIO_SetPins(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN);\
											GPIO_SetMode(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN, GPIO_MODE_OUT_OD);\
											SWIM_SETINPUT();\
											GPIO_SetMode(SYNCSW_DIR_PORT, SYNCSW_DIR_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define SWIM_SETINPUT()					GPIO_ClrPins(SYNCSW_DIR_PORT, SYNCSW_DIR_PIN)
#define SWIM_SETOUTPUT()				do{\
											GPIO_SetPins(SYNCSW_DIR_PORT, SYNCSW_DIR_PIN);\
											GPIO_ClrPins(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN);\
											GPIO_SetPins(SYNCSW_OUT_PORT, SYNCSW_OUT_PIN);\
										}while(0)
#define SWIM_SET()						SWIM_SETINPUT()
#define SWIM_CLR()						SWIM_SETOUTPUT()
#define SWIM_GET()						GPIO_GetInPins(SYNCSW_IN_PORT, SYNCSW_IN_PIN)

#define SWIM_PORT_INIT_PWM()			

/***************************** SWD ******************************/
#define SWD_SWDIO_SETOUTPUT()			JTAG_TAP_TMS_SETOUTPUT()
#define SWD_SWDIO_SETINPUT()			JTAG_TAP_TMS_SETINPUT()
#define SWD_SWDIO_SET()					JTAG_TAP_TMS_SET()
#define SWD_SWDIO_CLR()					JTAG_TAP_TMS_CLR()
#define SWD_SWDIO_GET()					JTAG_TAP_TMS_GET()

#define SWD_SWCLK_SETOUTPUT()			JTAG_TAP_TCK_SETOUTPUT()
#define SWD_SWCLK_SETINPUT()			JTAG_TAP_TCK_SETINPUT()
#define SWD_SWCLK_SET()					JTAG_TAP_TCK_SET()
#define SWD_SWCLK_CLR()					JTAG_TAP_TCK_CLR()

/***************************** JTAG ******************************/
#define JTAG_TAP_PORT					GPIOB
#define JTAG_TAP_TCK_PIN				GPIO_PIN_13
#define JTAG_TAP_TDO_PIN				GPIO_PIN_14
#define JTAG_TAP_TDI_PIN				GPIO_PIN_15
#define JTAG_TAP_RTCK_PORT				GPIOA
#define JTAG_TAP_RTCK_PIN				GPIO_PIN_8

#define JTAG_HAS_USER_PIN				1

#define JTAG_TAP_USR_PORT				GPIOA
#define JTAG_TAP_USR1_PIN				GPIO_PIN_9
#define JTAG_TAP_USR2_PIN				GPIO_PIN_10

#define JTAG_TAP_USR1_SETOUTPUT()		GPIO_SetMode(JTAG_TAP_USR_PORT, JTAG_TAP_USR1_PIN, GPIO_MODE_OUT_PP)
#define JTAG_TAP_USR1_SETINPUT()		GPIO_SetMode(JTAG_TAP_USR_PORT, JTAG_TAP_USR1_PIN, GPIO_MODE_IN_FLOATING)
#define JTAG_TAP_USR1_SET()				GPIO_SetPins(JTAG_TAP_USR_PORT, JTAG_TAP_USR1_PIN)
#define JTAG_TAP_USR1_CLR()				GPIO_ClrPins(JTAG_TAP_USR_PORT, JTAG_TAP_USR1_PIN)
#define JTAG_TAP_USR1_GET()				GPIO_GetInPins(JTAG_TAP_USR_PORT, JTAG_TAP_USR1_PIN)

#define JTAG_TAP_USR2_SETOUTPUT()		GPIO_SetMode(JTAG_TAP_USR_PORT, JTAG_TAP_USR2_PIN, GPIO_MODE_OUT_PP)
#define JTAG_TAP_USR2_SETINPUT()		GPIO_SetMode(JTAG_TAP_USR_PORT, JTAG_TAP_USR2_PIN, GPIO_MODE_IN_FLOATING)
#define JTAG_TAP_USR2_SET()				GPIO_SetPins(JTAG_TAP_USR_PORT, JTAG_TAP_USR2_PIN)
#define JTAG_TAP_USR2_CLR()				GPIO_ClrPins(JTAG_TAP_USR_PORT, JTAG_TAP_USR2_PIN)
#define JTAG_TAP_USR2_GET()				GPIO_GetInPins(JTAG_TAP_USR_PORT, JTAG_TAP_USR2_PIN)

#define JTAG_TAP_TMS_SETOUTPUT()		SYNCSW_SETOUTPUT()
#define JTAG_TAP_TMS_SETINPUT()			SYNCSW_SETINPUT()
#define JTAG_TAP_TMS_SET()				SYNCSW_SET()
#define JTAG_TAP_TMS_CLR()				SYNCSW_CLR()
#define JTAG_TAP_TMS_GET()				SYNCSW_GET()

#define JTAG_TAP_TCK_SETOUTPUT()		GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TCK_PIN, GPIO_MODE_OUT_PP)
#define JTAG_TAP_TCK_SETINPUT()			GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TCK_PIN, GPIO_MODE_IN_FLOATING)
#define JTAG_TAP_TCK_SET()				GPIO_SetPins(JTAG_TAP_PORT, JTAG_TAP_TCK_PIN)
#define JTAG_TAP_TCK_CLR()				GPIO_ClrPins(JTAG_TAP_PORT, JTAG_TAP_TCK_PIN)
#define JTAG_TAP_TCK_GET()				GPIO_GetOutPins(JTAG_TAP_PORT, JTAG_TAP_TCK_PIN)

#define JTAG_TAP_TDI_SETOUTPUT()		GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TDI_PIN, GPIO_MODE_OUT_PP)
#define JTAG_TAP_TDI_SETINPUT()			GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TDI_PIN, GPIO_MODE_IN_FLOATING)
#define JTAG_TAP_TDI_SET()				GPIO_SetPins(JTAG_TAP_PORT, JTAG_TAP_TDI_PIN)
#define JTAG_TAP_TDI_CLR()				GPIO_ClrPins(JTAG_TAP_PORT, JTAG_TAP_TDI_PIN)
#define JTAG_TAP_TDI_GET()				GPIO_GetOutPins(JTAG_TAP_PORT, JTAG_TAP_TDI_PIN)

#define JTAG_TAP_TDO_SETINPUT()			GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TDO_PIN, GPIO_MODE_IN_FLOATING)
#define JTAG_TAP_TDO_SET()				GPIO_SetPins(JTAG_TAP_PORT, JTAG_TAP_TDO_PIN)
#define JTAG_TAP_TDO_CLR()				GPIO_ClrPins(JTAG_TAP_PORT, JTAG_TAP_TDO_PIN)
#define JTAG_TAP_TDO_GET()				GPIO_GetInPins(JTAG_TAP_PORT, JTAG_TAP_TDO_PIN)

#define JTAG_TAP_TRST_SETOUTPUT()		SW_RST_SETOUTPUT()
#define JTAG_TAP_TRST_SETINPUT()		SW_RST_SETINPUT_PU()
#define JTAG_TAP_TRST_SET()				SW_RST_SET()
#define JTAG_TAP_TRST_CLR()				SW_RST_CLR()
#define JTAG_TAP_TRST_GET()				SW_RST_GET()

#define JTAG_TAP_RTCK_SETINPUT()		GPIO_SetMode(JTAG_TAP_RTCK_PORT, JTAG_TAP_RTCK_PIN, GPIO_MODE_IN_FLOATING)
#define JTAG_TAP_RTCK_GET()				GPIO_GetInPins(JTAG_TAP_RTCK_PORT, JTAG_TAP_RTCK_PIN)

#define JTAG_TAP_SRST_SETOUTPUT()		SW_SETOUTPUT()
#define JTAG_TAP_SRST_SETINPUT()		SW_SETINPUT_PU()
#define JTAG_TAP_SRST_SET()				SW_SET()
#define JTAG_TAP_SRST_CLR()				SW_CLR()
#define JTAG_TAP_SRST_GET()				SW_GET()


#define JTAG_TAP_HS_SPI_M				SPI2
#define JTAG_TAP_HS_SPI_S				SPI1

// DMA
#define JTAG_TAP_HS_SPI_M_TX_DMA		DMA1_Channel5
#define JTAG_TAP_HS_SPI_M_RX_DMA		DMA1_Channel4
#define JTAG_TAP_HS_SPI_S_TX_DMA		DMA1_Channel3

#define JTAG_TAP_HS_SPI_EnableDMA()		do{\
											SPI_I2S_DMACmd(JTAG_TAP_HS_SPI_M, SPI_I2S_DMAReq_Rx, ENABLE);\
											SPI_I2S_DMACmd(JTAG_TAP_HS_SPI_S, SPI_I2S_DMAReq_Tx, ENABLE);\
										}while(0)

#define JTAG_TAP_HS_SPIS_Disable()		SPI_Cmd(JTAG_TAP_HS_SPI_S, DISABLE)
#define JTAG_TAP_HS_SPIS_Enable()		SPI_Cmd(JTAG_TAP_HS_SPI_S, ENABLE)

#define JTAG_TAP_HS_DMA_FINI()			do{\
											DMA_DeInit(JTAG_TAP_HS_SPI_M_RX_DMA);\
											DMA_DeInit(JTAG_TAP_HS_SPI_M_TX_DMA);\
											DMA_DeInit(JTAG_TAP_HS_SPI_S_TX_DMA);\
											RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, DISABLE);\
										} while (0)
#define JTAG_TAP_HS_DMA_INIT()			do{\
											DMA_InitTypeDef  DMA_InitStructure;\
											\
											RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);\
											\
											DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&JTAG_TAP_HS_SPI_M->DR;\
											DMA_InitStructure.DMA_MemoryBaseAddr = (uint32)0;\
											DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;\
											DMA_InitStructure.DMA_BufferSize = 0;\
											DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;\
											DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;\
											DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;\
											DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;\
											DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;\
											DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;\
											DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;\
											DMA_Init(JTAG_TAP_HS_SPI_M_RX_DMA, &DMA_InitStructure);\
											\
											DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&JTAG_TAP_HS_SPI_S->DR;\
											DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;\
											DMA_Init(JTAG_TAP_HS_SPI_S_TX_DMA, &DMA_InitStructure);\
											\
											JTAG_TAP_HS_SPI_EnableDMA();\
										} while (0)

#define JTAG_TAP_HS_SPI_M_RX_DMA_LEN(l)	(JTAG_TAP_HS_SPI_M_RX_DMA->CNDTR = (uint32)(l))
#define JTAG_TAP_HS_SPI_M_RX_DMA_ADDR(a)(JTAG_TAP_HS_SPI_M_RX_DMA->CMAR = (uint32)(a))
#define JTAG_TAP_HS_SPI_M_RX_DMA_EN()	(JTAG_TAP_HS_SPI_M_RX_DMA->CCR |= (uint32)1)
#define JTAG_TAP_HS_SPI_M_RX_DMA_DIS()	(JTAG_TAP_HS_SPI_M_RX_DMA->CCR &= ~(uint32)1)
#define JTAG_TAP_HS_SPI_M_RX_DMA_WAIT()	do{while(!(DMA1->ISR & DMA1_FLAG_TC4)); DMA1->IFCR = DMA1_FLAG_TC4;}while(0)

#define JTAG_TAP_HS_SPI_S_TX_DMA_LEN(l)	(JTAG_TAP_HS_SPI_S_TX_DMA->CNDTR = (uint32)(l))
#define JTAG_TAP_HS_SPI_S_TX_DMA_ADDR(a)(JTAG_TAP_HS_SPI_S_TX_DMA->CMAR = (uint32)(a))
#define JTAG_TAP_HS_SPI_S_TX_DMA_EN()	(JTAG_TAP_HS_SPI_S_TX_DMA->CCR |= (uint32)1)
#define JTAG_TAP_HS_SPI_S_TX_DMA_DIS()	(JTAG_TAP_HS_SPI_S_TX_DMA->CCR &= ~(uint32)1)
#define JTAG_TAP_HS_SPI_S_TX_DMA_WAIT()	do{while(!(DMA1->ISR & DMA1_FLAG_TC3)); DMA1->IFCR = DMA1_FLAG_TC3;}while(0)

#define JTAG_TAP_HS_MPORT				GPIOB

#define JTAG_TAP_HS_SPORT				GPIOB
#define JTAG_TAP_TCK1_PIN				GPIO_PIN_3
#define JTAG_TAP_TMS_PIN				GPIO_PIN_4

#define JTAG_TAP_HS_PortIOInit()		do{\
											GPIO_SetMode(JTAG_TAP_HS_MPORT, JTAG_TAP_TCK_PIN, GPIO_MODE_AF_PP);\
											GPIO_SetMode(JTAG_TAP_HS_MPORT, JTAG_TAP_TDO_PIN, GPIO_MODE_AF_PP);\
											GPIO_SetMode(JTAG_TAP_HS_MPORT, JTAG_TAP_TDI_PIN, GPIO_MODE_AF_PP);\
											GPIO_SetMode(JTAG_TAP_HS_SPORT, JTAG_TAP_TCK1_PIN, GPIO_MODE_AF_PP);\
											GPIO_SetMode(JTAG_TAP_HS_SPORT, JTAG_TAP_TMS_PIN, GPIO_MODE_AF_PP);\
											JTAG_TAP_TMS_SETOUTPUT();\
										}while(0)

#define JTAG_TAP_HS_PortIOFini()		do{\
											JTAG_TAP_TMS_SETINPUT();\
											GPIO_SetMode(JTAG_TAP_HS_MPORT, JTAG_TAP_TCK_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(JTAG_TAP_HS_MPORT, JTAG_TAP_TDO_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(JTAG_TAP_HS_MPORT, JTAG_TAP_TDI_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(JTAG_TAP_HS_SPORT, JTAG_TAP_TCK1_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(JTAG_TAP_HS_SPORT, JTAG_TAP_TMS_PIN, GPIO_MODE_IN_FLOATING);\
										}while(0)

#define JTAG_TAP_HS_PortInit()			do{\
											RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);\
											RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);\
											GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);\
											JTAG_TAP_HS_PortIOInit();\
										}while(0)
#define JTAG_TAP_HS_PortFini()			do{\
											JTAG_TAP_HS_PortIOFini();\
											RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);\
											RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);\
											GPIO_PinRemapConfig(GPIO_Remap_SPI1, DISABLE);\
										}while(0)

#define JTAG_TAP_HS_SetSpeed(div)		do{\
											SPI_Configuration(JTAG_TAP_HS_SPI_M, SPI_Mode_Master, (div),\
																SPI_FirstBit_LSB, SPI_CPOL_High, SPI_CPHA_2Edge);\
											SPI_Configuration(JTAG_TAP_HS_SPI_S, SPI_Mode_Slave,SPI_BaudRatePrescaler_2, \
																SPI_FirstBit_LSB, SPI_CPOL_High, SPI_CPHA_2Edge);\
										}while(0)

#define JTAG_TAP_HS_TMS_Out(tms)		JTAG_TAP_HS_SPI_S->DR = (tms)
#define JTAG_TAP_HS_TDI_Out(tdi)		JTAG_TAP_HS_SPI_M->DR = (tdi)
#define JTAG_TAP_HS_Out(tms, tdi)		do{JTAG_TAP_HS_TMS_Out(tms); JTAG_TAP_HS_TDI_Out(tdi);}while(0)
#define JTAG_TAP_HS_In()				JTAG_TAP_HS_SPI_M->DR

#define JTAG_TAP_HS_WaitTxReady()		while(!(JTAG_TAP_HS_SPI_M->SR & SPI_I2S_FLAG_TXE))
#define JTAG_TAP_HS_WaitRxReady()		while(!(JTAG_TAP_HS_SPI_M->SR & SPI_I2S_FLAG_RXNE))
#define JTAG_TAP_HS_WaitReady()			while(JTAG_TAP_HS_SPI_M->SR & SPI_I2S_FLAG_BSY)

/****************************** SPI ******************************/
#define SPI_Interface					SPI2

#define SPI_Conf(br, fb, cpol, cpha)	SPI_Configuration(SPI_Interface,SPI_Mode_Master,\
															(br),(fb),(cpol),(cpha))

#define SPI_MOSI_SET()					JTAG_TAP_TDI_SET()
#define SPI_MOSI_CLR()					JTAG_TAP_TDI_CLR()
#define SPI_MOSI_GET()					JTAG_TAP_TDI_GET()
#define SPI_MOSI_SETOUTPUT()			JTAG_TAP_TDI_SETOUTPUT()
#define SPI_MOSI_SETINPUT()				JTAG_TAP_TDI_SETINPUT()

#define SPI_MISO_GET()					JTAG_TAP_TDO_GET()
#define SPI_MISO_SETINPUT()				JTAG_TAP_TDO_SETINPUT()
#define SPI_MISO_SETINPUT_PU()			GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TDO_PIN, GPIO_MODE_IPU)

#define SPI_SCK_SET()					JTAG_TAP_TCK_SET()
#define SPI_SCK_CLR()					JTAG_TAP_TCK_CLR()
#define SPI_SCK_GET()					JTAG_TAP_TCK_GET()
#define SPI_SCK_SETOUTPUT()				JTAG_TAP_TCK_SETOUTPUT()
#define SPI_SCK_SETINPUT()				JTAG_TAP_TCK_SETINPUT()

#define SPI_Disable()					SPI_I2S_DeInit(SPI_Interface)
#define SPI_SetData(d)					SPI_Interface->DR = (d)
#define SPI_GetData()					SPI_Interface->DR
#define SPI_WaitReady()					while((SPI_Interface->SR & SPI_I2S_FLAG_BSY))
#define SPI_WaitRxReady()				while(!(SPI_Interface->SR & SPI_I2S_FLAG_RXNE))
#define SPI_WaitTxReady()				while(!(SPI_Interface->SR & SPI_I2S_FLAG_TXE))

#define SPI_AllInput()					do{\
											SPI_SCK_SETINPUT();\
											SPI_MISO_SETINPUT();\
											SPI_MOSI_SETINPUT();\
											RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);\
										}while(0)
#define SPI_AllSPIIO()					do{\
											SPI_SCK_SETOUTPUT();\
											SPI_MOSI_SETOUTPUT();\
											SPI_MISO_SETINPUT_PU();\
										}while(0)
#define SPI_AllSPIHW()					do{\
											RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);\
											GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TCK_PIN, GPIO_MODE_AF_PP);\
											GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TDO_PIN, GPIO_MODE_AF_PP);\
											GPIO_SetMode(JTAG_TAP_PORT, JTAG_TAP_TDI_PIN, GPIO_MODE_AF_PP);\
										}while(0)


/****************************** Reset ******************************/
#define RST_SET()						SW_SET()
#define RST_CLR()						SW_CLR()
#define RST_GET()						SW_GET()

#define RST_SETOUTPUT()					SW_SETOUTPUT()
#define RST_SETINPUT()					SW_SETINPUT_PU()

/************************** MSP430 JTAG ****************************/
#define MSP430_JTAG_TEST_SETOUTPUT()	JTAG_TAP_TRST_SETOUTPUT()
#define MSP430_JTAG_TEST_SETINPUT()		JTAG_TAP_TRST_SETINPUT()
#define MSP430_JTAG_TEST_SET()			JTAG_TAP_TRST_SET()
#define MSP430_JTAG_TEST_CLR()			JTAG_TAP_TRST_CLR()
#define MSP430_JTAG_TEST_GET()			JTAG_TAP_TRST_GET()

/************************** MSP430 SBW ****************************/
#define MSP430_SBWTDIO_SETOUTPUT()		SW_SETOUTPUT()
#define MSP430_SBWTDIO_SETINPUT()		SW_SETINPUT_PU()
#define MSP430_SBWTDIO_SET()			SW_SET()
#define MSP430_SBWTDIO_CLR()			SW_CLR()
#define MSP430_SBWTDIO_GET()			SW_GET()

#define MSP430_SBWTCK_SETOUTPUT()		MSP430_JTAG_TCK_SETOUTPUT()
#define MSP430_SBWTCK_SETINPUT()		MSP430_JTAG_TCK_SETINPUT()
#define MSP430_SBWTCK_SET()				MSP430_JTAG_TCK_SET()
#define MSP430_SBWTCK_CLR()				MSP430_JTAG_TCK_CLR()

/************************** PSoC1 ISSP ****************************/
#define ISSP_SDATA_SET()				SW_SET()
#define ISSP_SDATA_CLR()				SW_CLR()
#define ISSP_SDATA_GET()				SW_GET()
#define ISSP_SDATA_SETOUTPUT()			SW_SETOUTPUT()
#define ISSP_SDATA_SETINPUT()			SW_SETINPUT_PD()

#define ISSP_SCLK_SET()					JTAG_TAP_TCK_SET()
#define ISSP_SCLK_CLR()					JTAG_TAP_TCK_CLR()
#define ISSP_SCLK_SETOUTPUT()			JTAG_TAP_TCK_SETOUTPUT()
#define ISSP_SCLK_SETINPUT()			JTAG_TAP_TCK_SETINPUT()

#define ISSP_XRES_SET()					SW_RST_SET()
#define ISSP_XRES_CLR()					SW_RST_CLR()
#define ISSP_XRES_SETOUTPUT()			SW_RST_SETOUTPUT()
#define ISSP_XRES_SETINPUT()			SW_RST_SETINPUT_PU()

#define ISSP_PowerOn()					PWREXT_ENABLE()
#define ISSP_PowerOff()					PWREXT_DISABLE()

/****************************** C2 ******************************/
#define C2_C2CK_SET()					JTAG_TAP_TCK_SET()
#define C2_C2CK_CLR()					JTAG_TAP_TCK_CLR()
#define C2_C2CK_SETOUTPUT()				JTAG_TAP_TCK_SETOUTPUT()
#define C2_C2CK_SETINPUT()				JTAG_TAP_TCK_SETINPUT()

#define C2_C2D_SET()					SW_SET()
#define C2_C2D_CLR()					SW_CLR()
#define C2_C2D_GET()					SW_GET()
#define C2_C2D_SETOUTPUT()				SW_SETOUTPUT()
#define C2_C2D_SETINPUT()				SW_SETINPUT_PU()

/****************************** LPCICP ******************************/
#define LPCICP_PDA_SET()				SW_SET()
#define LPCICP_PDA_CLR()				SW_CLR()
#define LPCICP_PDA_GET()				SW_GET()
#define LPCICP_PDA_SETOUTPUT()			SW_SETOUTPUT()
#define LPCICP_PDA_SETINPUT()			SW_SETINPUT_PU()

#define LPCICP_PCL_SET()				JTAG_TAP_TCK_SET()
#define LPCICP_PCL_CLR()				JTAG_TAP_TCK_CLR()
#define LPCICP_PCL_SETOUTPUT()			JTAG_TAP_TCK_SETOUTPUT()
#define LPCICP_PCL_SETINPUT()			JTAG_TAP_TCK_SETINPUT()

#define LPCICP_RST_SET()				SW_RST_SET()
#define LPCICP_RST_CLR()				SW_RST_CLR()
#define LPCICP_RST_SETOUTPUT()			SW_RST_SETOUTPUT()
#define LPCICP_RST_SETINPUT()			SW_RST_SETINPUT_PU()

/****************************** IIC ******************************/
#define IIC_PULL_INIT()					do{\
											SW_PULL_SET();\
											SW_RST_PULL_SET();\
										} while(0)

#define IIC_SCL_SETOUTPUT()				SW_RST_SETOUTPUT()
#define IIC_SCL_SETINPUT()				SW_RST_SETINPUT_PU()
#define IIC_SCL_SET()					IIC_SCL_SETINPUT()
#define IIC_SCL_CLR()					SW_RST_CLR()
#define IIC_SCL_GET()					SW_RST_GET()

#define IIC_SDA_SETOUTPUT()				SW_SETOUTPUT()
#define IIC_SDA_SETINPUT()				SW_SETINPUT_PU()
#define IIC_SDA_SET()					IIC_SDA_SETINPUT()
#define IIC_SDA_CLR()					SW_CLR()
#define IIC_SDA_GET()					SW_GET()

/****************************** USART ******************************/
// to change USART port below, modify the interrupt handler
#define USART_DEF_PORT					USART1
#define USART_IRQ						USART1_IRQn
#define USART_AUX_PORT_EN				0

#define USART_PORT						GPIOA
#define USART_TXD_PIN					GPIO_PIN_9
#define USART_RXD_PIN					GPIO_PIN_10

#define USART_AUX_PORT					GPIOB
#define USART_DTR_PIN					GPIO_PIN_10
#define USART_RTS_PIN					GPIO_PIN_11
#define USART_DSR_PIN					
#define USART_CTS_PIN					
#define USART_RI_PIN					

#define USART_DTR_SET()					GPIO_SetPins(USART_AUX_PORT, USART_DTR_PIN)
#define USART_DTR_CLR()					GPIO_ClrPins(USART_AUX_PORT, USART_DTR_PIN)
#define USART_RTS_SET()					GPIO_SetPins(USART_AUX_PORT, USART_RTS_PIN)
#define USART_RTS_CLR()					GPIO_ClrPins(USART_AUX_PORT, USART_RTS_PIN)

#define USART_AUX_Port_Init()			do{\
											GPIO_SetMode(USART_AUX_PORT, USART_DTR_PIN, GPIO_MODE_OUT_PP);\
											GPIO_SetMode(USART_AUX_PORT, USART_RTS_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define USART_AUX_Port_Fini()			do{\
											GPIO_SetMode(USART_AUX_PORT, USART_DTR_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(USART_AUX_PORT, USART_RTS_PIN, GPIO_MODE_IN_FLOATING);\
										}while(0)
#define USART_Port_Init()				do{\
											RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);\
											GPIO_SetMode(USART_PORT, USART_TXD_PIN, GPIO_MODE_AF_PP);\
											GPIO_SetMode(USART_PORT, USART_RXD_PIN, GPIO_MODE_IN_FLOATING);\
										}while(0)
#define USART_Port_Fini()				do{\
											RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);\
											GPIO_SetMode(USART_PORT, USART_TXD_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(USART_PORT, USART_RXD_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(USART_AUX_PORT, USART_DTR_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(USART_AUX_PORT, USART_RTS_PIN, GPIO_MODE_IN_FLOATING);\
										}while(0)

/****************************** ADC ******************************/
#define TVCC_PORT						GPIOB
#define TVCC_PIN						GPIO_PIN_0
#define TVCC_ADC_CHANNEL				ADC_Channel_8
#define TVCC_ADC_PORT					ADC1

#define TVCC_SAMPLE_MIN_POWER			1800

#define TVCC_SAMPLE_DIV					2
#define TVCC_SAMPLE_VREF				3300
#define TVCC_SAMPLE_MAXVAL				4096

/****************************** LED ******************************/
#define LED_PORT						GPIOB
#define LED_RED_PIN						GPIO_PIN_6
#define LED_GREEN_PIN					GPIO_PIN_7
#define LED_RED_ON()					GPIO_ClrPins(LED_PORT, LED_RED_PIN)
#define LED_RED_OFF()					GPIO_SetPins(LED_PORT, LED_RED_PIN)
#define LED_GREEN_ON()					GPIO_ClrPins(LED_PORT, LED_GREEN_PIN)
#define LED_GREEN_OFF()					GPIO_SetPins(LED_PORT, LED_GREEN_PIN)

#define LED_Init()						do{\
											GPIO_SetMode(LED_PORT, LED_RED_PIN, GPIO_MODE_OUT_PP);\
											GPIO_SetMode(LED_PORT, LED_GREEN_PIN, GPIO_MODE_OUT_PP);\
										}while(0)
#define LED_Fini()						do{\
											GPIO_SetMode(LED_PORT, LED_RED_PIN, GPIO_MODE_IN_FLOATING);\
											GPIO_SetMode(LED_PORT, LED_GREEN_PIN, GPIO_MODE_IN_FLOATING);\
										}while(0)

// LED_RW
#define LED_RW_PORT						GPIOA
#define LED_RW_PIN						GPIO_PIN_3
#define Led_RW_Init()					GPIO_SetMode(LED_RW_PORT, LED_RW_PIN, GPIO_MODE_OUT_PP)
#define Led_RW_ON()						GPIO_ClrPins(LED_RW_PORT, LED_RW_PIN)
#define Led_RW_OFF()					GPIO_SetPins(LED_RW_PORT, LED_RW_PIN)

// LED_USB
#define LED_USB_INIT()					
#define LED_USB_ON()					Led_RW_OFF()
#define LED_USB_OFF()					Led_RW_ON()

/****************************** KEY ******************************/
#define KEY_PORT						GPIOB
#define KEY_PIN							GPIO_PIN_9
#define KEY_IsDown()					!GPIO_GetInPins(KEY_PORT, KEY_PIN)
#define KEY_Init()						GPIO_SetMode(KEY_PORT, KEY_PIN, GPIO_MODE_IPU)
#define KEY_Fini()						GPIO_SetMode(KEY_PORT, KEY_PIN, GPIO_MODE_IN_FLOATING)

/****************************** USB *****************************/
// For USB 2.0, use DP
// For USB 1.1, use DM
#define USB_DP_PORT						GPIOA
#define USB_DP_PIN						GPIO_PIN_12

#define USB_Pull_Init()					
#define USB_Connect()					
#define USB_Disconnect()				

#define USB_Disable()					PowerOff()
#define USB_D_SETOUTPUT()				GPIO_SetMode(USB_DP_PORT, USB_DP_PIN, GPIO_MODE_OUT_PP)
#define USB_D_SET()						GPIO_SetPins(USB_DP_PORT, USB_DP_PIN)
#define USB_D_CLR()						GPIO_ClrPins(USB_DP_PORT, USB_DP_PIN)