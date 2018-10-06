/**
    String routines
**/
/* Convert an integer to a string */
void itoa(int value, char* buffer, int base);
/* Reverses the string array given in argument */
char* reverse(char *buffer, int i, int j);
/* Swaps the two strings */
void swap(char *x, char *y);
int abs(int n);

/**
    Print routines
**/
/* Prints a string and type fields */
void kprintf(const char *string, ...);
/* Prints the character at the given coordinates */
void write_char(const char c, int col, int row);
/* Updates the cursor to the given coordinates */
void update_cursor(int col, int row);
int getCursorOffet();
int getOffsetRow(int offset);
int getOffsetCol(int offset);
