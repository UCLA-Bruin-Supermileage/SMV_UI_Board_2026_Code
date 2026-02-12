# SMV_UI_TestBench

This is the test bench for the UI board.

## Transmitter

The `transmitter` folder is the code for the UI board. It uses a button class to send the appropriate message over. Each button is initialized with mode `PULLUP` and has a counter keeping track of how many times it has been pressed. This number is then sent over can every time it is updated. 

### Setup

To set up the UI Board, download all the files in the `transmitter` folder and add the `.h` to `Inc/` and the `.c` files to `Src/`. To set up the IOC configuration, you must follow the instructions in the CAN Setup megadoc (on Notion). Essentially just set up the clock and enable `CAN1`. The appropriate GPIO pins will already be initialized in `main.c`. You will also need to include the [SMV CANBus library](https://github.com/UCLA-Bruin-Supermileage/SMV_STM32_CANbus) in your project folder.

### Code Explanation

There is an array of buttons where each button has attributes, see `button.h`. Whenever a button is clicked, the GPIO pin state is flipped and a counter is incremented. This counter is sent over CAN with the correct message corresponding to what is being sent. This message is important for the recieving boards to know what data is being sent.

## Reciever

The `reciever` folder is the code that handles all the receiving of the CAN messages. For the sake of the test bench, all the messages are assumed to be sent to the same board, however in actual use, the messages will all propogate to their boards. Essentially the messages are read in depending on the message type in the CAN frame and then stored in an array. This part is wholly untested though so it may not function correctly. Also, the supercap and emergency stop data is being sent under the `DAQ_Button` and `Motor` message ids since these two haven't been added to the CAN library.

## Setup
Similar to the `transmitter` set up, the CANBus library files should be added and the same configuration for the MCU must be selected.
