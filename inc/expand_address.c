#include "expand_address.h"
int expand_address(uint16_t data){
    return (0x8000000 |(data <<2));
}

