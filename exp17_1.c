#include "main.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>

/* UART handle */
UART_HandleTypeDef huart2;

/* Task handles */
osThreadId defaultTaskHandle;
osThreadId ledTaskHandle;

/* Semaphores & Mutex */
SemaphoreHandle_t binarySem;
SemaphoreHandle_t uartMutex;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void StartDefaultTask(void const *argument);
void StartLedTask(void const *argument);

/* UART safe print */
void UART_Print(char *msg)
{
    if (xSemaphoreTake(uartMutex, portMAX_DELAY) == pdTRUE)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        xSemaphoreGive(uartMutex);
    }
}

/* MAIN */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();

    /* Create semaphore and mutex */
    binarySem = xSemaphoreCreateBinary();
    uartMutex = xSemaphoreCreateMutex();

    if (binarySem == NULL || uartMutex == NULL)
    {
        while (1); // error
    }

    /* Create tasks */
    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    osThreadDef(ledTask, StartLedTask, osPriorityAboveNormal, 0, 128);
    ledTaskHandle = osThreadCreate(osThread(ledTask), NULL);

    osKernelStart();

    while (1) {}
}

/* DEFAULT TASK */
void StartDefaultTask(void const *argument)
{
    char msg[100];

    while (1)
    {
        sprintf(msg, "Default Task Running\r\n");
        UART_Print(msg);

        osDelay(2000);
    }
}

/* LED TASK (triggered by interrupt) */
void StartLedTask(void const *argument)
{
    char msg[100];

    while (1)
    {
        if (xSemaphoreTake(binarySem, portMAX_DELAY) == pdTRUE)
        {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

            sprintf(msg, "Interrupt Received -> LED Toggled\r\n");
            UART_Print(msg);
        }
    }
}

/* INTERRUPT CALLBACK */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (GPIO_Pin == GPIO_PIN_13)
    {
        xSemaphoreGiveFromISR(binarySem, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
