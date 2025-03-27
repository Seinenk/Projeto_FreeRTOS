#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

#define BUTTON_PIN 5 // Pino do botão
#define LED_PIN 12   // Pino do LED

// Criação de duas filas: uma para transmitir o estado do botão e outra para controlar o LED.
QueueHandle_t buttonQueue;
QueueHandle_t ledQueue;

void setupHardware(void)
{
    stdio_init_all(); // Inicializa a saída serial
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT); // Configura LED como saída
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN); // Configura botão como entrada
    gpio_pull_up(BUTTON_PIN);          // Ativa pull-up interno
}

// Tarefa 1: Leitura do botão, executada a cada 100ms
void vTaskButtonReader(void *pvParameters)
{
    bool previousState = false;
    bool currentState = false;

    while (1)
    {
        currentState = !gpio_get(BUTTON_PIN); // Leitura invertida devido ao pull-up
        if (currentState != previousState)
        {
            // Envia o estado atual para a fila de processamento
            xQueueSend(buttonQueue, &currentState, portMAX_DELAY);
            previousState = currentState;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Tarefa 2: Processamento do estado do botão
void vTaskButtonProcessor(void *pvParameters)
{
    bool btnState;

    while (1)
    {
        if (xQueueReceive(buttonQueue, &btnState, portMAX_DELAY) == pdPASS)
        {
            printf("Processador: Botão %s\n", btnState ? "pressionado" : "liberado");
            // Encaminha o estado para a tarefa de controle do LED
            xQueueSend(ledQueue, &btnState, portMAX_DELAY);
        }
    }
}

// Tarefa 3: Controle do LED, atuando conforme o sinal recebido
void vTaskLedController(void *pvParameters)
{
    bool ledState;

    while (1)
    {
        if (xQueueReceive(ledQueue, &ledState, portMAX_DELAY) == pdPASS)
        {
            gpio_put(LED_PIN, ledState);
            printf("LED %s\n", ledState ? "ligado" : "desligado");
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Pequeno atraso para estabilidade
    }
}

int main()
{
    setupHardware();

    // Criação das filas para comunicação entre tarefas
    buttonQueue = xQueueCreate(5, sizeof(bool));
    ledQueue = xQueueCreate(5, sizeof(bool));
    if (buttonQueue == NULL || ledQueue == NULL)
    {
        printf("Erro na criação das filas.\n");
        while (1)
            ;
    }

    // Criação das tarefas com prioridades diferentes
    xTaskCreate(vTaskButtonReader, "LeituraBotao", 256, NULL, 1, NULL);
    xTaskCreate(vTaskButtonProcessor, "ProcessaBotao", 256, NULL, 2, NULL);
    xTaskCreate(vTaskLedController, "ControlaLED", 256, NULL, 3, NULL);

    vTaskStartScheduler(); // Inicia o escalonador do FreeRTOS

    // O código não deve chegar aqui
    while (1)
        ;
    return 0;
}
