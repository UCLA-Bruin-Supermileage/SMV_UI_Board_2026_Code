#ifndef BUTTON_H
#define BUTTON_H

#include "smv_board_enums.h"
#include "stm32f4xx_hal.h"
#include "smv_canbus.h"

/* struct to hold all the data per button */
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;

    uint8_t       last_state;
    uint32_t      last_press_time; /* used for debounce timer */

    uint32_t     *counter; /* counter to track button presses (send over CAN) */

    enum UIMessage msg; /* can message header */
} PushButton;

/**
 * @brief Initialize button state (must be called once after GPIO init)
 */
void Button_Init(PushButton *btn);

/**
 * @brief Update button debounce state (call periodically)
 */
void Button_UpdateCAN(PushButton *btn, CANBUS *can);

#endif
