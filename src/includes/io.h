#include <stdint.h>
#include "const.h"
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
/* Keypad */
#define INSERT 400
#define END   401
#define DOWN  402
#define PGDWN 403
#define LEFT  404
#define NP5   405
#define RIGHT 406
#define HOME  407
#define UP    408
#define PGUP  409
#define DIV   47
#define MULT  42
#define MINUS '-'
#define PLUS  '+'
#define NUMLK 414
#define DEL   415
/* F1 -> F12 */
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
/* Special keys after F keys */
#define SCRLK 514
#define PRTSC 515
#define PAUSE 516
/* ALT- CTRL - CAPSLOCK Keys */
#define ALT   517
#define CTRL  518
#define CPSLK 519
/* SHIFT + F1 -> SHIFT + F12 */
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
typedef struct Keyboard
{
    int *buffer;
    unsigned int buf_size;
    char *map;
    /* Booleans => keyboard status */
    int shift;
    int cpslock;
    int alt;
    int ctrl;
    int numlock;
    int special;
}kbd_t;
int scan_keyboard();
void kbd_interrupt(kbd_t * keyboard);
int keyToAscii(int scancode, kbd_t * keyboard);
struct Keyboard initKeyboard();
