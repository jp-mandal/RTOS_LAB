#include<Arduino_FreeRTOS.h> 
#include<timers.h> 
#define LED_PIN 7 
TimerHandle_t xTimer; 
bool ledState=false; 
void vTimerCallback(TimerHandle_t xTimer) 
{ 
    ledState=!ledState; 
    digitalWrite(LED_PIN,ledState); 
    Serial.println("Software Timer Running"); 
} 
void setup() 
{ 
    pinMode(LED_PIN,OUTPUT); 
    Serial.begin(9600); 
    
xTimer=xTimerCreate("LEDTimer",pdMS_TO_TICKS(1000),pdTRUE,(void*)0,vTimerCall
back); 
    if(xTimer!=NULL) 
 
50 
 
    { 
        xTimerStart(xTimer,0); 
    } 
} 
void loop() 
{ 
}
