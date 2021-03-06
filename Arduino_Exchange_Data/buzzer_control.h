#ifndef __BUZZER_CONTROL_H__
#define __BUZZER_CONTROL_H__

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
typedef struct
{
	uint8_t times;
	uint16_t duration;
	uint8_t interval;
} buzzer_t;

typedef buzzer_t* buzzer_p;

	// clang-format on
	/*******************************************************************************
	**                     EXTERNAL VARIABLE DECLARATIONS
	*******************************************************************************/

	/*******************************************************************************
	**                     EXTERNAL FUNCTION DECLARATIONS
	*******************************************************************************/
	void buzzer_init();
	void buzzer_start(buzzer_p p_buzzer);
	void buzzer_turnOn();
	void buzzer_turnOff();
#ifdef __cplusplus
}
#endif

#endif /* __VOVAN_H__ */

/******************************** End of file *********************************/
