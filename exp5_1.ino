#include<Arduino_FreeRTOS.h> 
#include<semphr.h> 
SemaphoreHandle_t S; 
SemaphoreHandle_t T; 
SemaphoreHandle_t serialMutex; 
void Task1(void *pvParameters); 
void Task2(void *pvParameters); 
void setup() 
{ 
    Serial.begin(9600); 
    S=xSemaphoreCreateBinary(); 
    T=xSemaphoreCreateBinary(); 
    serialMutex=xSemaphoreCreateMutex(); 
    if(S!=NULL&&T!=NULL&&serialMutex!=NULL) 
    { 
        Serial.println("Semaphores and Mutex Created"); 
    } 
    xSemaphoreGive(S); 
    xTaskCreate(Task1,"Task1",128,NULL,2,NULL); 
    xTaskCreate(Task2,"Task2",128,NULL,1,NULL); 
 
33 
 
} 
void loop() 
{ 
} 
void Task1(void *pvParameters) 
{ 
    while(1) 
    { 
        if(xSemaphoreTake(S,portMAX_DELAY)==pdTRUE) 
        { 
            xSemaphoreTake(serialMutex,portMAX_DELAY); 
            Serial.println("Task 1 Running"); 
            Serial.print("S Taken -> "); 
            Serial.println(uxSemaphoreGetCount(S)); 
            xSemaphoreGive(serialMutex); 
            vTaskDelay(500/portTICK_PERIOD_MS); 
            xSemaphoreGive(T); 
            xSemaphoreTake(serialMutex,portMAX_DELAY); 
            Serial.print("T Given -> "); 
            Serial.println(uxSemaphoreGetCount(T)); 
            Serial.println(); 
            xSemaphoreGive(serialMutex); 
        } 
    } 
} 
void Task2(void *pvParameters) 
{ 
    while(1) 
    { 
        if(xSemaphoreTake(T,portMAX_DELAY)==pdTRUE) 
        { 
            xSemaphoreTake(serialMutex,portMAX_DELAY); 
            Serial.println("Task 2 Running"); 
            Serial.print("T Taken -> "); 
            Serial.println(uxSemaphoreGetCount(T)); 
            xSemaphoreGive(serialMutex); 
            vTaskDelay(500/portTICK_PERIOD_MS); 
            xSemaphoreGive(S); 
            xSemaphoreTake(serialMutex,portMAX_DELAY); 
            Serial.print("S Given -> "); 
            Serial.println(uxSemaphoreGetCount(S)); 
            Serial.println(); 
            xSemaphoreGive(serialMutex); 
 
34 
 
        } 
    } 
}
