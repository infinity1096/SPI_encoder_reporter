#ifndef __BOARD_HPP
#define __BOARD_HPP

// C includes
#ifdef __cplusplus
extern "C" {
#endif

// add C includes here
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

#ifdef __cplusplus
}
#endif

// C++ includes
#include "encoder.hpp"

void boardInit();

//components
extern AS5048 enc_0;

void componentInit();

// function need to be called by timers

// 1kHz
extern "C" void updateEncoder();


#endif