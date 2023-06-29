/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "cmsis_os.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gd32f4xx_libopt.h"
#include "api.h"

#include <allocators.h>
#include <rcl/rcl.h>
#include <uxr/client/client.h>
#include <ucdr/microcdr.h>

#include <rmw_microros/rmw_microros.h>

#include <microros_transports.h>



#include "FreeRTOS.h"
#include "task.h"

#include <rmw_microxrcedds_c/config.h>

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

/* Definitions for initTask */
osThreadId_t initTaskHandle;
const osThreadAttr_t initTask_attributes = {
  .name = "initTask",
  .priority = (osPriority_t) osPriorityBelowNormal7,
  .stack_size = 1500 * 4
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART0_UART_Init(void);
static void MX_USART1_UART_Init(void);
void initTaskFunction(void *argument);

/* USER CODE BEGIN PFP */

extern void appMain(void *argument);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch)
{
  usart_data_transmit(USART1, (uint8_t)ch);
  while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
  return ch;
}

int _write(int file,char *ptr, int len)
{
  int DataIdx;
  for(DataIdx= 0; DataIdx< len; DataIdx++){
  __io_putchar(*ptr++);
  }
  return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Set Interrupt Group Priority */
  nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0); 
  NVIC_SetPriority(PendSV_IRQn, 
                  NVIC_EncodePriority(
                  NVIC_GetPriorityGrouping(), 15, 0));
  SysTick_Config(SystemCoreClock / 1000U);
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART0_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */



  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

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
  /* creation of initTask */
  initTaskHandle = osThreadNew(initTaskFunction, NULL, &initTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{
 
  rcu_periph_clock_enable(RCU_USART1);   

  gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_2 | GPIO_PIN_3);

  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);   
  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);  

  gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_3);   
  gpio_output_options_set(GPIOA, GPIO_MODE_ANALOG, GPIO_OSPEED_50MHZ, GPIO_PIN_3);  


  usart_deinit(USART1);    
  usart_word_length_set(USART1, USART_WL_8BIT);  
  usart_stop_bit_set(USART1, USART_STB_1BIT);    
  usart_parity_config(USART1, USART_PM_NONE);
  usart_baudrate_set(USART1, 115200U);     
  usart_receive_config(USART1, USART_RECEIVE_ENABLE);     
  usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);  
  usart_hardware_flow_rts_config(USART1, USART_RTS_DISABLE);
  usart_hardware_flow_cts_config(USART1, USART_CTS_DISABLE);
  usart_enable(USART1);  

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART0_UART_Init(void)
{
  
  rcu_periph_clock_enable(RCU_USART0);   

  gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9 | GPIO_PIN_10);

  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);   
  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);  

  gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_10);   
  gpio_output_options_set(GPIOA, GPIO_MODE_ANALOG, GPIO_OSPEED_50MHZ, GPIO_PIN_10);  


  usart_deinit(USART0);    
  usart_word_length_set(USART0, USART_WL_8BIT);  
  usart_stop_bit_set(USART0, USART_STB_1BIT);    
  usart_parity_config(USART0, USART_PM_NONE);
  usart_baudrate_set(USART0, 115200U);     
  usart_receive_config(USART0, USART_RECEIVE_ENABLE);     
  usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);  
  usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
  usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
  usart_enable(USART0);           

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{
    /* enable DMA1 */
    rcu_periph_clock_enable(RCU_DMA1);
    /* deinitialize DMA channel2(USART0 rx) */    
    dma_deinit(DMA1, DMA_CH2);    
    /* deinitialize DMA channel7(USART0 tx) */
    dma_deinit(DMA1, DMA_CH7);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
		rcu_periph_clock_enable(RCU_GPIOA);    
	  rcu_periph_clock_enable(RCU_GPIOE);    
	
	  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_15);   
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);  
	
	  gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);   
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5); 
	
	  gpio_bit_reset(GPIOA, GPIO_PIN_15);  
	  gpio_bit_reset(GPIOE, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);  

}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/* USER CODE BEGIN Header_initTaskFunction */
/**
  * @brief  Function implementing the initTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_initTaskFunction */
void initTaskFunction(void *argument)
{
  /* init code for LWIP */
  /* USER CODE BEGIN 5 */

  bool availableNetwork = false;

#ifdef RMW_UXRCE_TRANSPORT_CUSTOM
  availableNetwork = true;
  rmw_uros_set_custom_transport(
    true,
    NULL,
    freertos_serial_open,
    freertos_serial_close,
    freertos_serial_write,
    freertos_serial_read);
#elif defined(RMW_UXRCE_TRANSPORT_UDP)
  printf("Ethernet Initialization\r\n");

	//Waiting for an IP
  printf("Waiting for IP\r\n");
  int retries = 0;
	while(gnetif.ip_addr.addr == 0 && retries < 10){
    osDelay(500);  
    retries++;
  };

  availableNetwork = (gnetif.ip_addr.addr != 0);
  if (availableNetwork){
    printf("IP: %s\r\n",ip4addr_ntoa(&gnetif.ip_addr));
  }else{
    printf("Impossible to retrieve an IP\n");
  }
#endif

  // Launch app thread when IP configured
  rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
  freeRTOS_allocator.allocate = __freertos_allocate;
  freeRTOS_allocator.deallocate = __freertos_deallocate;
  freeRTOS_allocator.reallocate = __freertos_reallocate;
  freeRTOS_allocator.zero_allocate = __freertos_zero_allocate;

  if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
      printf("Error on default allocators (line %d)\n",__LINE__); 
  }

  osThreadAttr_t attributes;
  memset(&attributes, 0x0, sizeof(osThreadAttr_t));
  attributes.name = "microROS_app";
  attributes.stack_size = 4*6000;
  attributes.priority = (osPriority_t) osPriorityNormal;
  osThreadNew(appMain, NULL, &attributes);

  osDelay(500);
  char ptrTaskList[500];
  vTaskList(ptrTaskList);
  printf("**********************************\r\n");
  printf("Task  State   Prio    Stack    Num\r\n"); 
  printf("**********************************\r\n");
  printf(ptrTaskList);
  printf("**********************************\r\n");

  TaskHandle_t xHandle;
  xHandle = xTaskGetHandle("microROS_app");

  while (1){
    if (eTaskGetState(xHandle) != eSuspended && availableNetwork){ 
      gpio_bit_reset(GPIOE, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);  
      osDelay(100);
      gpio_bit_set(GPIOE, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);  
      osDelay(100); 
      gpio_bit_reset(GPIOE, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);  
      osDelay(150);
      gpio_bit_set(GPIOE, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);  
      osDelay(500);
    }else{
      gpio_bit_set(GPIOA, GPIO_PIN_15);  
      osDelay(1000);
      gpio_bit_reset(GPIOA, GPIO_PIN_15); 
      osDelay(1000);
    }
  }
  

  /* USER CODE END 5 */
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
