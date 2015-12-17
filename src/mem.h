#ifndef SKT_MEM_H
#define SKT_MEM_H

#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdnoreturn.h>

noreturn void skt_fatal(const char *msg, ...);

void *skt_malloc(size_t size)
#ifdef ___GNUC__
   __attribute__((malloc))
#endif
   ;

void *skt_calloc(size_t nmemb, size_t size)
#ifdef ___GNUC__
   __attribute__((malloc))
#endif
   ;

void *skt_realloc(void *mem, size_t size);

/* For reallocating arrays.
 * data: the array proper.
 * size: current number of elements.
 * alloc: current allocated memory (must be initialized to 0).
 * more: number of elements to reserve.
 * init: initial number of elements to allocate.
 */
#define SKT_GROW(data, size, alloc, more, init) do {                           \
   size_t need = size + more;                                                  \
   if (need < size)                                                            \
      skt_fatal("integer overflow");                                           \
   if (need > alloc) {                                                         \
      if (alloc) {                                                             \
         alloc += alloc >> 1;                                                  \
         if (alloc < need)                                                     \
            alloc = need;                                                      \
         if (alloc > SIZE_MAX / sizeof *data)                                  \
            skt_fatal("integer overflow");                                     \
         data = skt_realloc(data, alloc * sizeof *data);                       \
      } else {                                                                 \
         alloc = need < init ? init : need;                                    \
         if (alloc > SIZE_MAX / sizeof *data)                                  \
            skt_fatal("integer overflow");                                     \
         data = skt_malloc(alloc * sizeof *data);                              \
      }                                                                        \
   }                                                                           \
} while (0)

#endif
