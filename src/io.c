#include "io.h"
#define PBASE 0xFE000000
#define GPIO_REG_BASE (PBASE + 0x00200000)
#define AUX_BASE (PBASE + 0x00215000)

#define ALT5 0x2

// resistor enums
enum {
  PULL_NONE = 0,
  PULL_DOWN = 1,
  PULL_UP = 2,
};

// enumerations for GPIO registers
enum {
  GPFSEL0 = GPIO_REG_BASE + 0x00,
  GPFSEL1 = GPIO_REG_BASE + 0x04,
  GPFSEL2 = GPIO_REG_BASE + 0x0c,
  GPFSEL3 = GPIO_REG_BASE + 0x10,
  GPFSEL4 = GPIO_REG_BASE + 0x14,
  GPFSEL5 = GPIO_REG_BASE + 0x18,
  GPSET0 = GPIO_REG_BASE + 0x1c,
  GPSET1 = GPIO_REG_BASE + 0x20,
  GPCLR0 = GPIO_REG_BASE + 0x28,
  GPCLR1 = GPIO_REG_BASE + 0x2c,
  GPLEV0 = GPIO_REG_BASE + 0x34,
  GPLEV1 = GPIO_REG_BASE + 0x38,
  GPEDS0 = GPIO_REG_BASE + 0x40,
  GPEDS1 = GPIO_REG_BASE + 0x44,
  GPREN0 = GPIO_REG_BASE + 0x4c,
  GPREN1 = GPIO_REG_BASE + 0x50,
  GPFEN0 = GPIO_REG_BASE + 0x58,
  GPFEN1 = GPIO_REG_BASE + 0x5c,
  GPHEN0 = GPIO_REG_BASE + 0x64,
  GPHEN1 = GPIO_REG_BASE + 0x68,
  GPLEN0 = GPIO_REG_BASE + 0x70,
  GPLEN1 = GPIO_REG_BASE + 0x74,
  GPAREN0 = GPIO_REG_BASE + 0x7c,
  GPAREN1 = GPIO_REG_BASE + 0x80,
  GPAFEN0 = GPIO_REG_BASE + 0x88,
  GPAFEN1 = GPIO_REG_BASE + 0x8c,
  GPIO_PUP_PDN_CNTRL_REG0 = GPIO_REG_BASE + 0xe4,
  GPIO_PUP_PDN_CNTRL_REG1 = GPIO_REG_BASE + 0xe8,
  GPIO_PUP_PDN_CNTRL_REG2 = GPIO_REG_BASE + 0xec,
  GPIO_PUP_PDN_CNTRL_REG3 = GPIO_REG_BASE + 0xf0,
};

// mini uart enums for AUX
enum {
  AUX_IRQ = AUX_BASE,
  AUX_ENABLES = AUX_BASE + 0x04,
  AUX_MU_IO_REG = AUX_BASE + 0x40,
  AUX_MU_IER_REG = AUX_BASE + 0x44,
  AUX_MU_IIR_REG = AUX_BASE + 0x48,
  AUX_MU_LCR_REG = AUX_BASE + 0x4c,
  AUX_MU_MCR_REG = AUX_BASE + 0x50,
  AUX_MU_LSR_REG = AUX_BASE + 0x54,
  AUX_MU_MSR_REG = AUX_BASE + 0x58,
  AUX_MU_SCRATCH = AUX_BASE + 0x5c,
  AUX_MU_CNTL_REG = AUX_BASE + 0x60,
  AUX_MU_STAT_REG = AUX_BASE + 0x64,
  AUX_MU_BAUD_REG = AUX_BASE + 0x68,
};

void delay() {
  volatile int i = 0;
  while (i < 150) {
    i++;
  }
}

void write_to_register(long reg, unsigned int val) { 
  *(volatile unsigned int *)reg = val; 
}

unsigned int read_from_register(long reg) {
  return *(volatile unsigned int *)reg;
}

void clear_register_32(long reg)
{
  *(volatile unsigned int *)reg = 0x0000;
}

void modify_register(long reg, unsigned int value)
{
  *(volatile unsigned int *)reg |= value;
}

void initialize_uart_pins() {
  // pull up/pull down register
  modify_register(GPIO_PUP_PDN_CNTRL_REG0, (0b00 << 30));
  delay();
  modify_register(GPIO_PUP_PDN_CNTRL_REG0, (0b00 << 28));
  delay();
  clear_register_32(GPFSEL1);
  modify_register(GPFSEL1, (0x2 << 12));
  modify_register(GPFSEL1, (0x2 << 15));
  write_to_register(GPSET0, (1 << 14));
  modify_register(GPIO_PUP_PDN_CNTRL_REG0, (0 << 28) | (0 << 30));
  delay();
}
  
void uart_init() {
    // set gpio pins to ALT15
  initialize_uart_pins();
  /* write_to_register(AUX_IRQ, 0x00); */
  // enable the mini UART
  write_to_register(AUX_ENABLES, 0x01);
  // no interrupts needed
  write_to_register(AUX_MU_CNTL_REG, 0x00);
  write_to_register(AUX_MU_IER_REG, 0x00);
  write_to_register(AUX_MU_LCR_REG, 3);
  write_to_register(AUX_MU_MCR_REG, 0x00);
  write_to_register(AUX_MU_IER_REG, 0x00);
  write_to_register(AUX_MU_IIR_REG, 0xc6);
  write_to_register(AUX_MU_BAUD_REG, 541); // 115200 baud rate
  // enable RX/TX
  write_to_register(AUX_MU_CNTL_REG, 0b11);
}

unsigned int is_ready_write() {
  return read_from_register(AUX_MU_LSR_REG) & (1 << 5);
}

void write_byte(unsigned char b) {
  while(!is_ready_write());
  write_to_register(AUX_MU_IO_REG, (unsigned int)b);
}

void write_to_uart(char *data) {
  while(*data) {
    write_byte(*data++);
  }
}

void write_char(unsigned char b) {
  write_byte(b & 0xFF);
}

unsigned int is_ready_to_read() {
  return read_from_register(AUX_MU_LSR_REG) & 0x01;
}

unsigned int is_data_overan() {
  return read_from_register(AUX_MU_LSR_REG) & (0x01 << 1);
}

unsigned char read_byte() {
  return (unsigned char)read_from_register(AUX_MU_IO_REG);
}

