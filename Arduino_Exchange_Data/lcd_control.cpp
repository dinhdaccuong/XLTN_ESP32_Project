/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "lcd_control.h"
#include "config.h"
#include "LiquidCrystal.h"
#include "string_define.h"
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
void lcd_init()		// Khởi tạo LCD
{
	lcd.begin(16, 2);
	lcd.clear();
	lcd_write_string(STRING_STATUS);
	lcd.setCursor(X_LINE_STATUS, Y_LINE_STATUS);
	lcd_write_string(STRING_DISCONNECTED);

	lcd.setCursor(0, 1);
	lcd_write_string(STRING_COMMAND);
	lcd.setCursor(X_LINE_COMMAND, Y_LINE_COMMAND);
	lcd_write_string(STRING_NONE);
}

void lcd_clean()		// Xóa màn hình
{
	lcd.clear();
}
void lcd_write_char(char c)	// Ghi ký tự ra màn hình
{
	lcd.print(c);
}
void lcd_write_string(char* pc)	// Ghi chuỗi ra màn hình
{
	lcd.print(pc);
}
void lcd_set_cursor(uint8_t x, uint8_t y)		// Thiết lập vị trí con trỏ
{
	if (y > 1)
		return;
	if (x > 15)
		return;
	lcd.setCursor(x, y);
}

/******************************** End of file *********************************/
