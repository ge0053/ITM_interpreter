#include "expand_address.h"
#include <stdio.h>
int expand_address(uint16_t data){
    return (0x08000000 |(data <<2));
}

