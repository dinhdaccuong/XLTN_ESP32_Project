#ifndef __LED_CONTROL_H__
#define __LED_CONTROL_H__

#ifdef __cplusplus
extern "C"
{
#endif

	/*******************************************************************************
	**                               INCLUDES
	*******************************************************************************/
#include "config.h"
#include "sound.h"
	/*******************************************************************************
	**                                DEFINES
	*******************************************************************************/
	// clang-format off
	enum led_status
	{
		LED_ON,
		LED_OFF
	};
	typedef led_status led_status_e;
	// clang-format on
	/*******************************************************************************
	**                     EXTERNAL VARIABLE DECLARATIONS
	*******************************************************************************/

	/*******************************************************************************
	**                     EXTERNAL FUNCTION DECLARATIONS
	*******************************************************************************/
	void led_init();
	void led_control(ReceiveCommand command);
	void led_turnOn();
	void led_turnOff();
#ifdef __cplusplus
}
#endif

#endif /* __VOVAN_H__ */

/******************************** End of file *********************************/
