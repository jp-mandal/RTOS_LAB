#include<Arduino_FreeRTOS.h> 
void EDF_Task1(void *pvParameters); 
void EDF_Task2(void *pvParameters); 
void setup() 
{ 
    Serial.begin(9600); 
    xTaskCreate(EDF_Task1,"EDF1",128,NULL,2,NULL); 
    xTaskCreate(EDF_Task2,"EDF2",128,NULL,1,NULL); 
} 
void loop() 
{ 
} 
void EDF_Task1(void *pvParameters) 
{ 
    while(1) 
    { 
        Serial.println("EDF Task 1 - Earlier Deadline"); 
        vTaskDelay(300/portTICK_PERIOD_MS); 
    } 
 
21 
 
} 
void EDF_Task2(void *pvParameters) 
{ 
    while(1) 
    { 
        Serial.println("EDF Task 2 - Later Deadline"); 
        vTaskDelay(700/portTICK_PERIOD_MS); 
    } 
}
