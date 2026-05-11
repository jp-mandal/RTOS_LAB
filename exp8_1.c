/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>

/* RTOS objects */
osThreadId_t senderHandle;
osThreadId_t receiverHandle;
osMessageQueueId_t mailbox;

/* UART for printf */
extern UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}

/* Sender Task */
void SenderTask(void *argument)
{
    int data = 0;

    for (;;)
    {
        data += 10;

        osMessageQueuePut(mailbox, &data, 0, 0);
        printf("Sent: %d\r\n", data);

        osDelay(2000);
    }
}

/* Receiver Task */
void ReceiverTask(void *argument)
{
    int received;

    for (;;)
    {
        if (osMessageQueueGet(mailbox, &received, NULL, osWaitForever) == osOK)
        {
            printf("Received: %d\r\n", received);
        }
    }
}

/* Main */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    osKernelInitialize();

    /* Mailbox (queue length = 1) */
    mailbox = osMessageQueueNew(1, sizeof(int), NULL);

    if (mailbox == NULL)
    {
        printf("Queue creation failed!\r\n");
        while (1);
    }

    const osThreadAttr_t senderAttr = {
        .name = "Sender",
        .stack_size = 256 * 4,
        .priority = osPriorityNormal
    };

    const osThreadAttr_t receiverAttr = {
        .name = "Receiver",
        .stack_size = 256 * 4,
        .priority = osPriorityNormal
    };

    senderHandle = osThreadNew(SenderTask, NULL, &senderAttr);
    receiverHandle = osThreadNew(ReceiverTask, NULL, &receiverAttr);

    osKernelStart();

    while (1)
    {
    }
}
