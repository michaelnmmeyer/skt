#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mem.h"

noreturn void skt_fatal(const char *msg, ...)
{
   va_list ap;

   fputs("skt: ", stderr);
   va_start(ap, msg);
   vfprintf(stderr, msg, ap);
   va_end(ap);
   putc('\n', stderr);
   abort();
}

#define SKT_OOM() skt_fatal("out of memory")

void *skt_malloc(size_t size)
{
   assert(size);
   void *mem = malloc(size);
   if (!mem)
      SKT_OOM();
   return mem;
}

void *skt_realloc(void *mem, size_t size)
{
   assert(size);
   void *new = realloc(mem, size);
   if (!new)
      SKT_OOM();
   return new;
}

void *skt_calloc(size_t nmemb, size_t size)
{
   assert(nmemb && size);
   void *mem = calloc(nmemb, size);
   if (!mem)
      SKT_OOM();
   return mem;
}
