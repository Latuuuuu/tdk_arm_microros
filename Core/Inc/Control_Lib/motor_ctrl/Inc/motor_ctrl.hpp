#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f446xx.h"

#include "math.h"
#include "motor_config.h"

class MotorController{
public:
    MotorController(TIM_HandleTypeDef* enc, TIM_HandleTypeDef* pwm, uint32_t channel, GPIO_TypeDef* AGPIO, uint16_t APin, GPIO_TypeDef* BGPIO, uint16_t BPin, double kp, double ki, double kd):
        _enc(enc), _pwm(pwm), _channel(channel), _AGPIO(AGPIO), _APin(APin), _BGPIO(BGPIO), _BPin(BPin), _kp(kp), _ki(ki), _kd(kd){}
    ~MotorController() = default;
    
    void init(int en_ctrl,int dir_ctrl);                        // Initialize the basic parameter
//    void setSpeed(float speed);        // Set motor speed in RPS
//    float getSpeed();                  // Return the current speed (Need to enable setSpeed())
    void setgoal(float target_height);
    bool goal_reached();


private:
    TIM_HandleTypeDef* _enc;
    TIM_HandleTypeDef* _pwm;
    uint32_t _channel;
    GPIO_TypeDef* _AGPIO;
    uint16_t _APin;
    GPIO_TypeDef* _BGPIO;
    uint16_t _BPin;

    float _kp;
    float _ki;
    float _kd;

//    bool _isCountingDown = false;
//    bool _isRotating = false;
//    uint16_t _last_cnt = 0;
//    int16_t cnt = 0;
    uint16_t _pwmValue = 0;
//    float _pidOutput = 0.0;
//    float _currentSpeed = 0;
//    float _targetSpeed = 0;
    float _targrt_height = 0.0;
    float _error = 0;
//    float _lastError = 0;
    float _integral = 0;
    float _dt = 100;
//    uint16_t _current_cnt = 0;
    int _en_ctrl = 0;
    int _dir_ctrl = 0;
//    //int _doupdatespeed = 0;
    float _cascade_height = 250.0;
    int _check=0;
    int _microswitch_touched = 0;
    const float CASCADE_STARTHIGHT = 250.0;
    int16_t _enc_count;
    float _u = 0.0;
    int MAX_PWM = 1000;
    int MIN_PWM = 200;
//
//    float ComputePID();                // PID controller
//    float updateSpeed();               // Update the motor current speed
};

#ifdef __cplusplus
}
#endif

#endif /* MOTOR_CTRL_H */
