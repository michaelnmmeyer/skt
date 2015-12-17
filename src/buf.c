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

void skt_buf_set(struct skt_buf *buf, const void *data, size_t size)
{
   skt_buf_clear(buf);
   skt_buf_cat(buf, data, size);
}

void skt_buf_sets(struct skt_buf *buf, const char *str)
{
   skt_buf_set(buf, str, strlen(str));
}

void skt_buf_cat(struct skt_buf *buf, const void *data, size_t size)
{
   skt_buf_grow(buf, size);
   memcpy(&buf->data[buf->size], data, size);
   buf->data[buf->size += size] = '\0';
}

void skt_buf_catc(struct skt_buf *buf, int c)
{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = c;
   buf->data[buf->size] = '\0';
}

void skt_buf_cats(struct skt_buf *buf, const char *str)
{
   skt_buf_cat(buf, str, strlen(str));
}

void skt_buf_printf(struct skt_buf *buf, const char *fmt, ...)
{
   va_list ap;
   va_start(ap, fmt);
   skt_buf_vprintf(buf, fmt, ap);
   va_end(ap);
}

static size_t vsnprintf_unsigned(char *buf, size_t size,
                                 const char *fmt, va_list ap)
{
   int len = vsnprintf(buf, size, fmt, ap);
   return len < 0 ? 0 : len;
}

void skt_buf_vprintf(struct skt_buf *buf, const char *fmt, va_list ap)
{
   va_list copy;
   va_copy(copy, ap);
   size_t avail = buf->alloc - buf->size;
   size_t size = vsnprintf_unsigned(&buf->data[buf->size], avail, fmt, copy);
   va_end(copy);

   if (size >= avail) {
      skt_buf_grow(buf, size);
      avail = buf->alloc - buf->size;
      size = vsnprintf_unsigned(&buf->data[buf->size], avail, fmt, ap);
   }
   buf->size += size;
}
