/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


double brightNess;//����Ϊ1����������Ϊ0������� 

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Task_mainHandle;
osThreadId LED_PWM_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Task_main_Start(void const * argument);
void LED_PWM_Task_Start(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task_main */
  osThreadDef(Task_main, Task_main_Start, osPriorityAboveNormal, 0, 128);
  Task_mainHandle = osThreadCreate(osThread(Task_main), NULL);

  /* definition and creation of LED_PWM_Task */
  osThreadDef(LED_PWM_Task, LED_PWM_Task_Start, osPriorityIdle, 0, 128);
  LED_PWM_TaskHandle = osThreadCreate(osThread(LED_PWM_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Task_main_Start */
/**
  * @brief  Function implementing the Task_main thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_main_Start */
__weak void Task_main_Start(void const * argument)
{
  /* USER CODE BEGIN Task_main_Start */
  /* Infinite loop */
  for(;;)
  {
		for(uint8_t i = 0; i<100; i++){
		
			osDelay(13);
			brightNess = sin(i*(3.14159265/100));
			
		}
    osDelay(1);
  }
  /* USER CODE END Task_main_Start */
}

/* USER CODE BEGIN Header_LED_PWM_Task_Start */
/**
* @brief Function implementing the LED_PWM_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_PWM_Task_Start */
__weak void LED_PWM_Task_Start(void const * argument)
{
  /* USER CODE BEGIN LED_PWM_Task_Start */
	
	
	
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_WritePin(LED_Test_GPIO_Port,LED_Test_Pin,(GPIO_PinState)0);
    osDelay(brightNess*20);
		HAL_GPIO_WritePin(LED_Test_GPIO_Port,LED_Test_Pin,(GPIO_PinState)1);
    osDelay(20-brightNess*20);
  }
  /* USER CODE END LED_PWM_Task_Start */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
