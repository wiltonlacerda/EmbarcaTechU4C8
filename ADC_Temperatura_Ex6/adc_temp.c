/*
 * Por: Wilton Lacerda Silva
 * 
 * Demonstração de funcionamento do ADC do RP2040 (Pico).
 * 
 * Determina a temperatura interna do RP2040 (Pico) utilizando o sensor de temperatura interno.
 * 
 *   Ler 4.9.5. Temperature Sensor do Datasheet do RP2040 (Pico) para mais informações.
 * 
 */




#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main() {
    // Inicializa a comunicação serial (para printf)
    stdio_init_all();

    // Inicializa o ADC
    adc_init();

    // Seleciona o canal do sensor de temperatura (canal 4)
    adc_select_input(4);

    // Aguarda um pouco para estabilizar o ADC
    sleep_ms(500);

    while (true) {
        // Lê o valor bruto do ADC (12 bits)
        uint16_t raw_value = adc_read();

        // Converte o valor bruto para tensão (3.3V de referência)
        float voltage = raw_value * 3.3f / (1 << 12);

        // Converte a tensão para temperatura em graus Celsius
        // Fórmula ajustada
        float referencia = 0.5928f;
        float coeficiente = 0.0021f;
        float temperatura_celsius = 27.0f - (voltage - referencia) / coeficiente;

        // Exibe os valores para depuração
        printf("Valor bruto do ADC: %d\n", raw_value);
        printf("Tensão: %.3f V\n", voltage);
        printf("Temperatura interna: %.2f °C\n", temperatura_celsius);

        // Aguarda 1 segundo antes de ler novamente
        sleep_ms(1000);
    }

    return 0;
}