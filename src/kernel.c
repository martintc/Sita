#include "io.h"

int main()
{
  uart_init();
  write_to_uart("hello world");
  while(1);

  return 0;
  
}
