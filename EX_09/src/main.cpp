/***********************************************************  
*  Exemplo para demonstrar o uso de semafaro binário
*  Por Flavio Sanches
*  Data 01/2026
***********************************************************/
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#define LED 2 

TaskHandle_t xTaskADCHandle;

SemaphoreHandle_t xSemaphore;

void vTaskADC( void * pvParameters );

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  xSemaphore = xSemaphoreCreateBinary();

  if( xSemaphore == NULL ) {
    Serial.println("Não foi possivel criar o semaforo");
    while(1);
  }

  xTaskCreate(vTaskADC, "TaskADC", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xTaskADCHandle);

}

void loop() {
  digitalWrite(LED, !digitalRead(LED));
  Serial.println("Valor do LED:" + String(digitalRead(LED)));
  vTaskDelay(pdMS_TO_TICKS(500));
  xSemaphoreGive( xSemaphore );
}

void vTaskADC( void * pvParameters ) {
  while(1){

    int adcValue;
    xSemaphoreTake( xSemaphore, portMAX_DELAY );
    adcValue = analogRead(34);
    Serial.println("Valor do ADC:" + String(adcValue));
  }
}
