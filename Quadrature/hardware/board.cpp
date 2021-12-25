#include "board.hpp"

// STM32 hardware init
extern "C" void SystemClock_Config(void);

void boardInit(){
  HAL_Init();
  SystemClock_Config();
  MX_DMA_Init();  // DMA should be initialized before SPI using DMA !!
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();
  MX_SPI1_Init();
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

