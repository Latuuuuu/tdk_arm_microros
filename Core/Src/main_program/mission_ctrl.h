
#ifndef SRC_MAIN_PROGRAM_MISSION_CTRL_H_
#define SRC_MAIN_PROGRAM_MISSION_CTRL_H_
#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f446xx.h"
#include <stdbool.h>

// 函數宣告
void read_btn_sta();
void mission_set();
void send_mission();

// 外部變數宣告
extern bool mis_1, mis_2, mis_3, mis_4, mis_LR;
extern int mis_num, mis_dir, mis_set;
extern bool mis_set_flag;

#ifdef __cplusplus
}
#endif



#endif /* SRC_MAIN_PROGRAM_MISSION_CTRL_H_ */
