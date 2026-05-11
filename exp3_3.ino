// Resume Suspended Task
#include <Arduino_FreeRTOS.h>

#define LED1 6

TaskHandle_t Task1Handle;

// Task 1: Blinks LED
void Task1(void *pvParameters) {
  pinMode(LED1, OUTPUT);

  while (1) {
    digitalWrite(LED1, !digitalRead(LED1));
    Serial.println("TASK1 Running");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Control Task: Suspends and Resumes Task1
void ControlTask(void *pvParameters) {

  vTaskDelay(3000 / portTICK_PERIOD_MS);

  Serial.println("Suspending TASK1");
  vTaskSuspend(Task1Handle);

  vTaskDelay(3000 / portTICK_PERIOD_MS);

  Serial.println("Resuming TASK1");
  vTaskResume(Task1Handle);

  while (1) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(9600);

  xTaskCreate(Task1, "Task1", 128, NULL, 1, &Task1Handle);
  xTaskCreate(ControlTask, "Control", 128, NULL, 2, NULL);
}

// Required empty loop for Arduino compatibility
void loop() {
  // Nothing here (FreeRTOS handles everything)
}
