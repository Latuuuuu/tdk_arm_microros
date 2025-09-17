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
        task_created = 1;
        switch (mission_type)
        {
        case 1:
            if (!task_created) {
                xTaskCreate(mission_1, "mission_1", 512, NULL, 2, NULL);
            }
            break;
        case 2:
            if (!task_created) {
                xTaskCreate(mission_2, "mission_2", 512, NULL, 2, NULL);
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
    
    /* add motion here */

    mission_status = mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}

void mission_2(void *pvParameters){
    mission_status = 0;

    /* add motion here */
    
    /* add motion here */

    mission_status = mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}