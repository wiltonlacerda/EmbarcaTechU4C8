/*
   Exemplo 1 do EBook pelo prof. Pedro Henrique Almeida Miranda
*/


#include <stdio.h>            
#include "pico/stdlib.h"      
#include "hardware/adc.h"     

int main() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);   // Inicializa o GPIO 26 para o ADC
    adc_select_input(0); // Seleciona o canal 0, GPIO26 do ADC

    while (true) {
        uint16_t adc_value = adc_read();
        printf("Valor do ADC: %u\n", adc_value);
        sleep_ms(500);
    }
    return 0;
}
