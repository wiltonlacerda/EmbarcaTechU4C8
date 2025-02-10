/*
* Por: Wilton Lacerda Silva
* Utilização do Microfone do BitDogLab ligado ao canal ADC2 no GPIO28.
*/


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"

const uint led_pin_red = 13;   // LED vermelho na GPIO13
const uint led_pin_blue = 12;  // LED azul na GPIO12
const uint microfone = 28;     // GPIO28 para ADC2 (Microfone)
const uint limiar_1 = 2080;     // Limiar para o LED vermelho
const uint limiar_2 = 2200;    // Limiar para o LED azul

const uint amostras_por_segundo = 8000; // Frequência de amostragem (8 kHz)

int main() {
    // Inicializa os LEDs
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    // Inicializa o ADC
    adc_init();
    adc_gpio_init(microfone);  // Configura GPIO28 como entrada ADC para o microfone

    // Define o intervalo entre amostras (em microsegundos)
    uint64_t intervalo_us = 1000000 / amostras_por_segundo;

    while (true) {
        // Lê o valor do microfone (canal 2)
        adc_select_input(2);          // Seleciona o canal 2 (GPIO28)
        uint16_t mic_value = adc_read(); // Lê o ADC

        // Controle dos LEDs baseado no valor do microfone
        if ( mic_value > limiar_1 && mic_value < limiar_2 )  {
            gpio_put(led_pin_blue, true);  // Liga o LED azul
            gpio_put(led_pin_red, false); // Desliga o LED vermelho
        } else if (mic_value > limiar_2){
            gpio_put(led_pin_blue, false); // Desliga o LED azul
            gpio_put(led_pin_red, true);  // Liga o LED vermelho        
        }else {
            gpio_put(led_pin_blue, false); // Desliga o LED azul
            gpio_put(led_pin_red, false); // Desliga o LED vermelho
        }

        // Delay para alcançar a frequência de amostragem desejada
        sleep_us(intervalo_us);
    }
}
