#include "stm32gpio.hpp"

void STM32Gpio::write(bool isSet){
    HAL_GPIO_WritePin(this->port, this->pin, static_cast<GPIO_PinState>(isSet));
}
