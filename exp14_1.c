#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

/* Queue handle */
QueueHandle_t xQueue;

/* Function prototypes */
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

void TaskA(void *argument);
void TaskB(void *argument);
void TaskC(void *argument);

/* MAIN */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_FREERTOS_Init();

    osKernelStart();

    while (1) {}
}

/* Empty clock config (user defined in CubeMX normally) */
void SystemClock_Config(void)
{
}

/* FreeRTOS initialization */
void MX_FREERTOS_Init(void)
{
    /* Create queue (10 characters buffer) */
    xQueue = xQueueCreate(10, sizeof(char));

    if (xQueue == NULL)
    {
        printf("Queue creation failed!\r\n");
        while (1);
    }

    /* Create tasks */
    xTaskCreate(TaskA, "TaskA", 128, NULL, 2, NULL);
    xTaskCreate(TaskB, "TaskB", 128, NULL, 2, NULL);
    xTaskCreate(TaskC, "TaskC", 128, NULL, 1, NULL);
}

/* TASK A */
void TaskA(void *argument)
{
    char data = 'A';

    while (1)
    {
        xQueueSend(xQueue, &data, portMAX_DELAY);
        printf("Task A Sent: %c\r\n", data);

        data++;
        if (data > 'E')
            data = 'A';

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* TASK B */
void TaskB(void *argument)
{
    char data = '1';

    while (1)
    {
        xQueueSend(xQueue, &data, portMAX_DELAY);
        printf("Task B Sent: %c\r\n", data);

        data++;
        if (data > '5')
            data = '1';

        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

/* TASK C (Receiver) */
void TaskC(void *argument)
{
    char receivedData;

    while (1)
    {
        if (xQueueReceive(xQueue, &receivedData, portMAX_DELAY) == pdPASS)
        {
            printf("Task C Received: %c\r\n", receivedData);
        }
    }
}
