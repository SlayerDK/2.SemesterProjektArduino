#include "Master.h"
#include "Motor.h"
#include "Lys.h"
#include "Effekt.h"
#include "Kommunikation.h"

int main(void)
{
	_delay_ms(4000);
	adc_init();
	motor_setup();
	uart_init(MYUBRR);
	
	self_testing();
	_delay_ms(5000);
	
	while (1)
	{
		getSteps();
		//send_data_to_webserver(measure_watt(), get_light_intensity());
		_delay_ms(500);
	}
}