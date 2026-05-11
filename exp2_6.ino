#include<Arduino_FreeRTOS.h> 
void LLF_Task1(void *pvParameters); 
void LLF_Task2(void *pvParameters); 
void setup() 
{ 
    Serial.begin(9600); 
    xTaskCreate(LLF_Task1,"LLF1",128,NULL,2,NULL); 
    xTaskCreate(LLF_Task2,"LLF2",128,NULL,1,NULL); 
} 
void loop() 
{ 
} 
void LLF_Task1(void *pvParameters) 
{ 
    while(1) 
    { 
        Serial.println("LLF Task 1 - Least Laxity"); 
        vTaskDelay(200/portTICK_PERIOD_MS); 
    } 
} 
void LLF_Task2(void *pvParameters) 
{ 
    while(1) 
    { 
        Serial.println("LLF Task 2"); 
        vTaskDelay(800/portTICK_PERIOD_MS); 
    } 
}
