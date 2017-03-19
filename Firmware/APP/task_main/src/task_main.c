#include "defs.h"
#include "task_main.h"
#include "display.h"
#include "fat_opt.h"

//#include "task.h"

osThreadId TaskHandle;
osThreadId Shellhandle;
extern SPI_HandleTypeDef hspi1;
extern char USER_Path[4];

void task_main(void const * argument)
{
    //lcd_5510_init();
    dispaly_module_init(LCD_5510);
    LCD_init();
    LCD_clear();
    LCD_write_english_string(0,0," Welcome i  ");

    MX_FATFS_Init();
   FATFS fs; 
   FRESULT f_res;  
   f_res = f_mount(&fs,(TCHAR const*)USER_Path,1);
   if (f_res != FR_OK)
   {
        printf("fatfs mount error %d \n\r\n\r",f_res);
   }
    get_sd_free();
    //f_res = f_mount(NULL,(TCHAR const*)SPIFLASHPath,1);	
    
    for(;;)
    {
        LCD_write_english_string(0,0," Welcome i  ");
        LCD_write_english_string(0,2,"amy-studio.com");
#if 0
        SD_ReadDisk(buf_kk,0,1);
        printf("SECTOR 0 DATA:\n");
        for(sector_size=0;sector_size<512;sector_size++)
            printf("%x ",buf_kk[sector_size]);//打印MBR扇区数据           
				printf("\nDATA ENDED\n");
#endif
        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
        osDelay(1000);
        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);	
        osDelay(1000);

    }
  /* USER CODE END 5 */ 
}

void thread_init(void)
{
    osThreadDef(task, task_main, osPriorityNormal, 0, 256);
    TaskHandle = osThreadCreate(osThread(task), NULL);

    //osThreadDef(shell, shell_main, osPriorityBelowNormal, 0, 128);
    //Shellhandle = osThreadCreate(osThread(shell), NULL);
}



