#include<Arduino_FreeRTOS.h> 
#include<semphr.h> 
SemaphoreHandle_t xMutex; 
void Task1(void *pvParameters) 
{ 
    while(1) 
    { 
        if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE) 
        { 
            Serial.println("Task 1 using printer"); 
            xSemaphoreGive(xMutex); 
 
29 
 
        } 
        vTaskDelay(1000/portTICK_PERIOD_MS); 
    } 
} 
void Task2(void *pvParameters) 
{ 
    while(1) 
    { 
        if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE) 
        { 
            Serial.println("Task 2 using printer"); 
            xSemaphoreGive(xMutex); 
        } 
        vTaskDelay(1000/portTICK_PERIOD_MS); 
    } 
} 
void setup() 
{ 
    Serial.begin(9600); 
    xMutex=xSemaphoreCreateMutex(); 
    Serial.print("Mutex Handle: "); 
    Serial.println((int)xMutex); 
    xTaskCreate(Task1,"Task1",128,NULL,1,NULL); 
    xTaskCreate(Task2,"Task2",128,NULL,1,NULL); 
} 
void loop() 
{ 
}
