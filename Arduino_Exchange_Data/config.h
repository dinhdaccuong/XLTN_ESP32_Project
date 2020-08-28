#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

	/*******************************************************************************
	**                               INCLUDES
	*******************************************************************************/

	/*******************************************************************************
	**                                DEFINES
	*******************************************************************************/
	// clang-format off
	enum ResponseCommand
	{
		RES_TURNED_ON_LED,
		RES_TURNED_OFF_LED,
		RES_GO_MOTOR,
		RES_LEFT_MOTOR,
		RES_RIGHT_MOTOR,
		RES_STOP_MOTOR
	};

	enum ReceiveCommand
	{
		COMMAND_TURN_ON_LED,
		COMMAND_TURN_OFF_LED,
		COMMAND_GO_MOTOR,
		COMMAND_LEFT_MOTOR,
		COMMAND_RIGHT_MOTOR,
		COMMAND_STOP_MOTOR
	};

#define ONE_MILLION				1000000
#define SERVICE_UUID			"4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID		"beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define DESCRIPTOR_UUID			"1485cb0c-db0d-11ea-87d0-0242ac130003"

#define MOTOR_ENABLE_PIN		14
#define MOTOR_CONTROL1_PIN		16
#define MOTOR_CONTROL2_PIN		17

#define LED_PIN					13
#define BUZZER_PIN				12

#define LCD_RS					5
#define LCD_EN					18
#define LCD_D4					23
#define LCD_D5					19
#define LCD_D6					21
#define LCD_D7					22

#define TIMER_BUZZER			0
	// clang-format on
	/*******************************************************************************
	**                     EXTERNAL VARIABLE DECLARATIONS
	*******************************************************************************/

	/*******************************************************************************
	**                     EXTERNAL FUNCTION DECLARATIONS
	*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __VOVAN_H__ */

/******************************** End of file *********************************/
