#include "main.h"
#include "cmsis_os.h"
#include "queue.h"
#include <stdio.h>

/* Queue handle */
QueueHandle_t mailbox;

/* UART handle */
UART_HandleTypeDef huart2;

/* printf redirect to UART */
int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void SenderTask(void *argument);
void ReceiverTask(void *argument);

/* MAIN */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();

    /* Create mailbox (queue size = 1) */
    mailbox = xQueueCreate(1, sizeof(int));

    if (mailbox == NULL)
    {
        printf("Mailbox creation failed!\r\n");
        while (1);
    }

    /* Create tasks */
    xTaskCreate(SenderTask, "Sender", 128, NULL, 2, NULL);
    xTaskCreate(ReceiverTask, "Receiver", 128, NULL, 2, NULL);

    /* Start scheduler */
    vTaskStartScheduler();

    while (1) {}
}

/* SENDER TASK */
void SenderTask(void *argument)
{
    int val1 = 10;
    int val2 = 20;

    for (;;)
    {
        xQueueOverwrite(mailbox, &val1);
        printf("Sent: %d\r\n", val1);
        osDelay(2000);

        xQueueOverwrite(mailbox, &val2);
        printf("Sent: %d\r\n", val2);
        osDelay(2000);
    }
}

/* RECEIVER TASK */
void ReceiverTask(void *argument)
{
    int received;

    for (;;)
    {
        if (xQueueReceive(mailbox, &received, portMAX_DELAY) == pdTRUE)
        {
            printf("Received: %d\r\n", received);
        }
    }
}
