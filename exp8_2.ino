without structures – no need of using time stamp 
#include<Arduino_FreeRTOS.h> 
#include<queue.h> 
typedef struct 
{ 
    int value; 
    unsigned long timestamp; 
}MailData; 
QueueHandle_t mailbox; 
void SenderTask(void *pvParameters) 
{ 
    MailData data; 
    data.value=0; 
    while(1) 
    { 
        data.value++; 
 
47 
 
        data.timestamp=millis(); 
        xQueueOverwrite(mailbox,&data); 
        vTaskDelay(1000/portTICK_PERIOD_MS); 
    } 
} 
void ReceiverTask(void *pvParameters) 
{ 
    MailData receivedData; 
    while(1) 
    { 
        if(xQueueReceive(mailbox,&receivedData,portMAX_DELAY)==pdPASS) 
        { 
            Serial.print("Value: "); 
            Serial.print(receivedData.value); 
            Serial.print("  Timestamp: "); 
            Serial.println(receivedData.timestamp); 
        } 
    } 
} 
void setup() 
{ 
    Serial.begin(9600); 
    mailbox=xQueueCreate(1,sizeof(MailData)); 
    xTaskCreate(SenderTask,"Sender",128,NULL,1,NULL); 
    xTaskCreate(ReceiverTask,"Receiver",128,NULL,1,NULL); 
} 
void loop() 
{ 
} 
