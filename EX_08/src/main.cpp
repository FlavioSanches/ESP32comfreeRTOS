/***********************************************************  
*  Exemplo que demostra como enviar valores para uma fila
*  apartir de uma ISR (Interrupt Service Routine)
*  Por Flavio Sanches
*  Data 01/2026
***********************************************************/
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#define LED 2
#define BT 4

QueueHandle_t xFila;
TaskHandle_t xTask1handle;

void vTask1( void * pvParameters );

void IRAM_ATTR trataISR_BT() {
  static int valor;
  valor++;
  xQueueSendFromISR(xFila, &valor, NULL);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BT), trataISR_BT, FALLING);

  xFila = xQueueCreate(5, sizeof(int));
  xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xTask1handle);

}

void loop() {
  digitalWrite(LED, !digitalRead(LED));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTask1( void * pvParameters ){
  int valorRecebido;
  while(1){
    xQueueReceive(xFila, &valorRecebido, portMAX_DELAY);
    Serial.println("BT pressionado: "+String(valorRecebido));

  }



}