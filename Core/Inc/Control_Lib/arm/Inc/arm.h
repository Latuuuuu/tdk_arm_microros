#ifndef INC_ARM_H_
#define INC_ARM_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim12;
// C 函數宣告
extern float cascade_height;
extern int standard_pos_1,standard_pos_2;
extern int servo1_pos, servo2_pos, servo3_pos;
extern int gripper_open, gripper_close;
extern int camera_front, camera_down;
extern int camera_servo_pos;
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
