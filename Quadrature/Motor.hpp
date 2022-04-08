#ifndef MOTOR_HPP
#define MOTOR_HPP

#ifdef __cplusplus
extern "C" {
#endif

// add C includes here
#include "arm_math.h"

#ifdef __cplusplus
}
#endif

#include "encoder.hpp"
#include "current_sensor.hpp"
#include "modulator.hpp"
#include "PID_controller.hpp"
#include "FOC_math.hpp"
#include "VelocityObserver.hpp"

enum class MotorControlMode {
    NONE, VOLTAGE, CURRENT, VELOCITY, POSITION
};

class Motor{
    public:

    void currentLoopCallback(float32_t Iabc[3]){
        float32_t Iab0[3];
        inverseClarke(Iab0, Iabc);
    }


    private:
    // motor physical parameters
    float32_t Rs = 121.9e-3;       // Measured value, see notebook
    float32_t Lq = 103e-6;         // Measured value, see notebook
    float32_t pole_pairs = 11;     // Pole pairs
    bool is_encoder_inverted = false;

    // motor state
    MotorControlMode controlMode = MotorControlMode::NONE;
    float32_t targetCurrentIq;
    float32_t targetCurrentId;
    float32_t targetVelocity;
    float32_t targetPosition;
    
    // motor sensors
    AS5048* encoder;
    ADCSampledShunt* currentSensor;

    // motor state estimation
    VelocityObserver* vel_observer;
    
    // motor control policy
    PIDController dAxisCurrentController;
    PIDController qAxisCurrentController;

    PIDController velocityController;
    PIDController positionController;
    
    // motor actuator
    DRV8301* modulator;
};

#endif