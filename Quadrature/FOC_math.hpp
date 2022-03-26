#ifndef FOC_MATH_HPP
#define FOC_MATH_HPP

#include "stm32f405xx.h"
#include "arm_math.h"
#include "math.h"
#define USE_FPU_FOR_FOC_MATH

#define SQRT3_DIV2 0.866025403784439f
#define SQRT3_DIV3 0.577350269189626f

void forwardClarke(float32_t Vabc[3], float32_t Vab0[3]){
    Vab0[0] = 2.0f /3.0f * Vabc[0] - Vabc[1]/3.0f - Vabc[2]/3.0f;
    Vab0[1] = SQRT3_DIV3 * Vabc[1] - SQRT3_DIV3 * Vabc[2];
    Vab0[2] = (Vabc[0] + Vabc[1] + Vabc[2]) / 3.0f;
}

void inverseClarke(float32_t Vab0[3], float32_t Vabc[3]){
    Vabc[0] = Vab0[0] + Vab0[2];
    Vabc[1] = -0.5f * Vab0[0] + SQRT3_DIV2 * Vab0[1] + Vab0[2];
    Vabc[2] = -0.5f * Vab0[0] - SQRT3_DIV2 * Vab0[1] + Vab0[2];
}

void forwardPark(float32_t Vab0[3], float32_t theta_e, float32_t Vdq0[3]){
    float32_t sin_theta, cos_theta;
    #ifdef USE_FPU_FOR_FOC_MATH
        sin_theta = arm_sin_f32(theta_e);
        cos_theta = arm_cos_f32(theta_e);
    #else
        sin_theta = sin(theta_e);
        cos_theta = cos(theta_e);
    #endif

    Vdq0[0] =  cos_theta * Vab0[0] + sin_theta * Vab0[1];
    Vdq0[1] = -sin_theta * Vab0[0] + cos_theta * Vab0[1];
    Vdq0[2] = Vab0[2];
}

void inversePark(float32_t Vdq0[3], float32_t theta_e, float32_t Vab0[3]){
    float32_t sin_theta, cos_theta;
    #ifdef USE_FPU_FOR_FOC_MATH        
        sin_theta = arm_sin_f32(theta_e);
        cos_theta = arm_cos_f32(theta_e);
    #else
        sin_theta = sin(theta_e);
        cos_theta = cos(theta_e);
    #endif

    Vab0[0] = cos_theta * Vdq0[0] - sin_theta * Vdq0[1];
    Vab0[1] = sin_theta * Vdq0[0] + cos_theta * Vdq0[1];
    Vab0[2] = Vdq0[2];
}

#endif