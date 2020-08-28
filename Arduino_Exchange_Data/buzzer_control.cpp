/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config.h"
#include "buzzer_control.h"
#include "Arduino.h"
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
hw_timer_t* timerBuzzer = NULL;
buzzer_t* g_buzzer = NULL;		// global buzzer
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

void IRAM_ATTR onTimerBuzzer()
{

	static uint8_t buzzer_status = 0; // off
	static uint8_t buzzer_nSound = 0;	// number of sound

	if (!buzzer_status)
	{
		if (buzzer_nSound < g_buzzer->times)
		{
			buzzer_status = 1;
			buzzer_turnOn();
			buzzer_nSound++;
			timerRestart(timerBuzzer);
			timerAlarmWrite(timerBuzzer, g_buzzer->duration * ONE_THOUSAND, false);
			timerAlarmEnable(timerBuzzer);
		}
		else
		{
			buzzer_nSound = 0;
			buzzer_status = 0; // off
			timerStop(timerBuzzer);
		}
	}
	else
	{
		buzzer_status = 0;
		buzzer_turnOff();
		timerRestart(timerBuzzer);
		timerAlarmWrite(timerBuzzer, g_buzzer->interval * ONE_THOUSAND, false);
		timerAlarmEnable(timerBuzzer);
	}
}
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

void buzzer_init()
{
	pinMode(BUZZER_PIN, OUTPUT);
	buzzer_turnOff();
	timerBuzzer = timerBegin(TIMER_BUZZER, 80, true);
	timerAttachInterrupt(timerBuzzer, &onTimerBuzzer, true);
}

void buzzer_start(buzzer_p p_buzzer)
{
	g_buzzer = p_buzzer;
	timerAlarmWrite(timerBuzzer, 0, false);
	timerAlarmEnable(timerBuzzer);
}
void buzzer_turnOn()
{
	digitalWrite(BUZZER_PIN, HIGH);	// turn off the buzzer
}
void buzzer_turnOff()
{
	digitalWrite(BUZZER_PIN, LOW);	// turn off the buzzer
}
/******************************** End of file *********************************/
