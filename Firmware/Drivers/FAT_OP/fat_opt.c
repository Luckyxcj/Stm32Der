

#include "fat_opt.h"

extern char USER_Path[4]; 
                                   
void get_sd_free(void)                                                                     
{
    FRESULT f_res = 0;               
    FATFS *pfs;
    DWORD fre_clust, fre_sect, tot_sect;
    printf("\n*************** 设备信息获取 ***************\r\n");
    /* 获取设备信息和空簇大小 */
    f_res = f_getfree((TCHAR const*)USER_Path, &fre_clust, &pfs);
    /* 计算得到总的扇区个数和空扇区个数 */
    tot_sect = (pfs->n_fatent - 2) * pfs->csize;
    fre_sect = fre_clust * pfs->csize;
    printf("》设备总空间：%10lu M。\n\r》可用空间：  %10lu M。\n\r", tot_sect >>1 , fre_sect >>1);
    printf("\n*************** 设备信息获取 ***************\r\n");
}

static FRESULT test_write_read(void)
{
    FRESULT f_res;             
    UINT16 fnum;                    
    BYTE readbuffer[40];
    DIR dir;
    FIL file;  
    printf("\n******** 文件定位和格式化写入功能测试 ********\r\n\r");
    f_res = f_open(&file, (const TCHAR *)"ABCS.txt",FA_CREATE_ALWAYS|FA_WRITE|FA_READ|FA__WRITTEN );
    printf("\n******** OPEN %d ********\r\n\r",f_res);
    if ( f_res == FR_OK )
    {
        BYTE BUF_W[]="only test OKOKO HAPPY";
        f_res = f_write(&file,BUF_W, sizeof(BUF_W),&fnum);
        printf("f_write ：%d count = %d\n\r", f_res, fnum); 
        f_sync(&file);
        f_lseek(&file, 0);
        f_res = f_read(&file,readbuffer,sizeof(readbuffer),&fnum);
        printf("》%d 文件内容%scount%d\n\r ", f_res,readbuffer, fnum);
        f_res = f_close(&file);
        printf("f_close ：%d count = %d\n\r", f_res, fnum);
    }

#if 0 
    printf("\n********** 目录创建和重命名功能测试 **********\r\n");
    /* 尝试打开目录 */
    f_res=f_opendir(&dir,"TestDir");
    printf("f_opendir %d",f_res);
    if(f_res!=FR_OK)
    {
      /* 打开目录失败，就创建目录 */
      f_res = f_mkdir("TestDir");
      printf("mkdir %d",f_res);
    }
    else
    {
      /* 如果目录已经存在，关闭它 */
      
      f_res=f_closedir(&dir);
      printf("f_closedir %d \n\r",f_res);
      /* 删除文件 */
      //f_unlink("TestDir/testdir.txt");
      printf("f_unlink %d \n\r",f_res);
    }
    
    if(f_res==FR_OK)
    {
      /* 重命名并移动文件 */
     // f_res=f_rename("FatFs读写测试文件.txt","TestDir/testdir.txt");   
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
  * 文件信息获取
  */
static FRESULT file_check(void)
{  
    FRESULT f_res;
    static FILINFO finfo;
    /* 获取文件信息 */
    f_res=f_stat("TestDir/testdir.txt",&finfo);
    if(f_res==FR_OK)
    {
        printf("“testdir.txt”文件信息：\n");
        printf("》文件大小: %ld(字节)\n", finfo.fsize);
        printf("》时间戳: %u/%02u/%02u, %02u:%02u\n",
               (finfo.fdate >> 9) + 1980, finfo.fdate >> 5 & 15, finfo.fdate & 31,finfo.ftime >> 11, finfo.ftime >> 5 & 63);
        printf("》属性: %c%c%c%c%c\n\n",
               (finfo.fattrib & AM_DIR) ? 'D' : '-',      // 是一个目录
               (finfo.fattrib & AM_RDO) ? 'R' : '-',      // 只读文件
               (finfo.fattrib & AM_HID) ? 'H' : '-',      // 隐藏文件
               (finfo.fattrib & AM_SYS) ? 'S' : '-',      // 系统文件
               (finfo.fattrib & AM_ARC) ? 'A' : '-');     // 档案文件
    }
    return f_res;
}
