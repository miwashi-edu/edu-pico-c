#include <stdio.h>
#include "pico/stdlib.h"
#include "wifi_connect.h"
#include "update_firmware.h"

int main() {
    stdio_init_all();
    printf("Starting Pico W...\n");

    connect_to_wifi();  // Connect to Wi-Fi
    check_for_firmware_update();  // Download & apply updates if available

    while (1) {
        printf("Pico W Running...\n");
        sleep_ms(5000);
    }
}
