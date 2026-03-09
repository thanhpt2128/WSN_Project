
#include "aht20.h"

#define AHT_ADDR	0x38<<1
extern I2C_HandleTypeDef hi2c1;

void AHT20_Read(float* Temp, float* Humid)
{
	HAL_Delay(40);
	uint8_t dum[7];
	HAL_I2C_Mem_Read(&hi2c1, AHT_ADDR, 0x71, 1, dum, 1, 100);

	if(!(dum[0]&(1<<3)))
	{
		dum[0] = 0xBE, dum[1] = 0x08, dum[2] = 0x00;
		HAL_I2C_Master_Transmit(&hi2c1, AHT_ADDR, dum, 3, 100);
		HAL_Delay(10);
	}
	
	dum[0] = 0xAC, dum[1] = 0x33, dum[2] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c1, AHT_ADDR, dum, 3, 100);
	HAL_Delay(80);
	
	do {
		HAL_I2C_Mem_Read(&hi2c1, AHT_ADDR, 0x71, 1, dum, 1, 100);
		HAL_Delay(1);
	} while(dum[0]&(1<<7));
	
	HAL_I2C_Master_Receive(&hi2c1, AHT_ADDR, dum, 7, 100);
	uint32_t h20 = (dum[1])<<16 | (dum[2])<<8 | (dum[3]);
	uint32_t t20 = (dum[3])<<16 | (dum[4])<<8 | dum[5];
	h20 = h20>>4;
	t20 = t20&0xFFFFF;
	*Temp = (t20 / 1048576.0)*200.0 - 50.0;
	*Humid = h20 / 10485.76;
}