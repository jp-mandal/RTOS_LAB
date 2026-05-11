#include "FreeRTOS.h" 
#include "task.h" 
#include "semphr.h" 
#include <stdio.h> 
SemaphoreHandle_t S; 
SemaphoreHandle_t T; 
void Task1(void *argument) 
{ 
    while(1) 
    { 
        if(xSemaphoreTake(S,portMAX_DELAY)==pdTRUE) 
        { 
 
60 
 
            printf("Task 1 using Printer\r\n"); 
            vTaskDelay(pdMS_TO_TICKS(500)); 
            printf("Task 1 Giving T\r\n"); 
            xSemaphoreGive(T); 
        } 
} 
} 
void Task2(void *argument) 
{ 
    while(1) 
    { 
        if(xSemaphoreTake(T,portMAX_DELAY)==pdTRUE) 
        { 
            printf("Task 2 using Printer\r\n"); 
            vTaskDelay(pdMS_TO_TICKS(500)); 
            printf("Task 2 Giving S\r\n"); 
            xSemaphoreGive(S); 
        } 
} 
} 
void setup() 
{ 
    S=xSemaphoreCreateBinary(); 
    T=xSemaphoreCreateBinary(); 
    xSemaphoreGive(S); 
    xTaskCreate(Task1,"Task1",128,NULL,2,NULL); 
    xTaskCreate(Task2,"Task2",128,NULL,1,NULL); 
} 
