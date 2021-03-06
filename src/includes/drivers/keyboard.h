/* Keyboard scan port */
#define KEYBOARD_SCAN_PORT 0x60
/* Special keycodes */
#define NONE 0
/* Arrows */
#define KEY_UP_PRESS      392
#define KEY_UP_RELEASE    393
#define KEY_DOWN_PRESS    394
#define KEY_DOWN_RELEASE  395
#define KEY_LEFT_PRESS    396
#define KEY_LEFT_RELEASE  397
#define KEY_RIGHT_PRESS   398
#define KEY_RIGHT_RELEASE 399
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

/* Keyboard */
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
    int nbSpecial;
}kbd_t;
int scan_keyboard();
int keyToAscii(int scancode, kbd_t * keyboard);
struct Keyboard initKeyboard();
