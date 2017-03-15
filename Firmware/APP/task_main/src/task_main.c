#include "defs.h"
#include "task_main.h"
#include "display.h"
osThreadId TaskHandle;
osThreadId Shellhandle;
extern SPI_HandleTypeDef hspi1;

void task_main(void const * argument)
{
    //lcd_5510_init();
    dispaly_module_init(LCD_5510);
    LCD_init();
    LCD_clear();
    LCD_write_english_string(0,0," Welcome i  ");
    while(sd_init() != 0)
    {
    LCD_write_english_string(0,3,"SD CardFailed!");
    osDelay(1000);
    }
    printf("CS OK \n\r\n");
    LCD_write_english_string(0,3,"SD OK    !");
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
    UINT32 sector_size = 0;
    sector_size=SD_GetSectorCount();
	printf(" SD Sector Size:%d\n",sector_size );
    for(;;)
    {
        LCD_write_english_string(0,0," Welcome i  ");
        LCD_write_english_string(0,2,"amy-studio.com");

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

    osThreadDef(shell, shell_main, osPriorityBelowNormal, 0, 128);
    Shellhandle = osThreadCreate(osThread(shell), NULL);
}


