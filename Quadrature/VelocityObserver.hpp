#ifndef VELOCITY_OBSERVER_HPP
#define VELOCITY_OBSERVER_HPP

#ifdef __cplusplus
extern "C" {
#endif

// add C includes here
#include "arm_math.h"

#ifdef __cplusplus
}
#endif

#include "MicrosecondTimer.hpp"
#define SUB_STEPS 5

class VelocityObserver {
    public:
    VelocityObserver(float32_t bandwidth, MicrosecondsTimer* timer) : bandwidth(bandwidth), timer(timer) {}

    float32_t getVelocity(){
        if (!initialized){
            return 0.0f;
        }

        return velocity_est;
    }
    
    void update(float32_t position){
        uint64_t nowTime = timer->micros();

        if (!initialized){
            integratorState = position;
            initialized = true;
            last_updated_us = nowTime;
        }

        float32_t dt = static_cast<float32_t>(nowTime - last_updated_us) / 1e6;
        last_updated_us = nowTime;

        // derivative filtering
        for (int i = 0; i < SUB_STEPS; i++){
            integratorState += dt * bandwidth * (position - integratorState) / SUB_STEPS;
        }

        velocity_est = bandwidth * (position - integratorState);
    }

    private:
    float32_t integratorState = 0;
    bool initialized = false;
    uint64_t last_updated_us = 0;

    float32_t bandwidth;
    float32_t velocity_est;
    MicrosecondsTimer* timer;
};

#endif