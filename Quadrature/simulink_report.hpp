#ifndef SIMULINK_REPORT_HPP
#define SIMULINK_REPORT_HPP

// C includes
#ifdef __cplusplus
extern "C" {
#endif

#include "arm_math.h"


#ifdef __cplusplus
}
#endif

template<typename T, size_t buf_length>
class SimulinkReport{
    public:
    void append(const T& packet){
        if (current_write_idx >= buf_length){
            transmit();
        }
    
        auto writeAddress = buffer + sizeof(float)  + (current_write_idx) * sizeof(T);
        memcpy(writeAddress, &packet, sizeof(T));
        current_write_idx++;
    }

    bool transmit(){
        // prepare package header and end for simulink to recognize 
        memcpy(buffer, "SSSS", 4);
        memcpy(buffer + sizeof(float) + (buf_length) * sizeof(T), "EEEE", 4);
        
        CDC_Transmit_FS(buffer, 2 * sizeof(float) + buf_length * sizeof(T));
        current_write_idx = 0;

        return true;
    }

    bool isFull(){
        return current_write_idx >= buf_length;
    }

    uint8_t buffer[2 * sizeof(float) + buf_length * sizeof(T)];
    private:
    size_t current_write_idx = 0;
};



#endif