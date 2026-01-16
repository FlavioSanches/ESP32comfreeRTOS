/************************************** 
* Exemplo para passagem de paramentos na criacão da task
* Por: Flávio Sanches
* Data: 01/2026
***************************************/
/*Biblioteca do Arduino*/
#include <Arduino.h>
/*Biblioteca do FreeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/*mapeamento de pinos*/
#define LED1 2
#define LED2 15

/*Variaveis para armazenamento do handle das tasks*/
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;

/*protótipos das Task*/

void vTaskBlink( void * pvParameters );
void vTask2( void * pvParameters );

/*variaveis auxiliares*/
int valor = 500;

void setup() {
    Serial.begin(9600);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    xTaskCreate(vTaskBlink, "TASK1", configMINIMAL_STACK_SIZE, (void*)LED1, 1, &task1Handle);
    xTaskCreate(vTask2, "TASK2", configMINIMAL_STACK_SIZE+1024, (void*)valor, 2, &task2Handle);
    xTaskCreate(vTaskBlink, "TASK1", configMINIMAL_STACK_SIZE, (void*)LED2, 1, &task3Handle);
}


void loop() {
  vTaskDelay(3000);
}

void vTaskBlink( void * pvParameters )
{
    int pin = (int) pvParameters;
    pinMode(pin, OUTPUT);
    while(1)
    {
        digitalWrite(pin, !digitalRead(pin)); // Inverte o estado do LED
        vTaskDelay(pdMS_TO_TICKS(200)); // Aguarda 200 ms;

    }
}

void vTask2( void * pvParameters ){
  int cont = (int) pvParameters;
    while(1){
        Serial.println("TASK 2: "+String(cont++));
        vTaskDelay(pdMS_TO_TICKS(1000)); // Aguarda 1000 ms;
    }
}


