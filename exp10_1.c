#include "main.h"
#include "cmsis_os.h"

/* Task Handles */
osThreadId_t defaultTaskHandle;
osThreadId_t led1Handle;
osThreadId_t led2Handle;

/* Task attributes */
const osThreadAttr_t defaultTaskAttr = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = osPriorityNormal,
};

const osThreadAttr_t led1Attr = {
  .name = "LED1",
  .stack_size = 256 * 4,
  .priority = osPriorityLow,
};

const osThreadAttr_t led2Attr = {
  .name = "LED2",
  .stack_size = 256 * 4,
  .priority = osPriorityLow,
};

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void DefaultTask(void *argument);
void LED1_Task(void *argument);
void LED2_Task(void *argument);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  osKernelInitialize();

  defaultTaskHandle = osThreadNew(DefaultTask, NULL, &defaultTaskAttr);
  led1Handle = osThreadNew(LED1_Task, NULL, &led1Attr);
  led2Handle = osThreadNew(LED2_Task, NULL, &led2Attr);

  osKernelStart();

  while (1) {}
}

/* Default Task → Controls other tasks */
void DefaultTask(void *argument)
{
  for (;;)
  {
    osDelay(3000);

    /* Change priority */
    osThreadSetPriority(led1Handle, osPriorityHigh);

    osDelay(3000);

    /* Suspend LED2 */
    osThreadSuspend(led2Handle);

    osDelay(3000);

    /* Resume LED2 */
    osThreadResume(led2Handle);
  }
}

/* LED1 Task */
void LED1_Task(void *argument)
{
  for (;;)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    osDelay(500);
  }
}

/* LED2 Task */
void LED2_Task(void *argument)
{
  for (;;)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
    osDelay(700);
  }
}
