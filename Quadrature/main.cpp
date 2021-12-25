#include "board.hpp"

int main(){
    boardInit();
    componentInit();

    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);

    while (1){
        //HAL_Delay(500);
    }
}