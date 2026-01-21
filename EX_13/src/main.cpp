/************************************** 
* Exemplo para demonstrar po uso de software timer
* Por: Flávio Sanches
* Data: 01/2026
***************************************/
/*Biblioteca do Arduino*/
#include <Arduino.h>
/*Biblioteca do FreeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

#define LED1 2
#define LED2 15
#define BT 4

TaskHandle_t xTask1;
TaskHandle_t xTimer1,xTimer2;

void vTask1(void *pvParameters);

void callbackTimer1(TimerHandle_t xTimer);
void callbackTimer2(TimerHandle_t xTimer);

void setup()
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BT, INPUT_PULLUP);
  
  xTimer1 = xTimerCreate("TIMER1", pdMS_TO_TICKS(1000), pdTRUE, 0,callbackTimer1);
  xTimer2 = xTimerCreate("TIMER2", pdMS_TO_TICKS(10000), pdFALSE, 0,callbackTimer2);

  xTaskCreate(vTask1, "TASK1", configMINIMAL_STACK_SIZE+1024, NULL, 1, &xTask1);

  xTimerStart(xTimer1, 0);
}

void loop(){
 vTaskDelay(pdMS_TO_TICKS(1000)); 
}

void vTask1(void *pvParameters){
  
  uint8_t debouncingTimer = 0;
  while(1){
    if((digitalRead(BT) == LOW) && (xTimerIsTimerActive(xTimer2) == pdFALSE)){
      debouncingTimer++;
      if(debouncingTimer >= 10){
        debouncingTimer = 0;
        digitalWrite(LED2, HIGH);
        xTimerStart(xTimer2, 0);
        xTimerStop(xTimer1, 0);
        Serial.println("Iniciando o Timer 2 ...");
      }
    }else{
      debouncingTimer = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void callbackTimer1(TimerHandle_t xTimer){
  digitalWrite(LED1, !digitalRead(LED1));
}

void callbackTimer2(TimerHandle_t xTimer){
  digitalWrite(LED2, LOW);
  xTimerStart(xTimer1, 0);
}

