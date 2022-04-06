#ifndef __BOARD_HPP
#define __BOARD_HPP

// C includes
#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f405xx.h"
// add C includes here
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "i2c.h"
#include "adc.h"
#include "freertos.h"
#include "can.h"
#include "usb_device.h"
#include "gpio.h"

#include "arm_math.h"

#include "usbd_cdc_if.h"

#ifdef __cplusplus
}
#endif

// C++ includes
#include "encoder.hpp"
#include "modulator.hpp"

#include "simulink_report.hpp"


void boardInit();

//components
extern AS5048 enc_0;

extern DRV8301 modulator0;
extern DRV8301 modulator1;

typedef struct{
    float32_t enc_pos_0;
} Simulink_Packet_t;

typedef struct{
    float32_t Iabc_sense[3];
    float32_t angle;
} Simulink_ADC_Packet_t;

typedef struct{
    float32_t Idq0_sense[3];
    float32_t angle;
} Simulink_IDQ0_Packet_t;

void componentInit();

// function need to be called by timers

// 1kHz
extern "C" void updateEncoder();
extern "C" void reportAbsoluteAngle();

#endif