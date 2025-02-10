/*
   Exemplo 3 do EBook pelo prof. Pedro Henrique Almeida Miranda
*/

#include <stdio.h>             
#include "pico/stdlib.h"       
#include "hardware/adc.h"      


#define VRX_PIN 26   
#define VRY_PIN 27   
#define SW_PIN 22    
#define LED1_PIN 11  
#define LED2_PIN 13  
#define LED3_PIN 12  

int main() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(VRX_PIN); 
    adc_gpio_init(VRY_PIN); 
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN); 
    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);
    gpio_put(LED1_PIN, false); 
    gpio_init(LED2_PIN);
    gpio_set_dir(LED2_PIN, GPIO_OUT);
    gpio_put(LED2_PIN, false); 
    gpio_init(LED3_PIN);
    gpio_set_dir(LED3_PIN, GPIO_OUT);
    gpio_put(LED3_PIN, false);

    while (true) {
        adc_select_input(0); 
        uint16_t vrx_value = adc_read(); 
        adc_select_input(1); 
        uint16_t vry_value = adc_read(); 
        bool sw_value = gpio_get(SW_PIN) == 0; 
        if (vrx_value > 2100) {
            gpio_put(LED1_PIN, true); 
        } else {
            gpio_put(LED1_PIN, false);
        }
        if (vry_value > 2100) {
            gpio_put(LED2_PIN, true); 
        } else {
            gpio_put(LED2_PIN, false); 
        }
        if (sw_value) { 
            gpio_put(LED3_PIN, true); 
        } else {
            gpio_put(LED3_PIN, false);
        }
        printf("VRX: %u, VRY: %u, SW: %d\n", vrx_value, vry_value, sw_value);
        sleep_ms(500);
    }
    return 0;
}
