#include "expand_address.h"
int expand_address(uint16_t data){
    
    return (0x08000000 |(__builtin_bswap16(data) <<2));
}

