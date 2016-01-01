#ifndef SKT_BUF_H
#define SKT_BUF_H

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include "skt.h"

void skt_buf_grow(struct skt_buf *buf, size_t incr);

void skt_buf_set(struct skt_buf *buf, const void *data, size_t size);

static inline void skt_buf_truncate(struct skt_buf *buf, size_t size)
{
   assert(size < buf->alloc || size == 0);
   if (buf->alloc)
      buf->data[buf->size = size] = '\0';
}

#define skt_buf_clear(buf) skt_buf_truncate(buf, 0)

#endif
