/***********************************************************  
*  Exemplo que demostra como criar uma fila, adcionar e ler
*  dados da fila atraves de duas tasks
*  Por Flavio Sanches
*  Data 01/2026
***********************************************************/
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#define LED 2
QueueHandle_t xFila;
TaskHandle_t xTask1Handle,xTask2Handle;

void vTask1( void * pvParameters );
void vTask2( void * pvParameters );

void setup() {

  BaseType_t xReturned;
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
 
  xFila = xQueueCreate(5,sizeof(int));

  if(xFila == NULL){
    Serial.println("Nao foi possivel criar a fila");
    while(1);
  }

  xReturned = xTaskCreate(vTask1, "TASK1", configMINIMAL_STACK_SIZE+1024, NULL, 1, &xTask1Handle);
  
  if(xReturned == pdFAIL){
    Serial.println("Nao foi possivel criar a Task 1");
    while(1);
  }

  xReturned = xTaskCreate(vTask2, "TASK2", configMINIMAL_STACK_SIZE+1024, NULL, 1, &xTask2Handle);

   if(xReturned == pdFAIL){
    Serial.println("Nao foi possivel criar a Task 2");
    while(1);
  }
}

void loop() {
  digitalWrite(LED, !digitalRead(LED));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTask1( void * pvParameters ){
  int cont = 0;
  while(1){
    if(cont < 15){
    xQueueSend(xFila, &cont, portMAX_DELAY);
    cont++;
    }else{
      cont = 0;
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}
void vTask2( void * pvParameters ){
  int valorRecebido = 0;
 while(1){
  if(xQueueReceive(xFila, &valorRecebido, pdMS_TO_TICKS(1000)) == pdTRUE){
    Serial.println("Valor recebido: " + String(valorRecebido));
  }else{
    Serial.println("TIMEOUT");
  }
 }
}