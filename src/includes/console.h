/* Console default size */
static const int VGA_WIDTH  = 80;
static const int VGA_HEIGHT = 25;
/* Video memory start address (NOT AN ARRAY)*/
static const int VGA_MEM = 0xb8000;
/* Current cursor position */
static int curr_row;
static int curr_col;
/* Current printing color */
// static int color;
