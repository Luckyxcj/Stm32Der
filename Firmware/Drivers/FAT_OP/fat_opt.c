

#include "fat_opt.h"

extern char USER_Path[4]; 
                                   
void get_sd_free(void)                                                                     
{
    FRESULT f_res = 0;               
    FATFS *pfs;
    DWORD fre_clust, fre_sect, tot_sect;
    printf("\n*************** �豸��Ϣ��ȡ ***************\r\n");
    /* ��ȡ�豸��Ϣ�Ϳմش�С */
    f_res = f_getfree((TCHAR const*)USER_Path, &fre_clust, &pfs);
    /* ����õ��ܵ����������Ϳ��������� */
    tot_sect = (pfs->n_fatent - 2) * pfs->csize;
    fre_sect = fre_clust * pfs->csize;
    printf("���豸�ܿռ䣺%10lu M��\n\r�����ÿռ䣺  %10lu M��\n\r", tot_sect >>1 , fre_sect >>1);
    printf("\n*************** �豸��Ϣ��ȡ ***************\r\n");
}

static FRESULT test_write_read(void)
{
    FRESULT f_res;             
    UINT16 fnum;                    
    BYTE readbuffer[40];
    DIR dir;
    FIL file;  
    printf("\n******** �ļ���λ�͸�ʽ��д�빦�ܲ��� ********\r\n\r");
    f_res = f_open(&file, (const TCHAR *)"ABCS.txt",FA_CREATE_ALWAYS|FA_WRITE|FA_READ|FA__WRITTEN );
    printf("\n******** OPEN %d ********\r\n\r",f_res);
    if ( f_res == FR_OK )
    {
        BYTE BUF_W[]="only test OKOKO HAPPY";
        f_res = f_write(&file,BUF_W, sizeof(BUF_W),&fnum);
        printf("f_write ��%d count = %d\n\r", f_res, fnum); 
        f_sync(&file);
        f_lseek(&file, 0);
        f_res = f_read(&file,readbuffer,sizeof(readbuffer),&fnum);
        printf("��%d �ļ�����%scount%d\n\r ", f_res,readbuffer, fnum);
        f_res = f_close(&file);
        printf("f_close ��%d count = %d\n\r", f_res, fnum);
    }

#if 0 
    printf("\n********** Ŀ¼���������������ܲ��� **********\r\n");
    /* ���Դ�Ŀ¼ */
    f_res=f_opendir(&dir,"TestDir");
    printf("f_opendir %d",f_res);
    if(f_res!=FR_OK)
    {
      /* ��Ŀ¼ʧ�ܣ��ʹ���Ŀ¼ */
      f_res = f_mkdir("TestDir");
      printf("mkdir %d",f_res);
    }
    else
    {
      /* ���Ŀ¼�Ѿ����ڣ��ر��� */
      
      f_res=f_closedir(&dir);
      printf("f_closedir %d \n\r",f_res);
      /* ɾ���ļ� */
      //f_unlink("TestDir/testdir.txt");
      printf("f_unlink %d \n\r",f_res);
    }
    
    if(f_res==FR_OK)
    {
      /* ���������ƶ��ļ� */
     // f_res=f_rename("FatFs��д�����ļ�.txt","TestDir/testdir.txt");   
      printf("f_rename %d",f_res);
    } 
#endif
    return f_res;
}

static FRESULT scan_files (char* path) 
{ 
    FRESULT f_res;                                
    DIR dir;
  FRESULT res;               
  FILINFO fno;  
  int i;            
  char *fn;      
        
#if _USE_LFN 

  static char lfn[_MAX_LFN*2 + 1];         
  fno.lfname = lfn; 
  fno.lfsize = sizeof(lfn); 
#endif 

  res = f_opendir(&dir, path); 
  if (res == FR_OK) 
  { 
    i = strlen(path); 
    for (;;) 
     { 
      res = f_readdir(&dir, &fno);                                                                 
      if (res != FR_OK || fno.fname[0] == 0) break;         
#if _USE_LFN 
      fn = *fno.lfname ? fno.lfname : fno.fname; 
#else 
      fn = fno.fname; 
#endif 
      if (*fn == '.') 
      {
            continue;
      }
      if (fno.fattrib & AM_DIR)         
       {                         
        sprintf(&path[i], "/%s", fn);                 
        res = scan_files(path);        
        path[i] = 0;         
        if (res != FR_OK) 
        {
          printf("%s/%s\n\r", path, fn); 
          break; 
        }
      } 
      printf("%s/%s\n\r", path, fn); 
    } //for
  } 
  return res; 
}
/**
  * �ļ���Ϣ��ȡ
  */
static FRESULT file_check(void)
{  
    FRESULT f_res;
    static FILINFO finfo;
    /* ��ȡ�ļ���Ϣ */
    f_res=f_stat("TestDir/testdir.txt",&finfo);
    if(f_res==FR_OK)
    {
        printf("��testdir.txt���ļ���Ϣ��\n");
        printf("���ļ���С: %ld(�ֽ�)\n", finfo.fsize);
        printf("��ʱ���: %u/%02u/%02u, %02u:%02u\n",
               (finfo.fdate >> 9) + 1980, finfo.fdate >> 5 & 15, finfo.fdate & 31,finfo.ftime >> 11, finfo.ftime >> 5 & 63);
        printf("������: %c%c%c%c%c\n\n",
               (finfo.fattrib & AM_DIR) ? 'D' : '-',      // ��һ��Ŀ¼
               (finfo.fattrib & AM_RDO) ? 'R' : '-',      // ֻ���ļ�
               (finfo.fattrib & AM_HID) ? 'H' : '-',      // �����ļ�
               (finfo.fattrib & AM_SYS) ? 'S' : '-',      // ϵͳ�ļ�
               (finfo.fattrib & AM_ARC) ? 'A' : '-');     // �����ļ�
    }
    return f_res;
}
