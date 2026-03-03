
#include "expand_address.h"
#include "header.h"
#include "print_msg.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  uint32_t message = 0;
  if (!(argc == 3 || argc == 4)) {
    fprintf(stderr, "Usage: %s <binary_file> <patthern> <mode>\n", argv[0]);
    fprintf(stderr, "Mode: expand_address <e>, none <n>(default) %d", argc);
    return 1;
  }
  const char pattern = atoi(argv[2]);
  int mode = 0;
  // printf("%c",argv[3][0]);
  if (argc <= 3) {
    mode = MODE_DEFAULT;
  } else {
    switch ((char)argv[3][0]) {
    case 'e':
      mode = MODE_EXPAND;
      break;
    case 'x':
      mode=MODE_HEX;
      break;
    default:
      mode = MODE_DEFAULT;
      break;
    }
  }
  // printf("pattern %i",pattern);
  const char *filename = argv[1];
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    perror("Error opening file");
    return 1;
  }

  fseek(fp, 0, SEEK_SET);

  ITM_union_t header;
  header.u8 = 0;
  int byte_index = 0;
  int data_size = 0;
  int current_data_size = 0;
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
      //            printf("%x",current_byte & 0xff);
      header.u8 = current_byte;
      //            printf(" (addr:%d siz:%d
      //            id:%d)\n",header.fields.source_adress,
      //            header.fields.data_size,header.fields.identifyer);
      if (header.fields.source_adress == pattern) {
        print_msg(message, current_data_size, mode);
      }
      switch (header.fields.data_size) {
      case 1:
        data_size = 1;
        break;
      case 2:
        data_size = 2;
        break;
      case 3:
        data_size = 4;
        break;
      default:
        continue; // not valid
      }
      current_data_size = data_size;
      message = 0;
      fflush(stdout);

    } else {
      //            	printf("%x_",current_byte & 0xff);
      message = (message << 8) | current_byte;

      data_size--;
    }

    byte_index++;
  }

  fclose(fp);
  return 0;
}
