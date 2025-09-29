/*stm32 include*/
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "timers.h"
#include "uros_init.h"
#include "arm.h"
#include "mission_ctrl.h"

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim12;


uint16_t adcRead[7] = {0};

extern int code;
double LastCNT = 0;
double CNT = 500;
int pulse =0;
int currentsp = 0;
int sec = 0;


void StartDefaultTask(void *argument)
{
	HAL_TIM_Base_Start_IT(&htim4);
	uros_init();
	arm_init();

    for(;;){
        uros_agent_status_check();
        osDelay(50);
		currentsp ++;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	if (htim->Instance == TIM4)
	{
		arm_timer_callback();
		send_mission();
		sec ++;
	}
  /* USER CODE END Callback 0 */
	if (htim->Instance == TIM6)
	{
		HAL_IncTick();
	}
  /* USER CODE BEGIN Callback 1 */
  /* USER CODE END Callback 1 */
}


//TODO:motor_PID,chassis,odometry,
//TODO: check other PWM output


