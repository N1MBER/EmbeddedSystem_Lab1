#include "hal.h"

int umain() {
    int i = 0;
    int delay = 500;
    int leds_num[] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5,
                      GPIO_PIN_6, GPIO_PIN_8, GPIO_PIN_9,
                      GPIO_PIN_11, GPIO_PIN_12};
while (1) {
    GPIO_PinState state = GPIO_PIN_SET;
    while (state == GPIO_PIN_SET) {
        state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15); // read nBTN
    }
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_SET);
        HAL_Delay(delay);
        HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_RESET);
        HAL_Delay(delay);
    }

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
}
    return 0;
}