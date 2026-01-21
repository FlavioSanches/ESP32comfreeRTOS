/*********************************************************
* Exemplo para demonstrar po uso de task Notification de
* uma ISR para uma task
* Por: Flávio Sanches
* Data: 01/2026
***************************************/

/*Biblioteca do Arduino*/
#include <Arduino.h>

/*Biblioteca do FreeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED 2
#define BT 4

TaskHandle_t xTaskTrataBTHandle;

void vTaskTrataBT(void *pvParameters);

void callbackBT(){
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  // Passamos o endereço da variável (&xHigherPriorityTaskWoken)
  vTaskNotifyGiveFromISR(xTaskTrataBTHandle, &xHigherPriorityTaskWoken);

  // Se a task acordada tiver prioridade maior, solicita a troca de contexto
  if(xHigherPriorityTaskWoken == pdTRUE) {
    portYIELD_FROM_ISR();
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BT),callbackBT,FALLING);
  xTaskCreate(vTaskTrataBT, "TaskBT", configMINIMAL_STACK_SIZE, NULL, 1, &xTaskTrataBTHandle);
}

void loop(){
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTaskTrataBT(void *pvParameters){
  uint32_t quantidade = 0;
  
  while(1)
  {
    quantidade = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
    Serial.println("Tratando ISR do botão: " + String(quantidade));
    digitalWrite(LED, !digitalRead(LED));
    delay(2000);
  }
}