#include "s4459843_tsk_joystick.h"
xTaskHandle joystickTaskHandle;
void s4459843_tsk_joystick_init(void)
{
	xTaskCreate( (void *) &s4459843_tsk_joystick_ctrl, (const signed char *) "JOYSTICK", OLEDTASK_STACK_SIZE, NULL, OLEDTASK_PRIORITY+2, joystickTaskHandle );
}
void s4459843_tsk_joystick_ctrl(void)
{
	for(;;)
	{
		if(s4459843_reg_iss_eventcounter_read(JOYSTICK_Z_CHANNEL)>0)
		{
			s4459843_reg_iss_eventcounter_reset(JOYSTICK_Z_CHANNEL);
			BRD_LEDGreenToggle();
			if(  (eTaskGetState(leftTaskHandle) != eSuspended)  &&  (eTaskGetState(rightTaskHandle) != eSuspended)  )
			{
				vTaskSuspend(leftTaskHandle);
				vTaskSuspend(rightTaskHandle);
			}
			else
			{
				vTaskResume(leftTaskHandle);
				vTaskResume(rightTaskHandle);
			}
		}
		vTaskDelay(100);
	}
}
