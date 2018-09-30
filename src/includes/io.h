#include <stdint.h>
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
/* Reads an unsigned byte from the specified port */
unsigned char port_byte_in(uint8_t port);
/* Writes an unsigned byte into the specified port */
void port_byte_out(uint16_t port, uint8_t data);
/* Reads an unsigned short from the specified port */
unsigned short port_word_in(uint16_t port);
/* Writes an unsigned short into the specified port  */
void port_word_out(uint16_t port, uint16_t data);
