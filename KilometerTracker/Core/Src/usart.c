/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
uint8_t bufferUSART1dma[DMA_USART1_BUFFER_SIZE];

/* Declaration and initialization of callback function */
static void (* USART1_ProcessData)(uint8_t data) = 0;

/* Register callback */
void USART1_RegisterCallback(void *callback)
{
	if(callback != 0)
	{
		USART1_ProcessData = callback;
	}
}
/* USER CODE END 0 */

/* USART1 init function */

void MX_USART1_UART_Init(void)
{
  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  /**USART1 GPIO Configuration
  PA2   ------> USART1_TX
  PA15   ------> USART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4|LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*
   * USART1 DMA configuration. Write configuration for DMA used by USART1 for data Rx/Tx with INTERRUPTS.
   * Rx memory buffer will be handled in normal mode, not circular!
   * You can use configuration from example program and modify it.
   * For more information about DMA registers, refer to reference manual.
   */

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PRIORITY_MEDIUM);
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MODE_NORMAL);
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MEMORY_INCREMENT);
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PDATAALIGN_BYTE);
  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MDATAALIGN_BYTE);

  LL_DMA_ConfigAddresses(	DMA1, LL_DMA_CHANNEL_4,
						 	LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_RECEIVE),
							(uint32_t)bufferUSART1dma,
							LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4));

  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, DMA_USART1_BUFFER_SIZE);
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
  LL_USART_EnableDMAReq_RX(USART1);

  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
  LL_DMA_EnableIT_HT(DMA1, LL_DMA_CHANNEL_4);

  /* USART1_TX Init */
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_5, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PRIORITY_MEDIUM);
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MODE_NORMAL);
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MEMORY_INCREMENT);
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PDATAALIGN_BYTE);
  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MDATAALIGN_BYTE);

  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_5, LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_TRANSMIT));
  LL_USART_EnableDMAReq_TX(USART1);

  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_5);

  /* USART1 interrupt Init */
  NVIC_SetPriority(USART1_IRQn, 0);
  NVIC_EnableIRQ(USART1_IRQn);

  USART_InitStruct.BaudRate = 9600;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_DisableIT_CTS(USART1);

  /* Enable USART1 peripheral and interrupts*/
  LL_USART_EnableIT_IDLE(USART1);
  LL_USART_Enable(USART1);
  	  //type your code here:
}

/* USER CODE BEGIN 1 */
uint16_t buf_read_pos = 0;

void USART1_CheckDmaReception(void)
{
	uint16_t pos = DMA_USART1_BUFFER_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_4);

	if (pos >= DMA_USART1_BUFFER_SIZE)
	{
		// set the DMA address pointer back to the beginning of the buffer
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
		LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)bufferUSART1dma);
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, DMA_USART1_BUFFER_SIZE);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);

		// process all data until the end of the buffer
		while(buf_read_pos < DMA_USART1_BUFFER_SIZE)
		{
			if(USART1_ProcessData != 0)
			{
				USART1_ProcessData(bufferUSART1dma[buf_read_pos]);
//				if(bufferUSART1dma[buf_read_pos] > 15)
//					handle_display(bufferUSART1dma[buf_read_pos]);
			}
			buf_read_pos++;
		}

		buf_read_pos = 0;
	}
	else
	{
		// process new data
		while(buf_read_pos < pos)
		{
			if(USART1_ProcessData != 0)
			{
				USART1_ProcessData(bufferUSART1dma[buf_read_pos]);
//				if(bufferUSART1dma[buf_read_pos] > 15)
//					handle_display(bufferUSART1dma[buf_read_pos]);
			}
			buf_read_pos++;
		}
	}
}
/* USER CODE END 1 */
