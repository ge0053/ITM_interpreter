#pragma once
#include <stdint.h>
#include <stdio.h>
#include "expand_address.h"

enum Mode {
    MODE_DEFAULT,
    MODE_EXPAND,
    MODE_HEX
};
extern void print_msg(uint32_t data, int length, int mode);
