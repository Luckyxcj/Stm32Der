#include "defs.h"
#include "task_main.h"
#include "display.h"
osThreadId TaskHandle;
osThreadId Shellhandle;

void task_main(void const * argument)
{
  //lcd_5510_init();
  dispaly_module_init(2);
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
		
    // osDelay(1000);
		HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
		osDelay(500);
		HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);	
		osDelay(500);
  }
  /* USER CODE END 5 */ 
}

void thread_init(void)
{
    osThreadDef(task, task_main, osPriorityNormal, 0, 128);
    TaskHandle = osThreadCreate(osThread(task), NULL);

    osThreadDef(shell, shell_main, osPriorityNormal, 0, 128);
    Shellhandle = osThreadCreate(osThread(shell), NULL);
}


