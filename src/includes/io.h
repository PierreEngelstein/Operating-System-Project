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

/* Special keycodes */
#define F1  501
#define F2  502
#define F3  503
#define F4  504
#define F5  505
#define F6  506
#define F7  507
#define F8  508
#define F9  509
#define F10 510
#define F11 511
#define F12 512
#define NUMLK 513
#define SCRLK 514
#define HOME  515
#define UP    516
#define PGUP  517
#define ALT   518
#define CTRL  519
#define SHF1   521
#define SHF2   522
#define SHF3   523
#define SHF4   524
#define SHF5   525
#define SHF6   526
#define SHF7   527
#define SHF8   528
#define SHF9   529
#define SHF10  530
#define SHF11  531
#define SHF12  532

/* keyboard */
struct Keyboard
{
    char buffer[10];
    char *map;
    int isUpper;
};
int getKey();
char keyToAscii(int raw_key, struct Keyboard keyboard);
struct Keyboard initKeyboard();
