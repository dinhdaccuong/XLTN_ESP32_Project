#include "config.h"
#include "motor_control.h"
#include "led_control.h"
#include "buzzer_control.h"
#include "lcd_control.h"
#include "my_ble.h"
#include "sound.h"

void setup() {
    buzzer_init();
    buzzer_start(&sound_init);
    my_ble_init();
    lcd_init();   
    motor_init();
    led_init();
}

void loop() {
}




