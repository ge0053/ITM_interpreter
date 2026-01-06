#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct __attribute__((packed))
{
    uint8_t data_size:2;
    uint8_t identifyer:1;
    uint8_t source_adress:5;
    
    

}ITM_instrumentation_t;


typedef union {
    ITM_instrumentation_t fields;
    uint8_t u8;
} ITM_union_t;


