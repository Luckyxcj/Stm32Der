#include "defs.h"
#include "task_main.h"
#include "display.h"
osThreadId TaskHandle;
osThreadId Shellhandle;

void task_main(void const * argument)
{
  //lcd_5510_init();
  dispaly_module_init(LCD_5510);
  LCD_init();
  LCD_clear();
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    // osDelay(1000);
   // LCD_Disp_clkdot();
    LCD_write_english_string(0,0," Welcome i  ");
    LCD_write_english_string(0,2,"amy-studio.com");
    LCD_write_num_string(0,4,"NUM",-123456789); 
	HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
	osDelay(500);
	HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);	
	osDelay(500);
       
        //printf("HE");
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


