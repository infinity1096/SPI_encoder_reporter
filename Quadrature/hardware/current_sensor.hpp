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
    bool is_valid = false;    
};

class ADCSampledShunt : public ICurrentSensor{
    public:

    private:

};

#endif