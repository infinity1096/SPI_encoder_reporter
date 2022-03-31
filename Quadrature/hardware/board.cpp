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

  MX_USB_DEVICE_Init();
}

//components
AS5048 enc_0{
  &hspi1,               // SPI handle
  {GPIOA,GPIO_PIN_15}   // CS pin
};

DRV8301 modulator0{
  &htim1,
  {GPIOC, GPIO_PIN_9},
  {GPIOC, GPIO_PIN_5},
  {GPIOC, GPIO_PIN_15}
};

DRV8301 modulator1{
  &htim8,
  {GPIOB, GPIO_PIN_12},
  {GPIOB, GPIO_PIN_2},
  {GPIOB, GPIO_PIN_11}
};

void componentInit(){
  enc_0.initialize();
  modulator0.initialize();
  modulator1.initialize();

  // start timer
  HAL_TIM_Base_Start_IT(&htim4);
};

extern "C" void updateEncoder(){
    enc_0.initiateEncoderRead();
}

SimulinkReport<Simulink_Packet_t, 100> reporter;
Simulink_Packet_t packet;

extern "C" void reportAbsoluteAngle(){
  packet.enc_pos_0 = enc_0.getAbsoluteAngle();
  reporter.append(packet);
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

