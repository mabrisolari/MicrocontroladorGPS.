
#include "pico/stdlib.h"
#include <stdio.h>

// Definição dos pinos
#define LIXO_SENSOR_PIN 2  
#define BOTAO_A_PIN 5    
#define BOTAO_B_PIN 6     
#define LED_VERMELHO_PIN 13 
#define GPS_RX_PIN 3        // Pino RX do módulo GPS
#define GPS_TX_PIN 4        // Pino TX do módulo GPS
#define LORAWAN_CS_PIN 7    // Pino de Chip Select do LoRaWAN (se aplicável)

// Função principal
int main() {
    stdio_init_all();  // Inicializa a saída padrão para printf

    // Inicializa os pinos dos sensores, botões e LED
    gpio_init(LIXO_SENSOR_PIN);
    gpio_set_dir(LIXO_SENSOR_PIN, GPIO_IN);
    gpio_pull_up(LIXO_SENSOR_PIN);

    gpio_init(BOTAO_A_PIN);
    gpio_set_dir(BOTAO_A_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_A_PIN);

    gpio_init(BOTAO_B_PIN);
    gpio_set_dir(BOTAO_B_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_B_PIN);

    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);

    // Inicializa os pinos do módulo GPS
    gpio_init(GPS_RX_PIN);
    gpio_set_dir(GPS_RX_PIN, GPIO_IN);

    gpio_init(GPS_TX_PIN);
    gpio_set_dir(GPS_TX_PIN, GPIO_OUT);

    // Inicializa o pino do módulo de comunicação (Wi-Fi/LoRaWAN)
    gpio_init(LORAWAN_CS_PIN);
    gpio_set_dir(LORAWAN_CS_PIN, GPIO_OUT);

    bool botao_a_pressionado = false;
    bool botao_b_pressionado = false;

    while (true) {
        // Verifica o nível de lixo
        if (gpio_get(LIXO_SENSOR_PIN) == 0) {  
            printf("Mensagem enviada: Lixeira cheia\n");
            // Enviar notificação para a central de coleta (implementar comunicação)
        }

        // Verifica se o botão A foi pressionado
        if (gpio_get(BOTAO_A_PIN) == 0) {  
            if (!botao_a_pressionado) {
                printf("Botão A pressionado: Lixeira A cheia\n");
                gpio_put(LED_VERMELHO_PIN, true);  
                botao_a_pressionado = true;
            }
        } else {
            botao_a_pressionado = false;  
        }

        // Verifica se o botão B foi pressionado
        if (gpio_get(BOTAO_B_PIN) == 0) {  
            if (!botao_b_pressionado) {
                printf("Botão B pressionado: Lixeira B cheia\n");
                gpio_put(LED_VERMELHO_PIN, true);  
                botao_b_pressionado = true;
            }
        } else {
            botao_b_pressionado = false;  
        }

        sleep_ms(50);  // Debounce
    }
}
