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
	uint8_t duration;
	uint8_t interval;
} buzzer_t;

typedef buzzer_t* buzzer_p;

enum buzzer_type
{
	BUZZER_TYPE_0,
	BUZZER_TYPE_1
};
	// clang-format on
	/*******************************************************************************
	**                     EXTERNAL VARIABLE DECLARATIONS
	*******************************************************************************/

	/*******************************************************************************
	**                     EXTERNAL FUNCTION DECLARATIONS
	*******************************************************************************/
	void buzzer_init();
	void buzzer_start(buzzer_type buzzer_tp);
	void buzzer_turnOn();
	void buzzer_turnOff();
#ifdef __cplusplus
}
#endif

#endif /* __VOVAN_H__ */

/******************************** End of file *********************************/
