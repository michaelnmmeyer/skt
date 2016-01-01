#include <string.h>
#include "buf.h"
#include "mem.h"

#define SKT_BUF_INIT_SIZE 16

void skt_buf_grow(struct skt_buf *buf, size_t size)
{
   size_t need = buf->size + size + 1;
   if (need <= buf->size)
      skt_fatal("integer overflow");

   if (need > buf->alloc) {
      if (buf->alloc) {
         buf->alloc += buf->alloc >> 1;
         if (buf->alloc < need)
            buf->alloc = need;
         buf->data = skt_realloc(buf->data, buf->alloc);
      } else {
         buf->alloc = need < SKT_BUF_INIT_SIZE ? SKT_BUF_INIT_SIZE : need;
         buf->data = skt_malloc(buf->alloc);
      }
   }
}

void skt_buf_fini(struct skt_buf *buf)
{
   if (buf->alloc)
      free(buf->data);
}

static void skt_buf_cat(struct skt_buf *buf, const void *data, size_t size)
{
   skt_buf_grow(buf, size);
   memcpy(&buf->data[buf->size], data, size);
   buf->data[buf->size += size] = '\0';
}

void skt_buf_set(struct skt_buf *buf, const void *data, size_t size)
{
   skt_buf_clear(buf);
   skt_buf_cat(buf, data, size);
}
