#include "main.h"
#include "cmsis_os.h"
#include "timers.h"
#include <string.h>

/* UART handle */
UART_HandleTypeDef huart2;

/* Timer handles */
TimerHandle_t oneShotTimer;
TimerHandle_t autoReloadTimer;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* UART print function */
void printmsg(char *msg)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

/* One-shot timer callback */
void OneShotCallback(TimerHandle_t xTimer)
{
    printmsg("One Shot Timer Executed\r\n");
}

/* Auto-reload timer callback */
void AutoReloadCallback(TimerHandle_t xTimer)
{
    printmsg("Auto Reload Timer Executed\r\n");
}

/* MAIN */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();

    HAL_Delay(1000);

    printmsg("\r\nSTM32 FreeRTOS Software Timer Started\r\n");

    /* Create timers */
    oneShotTimer = xTimerCreate("OneShot",
                                pdMS_TO_TICKS(10000),
                                pdFALSE,
                                0,
                                OneShotCallback);

    autoReloadTimer = xTimerCreate("AutoReload",
                                   pdMS_TO_TICKS(3000),
                                   pdTRUE,
                                   0,
                                   AutoReloadCallback);

    /* Start timers */
    xTimerStart(oneShotTimer, 0);
    xTimerStart(autoReloadTimer, 0);

    /* Start scheduler */
    vTaskStartScheduler();

    while (1) {}
}
