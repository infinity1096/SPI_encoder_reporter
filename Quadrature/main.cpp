#include "FOC_math.hpp"

#include "board.hpp"
#define POLE_PAIR 11

double th = 0;
unsigned long loop_idx = 0;
double omega = 11.0 * 1.0;

uint32_t tick = 0;

int16_t data[3];

Simulink_ADC_Packet_t adcPacket;
Simulink_IDQ0_Packet_t dq0Packet;
SimulinkReport<Simulink_IDQ0_Packet_t, 200> dq0_info_reporter;

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    __NOP();
}

extern "C" void reportADC(void){

    dq0Packet.angle = -(enc_0.getAccumulatedAngle() - 0.178712);
    
    float32_t currentFloat[3], Iab0[3];
    currentFloat[0] = data[0];
    currentFloat[1] = data[1];
    currentFloat[2] = data[2];

    forwardClarke(currentFloat, Iab0);
    forwardPark(Iab0, POLE_PAIR * dq0Packet.angle, dq0Packet.Idq0_sense);

    vel_obs.update(dq0Packet.angle);
    dq0Packet.velocity_est = vel_obs.getVelocity();

    dq0_info_reporter.append(dq0Packet);
}

int main(){
    boardInit();
    componentInit();

    HAL_TIM_Base_Start_IT(&htim2);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) data, 3);

    modulator0.modulate(0.0,0.0,0.0);
    modulator0.hardwareEnable();
    while (1){
        float32_t Vdq0[3] = {0.0,0.0,0.0};
        float32_t Vab0[3] = {0.0,0.0,0.0};
        float32_t Vabc[3] = {0.0,0.0,0.0};

        float thetaElectric = -POLE_PAIR * (enc_0.getAccumulatedAngle() - 0.178712);

        inversePark(Vdq0, thetaElectric, Vab0);
        inverseClarke(Vab0, Vabc);

        modulator0.modulate(Vab0);

        HAL_Delay(1);
        loop_idx++;

        double t = (double)loop_idx / 1000.0;
        
    }
}