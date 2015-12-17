#ifndef SKT_BUF_H
#define SKT_BUF_H

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include "skt.h"

void skt_buf_grow(struct skt_buf *buf, size_t incr);

void skt_buf_set(struct skt_buf *buf, const void *data, size_t size);

#define skt_buf_setl(buf, lit) skt_buf_set(buf, "" lit, sizeof lit - 1)

void skt_buf_sets(struct skt_buf *buf, const char *str);

void skt_buf_cat(struct skt_buf *buf, const void *data, size_t size);

#define skt_buf_catl(buf, lit) skt_buf_cat(buf, "" lit, sizeof lit - 1)

void skt_buf_cats(struct skt_buf *buf, const char *str);

void skt_buf_catc(struct skt_buf *buf, int c);

void skt_buf_printf(struct skt_buf *buf, const char *format, ...)
#ifdef __GNUC__
   __attribute__((format(printf, 2, 3)))
#endif
   ;

void skt_buf_vprintf(struct skt_buf *buf, const char *format, va_list ap)
#ifdef __GNUC__
   __attribute__((format(printf, 2, 0)))
#endif
   ;

static inline void skt_buf_truncate(struct skt_buf *buf, size_t size)
{
   assert(size < buf->alloc || size == 0);
   if (buf->alloc)
      buf->data[buf->size = size] = '\0';
}

#define skt_buf_clear(buf) skt_buf_truncate(buf, 0)

#endif
