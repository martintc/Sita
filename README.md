# Sita

---

A minimal operating system for a Raspberri Pi 4B that allows for loading another kernel over a UART connection. It is intended to enable fast development of operating systems on the Raspberri Pi 4B system.

The primary pins for UART action are GPIO pins 14 (TXD) and 15 (RXD).

---

## Note for running

In order to get started. First, use the Raspberry Pi imaging tool to write an operating system to a USB or SD Card. I went with the 64-bit lite version. This will write some file to the disk needed for booting. From there, we can compile this kernel and replace the existing `kernel8.img` file with the compiled kernel.

Important not for getting UART to act correctly. The Mini-UART is able to get screwed up on the baud rate because of frequency scaling depening on the load on the CPU. My understanding is that to have a consistent value we can rely on being written into the baud register, we need a mechanism that will force the Pi into keeping a consistent frequency. We can do this by adding this line to `config.txt` that was provided by the imager.

```
dtoverlay=miniuart-bt
```
