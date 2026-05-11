#include <stdio.h>
#include "cmsis_os.h"
#include "queue.h"

/* Queue handle */
QueueHandle_t mailbox;

/* Sender Task */
void SenderTask(void *argument)
{
    int val1 = 10;
    int val2 = 20;

    for (;;)
    {
        xQueueOverwrite(mailbox, &val1);
        printf("Sent: %d\n", val1);
        osDelay(2000);

        xQueueOverwrite(mailbox, &val2);
        printf("Sent: %d\n", val2);
        osDelay(2000);
    }
}

/* Receiver Task */
void ReceiverTask(void *argument)
{
    int received;

    for (;;)
    {
        if (xQueueReceive(mailbox, &received, portMAX_DELAY) == pdTRUE)
        {
            printf("Received: %d\n", received);
        }
    }
}

/* Main / RTOS Init */
int main(void)
{
    /* Initialize RTOS (if required by your IDE like STM32CubeIDE) */
    osKernelInitialize();

    /* Create queue with length 1 (needed for xQueueOverwrite) */
    mailbox = xQueueCreate(1, sizeof(int));

    if (mailbox == NULL)
    {
        printf("Queue creation failed!\n");
        while (1);
    }

    /* Create tasks */
    osThreadNew(SenderTask, NULL, NULL);
    osThreadNew(ReceiverTask, NULL, NULL);

    /* Start scheduler */
    osKernelStart();

    while (1)
    {
    }
}
