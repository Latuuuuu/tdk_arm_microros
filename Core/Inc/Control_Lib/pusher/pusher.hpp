/*
 * pusher.hpp
 *
 *  Created on: Sep 27, 2025
 *      Author: ling
 */

#ifndef INC_CONTROL_LIB_PUSHER_PUSHER_HPP_
#define INC_CONTROL_LIB_PUSHER_PUSHER_HPP_
#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f446xx.h"
#include <stdbool.h>


void trace_init();            // Initialize infrared sensor
void pusher_move(int pusher_num, int pusher_dir);
void wheel_mive(int _dir);

#ifdef __cplusplus
}
#endif




#endif /* INC_CONTROL_LIB_PUSHER_PUSHER_HPP_ */
