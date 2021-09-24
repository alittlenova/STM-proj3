/**
 ******************************************************************************
 * @file    it_handler.c
 * @author  MDS
 * @date    02022021
 * @brief   Must only be used to for interrupt handlers. Only callbacks must be
 *          called in this file. No other code must be present.
 ******************************************************************************
 *
 */

#include "main.h"
//#include "s4459843_reg_keypad.h"
//#include "s4459843_reg_joystick.h"

/*
 * Interrupt handler for EXTI 3 IRQ Handler
 */ 
void EXTI3_IRQHandler(void) {
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != 0x00u)
	{
		s4459843_reg_joystick_iss_isr(GPIO_JOYSTICKZ);
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
	}
}
