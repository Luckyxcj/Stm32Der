#ifndef __DISPLAY_H__
#define __DISPLAY_H__

typedef enum dispaly_scheme
{
    LED,
    LCD_1602,
    LCD_5510,
    OLED,
    TFT_CLD,
    DISPALY_MAX
}DISPALY_SCHEME;

extern int dispaly_module_init(DISPALY_SCHEME scheme);

#endif /*__TASK_MAIN_H__*/
