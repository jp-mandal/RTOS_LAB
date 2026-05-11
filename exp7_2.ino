#include<Arduino_FreeRTOS.h> 
#include<queue.h> 
QueueHandle_t myQueue; 
void SenderTask(void *pvParameters); 
void ReceiverTask(void *pvParameters); 
void setup() 
{ 
    Serial.begin(9600); 
    myQueue=xQueueCreate(5,sizeof(int)); 
    if(myQueue!=NULL) 
    { 
        Serial.println("Queue Created Successfully"); 
    } 
    xTaskCreate(SenderTask,"Sender",128,NULL,2,NULL); 
    xTaskCreate(ReceiverTask,"Receiver",128,NULL,1,NULL); 
} 
void loop() 
{ 
} 
void SenderTask(void *pvParameters) 
{ 
    int value=1; 
    while(1) 
    { 
        while(uxQueueSpacesAvailable(myQueue)>0) 
        { 
 
42 
 
            xQueueSend(myQueue,&value,portMAX_DELAY); 
            Serial.print("Sent: "); 
            Serial.println(value); 
            value++; 
            vTaskDelay(500/portTICK_PERIOD_MS); 
        } 
        Serial.println("Queue FULL"); 
        Serial.println(); 
        vTaskDelay(2000/portTICK_PERIOD_MS); 
    } 
} 
void ReceiverTask(void *pvParameters) 
{ 
    int receivedValue; 
    while(1) 
    { 
        if(uxQueueMessagesWaiting(myQueue)==5) 
        { 
            Serial.println("Receiver Started"); 
            while(uxQueueMessagesWaiting(myQueue)>0) 
            { 
                xQueueReceive(myQueue,&receivedValue,portMAX_DELAY); 
                Serial.print("Received: "); 
                Serial.println(receivedValue); 
                vTaskDelay(500/portTICK_PERIOD_MS); 
            } 
            Serial.println("Queue EMPTY"); 
            Serial.println(); 
        } 
        vTaskDelay(100/portTICK_PERIOD_MS); 
    } 
} 
