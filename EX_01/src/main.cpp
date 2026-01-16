/************************************** 
* Exemplos para criação de tasks
* Esse exemplo exibe como criar tasks no FreeRTOS
* Por: Flávio Sanches
* Data: 01/2026
***************************************/
/*Biblioteca do Arduino*/
#include <Arduino.h>
/*Biblioteca do FreeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/*mapeamento de pinos*/
#define LED 2

/*Variaveis para armazenamento do handle das tasks*/
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

/*protótipos das Task*/

void vTask1( void * pvParameters );
void vTask2( void * pvParameters );

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);

    xTaskCreate(vTask1, "TASK1", configMINIMAL_STACK_SIZE, NULL, 1, &task1Handle);
    xTaskCreate(vTask2, "TASK2", configMINIMAL_STACK_SIZE+1024, NULL, 2, &task2Handle);
}


void loop() {
  vTaskDelay(3000);
}

void vTask1( void * pvParameters ){
    pinMode(LED, OUTPUT);
    while(1){
        digitalWrite(LED, !digitalRead(LED)); // Inverte o estado do LED
        vTaskDelay(pdMS_TO_TICKS(200)); // Aguarda 200 ms;

    }
}

void vTask2( void * pvParameters ){
  int cont = 0;
    while(1){
        Serial.println("TASK 2: "+String(cont++));
        vTaskDelay(pdMS_TO_TICKS(1000)); // Aguarda 1000 ms;
    }
}


