/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2023-05-13

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f0xx.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */

/* Private functions */
void init_GPIOA(){
	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	//GPIOA->PUPDR|=GPIO_PUPDR_PUPDR0_0;//�������� � ����� ���� �� ���������� �� ������ �� ��������
	GPIOA->PUPDR|=GPIO_PUPDR_PUPDR0_1;//�������� � ������ �������� ���, ��� ����� ������ ���������� ������������ �����, ����� ������� �������� �������
}

void init_GPIOC(){
	RCC->AHBENR|=RCC_AHBENR_GPIOCEN;
	GPIOC->MODER|=GPIO_MODER_MODER9_0;
}
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{


  /* TODO - Add your application code here */
	init_GPIOA();
	init_GPIOC();
  /* Infinite loop */
  while (1)
  {
	if(GPIOA->IDR & 0x00000001){
		GPIOC->BSRR|=GPIO_BSRR_BS_9;
	}
	else{
		GPIOC->BSRR|=GPIO_BSRR_BR_9;
	}
  }
}