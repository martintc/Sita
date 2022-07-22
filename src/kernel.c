#include "io.h"

int main()
{
  uart_init();
  write_to_uart("Hello");
  while(1) {
    if(is_ready_to_read()) {
      unsigned char data = read_byte();
      write_char(data);
    }
  }

  return 0;

}
