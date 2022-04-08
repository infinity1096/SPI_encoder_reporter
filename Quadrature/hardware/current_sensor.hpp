#ifndef __CURRENT_SENSOR_HPP
#define __CURRENT_SENSOR_HPP

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
class ICurrentSensor{
    public:

    void is_valid();
    void getCurrent(float32_t& Ia, float32_t& Ib, float32_t& Ic);

    virtual void ADCSampleCallback()=0;

    private:
    float32_t sensed_current[3];
    bool is_valid_ = false;    
};

class ADCSampledShunt {
    public:
    ADCSampledShunt(int16_t* DMATarget, float32_t amplifierGain, float32_t shuntResistance) {
        amplifier_gain = amplifierGain;
        shunt_resistance = shuntResistance;
        DMA_target = DMATarget;
    }

    void getCurrent(float32_t Iabc[3]) {
        Iabc[0] = ((float32_t)(DMA_target[0] - 2047)) * 1.65 / 2048.0 / shunt_resistance / amplifier_gain;
        Iabc[1] = ((float32_t)(DMA_target[1] - 2047)) * 1.65 / 2048.0 / shunt_resistance / amplifier_gain;
        Iabc[2] = ((float32_t)(DMA_target[2] - 2047)) * 1.65 / 2048.0 / shunt_resistance / amplifier_gain;
    }

    private:
    float32_t amplifier_gain = 20;
    float32_t shunt_resistance = 0.002;
    int16_t* DMA_target;
};

#endif