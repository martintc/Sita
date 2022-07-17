#include "io.h"

int main()
{
  uart_init();
  write_to_uart("Hello");
  while(1);

  return 0;

}
