
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2023 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "stm32l4xx_hal.h"
#include "liquidcrystal_i2c.h.txt"
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
#define c1 GPIO_PIN_5
#define c2 GPIO_PIN_1
#define c3 GPIO_PIN_6
#define c4 GPIO_PIN_7

#define alarm GPIO_PIN_0
#define button GPIO_PIN_1
#define r1 GPIO_PIN_11
#define r2 GPIO_PIN_12
#define r3 GPIO_PIN_0
#define r4 GPIO_PIN_4

#define relayPin GPIO_PIN_3
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint8_t a;
uint8_t password[5];
int count = 0;
int passwords[100];
int num_pass;
int found = 0;
uint8_t f = 0;
int gen_signal;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
passwords[0] = 12345;
	num_pass = 1;
	gen_signal = 0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
int psc = 15999;
__HAL_TIM_SET_PRESCALER(&htim1,psc);
  HD44780_Init(2);
  HD44780_Clear();
  HD44780_SetCursor(0,0);
  HD44780_PrintStr("Keypad:");
  HD44780_SetCursor(0,1);
  HD44780_PrintStr("New:");
  HAL_Delay(2000);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
//		HD44780_SetCursor(7,0);
//  HD44780_PrintStr((const char*)password);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		if(gen_signal)
		{if(num_pass != 99) //if max passwords not reached
		{
		char generated_pass[5];
		int x = (rand()%(90001))+9999;
		passwords[num_pass] = x;
		num_pass++;
		sprintf(generated_pass, "%d", x);
		HD44780_SetCursor(4,1);
  HD44780_PrintStr(generated_pass);
		HAL_UART_Transmit(&huart2,(uint8_t*)generated_pass,sizeof(generated_pass),1000);
			HAL_UART_Transmit(&huart2,(uint8_t*)"\r", 1, 100);
			HAL_UART_Transmit(&huart2,(uint8_t*)"\n", 1, 100);
			gen_signal = 0;
		}
			
		}
		HAL_GPIO_WritePin (GPIOA, c1, GPIO_PIN_RESET); //Pull the C1 low
HAL_GPIO_WritePin (GPIOA, c2, GPIO_PIN_SET);  // Pull the C2 High
HAL_GPIO_WritePin (GPIOA, c3, GPIO_PIN_SET);  // Pull the C3 High
HAL_GPIO_WritePin (GPIOA, c4, GPIO_PIN_SET);  // Pull the C4 High

if (!(HAL_GPIO_ReadPin (GPIOA, r1)))   // if row 1 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r1)));   // wait till the button is pressed
	a='1';
	if(count < 5)
	{
			
		password[count]=a;
		HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
		
//return '1';
}
if (!(HAL_GPIO_ReadPin (GPIOA, r2)))   // if row 2 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r2)));   // wait till the button is pressed
	a='4';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
//return '4';
}
if (!(HAL_GPIO_ReadPin (GPIOA, r3)))   // if row 3 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r3)));   // wait till the button is pressed
	a='7';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
//return '7';
}
if (!(HAL_GPIO_ReadPin (GPIOA, r4)))   // if row 4 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r4)));   // wait till the button is pressed
	a='0';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return '0';
}

//Column 2
HAL_GPIO_WritePin (GPIOA, c1, GPIO_PIN_SET); //Pull the C1 High
HAL_GPIO_WritePin (GPIOA, c2, GPIO_PIN_RESET);  // Pull the C2 Low
HAL_GPIO_WritePin (GPIOA, c3, GPIO_PIN_SET);  // Pull the C3 High
HAL_GPIO_WritePin (GPIOA, c4, GPIO_PIN_SET);  // Pull the C4 High

if (!(HAL_GPIO_ReadPin (GPIOA, r1)))   // if row 1 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r1)));   // wait till the button is pressed
	a='2';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
//return '2';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r2)))   // if row 2 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r2)));   // wait till the button is pressed
	a='5';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return '5';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r3)))   // if row 3 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r3)));   // wait till the button is pressed
	a='8';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return '8';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r4)))   // if row 4 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r4)));   // wait till the button is pressed
	a='F';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return 'F';
}

////Column 3
HAL_GPIO_WritePin (GPIOA, c1, GPIO_PIN_SET); //Pull the C1 High
HAL_GPIO_WritePin (GPIOA, c2, GPIO_PIN_SET);  // Pull the C2 High
HAL_GPIO_WritePin (GPIOA, c3, GPIO_PIN_RESET);  // Pull the C3 Low
HAL_GPIO_WritePin (GPIOA, c4, GPIO_PIN_SET);  // Pull the C4 High

if (!(HAL_GPIO_ReadPin (GPIOA, r1)))   // if row 1 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r1)));   // wait till the button is pressed
	a='3';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return '3';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r2)))   // if row 2 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r2)));   // wait till the button is pressed
	a='6';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return '6';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r3)))   // if row 3 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r3)));   // wait till the button is pressed
	a='9';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return '9';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r4)))   // if row 4 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r4)));   // wait till the button is pressed
	a='E';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
	//return 'E';
}
//Column 4
HAL_GPIO_WritePin (GPIOA, c1, GPIO_PIN_SET); //Pull the C1 High
HAL_GPIO_WritePin (GPIOA, c2, GPIO_PIN_SET);  // Pull the C2 High
HAL_GPIO_WritePin (GPIOA, c3, GPIO_PIN_SET);  // Pull the C3 High
HAL_GPIO_WritePin (GPIOA, c4, GPIO_PIN_RESET);  // Pull the C4 Low

if (!(HAL_GPIO_ReadPin (GPIOA, r1)))   // if row 1 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r1)));   // wait till the button is pressed
	a='A';
	
	if(count == 0) //if first digit
	{
		if(num_pass != 99) //if max passwords not reached
		{
		char generated_pass[5];
		int x = (rand()%(90001))+9999;
		passwords[num_pass] = x;
		num_pass++;
		sprintf(generated_pass, "%d", x);
		HD44780_SetCursor(4,1);
  HD44780_PrintStr(generated_pass);
		HAL_UART_Transmit(&huart2,(uint8_t*)generated_pass,sizeof(generated_pass),1000);
			HAL_UART_Transmit(&huart2,(uint8_t*)"\r", 1, 100);
			HAL_UART_Transmit(&huart2,(uint8_t*)"\n", 1, 100);
		}
	}
	else if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
		
	}
//return 'A';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r2)))   // if row 2 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r2)));   // wait till the button is pressed
	a='B';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
//return 'B';
}

if (!(HAL_GPIO_ReadPin (GPIOA, r3)))   // if row 3 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r3)));   // wait till the button is pressed
	a='C';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
	}
//return 'C';
}
if (!(HAL_GPIO_ReadPin (GPIOA, r4)))   // if row 4 is low
{
	while (!(HAL_GPIO_ReadPin (GPIOA, r4)));   // wait till the button is pressed
	a='D';
	if(count < 5)
	{
		password[count]=a;
				HD44780_SetCursor(7,0);
  HD44780_PrintStr((const char*)password);
		count++;
                                                                                                                                                     	}
//return 'D';
}
//HAL_UART_Transmit(&huart2,&a ,sizeof(a),100);
 
if(count >= 5)
{

		HD44780_SetCursor(7,0);
  HD44780_PrintStr("      ");
	count = 0;
	int correctSoFar = 0; //5 digits correct
	int index_found; //index where pass is located and found
	HAL_UART_Transmit(&huart2,&password[0] ,sizeof(password[0]),100);
	HAL_UART_Transmit(&huart2,&password[1] ,sizeof(password[1]),100);
	HAL_UART_Transmit(&huart2,&password[2] ,sizeof(password[2]),100);
	HAL_UART_Transmit(&huart2,&password[3] ,sizeof(password[3]),100);
	HAL_UART_Transmit(&huart2,&password[4] ,sizeof(password[4]),100);
	HAL_UART_Transmit(&huart2,(uint8_t*)"\r", 1, 100);
	HAL_UART_Transmit(&huart2,(uint8_t*)"\n", 1, 100);
	for(int i = 0; i < num_pass; i++) //loop over passwords
	{
		char checkPass[5];
		sprintf(checkPass, "%d", passwords[i]);
		//HAL_UART_Transmit(&huart2,(uint8_t*) checkpass,sizeof(checkpass),100);
		for (int j = 0; j < 5; j++){
			if ((uint8_t)checkPass[j] == password[j]){
				correctSoFar++;
			}
		}
		
		if (correctSoFar == 5)
		{
			found = 1;
			index_found = i;
			correctSoFar = 0;
			continue;
		}
		else
			correctSoFar = 0;
		
//		HAL_UART_Transmit(&huart2,(uint8_t*)"\r", 1, 100);
//		HAL_UART_Transmit(&huart2,(uint8_t*)"\n", 1, 100);
//		HAL_UART_Transmit(&huart2,(uint8_t*)checkPass,sizeof(checkPass),100);
//		HAL_UART_Transmit(&huart2,(uint8_t*)" ", 1, 100);
//		HAL_UART_Transmit(&huart2,(uint8_t*)password,sizeof(password),100);
//		if ((uint8_t*)checkPass == (uint8_t*)password){
//			HAL_UART_Transmit(&huart2,(uint8_t*)"def",sizeof("def"),100);
//			found =1;
//		}
	}
//	HAL_UART_Transmit(&huart2,(uint8_t*)found,sizeof(found),100);
	if(found)
	{
		found = 0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,6);
		HAL_Delay(1500);
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,11);
		passwords[index_found] = 12345;
	}
	else
	{
		HAL_GPIO_WritePin (GPIOB, alarm, GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin (GPIOB, alarm, GPIO_PIN_RESET);
	}
	
	password[0] = NULL;
	password[1] = NULL;
	password[2] = NULL;
	password[3] = NULL;
	password[4] = NULL;
}
	}
  
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure LSE Drive Capability
    */
  HAL_PWR_EnableBkUpAccess();

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the main internal regulator output voltage
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Enable MSI Auto calibration
    */
  HAL_RCCEx_EnableMSIPLLMode();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10909CEC;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  RTC_AlarmTypeDef sAlarm;

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

    /**Initialize RTC Only
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initialize RTC and set the Time and Date
    */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Enable the Alarm A
    */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x10;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS
                              |RTC_ALARMMASK_MINUTES;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 99;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim1);

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA4 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) { 
//  RTC_AlarmTypeDef sAlarm;
//  HAL_RTC_GetAlarm(hrtc,&sAlarm,RTC_ALARM_A,FORMAT_BIN);
//  if(sAlarm.AlarmTime.Seconds>58) {
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);
//    sAlarm.AlarmTime.Seconds=0;
//  }else{
//    sAlarm.AlarmTime.Seconds=sAlarm.AlarmTime.Seconds+1;
//  }
//    while(HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, FORMAT_BIN)!=HAL_OK){}
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_SET);
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
