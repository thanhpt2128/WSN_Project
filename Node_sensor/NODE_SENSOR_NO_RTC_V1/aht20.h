#ifndef __AHT20_H
#define __AHT20_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"
#include "math.h"

/* Exported functions --------------------------------------------------------*/
void AHT20_Read(float* Temp, float* Humid);

#ifdef __cplusplus
}
#endif

#endif /* __AHT20_H */
