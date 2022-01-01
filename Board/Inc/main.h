/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI3_CS0_Pin GPIO_PIN_13
#define SPI3_CS0_GPIO_Port GPIOC
#define SPI2_CS0_Pin GPIO_PIN_14
#define SPI2_CS0_GPIO_Port GPIOC
#define nOCTW0_Pin GPIO_PIN_15
#define nOCTW0_GPIO_Port GPIOC
#define PVCC_SENS_Pin GPIO_PIN_0
#define PVCC_SENS_GPIO_Port GPIOC
#define TEMP_SENSE0_Pin GPIO_PIN_1
#define TEMP_SENSE0_GPIO_Port GPIOC
#define TEMP_SENSE1_Pin GPIO_PIN_2
#define TEMP_SENSE1_GPIO_Port GPIOC
#define A_SENSE0_Pin GPIO_PIN_0
#define A_SENSE0_GPIO_Port GPIOA
#define B_SENSE0_Pin GPIO_PIN_1
#define B_SENSE0_GPIO_Port GPIOA
#define C_SENSE0_Pin GPIO_PIN_2
#define C_SENSE0_GPIO_Port GPIOA
#define A_SENSE1_Pin GPIO_PIN_3
#define A_SENSE1_GPIO_Port GPIOA
#define B_SENSE1_Pin GPIO_PIN_4
#define B_SENSE1_GPIO_Port GPIOA
#define C_SENSE1_Pin GPIO_PIN_5
#define C_SENSE1_GPIO_Port GPIOA
#define LA1_Pin GPIO_PIN_7
#define LA1_GPIO_Port GPIOA
#define D_C_Pin GPIO_PIN_4
#define D_C_GPIO_Port GPIOC
#define nFAULT0_Pin GPIO_PIN_5
#define nFAULT0_GPIO_Port GPIOC
#define LB0_Pin GPIO_PIN_0
#define LB0_GPIO_Port GPIOB
#define LC0_Pin GPIO_PIN_1
#define LC0_GPIO_Port GPIOB
#define nFAULT1_Pin GPIO_PIN_2
#define nFAULT1_GPIO_Port GPIOB
#define nOCTW1_Pin GPIO_PIN_11
#define nOCTW1_GPIO_Port GPIOB
#define EN1_Pin GPIO_PIN_12
#define EN1_GPIO_Port GPIOB
#define LA0_Pin GPIO_PIN_13
#define LA0_GPIO_Port GPIOB
#define LB1_Pin GPIO_PIN_14
#define LB1_GPIO_Port GPIOB
#define LC1_Pin GPIO_PIN_15
#define LC1_GPIO_Port GPIOB
#define HA1_Pin GPIO_PIN_6
#define HA1_GPIO_Port GPIOC
#define HB1_Pin GPIO_PIN_7
#define HB1_GPIO_Port GPIOC
#define HC1_Pin GPIO_PIN_8
#define HC1_GPIO_Port GPIOC
#define EN0_Pin GPIO_PIN_9
#define EN0_GPIO_Port GPIOC
#define HA0_Pin GPIO_PIN_8
#define HA0_GPIO_Port GPIOA
#define HB0_Pin GPIO_PIN_9
#define HB0_GPIO_Port GPIOA
#define HC0_Pin GPIO_PIN_10
#define HC0_GPIO_Port GPIOA
#define SPI1_CS2_Pin GPIO_PIN_15
#define SPI1_CS2_GPIO_Port GPIOA
#define SPI1_CS1_Pin GPIO_PIN_2
#define SPI1_CS1_GPIO_Port GPIOD
#define SPI1_CS0_Pin GPIO_PIN_4
#define SPI1_CS0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
