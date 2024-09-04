#include "stm32f0xx.h"

void delay(uint32_t milliseconds) {
    uint32_t i;
    for (i = 0; i < (milliseconds * 800); i++) {
        // Adjust the delay loop according to your system clock frequency
        __NOP();
    }
}

void USART2_Init(void) {
    // Enable USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Configure GPIOA pins for USART2
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Enable GPIOA clock
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1; // Alternate function mode for PA2 and PA3
    GPIOA->AFR[0] |= (1 << (2 * 4)) | (1 << (3 * 4)); // AF1 for PA2 and PA3

    // Configure USART2
    USART2->CR1 &= ~USART_CR1_UE; // Disable USART2
    USART2->BRR = SystemCoreClock / 38400; // Set baud rate to 38400
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // Enable transmitter and receiver
    USART2->CR1 |= USART_CR1_UE; // Enable USART2
}

void USART2_SendChar(char ch) {
    // Wait until transmit data register is empty
    while (!(USART2->ISR & USART_ISR_TXE))
        ;
    USART2->TDR = (ch & 0xFF);
}

void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);
    }
}

int main(void) {
    // Initialize system clock
    SystemInit();

    // Initialize USART2
    USART2_Init();

    while (1) {
        // Send "Hello, World!" every second
        USART2_SendString("Hello, World!\n");
        delay(1000);
    }
}
