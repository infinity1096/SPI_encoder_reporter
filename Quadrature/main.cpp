#include "FOC_math.hpp"

#include "board.hpp"



double th = 0;
double omega = 11.0 * 1.0;

uint32_t tick = 0;

int main(){
    boardInit();
    componentInit();
    
    HAL_Delay(100);

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
        th += 0.24;
    }
}