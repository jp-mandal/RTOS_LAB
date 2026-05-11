#include <Arduino_FreeRTOS.h>
#include <queue.h>

/* Mail structure */
typedef struct
{
  int value;
  unsigned long timestamp;
} MailData;

/* Queue handle */
QueueHandle_t mailbox;

/* Sender Task */
void SenderTask(void *pvParameters)
{
  MailData data;
  data.value = 0;

  while (1)
  {
    /* First value */
    data.value = 100;
    data.timestamp = millis();

    xQueueOverwrite(mailbox, &data);
    Serial.print("Sent Value: ");
    Serial.print(data.value);
    Serial.print("  Time: ");
    Serial.println(data.timestamp);

    vTaskDelay(2000 / portTICK_PERIOD_MS);

    /* Second value */
    data.value = 200;
    data.timestamp = millis();

    xQueueOverwrite(mailbox, &data);
    Serial.print("Sent Value: ");
    Serial.print(data.value);
    Serial.print("  Time: ");
    Serial.println(data.timestamp);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

/* Receiver Task */
void ReceiverTask(void *pvParameters)
{
  MailData receivedData;

  while (1)
  {
    if (xQueueReceive(mailbox, &receivedData, portMAX_DELAY) == pdPASS)
    {
      Serial.print("Received Value: ");
      Serial.print(receivedData.value);
      Serial.print("  Timestamp: ");
      Serial.println(receivedData.timestamp);
    }
  }
}

/* Setup */
void setup()
{
  Serial.begin(9600);

  /* Create mailbox queue (size = 1) */
  mailbox = xQueueCreate(1, sizeof(MailData));

  if (mailbox == NULL)
  {
    Serial.println("Queue creation failed!");
    while (1);
  }

  /* Create tasks */
  xTaskCreate(SenderTask, "Sender", 128, NULL, 1, NULL);
  xTaskCreate(ReceiverTask, "Receiver", 128, NULL, 1, NULL);
}

/* Empty loop (RTOS handles execution) */
void loop()
{
}
