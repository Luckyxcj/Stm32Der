#ifndef __SD_H__
#define __SD_H__
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#define SD_CS_Pin GPIO_PIN_3
#define SD_CS_GPIO_Port GPIOA


//�˿ڶ���
#define SD_CS_H	    HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET);
#define F_CS_H	    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
#define JF24_CS_H	HAL_GPIO_WritePin(JF24_RST_GPIO_Port, JF24_RST_Pin, GPIO_PIN_SET);

#define SD_CS_L	    HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);
#define F_CS_L	    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
#define JF24_CS_L	HAL_GPIO_WritePin(JF24_RST_GPIO_Port, JF24_RST_Pin, GPIO_PIN_RESET);

// SD�����Ͷ���  
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	   
// SD��ָ���  	   
#define CMD0    0       //����λ
#define CMD1    1
#define CMD8    8       //����8 ��SEND_IF_COND
#define CMD9    9       //����9 ����CSD����
#define CMD10   10      //����10����CID����
#define CMD12   12      //����12��ֹͣ���ݴ���
#define CMD16   16      //����16������SectorSize Ӧ����0x00
#define CMD17   17      //����17����sector
#define CMD18   18      //����18����Multi sector
#define CMD23   23      //����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24��дsector
#define CMD25   25      //����25��дMulti sector
#define CMD41   41      //����41��Ӧ����0x00
#define CMD55   55      //����55��Ӧ����0x01
#define CMD58   58      //����58����OCR��Ϣ
#define CMD59   59      //����59��ʹ��/��ֹCRC��Ӧ����0x00
//����д���Ӧ������
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD����Ӧ�����
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF

typedef unsigned long  UINT32;
typedef unsigned short UINT16;
typedef unsigned char  UINT8;

typedef unsigned long  INT32;
typedef unsigned short INT16;
typedef unsigned char  INT8;


extern UINT8 sd_init(void);
//extern UINT32 SD_GetSectorCount(void);
extern void set_spi_speedlow(void);
extern void set_spi_speedhight(void);
extern UINT8 spi_readwritebyte(UINT8);
extern UINT8 SD_WaitReady(void);							//�ȴ�SD��׼��
extern UINT8 SD_GetResponse(UINT8 Response);					//�����Ӧ
//extern UINT8 SD_Initialize(void);							//��ʼ��
extern UINT8 SD_ReadDisk(UINT8*buf,UINT32 sector,UINT8 cnt);		//����
extern UINT8 SD_WriteDisk(UINT8*buf,UINT32 sector,UINT8 cnt);		//д��
extern UINT32 SD_GetSectorCount(void);   					//��������
extern UINT8 SD_GetCID(UINT8 *cid_data);                     //��SD��CID
extern UINT8 SD_GetCSD(UINT8 *csd_data);                     //��SD��CSD
#endif

