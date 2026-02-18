#include "button.h"
#include "smv_canbus.h"

#define BUTTON_DEBOUNCE_MS 50 /* 50ms debounce */

/*
 * method to initialize button states
 *
 */
void Button_Init(PushButton *btn) {
  btn->last_state = HAL_GPIO_ReadPin(btn->port, btn->pin);

  btn->last_press_time = 0;
}

/*
 * method to detect button pushes and send accordingly over can
 */
void Button_UpdateCAN(PushButton *btn, CANBUS *can) {
  GPIO_PinState state = HAL_GPIO_ReadPin(btn->port, btn->pin);
  uint32_t now = HAL_GetTick();

  if (btn->last_state == GPIO_PIN_SET &&
      state == GPIO_PIN_RESET) /* check if state is changed from initial */
  {
    if (btn->last_press_time == 0 ||
        (now - btn->last_press_time) >=
            BUTTON_DEBOUNCE_MS) /* check for debounce timer */
    {
      btn->last_press_time = now;

      if (btn->counter) {
        (*btn->counter)++; /* increment counter and send over CAN with the
                              message */

        can->send(can, (double)(*btn->counter), btn->msg);
        HAL_Delay(10);
      }
    }
  }
  // on rising edge/release
  else if (btn->last_state == GPIO_PIN_RESET && state == GPIO_PIN_SET) {
    // check if an actual release not debounce based on last press time
    if (now - btn->last_press_time >= BUTTON_DEBOUNCE_MS) {
      btn->last_press_time = now;
    }
  }

  btn->last_state = state; /* if button is "unpressed" set state back */
}
