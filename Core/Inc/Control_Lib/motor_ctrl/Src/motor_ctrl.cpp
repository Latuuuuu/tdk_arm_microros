#include "../Inc/motor_ctrl.hpp"
#include "math.h"
int times = 0;
uint32_t current_cnt;
float v = 0.5;
float e = 1.0;

void MotorController::init(int en_ctrl,int dir_ctrl) {
    HAL_TIM_Encoder_Start(_enc, TIM_CHANNEL_ALL);
    HAL_TIM_PWM_Start(_pwm, _channel);
    _dir_ctrl = dir_ctrl;
    _en_ctrl = en_ctrl;
}

void MotorController::MotorOutput(void) {
    ComputePID();

    if (_dir_ctrl == 1){
    	HAL_GPIO_WritePin(_BGPIO, _BPin, _pidOutput >= 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }else{
    	HAL_GPIO_WritePin(_BGPIO, _BPin, _pidOutput >= 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }
    _pwmValue = (uint16_t)(fabs(_pidOutput) * PWM_ARR );///  10.0);
    if (_pwmValue < 10) _pwmValue = 0;
    __HAL_TIM_SET_COMPARE(_pwm, _channel, _pwmValue);
}

void MotorController::setSpeed(float speed) {
    _targetSpeed = speed;
}

float MotorController::getSpeed() {
    return _currentSpeed;
}

float MotorController::ComputePID() {
    updateSpeed();
    _error = _targetSpeed - _currentSpeed;

    _integral += _error * (DT / 1000.0);
    if(_integral >= INTEGRAL_LIMIT) _integral = INTEGRAL_LIMIT;
    else if(_integral <= -INTEGRAL_LIMIT) _integral = -INTEGRAL_LIMIT;


    float derivative = (_error - _lastError) / (DT / 1000.0);

    _pidOutput = (_kp * _error) + (_ki * _integral); //+ (_kd * derivative);

    // Update last error
    _lastError = _error;
    if(_pidOutput > 1) _pidOutput = 1;
    else if (_pidOutput < -1) _pidOutput = -1;
    return _pidOutput;
	float bound = 1.0f / _ki;
	_error = _targetSpeed - _currentSpeed;

	_integral += _error * (DT / 1000.0);
	if(_integral > bound) _integral = bound;
	else if(_integral < -bound) _integral = -bound;

	_pidOutput = _kp * _error + _ki * _integral ;

	if (_pidOutput > 1) _pidOutput = 1;
	else if (_pidOutput < -1) _pidOutput = -1;
    return _pidOutput;
}

float MotorController::updateSpeed() {
	cnt = __HAL_TIM_GetCounter(_enc);
	_cascade_height += -(float)cnt / (4.0f * ENCODER_RESOLUTION * REDUCTION_RATIO) * 3.14 * 35;
	_currentSpeed = (cnt/ENCODER_RESOLUTION / REDUCTION_RATIO / 4) / (DT / 1000.0);
    __HAL_TIM_SET_COUNTER(_enc, 0);
    _currentSpeed *= _en_ctrl;
    return _currentSpeed;
}

void MotorController::setgoal(float target_height) {
	_targrt_height  = target_height;
	if(fabs(_targrt_height - _cascade_height) <= e){
		setSpeed(0.0);
	}
	else if(_targrt_height - _cascade_height>0) setSpeed(v);
	else setSpeed(-v);
}

bool MotorController::goal_reached(){
    if(fabs(_cascade_height-_targrt_height )<= e){
        return true;
    } else
        return false;
}
