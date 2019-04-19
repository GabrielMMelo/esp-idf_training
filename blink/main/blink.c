#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BLINK_GPIO CONFIG_BLINK_GPIO  // set as 5 with 'menuconfig'
#define BLINK_GPIO2 18

void blink_cpu0_task(void *pvParameter)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void blink_cpu1_task(void *pvParameter)
{
    gpio_pad_select_gpio(BLINK_GPIO2);
    gpio_set_direction(BLINK_GPIO2, GPIO_MODE_OUTPUT);
    while(1) {
        gpio_set_level(BLINK_GPIO2, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO2, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    xTaskCreatePinnedToCore(&blink_cpu0_task, "blink_cpu0_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(&blink_cpu1_task, "blink_cpu1_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL, 1);
}
