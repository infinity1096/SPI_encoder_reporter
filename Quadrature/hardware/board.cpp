#include "board.hpp"

// STM32 hardware init
extern "C" void SystemClock_Config(void);

void boardInit(){
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init(); // DMA should be initialized before SPI using DMA !!

  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_CAN1_Init();
  MX_I2C1_Init();
 

  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();

  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM4_Init();
}

//components
AS5048 enc_0{
  &hspi1,               // SPI handle
  {GPIOA,GPIO_PIN_15}   // CS pin
};


void componentInit(){
  enc_0.initialize();
};

extern "C" void updateEncoder(){
    enc_0.initiateEncoderRead();
}

size_t frame_size = 10;
size_t frame_idx = 0;
float32_t float_frame_buffer[10];

float32_t float_buffer[11];
size_t counter = 0;

float32_t t = 0;
size_t idx = 0;

extern "C" void reportAbsoluteAngle(){
  idx++;

  size_t transmit_size = 0;

  //if (enc_0.is_data_valid()){
    float_frame_buffer[frame_idx++] = enc_0.getAccumulatedAngle();
  //}
  
  if (frame_idx == frame_size){
    frame_idx = 0;

    //send one frame
    if(counter == 0){
      float_buffer[0] = *(float32_t*)"SSSS";
      memcpy(float_buffer+1, float_frame_buffer, frame_size * sizeof(float32_t));
      counter ++;
      CDC_Transmit_FS((uint8_t*)float_buffer, (1 + frame_size) * sizeof(float32_t));
    } else if(counter == 99){
      memcpy(float_buffer, float_frame_buffer, frame_size * sizeof(float32_t));
      float_buffer[frame_size] = *(float32_t*)"EEEE";
      counter = 0;
      CDC_Transmit_FS((uint8_t*)float_buffer, (1 + frame_size) * sizeof(float32_t));
    }else{
      memcpy(float_buffer, float_frame_buffer, frame_size * sizeof(float32_t));
      CDC_Transmit_FS((uint8_t*)float_buffer, frame_size * sizeof(float32_t));
      counter++;
    }
  }
}


// called when SPI_Receive_DMA is called
extern "C" void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
  HAL_SPI_TxRxCpltCallback(hspi);
}

// called when SPI_TransmitReceive_DMA is called
extern "C" void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
  if (hspi == &hspi1){
    enc_0.encoderReadCompleteCallback();
  }
}

