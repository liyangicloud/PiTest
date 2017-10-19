#include <wiringPi.h>

// 
//wiringPiSetupSys is for  BCM code 
//
//
//
#define	LED	17

int main(void)
{
	wiringPiSetupSys();

	pinMode(LED, OUTPUT);

	while (true)
	{
		digitalWrite(LED, HIGH); 
		delay(500); 
		digitalWrite(LED, LOW);	
		delay(500);
	}
	return 0;
}