#include "encoder.hpp"

#define AS5048A_CLEAR_ERROR_FLAG_ADDR               0x0001
#define AS5048A_PROGRAMMING_CONTROL_ADDR            0x0003
#define AS5048A_OTP_REG_ZERO_POS_HIGH_ADDR          0x0016
#define AS5048A_OTP_REG_ZERO_POS_LOW_ADDR           0x0017
#define AS5048A_DIAGNOSTICS_AUTO_GAIN_CONTROL_ADDR  0x3FFD
#define AS5048A_MAGNITUDE_ADDR                      0x3FFE
#define AS5048A_ANGLE_ADDR                          0x3FFF

#define AS5048A_PARITY                              0x8000

#define AS5048A_READ_FLAG                           0x4000
#define AS5048A_WRITE_FLAG                          0x0000

#define AS5048A_CLEAR_ERROR_FLAG_CMD                0b0100000000000001
#define AS5048A_NOP_CMD                             0x0000

#define AS5048A_DATA_MASK                           0b0011111111111111

bool AS5048::initialize(){
    CS_pin.write(true);

    HAL_Delay(10);

    // clear error flag
    CS_pin.write(false);
    uint16_t clear_error_cmd = AS5048A_CLEAR_ERROR_FLAG_CMD;
    HAL_SPI_Receive(this->spix,(uint8_t*)&clear_error_cmd, 2, 1000);
    CS_pin.write(true);

    HAL_Delay(10);

    // test communication
    CS_pin.write(false);
    uint16_t nop_cmd = AS5048A_NOP_CMD;
    auto error_code = HAL_SPI_Receive(this->spix,(uint8_t*)&nop_cmd, 2, 1000);
    CS_pin.write(true);

    if(error_code != HAL_OK || nop_cmd != 0x00){
        return false;
    }

    return true;
}

bool AS5048::initiateEncoderRead(){
    
    // set CS pin to low voltage
    this->CS_pin.write(false);

    //prepare receive command
    this->raw_receive = AS5048A_PARITY | AS5048A_READ_FLAG | AS5048A_ANGLE_ADDR;
    
    HAL_StatusTypeDef status = HAL_ERROR;

    // check if DMA is free
    if (spix->hdmarx->State != HAL_DMA_STATE_READY){
        status = HAL_BUSY;
    }
    
    status = HAL_SPI_Receive_DMA(this->spix, (uint8_t*)&this->raw_receive, 1); //SPI data unit is 2 bytes, so length is 1 

    if (status != HAL_OK) {
        // this->CS_pin.write(true); FIXME: 
    }

    return status == HAL_OK;
}


bool AS5048::encoderReadCompleteCallback(){
    // parity check
    // parity computed according to https://www.geeksforgeeks.org/finding-the-parity-of-a-number-efficiently/

    this->CS_pin.write(true);

    uint16_t parity = raw_receive ^ (raw_receive >> 1);
    parity = parity ^ (parity >> 2);
    parity = parity ^ (parity >> 4);
    parity = parity ^ (parity >> 8);

    if ((parity & 0x01) == 0){
        //correct parity, data valid.
        int16_t raw_angle = raw_receive & AS5048A_DATA_MASK;
        this->absolute_angle = (raw_angle - 8192) * PI / 16384.0f;

        if(this->last_absolute_angle == ABSOLUTE_ANGLE_NOT_INITIALIZED){
            this->accumulated_angle = this->accumulated_angle_turns * PI + this->absolute_angle;
        }else{
            if (absolute_angle - last_absolute_angle > PI){
                this->accumulated_angle_turns--;
            }else if (absolute_angle - last_absolute_angle < -PI){
                this->accumulated_angle_turns++;
            }
            this->accumulated_angle = this->accumulated_angle_turns * PI + this->absolute_angle;
        }
        this->last_absolute_angle = this->absolute_angle;
    }else{
        //incorrect parity, data invalid
        return false;
    }
}