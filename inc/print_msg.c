#include"print_msg.h"

void print_msg(uint32_t data, int length, int mode){
    switch (mode)
    {
    case MODE_EXPAND:
        if (length ==2){
        printf("%x\n",expand_address(data));
        
        }else if(length==4){
            printf("%x\n",expand_address(data & 0xffff));
            printf("%x\n\n",expand_address((data>> 16)&0xffff));
            
            
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
