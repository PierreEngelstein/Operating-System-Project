#include "stdlib.h"
#include "const.h"
/** INITIALIZE AND RESET **/
cbuf_handle_t circular_buff_init(int* buffer, int size)
{
        cbuf_handle_t cbuf;
        cbuf->buffer = buffer;
        cbuf->max = size;
        circular_buff_reset(cbuf);
        return cbuf;
}

void circular_buff_reset(cbuf_handle_t cbuf)
{
        cbuf->head = 0;
        cbuf->tail = 0;
        cbuf->full = FALSE;
}

/** STATE CHECKS **/
int circular_buff_empty(cbuf_handle_t cbuf)
{
        return(!cbuf->full && (cbuf->head == cbuf->tail));
}
int circular_buff_full(cbuf_handle_t cbuf)
{
        return cbuf->full;
}
int circular_buff_capacity(cbuf_handle_t cbuf)
{
        return cbuf->max;
}
int circular_buff_size(cbuf_handle_t cbuf)
{
        int size = cbuf->max;
        if(!cbuf->full)
        {
                if(cbuf->head >= cbuf->tail)
                        size = (cbuf->head - cbuf->tail);
                else
                        size = (cbuf->max + cbuf->head - cbuf->tail);
        }
        return size;
}

/** ADDING AND REMOVING DATA **/
static void advance_pointer(cbuf_handle_t cbuf)
{
        if(cbuf->full)
        {
                cbuf->tail = (cbuf->tail + 1) % cbuf->max;
                kprintf("", cbuf->tail);
        }

        cbuf->head = (cbuf->head + 1) % cbuf->max;
        kprintf("", cbuf->head);
        cbuf->full = (cbuf->head == cbuf->tail);
}
static void retreat_pointer(cbuf_handle_t cbuf)
{
        cbuf->full = FALSE;
        cbuf->tail = (cbuf->tail + 1) % cbuf->max;
        kprintf("", cbuf->tail);
}
void circular_buff_put(cbuf_handle_t cbuf, int data)
{
        cbuf->buffer[cbuf->head] = data;
        advance_pointer(cbuf);
}
int circular_buff_put2(cbuf_handle_t cbuf, int data)
{
        int r = -1;
        if(!circular_buff_full(cbuf))
        {
                cbuf->buffer[cbuf->head] = data;
                advance_pointer(cbuf);
                r = 0;
        }
        return r;
}
int circular_buff_get(cbuf_handle_t cbuf, int *data)
{
        int r = -1;
        if(!circular_buff_empty(cbuf))
        {
                *data = cbuf->buffer[cbuf->tail];
                retreat_pointer(cbuf);
                r = 0;
        }
        return r;
}
