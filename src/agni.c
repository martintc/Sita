#include "io.h"
#include "util.h"

long get_size() {
  int i = 7;
  long size = 0;
  // loop for the 8 bytes expected for size
  while (i > -1) {
    // wait while a byte is not ready to receive
    while(!is_ready_to_read());
    unsigned char data = read_byte();
    size |= (data << get_position_in_long(i));
    i--;
  }
  return size;
}

void return_failure() {
  write_char(0x02); // failure status
  // send 0 as the size
  for (int i = 0; i < 8; i++) {
    write_char(0x00);
  }
}

void method_one() {
  // get size of message first
  long size = get_size();

  // if size is greater than 5, deviated from spec
  if (size > 5) {
    // first, clear buffer
    for (long i = 0; i < size; i++) {
      read_byte();
    }
    return_failure();
  }
  // create buffer for message body
  unsigned char buffer[size];
  // fill buffer
  for (long i = 0; i < size; i++) {
    // wait for a byte to read
    while(!is_ready_to_read());
    // read byte into buffer
    buffer[i] = read_byte();
  }
  /* if(!compare_strings(buffer, (unsigned char*)"Hello")) { */
  /*   return_failure(); */
  /* } */
  write_char(0x01);
  for(int i = 0; i < 7; i++) {
    write_char(0x00);
  }
  write_char(0x05);
  write_to_uart("Hello");
}


void handle_method(unsigned char method) {
  switch(method) {
  case 0x01:
    method_one();
  case 0x02:
    break;
  case 0x03:
    break;
  case 0x04:
    break;
  case 0x05:
    break;
  }
}
