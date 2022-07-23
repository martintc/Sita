#include "io.h"
#include "util.h"
#include "agni.h"

int main()
{
  uart_init();
  /* write_to_uart("Hello"); */
  /* while(1) { */
  /*   if(is_ready_to_read()) { */
  /*     unsigned char data = read_byte(); */
  /*     write_char(data); */
  /*   } */
  /* } */

  write_to_uart("Hello");

  while(1) {
    while(!is_ready_to_read());
    // retrieve the method
    // first byte
    unsigned char method = read_byte();
    handle_method(method);
  }
  
  return 0;

}
