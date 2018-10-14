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

// #define sizeof(x) ((&x + 1) - &x)

void kpanic(char *message);
#define assert(check, condition) do{ if ((check) != (condition)) kpanic();}while(0)

/* Circular buffer */
struct circular_buff_t{
        int *buffer;
        int head;
        int tail;
        int max;
        int full;
};
typedef struct circular_buff_t circular_buff_t;
typedef circular_buff_t *cbuf_handle_t;
/* Circular Buffer Functions */
cbuf_handle_t circular_buff_init(int* buffer, int size); /* Creates a circular buffer */
// void circular_buff_free(cbuf_handle_t cbuf); /* Free a circular buffer (does not free data buffer) */
void circular_buff_reset(cbuf_handle_t cbuf); /* Reset the circular buffer (head == tail) */
void circular_buff_put(cbuf_handle_t cbuf, int data); /* Adds an element to the buffer (even if is full) */
int circular_buff_put2(cbuf_handle_t cbuf, int data); /* Adds an element to the buffer if it is not full */
int circular_buff_get(cbuf_handle_t cbuf, int *data); /* Retrieves an element from the buffer */
int circular_buff_empty(cbuf_handle_t cbuf); /* Check if the circular buffer is empty */
int circular_buff_full(cbuf_handle_t cbuf); /* Checks if the circular buffer is full */
int circular_buff_capacity(cbuf_handle_t cbuf); /* Returns the max capacity of the buffer */
int circular_buff_size(cbuf_handle_t cbuf); /* Returns the current number of elements in the buffer */
