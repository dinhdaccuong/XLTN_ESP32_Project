#ifndef __MOTOR_CONTROL_H__
#define __MOTOR_CONTROL_H__

#ifdef __cplusplus
extern "C"
{
#endif

	/*******************************************************************************
	**                               INCLUDES
	*******************************************************************************/
#include "config.h"
#include "stdint.h"
	/*******************************************************************************
	**                                DEFINES
	*******************************************************************************/
	// clang-format off
#define PWM_FREQUENCY		1000
#define PWM_CHANNEL			0
#define PWM_RESOLUTION		8
#define PWM_PIN				MOTOR_ENABLE_PIN
#define DUTY_CYCLE			255
#define MOTOR_TIME_WAIT		1500	// 1000 ms
#define MOTOR_SPEED			200

	enum motor_status
	{
		MOTOR_TURN_LEFT,
		MOTOR_TURN_RIGHT,
		MOTOR_STOP
	};

	typedef motor_status motor_status_e;

	// clang-format on
	/*******************************************************************************
	**                     EXTERNAL VARIABLE DECLARATIONS
	*******************************************************************************/

	/*******************************************************************************
	**                     EXTERNAL FUNCTION DECLARATIONS
	*******************************************************************************/
	void motor_init();
	void motor_turnLeft(uint8_t speed);
	void motor_turnRight(uint8_t speed);
	void motor_stop();
	void motor_control(ReceiveCommand command);
#ifdef __cplusplus
}
#endif

#endif /* __VOVAN_H__ */

/******************************** End of file *********************************/
