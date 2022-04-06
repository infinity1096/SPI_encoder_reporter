#include "FOC_math.hpp"

#include "board.hpp"



double th = 0;
unsigned long loop_idx = 0;
double omega = 11.0 * 1.0;

uint32_t tick = 0;

int16_t data[3];

Simulink_ADC_Packet_t adcPacket;
SimulinkReport<Simulink_ADC_Packet_t, 1000> adc_info_reporter;

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    __NOP();
}

extern "C" void reportADC(void){
    adcPacket.Iabc_sense[0] = data[0];
    adcPacket.Iabc_sense[1] = data[1];
    adcPacket.Iabc_sense[2] = data[2];
    adcPacket.angle = enc_0.getAccumulatedAngle();
    adc_info_reporter.append(adcPacket);
}

int main(){
    boardInit();
    componentInit();
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) data, 3);

    modulator0.modulate(0.0,0.0,0.0);
    modulator0.hardwareEnable();
    while (1){
        float32_t Vdq0[3] = {0.5,0.0,0.0};
        float32_t Vab0[3] = {0.0,0.0,0.0};
        float32_t Vabc[3] = {0.0,0.0,0.0};

        inversePark(Vdq0, th, Vab0);
        inverseClarke(Vab0, Vabc);

        modulator0.modulate(Vab0);
        //modulator0.modulate(Vabc[0], Vabc[1], Vabc[2]);

        HAL_Delay(1);
        loop_idx++;

        double t = (double)loop_idx / 1000.0;

        th += 0.20 * sin(t);
    }
}