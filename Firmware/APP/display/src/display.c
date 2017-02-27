#include "display.h"
#include "defs.h"
enum dispaly_scheme
{
    LED,
    LCD_1602,
    LCD_5510,
    OLED,
    TFT_CLD,
    DISPALY_MAX
}dispaly_scheme;

int dispaly_module_init(int scheme)
{
    switch (scheme)
    {
        case LED: 
            printf("LED");
            break;
        case LCD_1602: 
            printf("LCD_1602");
            break;
        case LCD_5510: 
            printf("LCD_5510");
            break;
        case OLED: 
            printf("OLED");
            break;
        case TFT_CLD: 
            printf("TFT_CLD");
            break;
        dafault: 
            printf("none one break");
            break;
    }
    return 1;
}

