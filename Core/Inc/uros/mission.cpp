#include "mission.hpp"
#include "arm.h"
#include "cmsis_os.h"

/*
Please put all the mission related function here.
*/
int mission_type = 0; // 1: mission 1, 2: mission 2
int prev_mission_type = 0;
int mission_status = 0; // mission_type+status: 10*mission_type + status (0: working, 1: completed)
int task_created = 0; // Flag to indicate if the tasks


void mission_init(void){
    arm_init();
}

void mission_ctrl(void){
    if(prev_mission_type != mission_type){
        prev_mission_type = mission_type;
        switch (mission_type)
        {
        case 1:
            if (!task_created) {
                task_created = 1;
                xTaskCreate(mission_1, "mission_1", 512, NULL, 2, NULL);
            }
            break;
        case 2:
            if (!task_created) {
                task_created = 1;
                xTaskCreate(mission_2, "mission_2", 512, NULL, 2, NULL);
            }
            break;
        case 3:
            if (!task_created) {
                task_created = 1;
                xTaskCreate(mission_3, "mission_3", 512, NULL, 2, NULL);
            }
            break;
        case 4:
            if (!task_created) {
                task_created = 1;
                xTaskCreate(mission_4, "mission_4", 512, NULL, 2, NULL);
            }
            break;
        default:
            break;
        }
    }
}

void mission_1(void *pvParameters){
    mission_status = 0;
    
    /* add motion here */
    cascade_height = 250;
    servo1_pos = 180;
    servo2_pos = 201;
    servo3_pos = gripper_close;
	osDelay(2000);
//	osDelay(5000);
    /* add motion here */

    mission_status = mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}

void mission_2(void *pvParameters){
    mission_status = 0;

    /* add motion here */
    cascade_height = 574;
	servo1_pos = 92;
	servo2_pos = 83;
	servo3_pos = gripper_open;
    osDelay(3000);
    cascade_height = 474;
    osDelay(2000);
	servo3_pos = gripper_close;
    osDelay(2000);
    /* add motion here */

    mission_status = mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}
void mission_3(void *pvParameters){
    mission_status = 0;

    /* add motion here */
    cascade_height = 279;
	servo1_pos = 91;
	servo2_pos = 82;
	servo3_pos = gripper_close;
	osDelay(3000);
    /* add motion here */

    mission_status = mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}

void mission_4(void *pvParameters){
    mission_status = 0;

    /* add motion here */
    cascade_height = 423;
	servo1_pos = 54;
	servo2_pos = 45;
	servo3_pos = gripper_close;
	osDelay(3000);
	cascade_height = 323;
	servo3_pos = gripper_open;
	osDelay(2000);
	cascade_height = 250;
	servo1_pos = 180;
	servo2_pos = 201;
	servo3_pos = gripper_open;
    /* add motion here */

    mission_status = mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}
