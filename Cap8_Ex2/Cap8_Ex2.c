/*
   Exemplo 2 do EBook pelo prof. Pedro Henrique Almeida Miranda
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define VRX_PIN 26
#define VRY_PIN 27
#define SW_PIN 22

int main()
{
    stdio_init_all();
    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN);
    while (true)
    {
        adc_select_input(0);
        uint16_t vrx_value = adc_read(); // Lê o valor do eixo X, de 0 a 4095.
        adc_select_input(1);
        uint16_t vry_value = adc_read();       // Lê o valor do eixo Y, de 0 a 4095.
        bool sw_value = gpio_get(SW_PIN) == 0; // 0 indica que o botão está pressionado.
        printf("VRX: %u, VRY: %u, SW: %d\n", vrx_value, vry_value, sw_value);
        sleep_ms(500);
    }
    return 0;
}
