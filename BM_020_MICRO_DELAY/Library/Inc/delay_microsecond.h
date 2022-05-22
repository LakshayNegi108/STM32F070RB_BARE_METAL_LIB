/*
 * delay_microsecond.h
 *
 *  Created on: May 19, 2022
 *      Author: hp
 */

#ifndef INC_DELAY_MICROSECOND_H_
#define INC_DELAY_MICROSECOND_H_

#include "stm32f070xb.h"
#include "main.h"

void micro_delay(uint32_t us);
void milli_delay(uint32_t ms);
void tim_config();

#endif /* INC_DELAY_MICROSECOND_H_ */
