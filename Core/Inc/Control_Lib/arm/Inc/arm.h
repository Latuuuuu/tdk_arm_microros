#ifndef INC_ARM_H_
#define INC_ARM_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

// C 函數宣告
extern float cascade_height;
extern int servo1_pos, servo2_pos, servo3_pos;
extern int gripper_open, gripper_close;
extern int camera_front, camera_down;
extern int set_to_zero;

void arm_init(void);                        // init arm
void arm_timer_callback(void);              // arm timer callback
void arm_cascade_set_to_zero(void* pvParameters);         // set arm to zero position

#ifdef __cplusplus
}

// C++ 標頭檔和類別定義
#include "UART_servo.h"

#endif /* __cplusplus */

#endif /* INC_ARM_H_ */
