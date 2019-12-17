

#ifndef __TEMP_TAB_H_
#define __TEMP_TAB_H_

#include <stdint.h>



extern const uint16_t SSR_Tab[1000]; //移相线性输出时延表
extern const int32_t NTC103_3435tab[]; //NTC热敏电阻R/T对照表
extern const int32_t KTtab[]; //K型热电偶分度表 -59~1372C
extern const int32_t JTtab[]; //J型热电偶分度表 -209~120C

extern const int32_t NTtab[]; //N型热电偶分度表 -200~1100C
extern const int32_t STtab[]; //S型热电偶分度表 0~1760C


#endif


