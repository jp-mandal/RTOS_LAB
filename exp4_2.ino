#include<Arduino_FreeRTOS.h> 
#include<semphr.h> 
#define LED1 7 
#define LED2 8 
SemaphoreHandle_t serialMutex; 
void BlinkTask1(void *pvParameters) 
{ 
    pinMode(LED1,OUTPUT); 
    while(1) 
    { 
        digitalWrite(LED1,HIGH); 
        vTaskDelay(500/portTICK_PERIOD_MS); 
        digitalWrite(LED1,LOW); 
        vTaskDelay(500/portTICK_PERIOD_MS); 
        if(xSemaphoreTake(serialMutex,portMAX_DELAY)==pdTRUE) 
        { 
            Serial.println("Task 1 entered critical section"); 
            xSemaphoreGive(serialMutex); 
        } 
    } 
} 
void BlinkTask2(void *pvParameters) 
{ 
    pinMode(LED2,OUTPUT); 
    while(1) 
    { 
        digitalWrite(LED2,HIGH); 
        vTaskDelay(1000/portTICK_PERIOD_MS); 
        digitalWrite(LED2,LOW); 
        vTaskDelay(1000/portTICK_PERIOD_MS); 
        if(xSemaphoreTake(serialMutex,portMAX_DELAY)==pdTRUE) 
        { 
            Serial.println("Task 2 entered critical section"); 
            xSemaphoreGive(serialMutex); 
        }}} 
void setup() 
{ 
    Serial.begin(9600); 
    serialMutex=xSemaphoreCreateMutex(); 
    Serial.print("Mutex Handle: "); 
    Serial.println((int)serialMutex); 
    xTaskCreate(BlinkTask1,"Blink1",128,NULL,2,NULL); 
 
31 
 
    xTaskCreate(BlinkTask2,"Blink2",128,NULL,1,NULL); 
} 
void loop() 
{ 
} 
