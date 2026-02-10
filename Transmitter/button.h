#ifndef BUTTON_H
#define BUTTON_H

#include "smv_board_enums.h"
#include "stm32f4xx_hal.h"


typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;

    uint8_t       last_state;
    uint32_t      last_press_time;

    uint32_t     *counter;

    enum UIMessage msg;
} PushButton;

/**
 * @brief Initialize button state (must be called once after GPIO init)
 */
void Button_Init(PushButton *btn);

/**
 * @brief Update button debounce state (call periodically)
 */
void Button_Update(PushButton *btn);

#endif
