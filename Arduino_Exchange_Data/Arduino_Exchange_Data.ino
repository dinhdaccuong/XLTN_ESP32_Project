#include "config.h"
#include "motor_control.h"
#include "led_control.h"
#include "buzzer_control.h"
#include "lcd_control.h"
#include "my_ble.h"
#include "sound.h"

void setup() {
    buzzer_init();      // khởi tạo chương trình cho còi
    buzzer_start(&sound_init);  // bật còi
    my_ble_init();      // Khởi tạo BLE - Bluetooth Low Energy
    lcd_init();             // Khởi tạo LCD
    motor_init();           // Khởi tạo motor
    led_init();         // Khở tạo led
}

void loop() {

}




