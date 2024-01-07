/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../Drivers/RGB_led/RGB_led.h"
#include "../Drivers/display_7seg/display_7seg.h" 
#include "../Drivers/button_module/button_module.h"
#include "../Drivers/OKY3552/OKY3552.h"
#include "../Drivers/GPS_data_handling/GPS_data_handling.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void proccesDmaData(uint8_t sign);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ERROR_TRAVELED_DISTANCE_THRESHOLD_METERS	5000.0
#define GPS_2D_FIX									1
#define GPS_NO_FIX									0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
struct USER current_user;
struct USER user_A;
struct USER user_B;
struct USER user_C;
uint8_t button_state = BUTTON_STATE_INACTIVE;
uint8_t message = 0;
uint16_t num = 0;
struct position current_position;
struct position last_position;
struct Coordinate current_coordinate;
struct Coordinate last_coordinate;
double traveled_distance = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void next_user()
{
    if(current_user.ID == user_A.ID)
		current_user = user_B;
	else if(current_user.ID == user_B.ID)
		current_user = user_C;
	else if(current_user.ID == user_C.ID)
		current_user = user_A;
}

void save_user()
{
	if(current_user.ID == user_A.ID)
		user_A = current_user;
	else if(current_user.ID == user_B.ID)
		user_B = current_user;
	else if(current_user.ID == user_C.ID)
		user_C = current_user;
}

void setup_users()
{
	user_A.ID = 0;
	user_A.distance = 1234000.0;
	user_A.distance_km = user_A.distance * 0.001;
	user_A.red = 0;
	user_A.green = 1;
	user_A.blue = 1;

	user_B.ID = 1;
	user_B.distance = 0.0;
	user_B.distance_km = user_B.distance * 0.001;
	user_B.red = 1;
	user_B.green = 0;
	user_B.blue = 1;

	user_C.ID = 2;
	user_C.distance = 6969000.0;
	user_C.distance_km = user_C.distance * 0.001;
	user_C.red = 1;
	user_C.green = 1;
	user_C.blue = 0;

	current_user = user_A;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* System interrupt init*/
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  USART1_RegisterCallback(proccesDmaData);
  setup_users();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    set_RGB_led(current_user.red,current_user.green,current_user.blue);
    button_state = readButton();
    if(button_state == BUTTON_STATE_PRESS)
    {
      next_user();
    }
    else if(button_state == BUTTON_STATE_LONG_PRESS)
    {
      current_user.distance = 0.0;
      current_user.distance_km = 0.0;
      save_user();
    }    
    current_position = get_device_position();
	current_coordinate.latitude = current_position.LAT;
	current_coordinate.longitude = current_position.LON;

	last_coordinate.latitude = last_position.LAT;
	last_coordinate.longitude = last_position.LON;

	traveled_distance = haversineDistance(last_coordinate,current_coordinate);

	if(traveled_distance < ERROR_TRAVELED_DISTANCE_THRESHOLD_METERS &&
			current_position.fix != GPS_NO_FIX &&
			last_position.fix != GPS_NO_FIX)
	{
		current_user.distance += traveled_distance;
		current_user.distance_km = current_user.distance * 0.001;
		save_user();
	}

	handle_display((uint16_t)current_user.distance_km);
	last_position = current_position;
	LL_mDelay(2);
      /* USER CODE END WHILE */

      /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_Init1msTick(8000000);
  LL_SetSystemCoreClock(8000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
}

/* USER CODE BEGIN 4 */
void proccesDmaData(uint8_t sign)
{
	parse_uart_character(sign);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
