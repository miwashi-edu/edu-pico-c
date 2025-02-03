#include "pico/cyw43_arch.h"
#include <stdio.h>

#define WIFI_SSID "YourWiFi"
#define WIFI_PASS "YourPassword"

void connect_to_wifi() {
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed!\n");
        return;
    }

    cyw43_arch_enable_sta_mode();
    printf("Connecting to Wi-Fi...\n");

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_MIXED_PSK, 10000)) {
        printf("Wi-Fi connection failed!\n");
    } else {
        printf("Connected to Wi-Fi!\n");
    }
}
