#include "arm.h"
#include "math.h"
#include "UART_servo.h"
#include "stm32f4xx_hal.h"
#include "motor_monitor.hpp"
#include "motor_ctrl.hpp"
#include "cmsis_os.h"
#include <stdint.h>
#include <stdbool.h>

// UART_servo 物件
UART_servo servo1(1, 1000, &huart3);
UART_servo servo2(3, 1000, &huart3);
UART_servo servo3(4, 1000, &huart3);
int standard_pos_1 = 70,standard_pos_2 = 60;
int gripper_open = 75, gripper_close = 23;
int servo1_pos = standard_pos_1 + 90, servo2_pos = standard_pos_2 + 100, servo3_pos = gripper_close; 	// servo 初始位置
int basket_pos1 = 240, basket_pos2 = 0, basket_grab = 200;
int basket_right_pos = 500+200/180*basket_pos1, basket_left_pos = 500+1200/180*basket_pos2;
int doll_pos1 = 180, doll_pos2 = 1, doll_extend = 0, doll_open = 80;
int doll_arm_pos = 500+1200/180*doll_pos1, doll_claw_pos = 500+1200/180*doll_pos2;
int camera_front = 600+10*10, camera_down = 600+10*113;
int camera_servo_pos = camera_front;
int set_to_zero = 0; 										// 設定 Cascade 歸零旗標	
int started = 0; 											// 系統是否初始化完成，可以開始移動 Cascade


// Cascade 物件
#define CASCADE_STARTHIGHT 250.0f
float cascade_height = CASCADE_STARTHIGHT; //cascade起始高度
MotorController Motor_cas(&htim1, &htim12, TIM_CHANNEL_2, GPIOB, GPIO_PIN_12, 0.6, 30, 0);


void arm_init(void) {
	// 手臂初始化邏輯
	HAL_Init();
	// 啟動 Encoder 與 PWM
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
//	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	servo1.update_pos(servo1_pos);
	servo2.update_pos(servo2_pos);
	servo3.update_pos(servo3_pos);

	servo1.run();
	servo2.run();
	servo3.run();

	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, camera_servo_pos);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, doll_arm_pos);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, doll_claw_pos);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, basket_right_pos);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, basket_left_pos);

	// 初始化 Cascade
	Motor_cas.init(-1,-1);								// 初始化 Cascade 馬達控制器
	Motor_cas.setSpeed(0.0);							// 停止移動
	xTaskCreate(arm_cascade_set_to_zero, "arm_cascade_set_to_zero", 512, NULL, 2, NULL); // 開啟 Cascade 歸零任務
}


void arm_timer_callback(void) {							// constantly run the servo in timer callback
	if(started) Motor_cas.setgoal(cascade_height); 		// after the system is fully initialized, keep updating the goal position
	Motor_cas.MotorOutput();							// update the motor PWM output	
	servo1.update_pos(servo1_pos);
	servo2.update_pos(servo2_pos);
	servo3.update_pos(servo3_pos);
	servo1.run();
	servo2.run();
	servo3.run();
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, camera_servo_pos);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, doll_arm_pos);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, doll_claw_pos);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, basket_right_pos);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, basket_left_pos);
}


void arm_cascade_set_to_zero(void* pvParameters){
	set_to_zero = 0;
	cascade_height = CASCADE_STARTHIGHT + 30.0f; 		// 設定目標高度為目前位置向上30mm
	while(!Motor_cas.goal_reached()){
		Motor_cas.setgoal(cascade_height); 				// 往上移動一點點，防止原本已經在底部
		osDelay(10);									// delay 10ms to avoid too high refreshing rate
	}
	while(!set_to_zero){
		Motor_cas.setSpeed(-0.3f); 						// 以固定速度往下移動
		osDelay(10);									// delay 10ms to avoid too high refreshing rate
	}
	started = 1;										// 系統初始化完成，可以開始移動 Cascade
	cascade_height = 280;
	vTaskDelete(NULL);  // Delete current task when mission is complete
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_2) {
		set_to_zero = 1;								// 設定 Cascade 歸零旗標
		Motor_cas.setSpeed(0.0f);						// 停止移動
		Motor_cas._cascade_height = CASCADE_STARTHIGHT;	// 重置 Cascade 量測高度
		cascade_height = CASCADE_STARTHIGHT;			// 重置 Cascade 目標高度
	}
}
