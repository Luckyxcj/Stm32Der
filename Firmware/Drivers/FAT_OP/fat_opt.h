#ifndef __FAT_OPT__
#define __FAT_OPT__
#include "ff.h"
#include "ff_gen_drv.h"
#include "string.h"
#include "defs.h"
extern void get_sd_free(void);
extern FRESULT test_write_read(void);
extern FRESULT scan_files (char* path);

#endif /*__FAT_OPT__*/
