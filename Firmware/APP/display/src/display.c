#include "display.h"
#include "defs.h"


int dispaly_module_init(DISPALY_SCHEME scheme)
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
        default: 
            printf("none one break");
            break;
    }
    
    return 1;
}

