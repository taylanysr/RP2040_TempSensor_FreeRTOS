/*
 * Name        : main.c 
 * Author      : Taylan Yasar 
 * Version     : 1.0
 * Date        : 11.12.2021
 * Description : Temperature sensor control on FreeRTOS
 */

// Standard includes.
#include <stdio.h>

// FreeRTOS includes.
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"


int main() 
{
    stdio_init_all();                                       // Standart init

    // Configure ADC
    adc_init();                                             // ADC init
    adc_set_temp_sensor_enabled(true);                      // Temperature sensor active
    adc_select_input(4);                                    // The currently selected input channel. 0...3 are GPIOs 26...29 respectively. Input 4 is the onboard temperature sensor.


    // The temperature is written on the screen every 1 second.
    while(1){
        uint16_t raw = adc_read();                          // Value read from ADC.                    
        const float conversion_factor = 3.3f / (1<<12);     
        float result = raw * conversion_factor;
        float temp = 27 - (result -0.706)/0.001721;
        printf("Temp = %f C\n", temp);                      // Write the temperature on the screen
        sleep_ms(1000);                                     // 2 seconds delay
    }

        /*
        The temperature sensor measures the Vbe voltage of a biased bipolar diode, connected to the fifth ADC channel (AINSEL=4). 
        Typically, Vbe = 0.706V at 27 degrees C, with a slope of -1.721mV per degree. 
        Therefore the temperature can be approximated as follows:
        
        T = 27 - (ADC_voltage - 0.706)/0.001721

        */



}
