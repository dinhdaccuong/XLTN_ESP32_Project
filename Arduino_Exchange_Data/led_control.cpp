/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config.h"
#include "Arduino.h"
#include "led_control.h"
#include "sound.h"
#include "buzzer_control.h"
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
led_status_e led_s = LED_OFF;
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
void led_init()
{
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);	// turn off the led
}

void led_control(ReceiveCommand command)
{
	switch (command)
	{
	case COMMAND_TURN_ON_LED:
		if (led_s == LED_OFF)
		{
			led_s = LED_ON;
			led_turnOn();
			buzzer_start(&sound_command);
		}
		break;
	case COMMAND_TURN_OFF_LED:
		if (led_s == LED_ON)
		{
			led_s = LED_OFF;
			led_turnOff();
			buzzer_start(&sound_command);
		}
		break;
	default:
		break;
	}
}


void led_turnOn()
{
	digitalWrite(LED_PIN, LOW);
}
void led_turnOff()
{
	digitalWrite(LED_PIN, HIGH);
}

/******************************** End of file *********************************/
