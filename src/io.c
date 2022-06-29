#define GPIO_REG_BASE 0x7e200000

#define UART_BASE 0x7e201000 // for UART0

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

// GPFSEL0 FSELn field determines the functionality of the nth GPIO pins// 

// GPSET0 ouput set register

// GPCLR0

// GPPUPPDN0

// enumerations for UART registers
