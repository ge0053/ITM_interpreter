
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "header.h"
#include "expand_address.h"
#include "print_msg.h"

int main(int argc, char *argv[]) {
    uint32_t message;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <binary_file> <patthern> <mode>\n", argv[0]);
        fprintf(stderr,"Mode: expand_address <e>, none <n>(default)");
        return 1;
    }
    const char pattern=atoi(argv[2]);
    int mode =0;
    switch ((char)argv[3])
    {
    case 'e':
        mode=MODE_EXPAND;
        break;
    
    default:
        mode=MODE_DEFAULT;
        break;
    }
    printf("pattern %i",pattern);
    const char *filename = argv[1];
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    fseek(fp, 0, SEEK_SET);

    ITM_union_t header;
    header.u8=0;
    int byte_index = 0;
    int data_size=0;
    int current_data_size=0;
    while (1) {
        int c = fgetc(fp);
        if (c == EOF) {
            // No new data yet, wait and retry
            clearerr(fp);
            usleep(1000000); // 1 second delay
            continue;
        }
        

        uint8_t current_byte = (uint8_t)c;
        if (data_size == 0) {
            header.u8 = current_byte;
            print_msg(message,current_data_size,mode);
            data_size=header.fields.data_size;
            current_data_size=header.fields.data_size;
            
            message=0;
        } else {
            if (header.fields.source_adress == pattern) {
                message=(message<<8)|current_byte;
                //printf("%c", current_byte);
                //fflush(stdout);
                
            }
            data_size--;           
        }

        byte_index++;
    }

    fclose(fp);
    return 0;
}
