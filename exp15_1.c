#include "main.h"
#include "cmsis_os.h"
#include "queue.h"
#include <stdio.h>

/* Data structure */
typedef struct
{
    int value;
    uint32_t timestamp;
} MailData;

/* Queue handle */
QueueHandle_t mailbox;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void SenderTask(void *argument);
void ReceiverTask(void *argument);

/* printf redirect to UART */
extern UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}

/* MAIN */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();

    /* Create mailbox (queue size = 1) */
    mailbox = xQueueCreate(1, sizeof(MailData));

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
    MailData data;

    for (;;)
    {
        data.value = 100;
        data.timestamp = HAL_GetTick();

        xQueueOverwrite(mailbox, &data);
        printf("Sent: %d | Time: %lu ms\r\n", data.value, data.timestamp);

        vTaskDelay(pdMS_TO_TICKS(2000));

        data.value = 200;
        data.timestamp = HAL_GetTick();

        xQueueOverwrite(mailbox, &data);
        printf("Sent: %d | Time: %lu ms\r\n", data.value, data.timestamp);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

/* RECEIVER TASK */
void ReceiverTask(void *argument)
{
    MailData received;

    for (;;)
    {
        if (xQueueReceive(mailbox, &received, portMAX_DELAY) == pdTRUE)
        {
            printf("Value: %d | Time: %lu ms\r\n",
                   received.value,
                   received.timestamp);
        }
    }
}
