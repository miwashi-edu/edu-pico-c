#ifndef UPDATE_FIRMWARE_H
#define UPDATE_FIRMWARE_H

#include <stddef.h>
#include <stdint.h>

void check_for_firmware_update();

void write_firmware_to_flash(const uint8_t *data, size_t len);

#endif
