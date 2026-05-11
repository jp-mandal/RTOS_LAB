#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* Pins */
#define LED_PIN     GPIO_NUM_4
#define BUTTON_PIN  GPIO_NUM_25

/* Semaphore */
SemaphoreHandle_t buttonSemaphore;

/* TAG */
static const char *TAG = "APP";

/* LED TASK */
void task_led(void *params)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(LED_PIN, 1);
        ESP_LOGI(TAG, "LED ON");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_PIN, 0);
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* UART / LOG TASK */
void task_uart(void *params)
{
    while (1)
    {
        ESP_LOGI(TAG, "Periodic UART Message");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* BUTTON TASK (WAIT FOR ISR EVENT) */
void task_button(void *params)
{
    while (1)
    {
        if (xSemaphoreTake(buttonSemaphore, portMAX_DELAY) == pdTRUE)
        {
            ESP_LOGI(TAG, "Button Press Detected!");

            vTaskDelay(pdMS_TO_TICKS(200));

            /* Re-enable interrupt after processing */
            gpio_intr_enable(BUTTON_PIN);
        }
    }
}

/* ISR HANDLER */
static void IRAM_ATTR button_isr_handler(void *arg)
{
    BaseType_t higher_priority_task_woken = pdFALSE;

    /* Disable interrupt to avoid bouncing */
    gpio_intr_disable(BUTTON_PIN);

    /* Give semaphore from ISR */
    xSemaphoreGiveFromISR(buttonSemaphore, &higher_priority_task_woken);

    if (higher_priority_task_woken)
    {
        portYIELD_FROM_ISR();
    }
}

/* MAIN */
void app_main(void)
{
    ESP_LOGI(TAG, "System Starting...");

    /* Configure button GPIO */
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };

    gpio_config(&io_conf);

    /* Create semaphore */
    buttonSemaphore = xSemaphoreCreateBinary();

    if (buttonSemaphore == NULL)
    {
        ESP_LOGE(TAG, "Semaphore creation failed!");
        return;
    }

    /* Install ISR service */
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, NULL);

    /* Enable interrupt */
    gpio_intr_enable(BUTTON_PIN);

    /* Create tasks */
    xTaskCreate(task_led, "LED_TASK", 2048, NULL, 1, NULL);
    xTaskCreate(task_uart, "UART_TASK", 2048, NULL, 2, NULL);
    xTaskCreate(task_button, "BUTTON_TASK", 2048, NULL, 3, NULL);

    ESP_LOGI(TAG, "System Started Successfully");
}
