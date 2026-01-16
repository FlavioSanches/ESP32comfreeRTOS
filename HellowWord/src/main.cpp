#include <Arduino.h>

// A maioria das placas ESP32 usa o pino 2 para o LED interno.
// Se a sua não acender, tente mudar para o pino 5 ou 18.
#define LED_PIN 2
#define BOTAO_PIN 4
#define POTECIOMENTRO_PIN 34

int sensorValue = 0; // Variável para armazenar o valor lido do potenciômetro
float voltage; // Variável para armazenar a tensão calculada

void setup() {
    // Configura o pino do LED como saída
    pinMode(LED_PIN, OUTPUT);
    pinMode(BOTAO_PIN, INPUT_PULLUP);
    pinMode(POTECIOMENTRO_PIN, INPUT);
    Serial.begin(115200);
    Serial.println("Sistema iniciado. Piscando LED...");
}

void loop() {
    // Liga o LED (HIGH é o nível de tensão alto)
    if(digitalRead(BOTAO_PIN) == LOW){
        Serial.println("Botão pressionado! LED ligado.");
        digitalWrite(LED_PIN, HIGH);
    } else {
        Serial.println("Botão solto! LED desligado.");
        digitalWrite(LED_PIN, LOW);
    }

sensorValue = analogRead(POTECIOMENTRO_PIN); // leitura da entrada analógica A0
//voltage = sensorValue * (3.3 / 1024); // cálculo da tensão
//Serial.print("Tensão do potenciometro: "); // imprime no monitor serial
//Serial.print(voltage); // imprime a tensão
 Serial.print(" Valor: "); // imprime no monitor serial
Serial.println(sensorValue); // imprime o valor
delay(500); // atraso de 500 milisegundos

}