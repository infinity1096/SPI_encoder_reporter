#include "modulator.hpp"

void DRV8301::initialize(){
    hardwareDisable();
}

void DRV8301::hardwareEnable(){
    HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Start(htimx, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(htimx, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(htimx, TIM_CHANNEL_3);

    this->enable_pin.write(true);
}

void DRV8301::hardwareDisable(){
    HAL_TIM_PWM_Stop(htimx, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(htimx, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(htimx, TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Stop(htimx, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(htimx, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Stop(htimx, TIM_CHANNEL_3);
    this->enable_pin.write(false);
}

void DRV8301::modulate(float32_t Va, float32_t Vb, float32_t Vc){
    uint16_t tim_period = htimx->Init.Period;

    htimx->Instance->CCR1 = tim_period * (0.5f + Va / this->V_dc);
    htimx->Instance->CCR2 = tim_period * (0.5f + Vb / this->V_dc);
    htimx->Instance->CCR3 = tim_period * (0.5f + Vc / this->V_dc); 
}