#include "board.hpp"

double th = 0;
double omega = 11.0 * 1.0;

uint32_t tick = 0;

int main(){
    boardInit();
    componentInit();
    
    HAL_Delay(100);

    modulator1.modulate(0.0,0.0,0.0);
    modulator1.hardwareEnable();
    while (1){
        modulator1.modulate(2.0 * cos(th),2.0 * cos(th + 2.0 * PI / 3.0),2.0 * cos(th - 2.0 * PI / 3.0));
        HAL_Delay(1);
    }
}