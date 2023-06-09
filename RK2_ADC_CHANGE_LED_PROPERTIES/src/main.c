/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2023-05-28

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

#define LED_PIN GPIO_Pin_13
#define ADC1_CHANNEL_2 2
#define ADC1_CHANNEL_6 6

void GPIO_Config(void);
void ADC_Config(void);
void TIM_Config(uint32_t frequency);

int main(void)
{
    GPIO_Config();
    ADC_Config();
    TIM_Config(0);  // ���������� ������������� ������� ������� �� ����� 6 ������ ADC � 0 ��

    while (1)
    {
        // ��������� �������������� ADC
        ADC1->CR |= ADC_CR_ADSTART;

        // ���� ���������� �������������� ADC
        while (!(ADC1->ISR & ADC_ISR_EOC))
        {
        }

        // �������� �������� ���������� � ������ 2 � 6 ������� ADC
        uint16_t voltage2 = ADC1->DR;
        uint16_t voltage6 = ADC1->DR;

        // ������������ ������������ �������� ���������� � ����������� �� ����������
        uint32_t duration = voltage2 * 100;  // ��������� �����������: ������������ = ���������� * 100

        // ������������� ������������ �������� ����������
        if (duration > 1000)
        {
            duration = 1000;
        }
        TIM3->CCR1 = duration;

        // ������������� ������� ������� �� ����� 6 ������ ADC
        uint32_t frequency = voltage6 * 10;  // ��������� �����������: ������� = ���������� * 10
        TIM_Config(frequency);
    }
}

void GPIO_Config(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    GPIOC->MODER |= GPIO_MODER_MODER13_0;  // ��������� ���� PC13 �� �����
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT_13;    // �������� ����
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_0;  // �������� I/O - ������
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13;    // ���������� ������������� ����������
}

void ADC_Config(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    GPIOA->MODER |= GPIO_MODER_MODER1;     // ��������� ���� PA1 �� ���������� ���� (ADC1_IN2)
    GPIOA->MODER |= GPIO_MODER_MODER6;     // ��������� ���� PA6 �� ���������� ���� (ADC1_IN6)

    ADC1->CFGR1 |= ADC_CFGR1_RES_1;         // ��������� ���������� ADC �� 8 ���
    ADC1->CHSELR |= ADC_CHSELR_CHSEL2;      // ����� ������ 2 ��� ��������������
    ADC1->CHSELR |= ADC_CHSELR_CHSEL6;      // ����� ������ 6 ��� ��������������
    ADC1->CFGR1 |= ADC_CFGR1_CONT;          // ��������� ������������ ������ ��������������
    ADC1->CR |= ADC_CR_ADEN;                // ��������� ADC

    while (!(ADC1->ISR & ADC_ISR_ADRDY))    // �������� ���������� ADC
    {
    }

    ADC1->CR |= ADC_CR_ADSTART;             // ������ �������������� ADC
}

void TIM_Config(uint32_t frequency)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 48000 - 1;                  // ������������ ��� ��������� ������� ������� 1 ���
    TIM3->ARR = 1000;                       // ������������ �������� ��������

    TIM3->CCR1 = 0;                         // ���������� ������������ �������� ���������� = 0

    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;  // ����� PWM1 �� ������ CCR1
    TIM3->CCER |= TIM_CCER_CC1E;            // ���������� ��������� ������� �� ������ CCR1

    TIM3->CR1 |= TIM_CR1_CEN;               // ��������� �������

    TIM3->ARR = 1000 / frequency;           // ��������� ������� ��������� �������
}
