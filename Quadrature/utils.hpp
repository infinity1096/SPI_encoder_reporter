#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef __cplusplus
extern "C" {
#endif

// add C includes here
#include "arm_math.h"

#ifdef __cplusplus
}
#endif

float32_t clip(float32_t val, float32_t min, float32_t max){
    if (val < min){
        return min;
    }else if (val > max){
        return max;
    }else{
        return val;
    }
}

#endif