/***********************************************************  
*  Exemplo para demosntrar o uso de semafaro contador dentro
* de uma ISR
*  Por Flavio Sanches
*  Data 01/2026
***********************************************************/
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#define LED 2 
#define BT 4


SemaphoreHandle_t semafarocontador;

TaskHandle_t xTaskTrataBTHandle;

void vTaskTrataBT( void * pvParameters );

void ISR_Callback(){
  BaseType_t xHighPriorityTaskWoken = pdTRUE;
  xSemaphoreGiveFromISR( semafarocontador, &xHighPriorityTaskWoken );
  if( xHighPriorityTaskWoken  == pdTRUE ){ 
    portYIELD_FROM_ISR();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BT),ISR_Callback, FALLING);
  
  semafarocontador = xSemaphoreCreateCounting(255,0);
  xTaskCreate(vTaskTrataBT, "Task BT", configMINIMAL_STACK_SIZE + 1024, NULL, 3, &xTaskTrataBTHandle);
}

void loop() {
  digitalWrite(LED, HIGH);
  vTaskDelay(pdMS_TO_TICKS(10));
  digitalWrite(LED, LOW);
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTaskTrataBT( void * pvParameters ) {
  UBaseType_t x;

  while(1){
    xSemaphoreTake( semafarocontador, portMAX_DELAY );
    Serial.print("Tratando a ISR do BT: ");

    x = uxSemaphoreGetCount( semafarocontador );

    Serial.println(x);
    delay(1000);
    
  }
}