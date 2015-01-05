#include <wiringPiI2C.h>
#include <stdio.h>

int main(void)
{
	int id = wiringPiI2CSetup(0x32);
	
	int res = wiringPiI2CRead(id);
	int wr = wiringPiI2CWrite (id, 42);
	
	printf("id: %d, res: %d, wr: %d\n", id, res, wr);
	
	return 0;
}
