#include<Arduino_FreeRTOS.h> 
void Task1(void *pvParameters); 
void Task2(void *pvParameters); 
void setup() 
{ 
    Serial.begin(9600); 
    xTaskCreate(Task1,"Task1",128,NULL,2,NULL); 
    xTaskCreate(Task2,"Task2",128,NULL,1,NULL); 
} 
void loop() 
{ 
} 
void Task1(void *pvParameters) 
{ 
    while(1) 
    { 
        Serial.println("DMS Task 1 - Short Deadline"); 
        vTaskDelay(400/portTICK_PERIOD_MS); 
    } 
 
19 
 
} 
void Task2(void *pvParameters) 
{ 
    while(1) 
    { 
        Serial.println("DMS Task 2 - Long Deadline"); 
        vTaskDelay(800/portTICK_PERIOD_MS); 
    } 
}
