/*
 * init.h
 *
 *  Created on: 25 мая 2023 г.
 *      Author: goodg
 */

#ifndef INIT_H_
#define INIT_H_
uint32_t countFronts;
void EXTI0_1_IRQHandler(void);
void TIM6_IRQHandler(void);
void initEXTI0(void);
void initGPIO(void);
void initTIM6(void);
#endif /* INIT_H_ */
