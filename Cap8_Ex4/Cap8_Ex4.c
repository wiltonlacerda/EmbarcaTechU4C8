/*
   Exemplo 4 do EBook pelo prof. Pedro Henrique Almeida Miranda
*/

#include <stdio.h>            
#include "pico/stdlib.h"      
#include "hardware/adc.h"     
#include "hardware/pwm.h"     

#define VRX_PIN 26  
#define LED_PIN 13  

uint pwm_init_gpio(uint gpio, uint wrap) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, wrap);
    
    pwm_set_enabled(slice_num, true);  
    return slice_num;  
}

int main() {
    
    stdio_init_all();

    adc_init(); 

    adc_gpio_init(VRX_PIN); 

    uint pwm_wrap = 4096;  
    uint pwm_slice = pwm_init_gpio(LED_PIN, pwm_wrap);  
    
    uint32_t last_print_time = 0; 

    while (true) {
        adc_select_input(0);  
        uint16_t vrx_value = adc_read(); 

        pwm_set_gpio_level(LED_PIN, vrx_value); 

        float duty_cycle = (vrx_value / 4095.0) * 100;  

        
        uint32_t current_time = to_ms_since_boot(get_absolute_time());  
        if (current_time - last_print_time >= 1000) {  
            printf("VRX: %u\n", vrx_value); 
            printf("Duty Cycle LED: %.2f%%\n", duty_cycle); 
            last_print_time = current_time;  
        }

        sleep_ms(100);  
    }

    return 0;  
}
