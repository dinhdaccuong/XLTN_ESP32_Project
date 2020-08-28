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
buzzer_t buzzer_type_0 = { 2, 1, 1 };
buzzer_t buzzer_type_1 = { 2, 500, 500 };
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
buzzer_type g_buzzer_type;

void IRAM_ATTR onTimerBuzzer()
{
	static uint8_t nTimeBuzzer0 = 0;
	static uint8_t buzzer0_status = 0; // off
	static uint8_t nTimeBuzzer1 = 0;
	static uint8_t buzzer1_status = 0; // off
	switch (g_buzzer_type)
	{
	case BUZZER_TYPE_0:
		if (!buzzer0_status )
		{
			//Serial.println("buzzer ON");
			if (nTimeBuzzer0 < buzzer_type_0.times)
			{
				Serial.println("buzzer ON");
				buzzer0_status = 1;
				digitalWrite(BUZZER_PIN, HIGH);
				nTimeBuzzer0++;		
				timerRestart(timerBuzzer);
				timerAlarmWrite(timerBuzzer, ONE_MILLION, false);
				timerAlarmEnable(timerBuzzer);
			}
			else
			{
				nTimeBuzzer0 = 0;
				buzzer0_status = 0; // off
				timerStop(timerBuzzer);
			}
		}
		else
		{
			Serial.println("buzzer Off");
			buzzer0_status = 0;
			digitalWrite(BUZZER_PIN, LOW);
			timerRestart(timerBuzzer);
			timerAlarmWrite(timerBuzzer, ONE_MILLION, false);
	
			timerAlarmEnable(timerBuzzer);	
		
		}
		break;
	case BUZZER_TYPE_1:
		break;
	}
}
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

void buzzer_init()
{
	pinMode(BUZZER_PIN, OUTPUT);
	digitalWrite(BUZZER_PIN, LOW);	// turn off the buzzer
	timerBuzzer = timerBegin(TIMER_BUZZER, 80, true);
	timerAttachInterrupt(timerBuzzer, &onTimerBuzzer, true);
	//yield();
}

void buzzer_start(buzzer_type buzzer_tp)
{
	g_buzzer_type = buzzer_tp;
	timerAlarmWrite(timerBuzzer, 0, false);
	timerAlarmEnable(timerBuzzer);
}
void buzzer_turnOn()
{

}
void buzzer_turnOff()
{

}
/******************************** End of file *********************************/
