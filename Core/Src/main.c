/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define c1 GPIO_PIN_5
#define c2 GPIO_PIN_1
#define c3 GPIO_PIN_6
#define c4 GPIO_PIN_7

#define r1 GPIO_PIN_11
#define r2 GPIO_PIN_10
#define r3 GPIO_PIN_9
#define r4 GPIO_PIN_8

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t a;
uint8_t password[5];
int count = 0;
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
  /* USER CODE BEGIN 2 */
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//Column 1
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
	if(count < 5)
	{
		password[count]=a;
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
		count++;
	}
//return 'D';
}
HAL_Delay(100);
//HAL_UART_Transmit(&huart2,&a ,sizeof(a),100);
 
if(count >= 5)
{
	count = 0;
//	HAL_UART_Transmit(&huart2,&password[0] ,sizeof(password[0]),100);
//	HAL_UART_Transmit(&huart2,&password[1] ,sizeof(password[1]),100);
//	HAL_UART_Transmit(&huart2,&password[2] ,sizeof(password[2]),100);
//	HAL_UART_Transmit(&huart2,&password[3] ,sizeof(password[3]),100);
//	HAL_UART_Transmit(&huart2,&password[4] ,sizeof(password[4]),100);
	HAL_UART_Transmit(&huart2,password,sizeof(password),100);
	HAL_Delay(5000);
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
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
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA4 PA5 PA6
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
