#include "button.h"
#include "smv_canbus.h"

#define BUTTON_DEBOUNCE_MS  50

void Button_Init(PushButton *btn)
{
    btn->last_state =
        HAL_GPIO_ReadPin(btn->port, btn->pin);

    btn->last_press_time = 0;
}

void Button_UpdateCAN(PushButton *btn, CANBUS *can)
{
    GPIO_PinState state = HAL_GPIO_ReadPin(btn->port, btn->pin);

    if (btn->last_state == GPIO_PIN_SET && state == GPIO_PIN_RESET)
    {
        uint32_t now = HAL_GetTick();

        if (btn->last_press_time == 0 || (now - btn->last_press_time) >= BUTTON_DEBOUNCE_MS)
        {
            btn->last_press_time = now;

            if (btn->counter) {
                (*btn->counter)++;

                can->send(can, (double)(*btn->counter), btn->msg);
                HAL_Delay(10);
            }
        }
    }

    btn->last_state = state;
}
