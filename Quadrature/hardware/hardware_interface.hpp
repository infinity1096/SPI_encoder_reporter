#ifndef __HARDWARE_INTERFACE_HPP
#define __HARDWARE_INTERFACE_HPP

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


void boardInit();

#endif