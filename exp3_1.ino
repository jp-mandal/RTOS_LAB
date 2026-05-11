#include <Arduino_FreeRTOS.h> 
#define LED1 6 
#define LED2 7 
#define LED3 8 
void Task1(void *pvParameters) 
{ 
  pinMode(LED1, OUTPUT); 
  while (1) 
  { 
    digitalWrite(LED1, !digitalRead(LED1)); 
    Serial.println("TASK1 -> LED1 Blinking"); 
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  } 
} 
void Task2(void *pvParameters) 
{ 
 pinMode(LED2, OUTPUT); 
  while (1) 
  { 
    digitalWrite(LED2, !digitalRead(LED2)); 
    Serial.println("TASK2 -> LED2 Blinking"); 
    vTaskDelay(500 / portTICK_PERIOD_MS); 
  } 
} 
void Task3(void *pvParameters) 
 
25 
 
{ 
  pinMode(LED3, OUTPUT); 
  while (1) 
  { 
    digitalWrite(LED3, !digitalRead(LED3)); 
    Serial.println("TASK3 -> LED3 Blinking"); 
    vTaskDelay(700 / portTICK_PERIOD_MS); 
  } 
} 
void setup() 
{ 
  Serial.begin(9600); 
  xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL); 
  xTaskCreate(Task2, "Task2", 128, NULL, 1, NULL); 
  xTaskCreate(Task3, "Task3", 128, NULL, 1, NULL); 
} 
void loop() 
{ 
}
