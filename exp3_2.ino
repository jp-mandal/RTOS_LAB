#include <Arduino_FreeRTOS.h> 
#define LED1 6 
#define LED2 7 
void Task1(void *pvParameters) 
{ 
  pinMode(LED1, OUTPUT); 
 
  while (1) 
  { 
    digitalWrite(LED1, !digitalRead(LED1)); 
 
26 
 
 
    Serial.println("TASK1 Priority = 1"); 
 
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  } 
} 
void Task2(void *pvParameters) 
{ 
  pinMode(LED2, OUTPUT); 
  while (1) 
  { 
    digitalWrite(LED2, !digitalRead(LED2)); 
 
    Serial.println("TASK2 Priority = 3"); 
 
    vTaskDelay(300 / portTICK_PERIOD_MS); 
  } 
} 
void setup() 
{ 
  Serial.begin(9600); 
  // LOW PRIORITY 
  xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL); 
  // HIGH PRIORITY 
  xTaskCreate(Task2, "Task2", 128, NULL, 3, NULL); 
} 
void loop() 
{ 
}
