#include "hal.h"

int umain() {
    unsigned int leds_num[] ={GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5,GPIO_PIN_6, GPIO_PIN_8, GPIO_PIN_9,GPIO_PIN_11, GPIO_PIN_12};
    unsigned int sw_num[] = {GPIO_PIN_4, GPIO_PIN_8, GPIO_PIN_10, GPIO_PIN_12};
    int first_count = 7;
    int second_count = 6;
    bool stop = 0;
    bool direction = 1; // right side
    int delay = 500;
    while (1){
        GPIO_PinState state1 = HAL_GPIO_ReadPin(GPIOE, sw_num[0]);
        GPIO_PinState state2 = HAL_GPIO_ReadPin(GPIOE, sw_num[1]);
        GPIO_PinState state3 = HAL_GPIO_ReadPin(GPIOE, sw_num[2]);
        GPIO_PinState state4 = HAL_GPIO_ReadPin(GPIOE, sw_num[3]);
        if ((state4 == GPIO_PIN_SET && state3 == GPIO_PIN_SET) && (state2 != GPIO_PIN_SET && state1 != GPIO_PIN_SET)){
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) != GPIO_PIN_SET){
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
                stop = !stop;
            }
            HAL_Delay(delay);
            if (!stop){
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, leds_num[first_count], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds_num[second_count], GPIO_PIN_RESET);
                if(direction){
                    if(first_count != 7){
                        first_count++;
                        second_count++;
                    } else{
                        direction = !direction;
                        first_count--;
                        second_count--;
                    }
                } else{
                    if(second_count != 0){
                        first_count--;
                        second_count--;
                    } else{
                        direction = !direction;
                        first_count++;
                        second_count++;
                    }
                }
                HAL_GPIO_WritePin(GPIOD, leds_num[2], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds_num[3], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds_num[first_count], GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, leds_num[second_count], GPIO_PIN_SET);
            }
        } else{
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, leds_num[first_count], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, leds_num[second_count], GPIO_PIN_RESET);
            first_count = 7;
            second_count = 6;
            for (int i = 0; i < 4 ; ++i) {
                GPIO_PinState state = HAL_GPIO_ReadPin(GPIOE, sw_num[i]);
                HAL_GPIO_WritePin(GPIOD, leds_num[i], state);
            }
        }
    }
    return 0;
}