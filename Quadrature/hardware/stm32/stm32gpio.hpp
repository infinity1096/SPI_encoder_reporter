#ifndef __STM32GPIO_HPP
#define __STM32GPIO_HPP

// C includes
#ifdef __cplusplus
extern "C" {
#endif

// add C includes here
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
}
#endif

class STM32Gpio{
    public:
    STM32Gpio(GPIO_TypeDef* port, uint16_t pin) : port(port), pin(pin) {};

    void write(bool isSet);
    bool read();

    private:
    GPIO_TypeDef* port;
    uint16_t pin;
};

#endif