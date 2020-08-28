/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config.h"
#include "motor_control.h"
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

/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
void motor_init()
{
	pinMode(MOTOR_ENABLE_PIN, OUTPUT);
	pinMode(MOTOR_CONTROL1_PIN, OUTPUT);
	pinMode(MOTOR_CONTROL2_PIN, OUTPUT);
	ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
	ledcAttachPin(PWM_PIN, PWM_CHANNEL);
}
void motor_turnLeft(uint8_t speed)
{
	digitalWrite(MOTOR_CONTROL1_PIN, HIGH);
	digitalWrite(MOTOR_CONTROL2_PIN, LOW);
	ledcWrite(PWM_CHANNEL, speed);
}
void motor_turnRight(uint8_t speed)
{
	digitalWrite(MOTOR_CONTROL1_PIN, LOW);
	digitalWrite(MOTOR_CONTROL2_PIN, HIGH);
	ledcWrite(PWM_CHANNEL, speed);
}
void motor_stop()
{
	ledcDetachPin(PWM_PIN);
}

/******************************** End of file *********************************/
