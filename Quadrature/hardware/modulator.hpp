#ifndef __MODULATOR_HPP
#define __MODULATOR_HPP

// C includes
#ifdef __cplusplus
extern "C" {
#endif

// add C includes here
#include "stm32f4xx_hal.h"
#include "arm_math.h"

#ifdef __cplusplus
}
#endif

// C++ includes
#include "stm32gpio.hpp"
#include "FOC_math.hpp"
class IModulator {
    public:
    virtual void initialize()=0;

    virtual void hardwareEnable()=0;
    virtual void hardwareDisable()=0;

    bool isFault(){
        return this->fault;
    }
    
    virtual void modulate(float32_t Va, float32_t Vb, float32_t Vc)=0;
    virtual void modulate(float32_t Vab0[3])=0;

    private:
    bool fault = false;
    bool enabled = false;
};

class DRV8301 : public IModulator{
    public:
    DRV8301(TIM_HandleTypeDef* htimx, STM32Gpio enable_pin, STM32Gpio nfault_pin, STM32Gpio noctw_pin) : htimx(htimx), enable_pin(enable_pin), nfault_pin(nfault_pin), noctw_pin(noctw_pin) {};

    void initialize();

    void hardwareEnable();
    void hardwareDisable();
    void modulate(float32_t Va, float32_t Vb, float32_t Vc) override;
    void modulate(float32_t Vab0[3]) override;

    TIM_HandleTypeDef* htimx;

    private:
    STM32Gpio enable_pin;
    STM32Gpio nfault_pin;
    STM32Gpio noctw_pin;

    float32_t V_dc = 24.0; // FIXME: make this real value sensed by ADC
};

#endif