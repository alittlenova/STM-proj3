/**
 ******************************************************************************
 * @file    peripherals/oled/main.c
 * @author  MDS
 * @date    03042021
 * @brief   I2C example with the SSD1306 OLED Display (0.91 inch, 128x32 pixel). 
 * 			A boundary box, text and a moving cursor is shown on the OLED.
 *          The Blue LED will toggle to indicate periodic reading of the 
 *  		REFERENCE: SSD1306 Datasheet
 * 			Uses D15 (I2C_A_SCL) & D14 (I2C_A_SDA)
 *			Uses the following macros:
 * 				 MODIFY_REG( Register, clear mask (bits to clear), set mask (bits to set))
 *               WRITE_REG( Register, value to set)
 *				 READ_REG( (Register)
 *				 SET_BIT (Register, bit mask to set)
 *				 CLEAR_BIT (Register, bit mask to clear)
 ******************************************************************************
 *
 */
#include "main.h"
//int highorlow=1;
//uint8_t buffer1=0x00;
//uint8_t buffer2=0x00;
//uint16_t buffer2_Encode=0x00;
//uint16_t buffer2_Decode=0x00;
/*
 * Main program
 */
int main(void) 
{

	
	
	HAL_Init(); 		// Initialise Board
	
	
	//s4459843_reg_oled_init();// Initialise OLED peripherals
	//ssd1306_Init();
	//Hardware_init();
	s4459843_reg_iss_init();// Initialise system ISS
	s4459843_reg_joystick_init();// Initialise joystick peripherals
	s4459843_tsk_joystick_init();
	s4459843_tsk_timer_init();
	s4459843_tsk_oled_init();
	vTaskStartScheduler();
	
	// Cyclic Executive (CE) loop
	/*
	while (1) {

		s4459843_reg_oled_writetwonumbers(20,21);

		BRD_LEDBlueToggle();	//Toggle blue LED on/off
		HAL_Delay(1000);		//Delay for 1s (1000ms)
	}
	*/
	while(1){
	}
	return 0;
	// Cyclic Executive (CE) loop
}



