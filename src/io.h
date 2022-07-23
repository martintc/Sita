void uart_init();
void write_to_uart(char *data);
void write_char(unsigned char b);
unsigned int is_ready_to_read();
unsigned char read_byte();
void write_to_register(long reg, unsigned int val);
unsigned int read_from_register(long reg);
