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
void initTIM1(void);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
#endif /* INIT_H_ */
