#include"print_msg.h"

void print_msg(uint32_t data, int length, int mode){
    switch (mode)
    {
    case MODE_EXPAND:
        if (length ==2){
        printf("%x\n",expand_address(__builtin_bswap16(data)));
        
        }else if(length==4){
            printf("%x\n",expand_address(__builtin_bswap32(data) & 0x7fff));
            printf("%x\n\n",expand_address((__builtin_bswap32(data)>> (16-1)) & 0x7fff));
            
            
        }
        break;
    default:
     for (int i=0; i<length;i++){
        char character=data >>(8*i);
        printf("%c",character);
     }
        break;
    }
}
