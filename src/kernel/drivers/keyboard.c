#include "lib.h"
#include "const.h"
/* Keyboard driver */
static const unsigned short keycodes[0x60] =   /* AZERTY lowercase keycodes */
{
        /* 0, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F  */
        0, 27,   '&',  0,  '"',  39,   '(',  '-',  138,  '_',  128,  133,  ')',  '=',  8,    9,
        /* 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F*/
        'a',  'z',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  94,   36,   '\n',   CTRL, 'q',  's',
        /* 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F */
        'd',  'f',  'g',  'h',  'j',  'k',  'l',  'm',  129,  '2',  15,   '*',  'w',  'x',  'c',  'v',
        /* 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F */
        'b',  'n',  ',',  ';',  ':',  '!',  15,   0,    ALT,  ' ',  CPSLK,F1,   F2,   F3,   F4,    F5,
        /* 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F */
        F6,   F7,   F8,   F9,   F10,  NUMLK,SCRLK,HOME, UP,   PGUP, MINUS,  LEFT,  NP5,  RIGHT,  PLUS,  END,   // <- From numpad
        /* 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F */
        DOWN,  PGDWN,  INSERT,  DEL,  SHF1, SHF2, '>', SHF4, SHF5, SHF6, SHF7, SHF8, SHF9, SHF10,SHF11,SHF12
};
static const unsigned short keycodes_shift[0x60] =   /* AZERTY lowercase keycodes */
{
        /* 0, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F  */
        0, 27,   '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',  ')',  '+',  8,    9,
        /* 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F*/
        'A',  'Z',  'E',  'R',  'T',  'Y',  'U',  'I',  'O',  'P',  94,   156,   '\n',  CTRL, 'Q',  'S',
        /* 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F */
        'D',  'F',  'G',  'H',  'J',  'K',  'L',  'M',  129,  '2',  15,   0,  'W',  'X',  'C',  'V',
        /* 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F */
        'B',  'N',  '?',  '.',  '/',  0,  15,   0,    ALT,  ' ',  CPSLK,F1,   F2,   F3,   F4,    F5,
        /* 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F */
        F6,   F7,   F8,   F9,   F10,  NUMLK,SCRLK,HOME, UP,   PGUP, MINUS,  LEFT,  NP5,  RIGHT,  PLUS,  END,// <- From numpad
        /* 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F */
        DOWN,  PGDWN,  INSERT,  DEL,  SHF1, SHF2, '>', SHF4, SHF5, SHF6, SHF7, SHF8, SHF9, SHF10,SHF11,SHF12
};
// static const unsigned short keycodes_altgr[0x0E] =   /* AZERTY lowercase keycodes */
// {
//         /* 0, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D  */
//         0, 27,   '&',  '~',  '#',  '{',  '[',  '|',  '`',  92,  '^',  '@',  ']',  '}'
// };

int scan_keyboard() /* Get the input from 0x60 port (PRIVATE function -> don't access it outside this file) */
{
        return port_byte_in(0x60);
}

void kbd_interrupt(kbd_t * keyboard) /* Process the keyboard interrupt by putting it in the keyboard buffer */
{
        int scancode;
        scancode = scan_keyboard(); /* Get the scancode from keycode */
        /* Manage the FIFO Buffer */
        int kb;
        for(kb = 0; kb < keyboard->buf_size - 1; kb++) /* Move each element upward */
                keyboard->buffer[kb] = keyboard->buffer[kb + 1];
        keyboard->buffer[keyboard->buf_size-1] = scancode; /* Store scan code */
}

int keyToAscii(int scancode, kbd_t * keyboard)
{
        int result = NONE;
        if(scancode < 0x60) /* If the scancode is something mapped in the keycodes array, process it */
        {
                if(keyboard->cpslock ^ keyboard->shift) /* If the keyboard is on shift or shift verr */
                        result = keycodes_shift[scancode];
                else                               /* If the keyboard is not on shift*/
                        result = keycodes[scancode];
                if(!keyboard->numlock)  /* If the numpad is on, transform the result to number */
                {
                        if(result == DEL)
                                result = '.';
                        else if(result >= INSERT && result <= PGUP)
                                result = '0' + result - INSERT; /* 0-9 */
                }
                if(result == 15)         /* Shift pressed*/
                        keyboard->shift = TRUE;
                if(result == CTRL) /* CTRL pressed */
                        keyboard->ctrl = TRUE;
                if(result == CPSLK) /* CAPS LOCK pressed */
                        keyboard->cpslock = !keyboard->cpslock; /* Invert caps lock */
                if(result == NUMLK)
                        keyboard->numlock = !keyboard->numlock;
        }
        else /* Otherwise, it means that it is a released key */
        {
                if(!keyboard->special)
                {
                        if(scancode - 128 == 0x2A) /* Shift released */
                                keyboard->shift = FALSE;
                        if(scancode - 128 == 0x1D) /* ctrl released */
                                keyboard->ctrl = FALSE;
                }
                else
                {
                        switch (result) {
                                case 0x48:
                                        printf("KEY_UP\n");
                                        result = KEY_UP_PRESS;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                case 0xC8:
                                        result = KEY_UP_RELEASE;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                case 0x4B:
                                        result = KEY_LEFT_PRESS;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                case 0xCB:
                                        result = KEY_LEFT_RELEASE;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                case 0x4D:
                                        result = KEY_RIGHT_PRESS;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                case 0xCD:
                                        result = KEY_RIGHT_RELEASE;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                case 0x50:
                                        result = KEY_DOWN_PRESS;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                case 0xD0:
                                        result = KEY_DOWN_RELEASE;
                                        keyboard->nbSpecial++;
                                        keyboard->special = !keyboard->special;
                                        break;
                                default:
                                        result = -1;
                                        break;
                        }
                }
        }
        // kprintf("%d\n", result);
        return result;
}

kbd_t initKeyboard()
{
        kbd_t keyboard;
        keyboard.buf_size = 10;
        keyboard.buffer = (int *)0x100000; /* For the moment, the keyboard buffer is allocated statically since I don't have any memory management... */
        keyboard.shift = FALSE;
        keyboard.cpslock = FALSE;
        keyboard.alt = FALSE;
        keyboard.ctrl = FALSE;
        keyboard.numlock = FALSE;
        keyboard.special = FALSE;
        keyboard.nbSpecial = 0;
        int kb;
        for(kb = 0; kb < keyboard.buf_size; kb++) /* Init the keyboard buffer with 0 */
                keyboard.buffer[kb] = 0;
        return keyboard;
}
