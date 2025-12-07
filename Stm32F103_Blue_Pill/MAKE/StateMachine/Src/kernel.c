#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/* ----------------- Hardware Simulation ----------------- */
bool buttonA(void);
bool buttonB(void);
bool buttonC(void);
bool timerExpired(void);
void startTimer(uint32_t ms);

void clearDisplay(void);
void print(const char *msg);

/* ----------------- State Machine ----------------- */
typedef enum {
    STATE_PRINT_MENU,
    STATE_WAIT_BUTTON,
    STATE_CLEAR_AND_HELLO,
    STATE_START_TIMER,
    STATE_WAIT_TIMER,
} State;

/* Forward declarations */
State state_print_menu(void);
State state_wait_button(void);
State state_clear_and_hello(void);
State state_start_timer(void);
State state_wait_timer(void);

/* Lookup table */
State (*state_table[])(void) = {
    state_print_menu,
    state_wait_button,
    state_clear_and_hello,
    state_start_timer,
    state_wait_timer
};

/* ----------------- STATE IMPLEMENTATIONS ----------------- */

/* State 1: Print watering system */
State state_print_menu(void)
{
    print("Watering system");
    return STATE_WAIT_BUTTON;   // flowchart arrow down
}

/* Decision: Button A or B or C pressed? */
State state_wait_button(void)
{
    if (buttonA() || buttonB() || buttonC())
        return STATE_CLEAR_AND_HELLO;

    return STATE_PRINT_MENU;  // loop back according to the flowchart
}

/* Clear display & print hello */
State state_clear_and_hello(void)
{
    clearDisplay();
    print("Hello!");
    return STATE_START_TIMER;
}

/* Start wait timer */
State state_start_timer(void)
{
    startTimer(2000);   // example 2 seconds
    return STATE_WAIT_TIMER;
}

/* Decision: Timer times out? */
State state_wait_timer(void)
{
    if (timerExpired())
        return STATE_PRINT_MENU;

    return STATE_WAIT_TIMER;
}

/* ----------------- Main Loop ----------------- */

int main(void)
{
    State current = STATE_PRINT_MENU;

    while (1)
        current = state_table[current]();

    return 0;
}
