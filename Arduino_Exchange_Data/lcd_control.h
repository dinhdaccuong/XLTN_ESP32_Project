#ifndef __VOVAN_H__
#define __VOVAN_H__

#ifdef __cplusplus
extern "C"
{
#endif

	/*******************************************************************************
	**                               INCLUDES
	*******************************************************************************/
#include "stdint.h"
	/*******************************************************************************
	**                                DEFINES
	*******************************************************************************/
	// clang-format off

	// clang-format on
	/*******************************************************************************
	**                     EXTERNAL VARIABLE DECLARATIONS
	*******************************************************************************/
	
	/*******************************************************************************
	**                     EXTERNAL FUNCTION DECLARATIONS
	*******************************************************************************/
	void lcd_init();
	void lcd_clean();
	void lcd_write_char(char c);
	void lcd_write_string(char* pc);
	void lcd_set_cursor(uint8_t x, uint8_t y);
#ifdef __cplusplus
}
#endif

#endif /* __VOVAN_H__ */

/******************************** End of file *********************************/
