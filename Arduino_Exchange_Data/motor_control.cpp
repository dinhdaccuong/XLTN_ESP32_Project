/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config.h"
#include "motor_control.h"
#include "Arduino.h"
#include "buzzer_control.h"
#include "sound.h"
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
motor_status_e motor_status_t = MOTOR_STOP;

hw_timer_t* timerMotor = NULL;
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
void motorTimerStart(uint16_t time);
void motorTimerStop();
void motorTimerInit();
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
void IRAM_ATTR onTimerMotor()
{
	switch (motor_status_t)
	{
	case MOTOR_TURN_LEFT:
		motor_turnLeft(MOTOR_SPEED);
		break;
	case MOTOR_TURN_RIGHT:
		motor_turnRight(MOTOR_SPEED);
		break;
	case MOTOR_STOP:
		motor_stop();
		break;
	default:
		break;
	}
}
void motor_init()			// Khởi tạo motor
{
	pinMode(MOTOR_ENABLE_PIN, OUTPUT);
	pinMode(MOTOR_CONTROL1_PIN, OUTPUT);
	pinMode(MOTOR_CONTROL2_PIN, OUTPUT);
	ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
	ledcAttachPin(PWM_PIN, PWM_CHANNEL);
	motorTimerInit();
}

void motor_control(ReceiveCommand command)
{
	switch (command)
	{
	case COMMAND_GO_MOTOR:
	case COMMAND_LEFT_MOTOR:
		if (motor_status_t == MOTOR_TURN_RIGHT)
		{
			motor_status_t = MOTOR_TURN_LEFT;
			motor_stop();
			motorTimerStart(MOTOR_TIME_WAIT);
			buzzer_start(&sound_command);
		}
		else if (motor_status_t == MOTOR_STOP)
		{
			motor_status_t = MOTOR_TURN_LEFT;
			motor_turnLeft(MOTOR_SPEED);
			buzzer_start(&sound_command);
		}
		break;
	case COMMAND_RIGHT_MOTOR:
		if (motor_status_t == MOTOR_TURN_LEFT)
		{
			motor_status_t = MOTOR_TURN_RIGHT;
			motor_stop();
			motorTimerStart(MOTOR_TIME_WAIT);
			buzzer_start(&sound_command);
		}
		else if (motor_status_t == MOTOR_STOP)
		{
			motor_status_t = MOTOR_TURN_RIGHT;
			motor_turnRight(MOTOR_SPEED);
			buzzer_start(&sound_command);
		}
		break;
	case COMMAND_STOP_MOTOR:
		if (motor_status_t != MOTOR_STOP)
		{
			motor_status_t = MOTOR_STOP;
			motor_stop();
			buzzer_start(&sound_command);
		}
		break;
	default:
		break;
	}
}
void motor_turnLeft(uint8_t speed)  // Quay trái motor
{
	digitalWrite(MOTOR_CONTROL1_PIN, LOW);
	digitalWrite(MOTOR_CONTROL2_PIN, HIGH);
	ledcWrite(PWM_CHANNEL, MOTOR_SPEED);
}
void motor_turnRight(uint8_t speed)	// Quay phải motor
{
	digitalWrite(MOTOR_CONTROL1_PIN, HIGH);
	digitalWrite(MOTOR_CONTROL2_PIN, LOW);
	ledcWrite(PWM_CHANNEL, MOTOR_SPEED);
}
void motor_stop()		// stop motor
{
	digitalWrite(MOTOR_CONTROL1_PIN, LOW);
	digitalWrite(MOTOR_CONTROL2_PIN, LOW);
	ledcWrite(PWM_CHANNEL, 0);
}

void motorTimerStart(uint16_t time)	
{
	timerRestart(timerMotor);
	timerAlarmWrite(timerMotor, time * ONE_THOUSAND, false);
	timerAlarmEnable(timerMotor);
}

void motorTimerStop()
{
	timerStop(timerMotor);
}

void motorTimerInit()
{
	timerMotor = timerBegin(TIMER_MOTOR, 80, true);
	timerAttachInterrupt(timerMotor, &onTimerMotor, true);
}

/******************************** End of file *********************************/
