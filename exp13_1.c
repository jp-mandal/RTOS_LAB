#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>

/* UART handle */
UART_HandleTypeDef huart2;

/* Thread handles */
osThreadId Task_1Handle;
osThreadId Task_2Handle;
osThreadId Task_3Handle;

/* Counting semaphore */
osSemaphoreId myCountingSem01Handle;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void StartTask_1(void const * argument);
void StartTask_2(void const * argument);
void StartTask_3(void const * argument);

/* printf redirect to UART */
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

    /* Create counting semaphore (initial count = 5) */
    osSemaphoreDef(myCountingSem01);
    myCountingSem01Handle = osSemaphoreCreate(osSemaphore(myCountingSem01), 5);

    /* Create tasks */
    osThreadDef(Task_1, StartTask_1, osPriorityNormal, 0, 128);
    Task_1Handle = osThreadCreate(osThread(Task_1), NULL);

    osThreadDef(Task_2, StartTask_2, osPriorityNormal, 0, 128);
    Task_2Handle = osThreadCreate(osThread(Task_2), NULL);

    osThreadDef(Task_3, StartTask_3, osPriorityNormal, 0, 128);
    Task_3Handle = osThreadCreate(osThread(Task_3), NULL);

    osKernelStart();

    while (1) {}
}

/* TASK 1 */
void StartTask_1(void const * argument)
{
    for (;;)
    {
        osSemaphoreWait(myCountingSem01Handle, osWaitForever);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        printf("Task 1 Executing\r\n");
        osDelay(500);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

        osSemaphoreRelease(myCountingSem01Handle);
        osSemaphoreRelease(myCountingSem01Handle);

        printf("Sem Count (T1): %d\r\n",
               uxSemaphoreGetCount(myCountingSem01Handle));

        osDelay(1000);
    }
}

/* TASK 2 */
void StartTask_2(void const * argument)
{
    for (;;)
    {
        osSemaphoreWait(myCountingSem01Handle, osWaitForever);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
        printf("Task 2 Executing\r\n");
        osDelay(500);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

        osSemaphoreRelease(myCountingSem01Handle);
        osSemaphoreRelease(myCountingSem01Handle);

        printf("Sem Count (T2): %d\r\n",
               uxSemaphoreGetCount(myCountingSem01Handle));

        osDelay(1000);
    }
}

/* TASK 3 */
void StartTask_3(void const * argument)
{
    for (;;)
    {
        osSemaphoreWait(myCountingSem01Handle, osWaitForever);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
        printf("Task 3 Executing\r\n");
        osDelay(500);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);

        osSemaphoreRelease(myCountingSem01Handle);
        osSemaphoreRelease(myCountingSem01Handle);
        osSemaphoreRelease(myCountingSem01Handle);

        printf("Sem Count (T3): %d\r\n",
               uxSemaphoreGetCount(myCountingSem01Handle));

        osDelay(1000);
    }
}
