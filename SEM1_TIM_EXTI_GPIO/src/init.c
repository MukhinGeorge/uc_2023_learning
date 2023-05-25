/*
 * init.c
 *
 *  Created on: 25 ��� 2023 �.
 *      Author: goodg
 */
#include "stm32f0xx.h"
#include "init.h"
uint32_t countFronts = 0;

void EXTI0_1_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR0){
		EXTI->PR |= EXTI_PR_PR0;
		//GPIOC->ODR ^= GPIO_ODR_9;
		if(GPIOA->IDR & 0x01){
		countFronts++;

		}
		else{

		}
		TIM6->CNT = 0;
	}
}
void TIM6_IRQHandler(void){
	if(TIM6->SR & TIM_SR_UIF){
		TIM6->SR &= ~TIM_SR_UIF;
		//GPIOA->MODER|=GPIO_MODER_MODER0_0;

	}
//	for(int i=0; i<countFronts; i++){
//		GPIOC->BSRR|=GPIO_BSRR_BS_9;
//		for(int j=0; j<50000; j++){}
//		GPIOC->BSRR|=GPIO_BSRR_BR_9;
//	}
	if(GPIOA->IDR & 0x01){
		TIM6->CNT=0;
		return;
	}
	else{
		GPIOA->MODER|=GPIO_MODER_MODER0_0;
		for(int i=0; i<countFronts; i++){
					GPIOC->BSRR|=GPIO_BSRR_BS_9;
					for(int j=0; j<500000; j++){}
					GPIOC->BSRR|=GPIO_BSRR_BR_9;
					for(int k=0; k<500000; k++){}
				}
	}
	countFronts = 0;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
}
void initEXTI0(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->EMR |= EXTI_EMR_EM0;
	EXTI->RTSR |= EXTI_RTSR_RT0;
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	NVIC_SetPriority(EXTI0_1_IRQn, 8);
}
void initGPIO(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER9_0;
}
void initTIM6(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 886;//886
	TIM6->ARR = 901;//901
	TIM6->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM6_IRQn);
	NVIC_SetPriority(TIM6_IRQn, 2);
	//TIM6->CR1 |= TIM_CR1_CEN;
	TIM6->CR1 |= TIM_CR1_CEN;

}
