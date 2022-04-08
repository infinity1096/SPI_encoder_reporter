#ifndef MICROSECOND_TIMER_HPP
#define MICROSECOND_TIMER_HPP

#ifdef __cplusplus
extern "C" {
#endif

// add C includes here
#include "stm32f4xx_hal.h"
#include "arm_math.h"

#ifdef __cplusplus
}
#endif

#define HALF_PERIOD (((uint64_t)htimx->Instance->ARR) + 1)

class MicrosecondsTimer{
    public:
    MicrosecondsTimer(TIM_HandleTypeDef* htimx, uint32_t TIMClockFreq=168000000ul) : htimx(htimx), tim_clock_freq(TIMClockFreq) {}

    void initialize(){
        htimx->Instance->ARR = 65535;
        htimx->Instance->PSC = (tim_clock_freq / 500000ul) - 1;

        HAL_TIM_Base_Start_IT(htimx);
    }

    void TIMCallback(){
        bool dir = ((htimx->Instance->CR1 >> 4) & 0x01);
        accumlated_us += HALF_PERIOD;
        last_count_dir = dir;
    }

    uint64_t micros(){
        uint32_t current_timer_tick = htimx->Instance->CNT;
        bool dir = ((htimx->Instance->CR1 >> 4) & 0x01);

        if (dir == true){
            current_timer_tick = HALF_PERIOD - current_timer_tick;
        }else{
            current_timer_tick = current_timer_tick;
        }

        if (dir != last_count_dir){
            return accumlated_us + current_timer_tick + HALF_PERIOD;
        }

        return 2 * (accumlated_us + current_timer_tick);
    }

    private:
    TIM_HandleTypeDef* htimx;
    uint32_t           tim_clock_freq = 168000000ul;
    uint64_t           accumlated_us = 0;
    bool               last_count_dir = true;
};

#endif