#include "FreeRTOS.h" 
#include "task.h" 
#include "queue.h" 
#include "cmsis_os.h" 
#include "main.h" 
#include <stdint.h> 
#include <stdio.h> 
 
QueueHandle_t xQueue; 
TaskHandle_t SenderHandle; 
 
#define RCC_BASE       0x40021000UL 
#define GPIOA_BASE     0x48000000UL 
#define USART2_BASE    0x40004400UL 
#define RCC_AHB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x4C)) 
#define RCC_APB1ENR1    (*(volatile uint32_t *)(RCC_BASE + 0x58)) 
 
69 
 
 
void UART2_Init(void); 
void UART_Write(char ch); 
void SenderTask(void *argument); 
void ReceiverTask(void *argument); 
 
void UART_Write(char ch) 
{ 
    while(!(*(volatile uint32_t *)(USART2_BASE + 0x1C) & (1 << 7))); 
    *(volatile uint32_t *)(USART2_BASE + 0x28) = ch; 
} 
int __io_putchar(int ch) 
{ 
    UART_Write(ch); 
    return ch; 
} 
void MX_FREERTOS_Init(void) 
{ 
    UART2_Init(); 
    xQueue = xQueueCreate(5, sizeof(int)); 
    xTaskCreate(SenderTask, "SenderTask", 128, NULL, 2, &SenderHandle); 
    xTaskCreate(ReceiverTask, "ReceiverTask", 128, NULL, 1, NULL); 
} 
void SenderTask(void *argument) 
{ 
    int value = 1; 
    while(1) 
    { 
        for(int i = 0; i < 5; i++) 
        { 
            xQueueSend(xQueue, &value, portMAX_DELAY); 
            printf("Sent: %d\r\n", value); 
            value++; 
            vTaskDelay(pdMS_TO_TICKS(500)); 
        } 
        vTaskSuspend(NULL); 
    }} 
void ReceiverTask(void *argument) 
{ 
    int receivedData; 
    while(1) 
    { 
        if(uxQueueMessagesWaiting(xQueue) == 5) 
 
70 
 
        { 
            printf("\r\nQueue Full! Receiving Data...\r\n"); 
            for(int i = 0; i < 5; i++) 
            { 
                xQueueReceive(xQueue, &receivedData, portMAX_DELAY); 
                printf("Received: %d\r\n", receivedData); 
                vTaskDelay(pdMS_TO_TICKS(500)); 
            } 
            printf("\r\nQueue Empty\r\n\r\n"); 
            vTaskResume(SenderHandle); 
        } 
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }} 
static StaticTask_t xIdleTaskTCBBuffer; 
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE]; 
void vApplicationGetIdleTaskMemory( 
        StaticTask_t **ppxIdleTaskTCBBuffer, 
        StackType_t **ppxIdleTaskStackBuffer, 
        uint32_t *pulIdleTaskStackSize) 
{ 
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer; 
    *ppxIdleTaskStackBuffer = &xIdleStack[0]; 
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE; 
} 
