#include "mission.hpp"
#include "arm.h"
#include "cmsis_os.h"

/*
Please put all the mission related function here.
*/
int mission_type = 0; // 1: mission 1, 2: mission 2
int mission_status = 0; // 0: not started, 1: in progress, 2: completed
int task_created = 0; // Flag to indicate if the tasks


void mission_init(void){
    arm_init();
}

void mission_1(void *pvParameters){
    mission_status = 0 + 10*mission_type;
    
    /* add motion here */
    
    /* add motion here */

    mission_status = 1 + 10*mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}

void mission_2(void *pvParameters){
    mission_status = 0 + 10*mission_type;

    /* add motion here */
    
    /* add motion here */

    mission_status = 1 + 10*mission_type;
    task_created = 0;
    vTaskDelete(NULL);  // Delete current task when mission is complete
}