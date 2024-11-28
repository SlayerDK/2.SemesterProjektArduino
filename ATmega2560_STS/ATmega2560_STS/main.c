#include "Master.h"
#include "Motor.h"
#include "Lys.h"
#include "Effekt.h"
#include "Kommunikation.h"

int main(void)
{
	adc_init();
	motor_setup();
	uart_init(MYUBRR);
	
	while (1)
	{
		send_data_to_webserver(measure_watt(), get_light_intensity());
		_delay_ms(500);
	}
}