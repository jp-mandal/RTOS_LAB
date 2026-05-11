#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart2;
SemaphoreHandle_t uartMutex;

/* UART Safe Print */
void UART_Print(char *msg)
{
    if (xSemaphoreTake(uartMutex, portMAX_DELAY) == pdTRUE)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        xSemaphoreGive(uartMutex);
    }
}

/* Task 1 */
void Task1(void *argument)
{
    while (1)
    {
        UART_Print("TASK 1: Sending Data...\r\n");
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}

/* Task 2 */
void Task2(void *argument)
{
    while (1)
    {
        UART_Print("TASK 2: Processing Data...\r\n");
        vTaskDelay(pdMS_TO_TICKS(1200));
    }
}

/* Task 3 */
void Task3(void *argument)
{
    while (1)
    {
        UART_Print("TASK 3: Monitoring System...\r\n");
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    uartMutex = xSemaphoreCreateMutex();

    if (uartMutex != NULL)
    {
        HAL_UART_Transmit(&huart2,
                          (uint8_t *)"Mutex Initialized\r\n",
                          strlen("Mutex Initialized\r\n"),
                          HAL_MAX_DELAY);
    }

    xTaskCreate(Task1, "T1", 128, NULL, 2, NULL);
    xTaskCreate(Task2, "T2", 128, NULL, 2, NULL);
    xTaskCreate(Task3, "T3", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1) {}
}
