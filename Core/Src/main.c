#include "stm32f4xx.h"
#include <stdio.h>

int __io_putchar(int ch) {
    while (!(USART2->SR & (1 << 7)));
    USART2->DR = (ch & 0xFF);
    return ch;
}

void delay_ms(volatile uint32_t ms) {
    ms *= 1600; // 16 MHz
    while(ms--) {
        __asm("NOP");
    }
}

void System_Init(void){
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB2ENR |= (1 << 8);
	RCC->APB1ENR |= (1 << 17);

	GPIOA->MODER |= (3 << 2);

	GPIOA->MODER &= ~(3 << 4);
	GPIOA->MODER |= (2 << 4);

	GPIOA->AFR[0] &= ~(0xF << 8);
	GPIOA->AFR[0] |= (7 << 8);
}

void ADC1_Init(void){
	ADC1->SQR3 = 1;
	ADC1->SQR1 = 0;

	ADC1->CR2 |= (1 << 1);
	ADC1->CR2 |= (1 << 0);
	ADC1->CR2 |= (1 << 30);
}

void USART2_Init(void){
	USART2->BRR = 0x008B;
	USART2->CR1 |= (1 << 3);
	USART2->CR1 |= (1 << 13);
}

int main(void){

	System_Init();
	ADC1_Init();
	USART2_Init();

	uint16_t adc_val = 0;
	uint32_t mv = 0;

	while(1){

		while(!(ADC1->SR & (1 << 1)));

		adc_val = ADC1->DR;

		mv = (adc_val * 3300) / 4095;
		printf("ADC: %4d | Voltage: %4d mV\r\n", adc_val, (uint16_t)mv);

		delay_ms(100);
	}
}

