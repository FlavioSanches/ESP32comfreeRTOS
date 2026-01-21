/*****************************************************************
* Exemplo para demonstrar o uso de MUTEX para acesso a recursos 
* e a inversão de priorirdade
* Por: Flavio Sanches
* Data: 01/2026
*****************************************************************/

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#define LED 2

SemaphoreHandle_t mutex;

TaskHandle_t Task1Handle, Task2Handle;

void vTask1(void *pvParameters);

void vTask2(void *pvParameters);


void enviaInformacao(int i) {
    Serial.println("Enviando informacao da Task: "+String(i));
  
}
  
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  mutex = xSemaphoreCreateMutex();

  xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE+1024, NULL, 1, &Task1Handle);
  xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE+1024, NULL, 4, &Task2Handle);

}

void loop() {
  digitalWrite(LED, HIGH);
  vTaskDelay(pdMS_TO_TICKS(100));
  digitalWrite(LED, LOW);
  vTaskDelay(pdMS_TO_TICKS(1000));
  
}



void vTask1(void *pvParameters) {

  while(1) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    enviaInformacao(1);
    delay(2000);
    xSemaphoreGive(mutex);
    vTaskDelay(10);
  }
}

void vTask2(void *pvParameters) {
  while(1) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    enviaInformacao(2);
    delay(2000);
    xSemaphoreGive(mutex);
    vTaskDelay(10);
  }
}