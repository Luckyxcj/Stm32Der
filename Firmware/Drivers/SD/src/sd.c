#include "sd.h"
#include "string.h"

extern SPI_HandleTypeDef hspi1;
UINT8  sdata[512];
UINT8  rdata[512];
UINT8  SD_Type;

UINT8 spi_readwritebyte(UINT8 send_data)
{
    UINT8 read_data=0;
    UINT8 ret = HAL_SPI_TransmitReceive(&hspi1,&send_data,&read_data,sizeof(UINT8),1);
    return read_data;
}   
void sd_spi_init(void)
{
     JF24_CS_H;
     SD_CS_H;
     F_CS_H;  
}
void set_spi_speedlow()
{
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    hspi1.State = HAL_SPI_STATE_RESET;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        printf("error INIT\r\n\r");
    }
    __HAL_SPI_ENABLE(&hspi1);
}
void set_spi_speedhight()
{
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
			 printf("error INIT\r\n\r");
    }
     HAL_SPI_MspInit(&hspi1);
     __HAL_SPI_ENABLE(&hspi1);
}


void SD_DisSelect(void)
{
	SD_CS_H
	spi_readwritebyte(0xFF);
}
UINT8 SD_WaitReady(void)
{
	UINT32 t=0;
	do
	{
        if(spi_readwritebyte(0xFF) == 0xff)
        {
            return 0;
        } 
		t++;		  	
	}
    while(t < 0XFFFFFF);
	return 1;
}
UINT8 SD_Select(void)
{
	SD_CS_L
	if(SD_WaitReady()==0)
        return 0;
	SD_DisSelect();
	return 1;
}
UINT8 SD_SendCmd(UINT8 cmd,UINT32 arg, UINT8 crc)
{
    UINT8 r1;	
	UINT8 Retry=0; 
    
	SD_DisSelect();
    
	if (SD_Select())
	{
        return 0XFF;
    }
        
    spi_readwritebyte(cmd | 0x40);
    spi_readwritebyte(arg >> 24);
    spi_readwritebyte(arg >> 16);
    spi_readwritebyte(arg >> 8);
    spi_readwritebyte(arg);
    spi_readwritebyte(crc);

	if(cmd == CMD12)
	{
        spi_readwritebyte(0xff);
    }
    
 
	Retry = 0X1F;
	do
	{
        r1 = spi_readwritebyte(0xFF);
	}while((r1 &0X80) && (Retry--));	
    
    return r1; 
}
UINT8 SD_GetResponse(UINT8 Response)
{
    UINT Count=0xFFF;//等待次数	   						  
    while ((spi_readwritebyte(0XFF)!=Response)&&Count)
    {
        Count--;
    }
    if (Count==0)return MSD_RESPONSE_FAILURE;
    else return MSD_RESPONSE_NO_ERROR;
}
UINT8 SD_RecvData(UINT8*buf,UINT len)
{			  	  
	if(SD_GetResponse(0xFE))
    {
        return 1;
    }
    while(len--)
    {
        *buf=spi_readwritebyte(0xFF);
        buf++;
    }
    //下面是2个伪CRC（dummy CRC）
    spi_readwritebyte(0xFF);
    spi_readwritebyte(0xFF);									  					    
    return 0;//读取成功
}
/*
Access to SD card CSD information, including information capacity and speed
*/
UINT8 SD_GetCSD(UINT8 *csd_data)
{
    UINT8 r1;	 
    r1 = SD_SendCmd(CMD9,0,0x01);
    if (r1 == 0)
	{
    	r1 = SD_RecvData(csd_data, 16);
    }
	SD_DisSelect();
	if (r1)
    {
        return 1;
	}
	else return 0;
}  
/*
    SD card for the total number of sectors (sectors)
    return values: 0: take capacity to make mistakes
    other: the capacity of the SD card (sectors / 512 bytes)
    the number of bytes of each sector will be 512, because if not 512, initialization is not through
*/
UINT32 SD_GetSectorCount(void)
{
    UINT8  csd[16];
    UINT32 Capacity;  
    UINT8  n;
	UINT   csize;  					    
    if(SD_GetCSD(csd)!=0) 
    {
        return 0;
    }
    /*sectors*/
    if((csd[0] & 0xC0) == 0x40)	
    {	
        printf("beta V2\n\r");
		csize    = csd[9] + ((UINT)csd[8] << 8) + 1;
		Capacity = (UINT32)csize << 10;
    }
    else
    {	
        printf("beta V1\n\r");
		n        = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
		csize    = (csd[8] >> 6) + ((UINT)csd[7] << 2) + ((UINT)(csd[6] & 3) << 10) + 1;
		Capacity = (UINT32)csize << (n - 9);
    }
    return Capacity;
}

UINT8 sd_init(void)
{
    INT8    r1;
    UINT    retry;
    UINT8   buf[4];
    UINT    i;

    sd_spi_init(); 
    for(i=1;i<10;i++)
    {
       spi_readwritebyte(0xFF); 
    }
    
    retry=20;
    do
    {
    	r1=SD_SendCmd(CMD0,0,0x95);//进入IDLE状态
    }
    while((r1!=0X01) && retry--);

    SD_Type=0;
    printf("CMD0 %d \n\r",r1);
    if (r1==0X01)
	{
        /*sd v2.0*/
		if (SD_SendCmd(CMD8,0x1AA,0x87) == 1)
		{
             /*Get trailing return value of R7 resp*/
			for(i=0;i<4;i++)
            {
                buf[i]=spi_readwritebyte(0XFF);
            }
            /*sd support voltage 2.7V ~ 3.6V*/
			if((buf[2] == 0X01) && (buf[3] == 0XAA))
			{
				retry=0XFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);	
					r1=SD_SendCmd(CMD41,0x40000000,0X01);
				}while(r1 && (retry--));
                /*Judge sd card version*/
				if(retry && (SD_SendCmd(CMD58,0,0X01) == 0))
				{
					for(i = 0;i < 4;i++)
                    {
                        buf[i]=spi_readwritebyte(0XFF);
					}
					if(buf[0]&0x40)
                    {
                        SD_Type=SD_TYPE_V2HC;    
                    }
					else SD_Type=SD_TYPE_V2;   
				}
			}
		}
        else//SD V1.x/ MMC	V3
		{
			SD_SendCmd(CMD55,0,0X01);		
			r1 = SD_SendCmd(CMD41,0,0X01);	
			if(r1 <= 1)
			{		
				SD_Type = SD_TYPE_V1;
				retry   = 0XFFFE;
				do 
				{
					SD_SendCmd(CMD55,0,0X01);	
					r1=SD_SendCmd(CMD41,0,0X01);
				}while(r1&&retry--);
			}else
			{
				SD_Type = SD_TYPE_MMC;
				retry   = 0XFFFE;
				do
				{											    
					r1 = SD_SendCmd(CMD1,0,0X01);
				}while(r1 && (retry--));  
			}
			if((retry == 0) || (SD_SendCmd(CMD16,512,0X01)!=0))
            {
                SD_Type=SD_TYPE_ERR;
            }
		}
	}
	SD_DisSelect();
    set_spi_speedhight();
	if(SD_Type)
    {
        return 0;
	}
	else if(r1)
    {
        return r1; 
	}
	return 0xaa;//其他错误
}
