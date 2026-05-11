#include<Arduino.h> 
SemaphoreHandle_t xCountingSemaphore; 
void Task1(void *pvParameters) 
{ 
    while(1) 
    { 
        if(xSemaphoreTake(xCountingSemaphore,portMAX_DELAY)==pdTRUE) 
        { 
            Serial.print("Task1 Running | Semaphore Count: "); 
            Serial.println(uxSemaphoreGetCount(xCountingSemaphore)); 
            delay(1000); 
        }}} 
void setup() 
{ 
    Serial.begin(115200); 
    xCountingSemaphore=xSemaphoreCreateCounting(5,0); 
    xTaskCreate(Task1,"Task1",2048,NULL,1,NULL); 
    delay(1000); 
    Serial.println("Giving Semaphore 3 Times"); 
    xSemaphoreGive(xCountingSemaphore); 
    Serial.print("Count: "); 
    Serial.println(uxSemaphoreGetCount(xCountingSemaphore)); 
    xSemaphoreGive(xCountingSemaphore); 
    Serial.print("Count: "); 
    Serial.println(uxSemaphoreGetCount(xCountingSemaphore)); 
    xSemaphoreGive(xCountingSemaphore); 
    Serial.print("Count: "); 
    Serial.println(uxSemaphoreGetCount(xCountingSemaphore)); 
    Serial.println("Giving More Than Max Value"); 
    for(int i=0;i<7;i++) 
    { 
        BaseType_t status=xSemaphoreGive(xCountingSemaphore); 
        Serial.print("Attempt "); 
        Serial.print(i+1); 
        if(status==pdTRUE) 
        { 
            Serial.println(" -> Success"); 
        } 
        else 
 
37 
 
        { 
            Serial.println(" -> Failed (Max Reached)"); 
        } 
        Serial.print("Current Count: "); 
        Serial.println(uxSemaphoreGetCount(xCountingSemaphore)); 
        delay(500); 
    }} 
void loop() 
{}
