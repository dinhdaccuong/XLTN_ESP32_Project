/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "lcd_control.h"
#include "config.h"
#include "LiquidCrystal.h"

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
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
void lcd_init()
{
	lcd.begin(16, 2);
	lcd.clear();
}
void lcd_write_char(char c)
{
	lcd.print(c);
}
void lcd_write_string(char* pc)
{
	lcd.print(pc);
}
void lcd_set_cursor(uint8_t x, uint8_t y)
{
	if (y > 1)
		return;
	if (x > 15)
		return;
	lcd.setCursor(x, y);
}

/******************************** End of file *********************************/
