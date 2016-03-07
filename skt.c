#line 1 "buf.c"
#include <string.h>
#line 1 "buf.h"
#ifndef SKT_BUF_H
#define SKT_BUF_H

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#line 1 "skt.h"
#ifndef SKT_H
#define SKT_H

#include <stddef.h>

/* General notes:
 * - Strings provided as input to the transliteration functions and to
 *   skt_sort_key() must be valid UTF-8 and be normalized to NFC or NFKC,
 *   otherwise they won't be treated correctly.
 * - All functions erase the contents of the buffer they are provided as
 *   argument.
 */

/******************************************************************************
 * Metadata.
 *****************************************************************************/

#define SKT_NUM_SCHEMES 5

/* All transliteration schemes, lexicographically sorted, NULL-terminated. */
const char *const skt_schemes[SKT_NUM_SCHEMES + 1];

/* Returns a string describing the set of substitutions performed when a given
 * transliteration mapping is used.
 */
const char *skt_map_description(const char *input_scheme,
                                const char *output_scheme);


/******************************************************************************
 * Dynamic buffer.
 *****************************************************************************/

struct skt_buf {
   char *data;    /* Buffer contents, nul-terminated. */
   size_t size;   /* Buffer size, the terminating nul byte not included. */
   size_t alloc;
};

/* Initializer. */
#define SKT_BUF_INIT {.data = ""}

/* Destructor. */
void skt_buf_fini(struct skt_buf *buf);


/******************************************************************************
 * Main functions.
 *****************************************************************************/

/* Creates a sort key for a IAST-encoded string.
 * Equivalent to strxfrm(). If the provided string doesn't contain nul bytes,
 * the created key won't, too.
 */
void skt_sort_key(struct skt_buf *buf, const char *str, size_t len);

/* A function that transliterates a string.
 * Unknown characters are left unchanged. Sequences of characters known the
 * transliteration function are replaced with NFC-normalized sequences, which
 * are also valid NFKC sequences.
 */
typedef void (*skt_translit)(struct skt_buf *, const char *str, size_t len);

/* Returns a transliteration function for the provided input and output
 * schemes. If the requested mapping is not available, 0 is returned.
 */
skt_translit skt_translit_func(const char *input_scheme,
                               const char *output_scheme);

#endif
#line 8 "buf.h"

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
#line 3 "buf.c"
#line 1 "mem.h"
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
#line 4 "buf.c"

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
#line 1 "mem.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
#line 1 "skt.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

enum {
   IAST,
   IASTC,
   NAGARI,
   SLP1,
   VELTHUIS,

   NUM_SCHEMES,
};

const char *const skt_schemes[NUM_SCHEMES + 1] = {
   [IAST] =     "iast",
   [IASTC] =    "iastc",
   [NAGARI] =   "nagari",
   [SLP1] =     "slp1",
   [VELTHUIS] = "velthuis",
};

static size_t skt_scheme_value(const char *name)
{
   for (size_t i = 0; skt_schemes[i]; i++)
      if (!strcmp(skt_schemes[i], name))
         return i;
   return SIZE_MAX;
}

/* When input_scheme = output_scheme. */
static void skt_translit_identity(struct skt_buf *buf, const char *str,
                                  size_t len)
{
   skt_buf_set(buf, str, len);
}

/* Ragel generates useless variables. */
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#line 1 "skt_maps.ic"
#line 1 "skt_translit_slp1_iast.ic"

#line 1 "skt_translit_slp1_iast.rl"

#line 538 "skt_translit_slp1_iast.rl"


static void skt_translit_slp1_iast(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_slp1_iast.ic"
static const char _skt_translit_slp1_iast_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41, 1, 42, 1,
   43, 1, 44, 1, 45, 1, 46, 1,
   47, 1, 48, 1, 49, 1, 50, 1,
   51, 1, 52, 1, 53, 1, 54, 1,
   55, 1, 56, 1, 57, 1, 58, 1,
   59, 1, 60, 1, 61, 1, 62, 1,
   63, 1, 64, 1, 65, 1, 66, 1,
   67, 1, 68, 1, 69, 1, 70, 1,
   71, 1, 72, 1, 73, 1, 74, 1,
   75, 1, 76, 1, 77, 1, 78, 1,
   79, 1, 80, 1, 81
};

static const char _skt_translit_slp1_iast_key_offsets[] = {
   0, 37, 38, 53, 67, 81, 82
};

static const unsigned char _skt_translit_slp1_iast_trans_keys[] = {
   46u, 47u, 65u, 66u, 67u, 68u, 69u, 70u,
   71u, 72u, 73u, 74u, 75u, 76u, 77u, 78u,
   79u, 80u, 81u, 82u, 83u, 84u, 85u, 87u,
   88u, 89u, 94u, 96u, 102u, 106u, 107u, 113u,
   119u, 120u, 122u, 124u, 126u, 46u, 65u, 69u,
   70u, 73u, 76u, 79u, 85u, 88u, 97u, 101u,
   102u, 105u, 111u, 117u, 120u, 65u, 69u, 70u,
   73u, 79u, 85u, 88u, 97u, 101u, 102u, 105u,
   111u, 117u, 120u, 65u, 69u, 70u, 73u, 79u,
   85u, 88u, 97u, 101u, 102u, 105u, 111u, 117u,
   120u, 89u, 122u, 0
};

static const char _skt_translit_slp1_iast_single_lengths[] = {
   37, 1, 15, 14, 14, 1, 1
};

static const char _skt_translit_slp1_iast_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_slp1_iast_index_offsets[] = {
   0, 38, 40, 56, 71, 86, 88
};

static const char _skt_translit_slp1_iast_trans_targs[] = {
   1, 2, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 3, 4, 0, 5, 6, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0
};

static const unsigned char _skt_translit_slp1_iast_trans_actions[] = {
   0, 0, 37, 39, 41, 43, 45, 47,
   49, 51, 53, 55, 57, 59, 61, 63,
   65, 67, 69, 71, 73, 75, 77, 79,
   81, 83, 0, 0, 141, 0, 0, 147,
   149, 151, 153, 155, 157, 159, 5, 161,
   7, 9, 11, 13, 15, 17, 19, 21,
   23, 25, 27, 29, 31, 33, 35, 163,
   85, 87, 89, 91, 93, 95, 97, 99,
   101, 103, 105, 107, 109, 111, 163, 113,
   115, 117, 119, 121, 123, 125, 127, 129,
   131, 133, 135, 137, 139, 163, 143, 163,
   145, 163, 161, 163, 163, 163, 163, 163,
   0
};

static const unsigned char _skt_translit_slp1_iast_to_state_actions[] = {
   1, 0, 0, 0, 0, 0, 0
};

static const unsigned char _skt_translit_slp1_iast_from_state_actions[] = {
   3, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_slp1_iast_eof_trans[] = {
   0, 91, 96, 96, 96, 96, 96
};

static const int skt_translit_slp1_iast_start = 0;
static const int skt_translit_slp1_iast_first_final = 0;
static const int skt_translit_slp1_iast_error = -1;

static const int skt_translit_slp1_iast_en_main = 0;


#line 551 "skt_translit_slp1_iast.rl"

#line 127 "skt_translit_slp1_iast.ic"
   {
   cs = skt_translit_slp1_iast_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 552 "skt_translit_slp1_iast.rl"

#line 137 "skt_translit_slp1_iast.ic"
   {
   int _klen;
   unsigned int _trans;
   const char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_slp1_iast_actions + _skt_translit_slp1_iast_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 156 "skt_translit_slp1_iast.ic"
      }
   }

   _keys = _skt_translit_slp1_iast_trans_keys + _skt_translit_slp1_iast_key_offsets[cs];
   _trans = _skt_translit_slp1_iast_index_offsets[cs];

   _klen = _skt_translit_slp1_iast_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_slp1_iast_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_slp1_iast_trans_targs[_trans];

   if ( _skt_translit_slp1_iast_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_slp1_iast_actions + _skt_translit_slp1_iast_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 38 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 124;
   buf->data[buf->size++] = 124;
}}
   break;
   case 3:
#line 404 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 4:
#line 438 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}}
   break;
   case 5:
#line 84 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 6:
#line 218 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 7:
#line 254 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}}
   break;
   case 8:
#line 364 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}}
   break;
   case 9:
#line 246 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 10:
#line 62 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 11:
#line 151 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 161;
}}
   break;
   case 12:
#line 184 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 169;
}}
   break;
   case 13:
#line 44 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 14:
#line 358 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}}
   break;
   case 15:
#line 171 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 179;
}}
   break;
   case 16:
#line 8 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}}
   break;
   case 17:
#line 395 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 18:
#line 117 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}}
   break;
   case 19:
#line 389 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 98;
   buf->data[buf->size++] = 104;
}}
   break;
   case 20:
#line 279 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 99;
   buf->data[buf->size++] = 104;
}}
   break;
   case 21:
#line 240 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 100;
   buf->data[buf->size++] = 104;
}}
   break;
   case 22:
#line 383 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 105;
}}
   break;
   case 23:
#line 419 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
}}
   break;
   case 24:
#line 332 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 103;
   buf->data[buf->size++] = 104;
}}
   break;
   case 25:
#line 177 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}}
   break;
   case 26:
#line 445 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}}
   break;
   case 27:
#line 352 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 104;
}}
   break;
   case 28:
#line 285 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 104;
}}
   break;
   case 29:
#line 157 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 187;
}}
   break;
   case 30:
#line 137 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}}
   break;
   case 31:
#line 412 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}}
   break;
   case 32:
#line 318 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 117;
}}
   break;
   case 33:
#line 432 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 112;
   buf->data[buf->size++] = 104;
}}
   break;
   case 34:
#line 324 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
   buf->data[buf->size++] = 104;
}}
   break;
   case 35:
#line 266 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}}
   break;
   case 36:
#line 298 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}}
   break;
   case 37:
#line 111 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 116;
   buf->data[buf->size++] = 104;
}}
   break;
   case 38:
#line 196 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}}
   break;
   case 39:
#line 129 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
   buf->data[buf->size++] = 104;
}}
   break;
   case 40:
#line 71 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
}}
   break;
   case 41:
#line 426 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}}
   break;
   case 42:
#line 30 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 43:
#line 14 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 44:
#line 53 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 45:
#line 304 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 46:
#line 144 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 47:
#line 202 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 48:
#line 21 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 49:
#line 338 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}}
   break;
   case 50:
#line 273 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}}
   break;
   case 51:
#line 102 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 52:
#line 312 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 53:
#line 190 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
}}
   break;
   case 54:
#line 123 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 55:
#line 93 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 56:
#line 30 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 57:
#line 14 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 58:
#line 53 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 59:
#line 304 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 60:
#line 144 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 61:
#line 202 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 62:
#line 21 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 63:
#line 338 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}}
   break;
   case 64:
#line 273 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}}
   break;
   case 65:
#line 102 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 66:
#line 312 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 67:
#line 190 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
}}
   break;
   case 68:
#line 123 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 69:
#line 93 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 70:
#line 371 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}}
   break;
   case 71:
#line 164 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}}
   break;
   case 72:
#line 344 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}}
   break;
   case 73:
#line 259 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}}
   break;
   case 74:
#line 233 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}}
   break;
   case 75:
#line 226 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}}
   break;
   case 76:
#line 291 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}}
   break;
   case 77:
#line 210 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 104;
}}
   break;
   case 78:
#line 78 "skt_translit_slp1_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 131;
}}
   break;
   case 79:
#line 532 "skt_translit_slp1_iast.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 80:
#line 378 "skt_translit_slp1_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}}
   break;
   case 81:
#line 532 "skt_translit_slp1_iast.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 938 "skt_translit_slp1_iast.ic"
      }
   }

_again:
   _acts = _skt_translit_slp1_iast_actions + _skt_translit_slp1_iast_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 951 "skt_translit_slp1_iast.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_slp1_iast_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_slp1_iast_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 553 "skt_translit_slp1_iast.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 2 "skt_maps.ic"
#line 1 "skt_translit_slp1_iastc.ic"

#line 1 "skt_translit_slp1_iastc.rl"

#line 542 "skt_translit_slp1_iastc.rl"


static void skt_translit_slp1_iastc(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_slp1_iastc.ic"
static const char _skt_translit_slp1_iastc_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41, 1, 42, 1,
   43, 1, 44, 1, 45, 1, 46, 1,
   47, 1, 48, 1, 49, 1, 50, 1,
   51, 1, 52, 1, 53, 1, 54, 1,
   55, 1, 56, 1, 57, 1, 58, 1,
   59, 1, 60, 1, 61, 1, 62, 1,
   63, 1, 64, 1, 65, 1, 66, 1,
   67, 1, 68, 1, 69, 1, 70, 1,
   71, 1, 72, 1, 73, 1, 74, 1,
   75, 1, 76, 1, 77, 1, 78, 1,
   79, 1, 80, 1, 81
};

static const char _skt_translit_slp1_iastc_key_offsets[] = {
   0, 37, 38, 53, 67, 81, 82
};

static const unsigned char _skt_translit_slp1_iastc_trans_keys[] = {
   46u, 47u, 65u, 66u, 67u, 68u, 69u, 70u,
   71u, 72u, 73u, 74u, 75u, 76u, 77u, 78u,
   79u, 80u, 81u, 82u, 83u, 84u, 85u, 87u,
   88u, 89u, 94u, 96u, 102u, 106u, 107u, 113u,
   119u, 120u, 122u, 124u, 126u, 46u, 65u, 69u,
   70u, 73u, 76u, 79u, 85u, 88u, 97u, 101u,
   102u, 105u, 111u, 117u, 120u, 65u, 69u, 70u,
   73u, 79u, 85u, 88u, 97u, 101u, 102u, 105u,
   111u, 117u, 120u, 65u, 69u, 70u, 73u, 79u,
   85u, 88u, 97u, 101u, 102u, 105u, 111u, 117u,
   120u, 89u, 122u, 0
};

static const char _skt_translit_slp1_iastc_single_lengths[] = {
   37, 1, 15, 14, 14, 1, 1
};

static const char _skt_translit_slp1_iastc_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_slp1_iastc_index_offsets[] = {
   0, 38, 40, 56, 71, 86, 88
};

static const char _skt_translit_slp1_iastc_trans_targs[] = {
   1, 2, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 3, 4, 0, 5, 6, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0
};

static const unsigned char _skt_translit_slp1_iastc_trans_actions[] = {
   0, 0, 37, 39, 41, 43, 45, 47,
   49, 51, 53, 55, 57, 59, 61, 63,
   65, 67, 69, 71, 73, 75, 77, 79,
   81, 83, 0, 0, 141, 0, 0, 147,
   149, 151, 153, 155, 157, 159, 5, 161,
   7, 9, 11, 13, 15, 17, 19, 21,
   23, 25, 27, 29, 31, 33, 35, 163,
   85, 87, 89, 91, 93, 95, 97, 99,
   101, 103, 105, 107, 109, 111, 163, 113,
   115, 117, 119, 121, 123, 125, 127, 129,
   131, 133, 135, 137, 139, 163, 143, 163,
   145, 163, 161, 163, 163, 163, 163, 163,
   0
};

static const unsigned char _skt_translit_slp1_iastc_to_state_actions[] = {
   1, 0, 0, 0, 0, 0, 0
};

static const unsigned char _skt_translit_slp1_iastc_from_state_actions[] = {
   3, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_slp1_iastc_eof_trans[] = {
   0, 91, 96, 96, 96, 96, 96
};

static const int skt_translit_slp1_iastc_start = 0;
static const int skt_translit_slp1_iastc_first_final = 0;
static const int skt_translit_slp1_iastc_error = -1;

static const int skt_translit_slp1_iastc_en_main = 0;


#line 555 "skt_translit_slp1_iastc.rl"

#line 127 "skt_translit_slp1_iastc.ic"
   {
   cs = skt_translit_slp1_iastc_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 556 "skt_translit_slp1_iastc.rl"

#line 137 "skt_translit_slp1_iastc.ic"
   {
   int _klen;
   unsigned int _trans;
   const char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_slp1_iastc_actions + _skt_translit_slp1_iastc_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 156 "skt_translit_slp1_iastc.ic"
      }
   }

   _keys = _skt_translit_slp1_iastc_trans_keys + _skt_translit_slp1_iastc_key_offsets[cs];
   _trans = _skt_translit_slp1_iastc_index_offsets[cs];

   _klen = _skt_translit_slp1_iastc_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_slp1_iastc_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_slp1_iastc_trans_targs[_trans];

   if ( _skt_translit_slp1_iastc_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_slp1_iastc_actions + _skt_translit_slp1_iastc_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 353 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 124;
   buf->data[buf->size++] = 124;
}}
   break;
   case 3:
#line 63 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 4:
#line 22 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}}
   break;
   case 5:
#line 233 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 6:
#line 157 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 7:
#line 58 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}}
   break;
   case 8:
#line 259 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}}
   break;
   case 9:
#line 332 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 10:
#line 365 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 11:
#line 423 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 161;
}}
   break;
   case 12:
#line 305 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 169;
}}
   break;
   case 13:
#line 29 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 14:
#line 221 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}}
   break;
   case 15:
#line 410 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 179;
}}
   break;
   case 16:
#line 449 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}}
   break;
   case 17:
#line 212 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}}
   break;
   case 18:
#line 299 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}}
   break;
   case 19:
#line 382 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 98;
   buf->data[buf->size++] = 104;
}}
   break;
   case 20:
#line 227 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 99;
   buf->data[buf->size++] = 104;
}}
   break;
   case 21:
#line 340 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 100;
   buf->data[buf->size++] = 104;
}}
   break;
   case 22:
#line 71 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 105;
}}
   break;
   case 23:
#line 105 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 24:
#line 199 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 103;
   buf->data[buf->size++] = 104;
}}
   break;
   case 25:
#line 114 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}}
   break;
   case 26:
#line 165 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}}
   break;
   case 27:
#line 404 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 104;
}}
   break;
   case 28:
#line 77 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 104;
}}
   break;
   case 29:
#line 192 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 187;
}}
   break;
   case 30:
#line 121 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}}
   break;
   case 31:
#line 98 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}}
   break;
   case 32:
#line 359 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 117;
}}
   break;
   case 33:
#line 326 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 112;
   buf->data[buf->size++] = 104;
}}
   break;
   case 34:
#line 242 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
   buf->data[buf->size++] = 104;
}}
   break;
   case 35:
#line 346 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}}
   break;
   case 36:
#line 429 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}}
   break;
   case 37:
#line 136 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 116;
   buf->data[buf->size++] = 104;
}}
   break;
   case 38:
#line 435 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}}
   break;
   case 39:
#line 128 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
   buf->data[buf->size++] = 104;
}}
   break;
   case 40:
#line 250 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 41:
#line 320 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}}
   break;
   case 42:
#line 8 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 43:
#line 38 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 44:
#line 311 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 45:
#line 142 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 46:
#line 205 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 47:
#line 374 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 48:
#line 89 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 49:
#line 45 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}}
   break;
   case 50:
#line 171 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}}
   break;
   case 51:
#line 395 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 52:
#line 286 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 53:
#line 16 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
}}
   break;
   case 54:
#line 271 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 55:
#line 277 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 56:
#line 8 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 57:
#line 38 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 58:
#line 311 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 59:
#line 142 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 60:
#line 205 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 61:
#line 374 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 62:
#line 89 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 63:
#line 45 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}}
   break;
   case 64:
#line 171 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}}
   break;
   case 65:
#line 395 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 66:
#line 286 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}}
   break;
   case 67:
#line 16 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
}}
   break;
   case 68:
#line 271 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}}
   break;
   case 69:
#line 277 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}}
   break;
   case 70:
#line 292 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 71:
#line 388 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}}
   break;
   case 72:
#line 177 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}}
   break;
   case 73:
#line 150 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}}
   break;
   case 74:
#line 185 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}}
   break;
   case 75:
#line 51 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 76:
#line 416 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}}
   break;
   case 77:
#line 441 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 104;
}}
   break;
   case 78:
#line 83 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 131;
}}
   break;
   case 79:
#line 536 "skt_translit_slp1_iastc.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 80:
#line 266 "skt_translit_slp1_iastc.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}}
   break;
   case 81:
#line 536 "skt_translit_slp1_iastc.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 942 "skt_translit_slp1_iastc.ic"
      }
   }

_again:
   _acts = _skt_translit_slp1_iastc_actions + _skt_translit_slp1_iastc_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 955 "skt_translit_slp1_iastc.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_slp1_iastc_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_slp1_iastc_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 557 "skt_translit_slp1_iastc.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 3 "skt_maps.ic"
#line 1 "skt_translit_iastc_iast.ic"

#line 1 "skt_translit_iastc_iast.rl"

#line 81 "skt_translit_iastc_iast.rl"


static void skt_translit_iastc_iast(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_iastc_iast.ic"
static const char _skt_translit_iastc_iast_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17
};

static const char _skt_translit_iastc_iast_key_offsets[] = {
   0, 1, 2, 3, 4, 5, 6, 7,
   8, 12, 13, 14, 15, 16, 17, 18,
   19
};

static const unsigned char _skt_translit_iastc_iast_trans_keys[] = {
   165u, 132u, 165u, 132u, 165u, 132u, 165u, 132u,
   76u, 82u, 108u, 114u, 204u, 204u, 204u, 204u,
   204u, 204u, 204u, 204u, 0
};

static const char _skt_translit_iastc_iast_single_lengths[] = {
   1, 1, 1, 1, 1, 1, 1, 1,
   4, 1, 1, 1, 1, 1, 1, 1,
   1
};

static const char _skt_translit_iastc_iast_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0
};

static const char _skt_translit_iastc_iast_index_offsets[] = {
   0, 2, 4, 6, 8, 10, 12, 14,
   16, 21, 23, 25, 27, 29, 31, 33,
   35
};

static const char _skt_translit_iastc_iast_trans_targs[] = {
   10, 8, 8, 8, 12, 8, 8, 8,
   14, 8, 8, 8, 16, 8, 8, 8,
   9, 11, 13, 15, 8, 0, 8, 1,
   8, 2, 8, 3, 8, 4, 8, 5,
   8, 6, 8, 7, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 0
};

static const char _skt_translit_iastc_iast_trans_actions[] = {
   5, 35, 7, 27, 5, 35, 9, 29,
   5, 35, 11, 31, 5, 35, 13, 33,
   5, 5, 5, 5, 15, 0, 25, 0,
   17, 0, 25, 0, 19, 0, 25, 0,
   21, 0, 25, 0, 23, 35, 27, 35,
   29, 35, 31, 35, 33, 25, 17, 25,
   19, 25, 21, 25, 23, 0
};

static const char _skt_translit_iastc_iast_to_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0,
   0
};

static const char _skt_translit_iastc_iast_from_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   3, 0, 0, 0, 0, 0, 0, 0,
   0
};

static const char _skt_translit_iastc_iast_eof_trans[] = {
   44, 39, 44, 41, 44, 43, 44, 45,
   0, 52, 47, 52, 49, 52, 51, 52,
   53
};

static const int skt_translit_iastc_iast_start = 8;
static const int skt_translit_iastc_iast_first_final = 8;
static const int skt_translit_iastc_iast_error = -1;

static const int skt_translit_iastc_iast_en_main = 8;


#line 94 "skt_translit_iastc_iast.rl"

#line 105 "skt_translit_iastc_iast.ic"
   {
   cs = skt_translit_iastc_iast_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 95 "skt_translit_iastc_iast.rl"

#line 115 "skt_translit_iastc_iast.ic"
   {
   int _klen;
   unsigned int _trans;
   const char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_iastc_iast_actions + _skt_translit_iastc_iast_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 134 "skt_translit_iastc_iast.ic"
      }
   }

   _keys = _skt_translit_iastc_iast_trans_keys + _skt_translit_iastc_iast_key_offsets[cs];
   _trans = _skt_translit_iastc_iast_index_offsets[cs];

   _klen = _skt_translit_iastc_iast_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_iastc_iast_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_iastc_iast_trans_targs[_trans];

   if ( _skt_translit_iastc_iast_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_iastc_iast_actions + _skt_translit_iastc_iast_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 1 "NONE"
   {te = p+1;}
   break;
   case 3:
#line 36 "skt_translit_iastc_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 184;
}}
   break;
   case 4:
#line 57 "skt_translit_iastc_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 156;
}}
   break;
   case 5:
#line 29 "skt_translit_iastc_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
}}
   break;
   case 6:
#line 8 "skt_translit_iastc_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
}}
   break;
   case 7:
#line 75 "skt_translit_iastc_iast.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 8:
#line 50 "skt_translit_iastc_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 182;
}}
   break;
   case 9:
#line 43 "skt_translit_iastc_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 154;
}}
   break;
   case 10:
#line 22 "skt_translit_iastc_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}}
   break;
   case 11:
#line 15 "skt_translit_iastc_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}}
   break;
   case 12:
#line 75 "skt_translit_iastc_iast.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 13:
#line 50 "skt_translit_iastc_iast.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 182;
}}
   break;
   case 14:
#line 43 "skt_translit_iastc_iast.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 154;
}}
   break;
   case 15:
#line 22 "skt_translit_iastc_iast.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}}
   break;
   case 16:
#line 15 "skt_translit_iastc_iast.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}}
   break;
   case 17:
#line 75 "skt_translit_iastc_iast.rl"
   {{p = ((te))-1;}{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 332 "skt_translit_iastc_iast.ic"
      }
   }

_again:
   _acts = _skt_translit_iastc_iast_actions + _skt_translit_iastc_iast_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 345 "skt_translit_iastc_iast.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_iastc_iast_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_iastc_iast_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 96 "skt_translit_iastc_iast.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 4 "skt_maps.ic"
#line 1 "skt_translit_iast_nagari.ic"

#line 1 "skt_translit_iast_nagari.rl"

#line 1116 "skt_translit_iast_nagari.rl"


static void skt_translit_iast_nagari(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_iast_nagari.ic"
static const short _skt_translit_iast_nagari_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41, 1, 42, 1,
   43, 1, 44, 1, 45, 1, 46, 1,
   47, 1, 48, 1, 49, 1, 50, 1,
   51, 1, 52, 1, 53, 1, 54, 1,
   55, 1, 56, 1, 57, 1, 58, 1,
   59, 1, 60, 1, 61, 1, 62, 1,
   63, 1, 64, 1, 65, 1, 66, 1,
   67, 1, 68, 1, 69, 1, 70, 1,
   71, 1, 72, 1, 73, 1, 74, 1,
   75, 1, 76, 1, 77, 1, 78, 1,
   79, 1, 80, 1, 81, 1, 82, 1,
   83, 1, 84, 1, 85, 1, 86, 1,
   87, 1, 88, 1, 89, 1, 90, 1,
   91, 1, 92, 1, 93, 1, 94, 1,
   95, 1, 96, 1, 97, 1, 98, 1,
   99, 1, 100, 1, 101, 1, 102, 1,
   103, 1, 104, 1, 105, 1, 106, 1,
   107, 1, 108, 1, 109, 1, 110, 1,
   111, 1, 112, 1, 113, 1, 114, 1,
   115, 1, 116, 1, 117, 1, 118, 1,
   119, 1, 120, 1, 121, 1, 122, 1,
   123, 1, 124, 1, 125, 1, 126, 1,
   127, 1, 128, 1, 129, 1, 130, 1,
   131, 1, 132, 1, 133, 1, 134, 1,
   135, 1, 136, 1, 137, 1, 138, 1,
   139, 1, 140, 1, 141, 1, 142, 1,
   143, 1, 144, 1, 145, 1, 146, 1,
   147, 1, 148, 1, 149, 1, 150, 1,
   151, 1, 152, 1, 153, 1, 154, 1,
   155, 1, 156, 1, 157, 1, 158, 1,
   159, 1, 160, 1, 161, 1, 162, 1,
   163, 1, 164, 1, 165, 1, 166, 1,
   167, 1, 168, 1, 169, 1, 170, 1,
   171, 1, 172, 1, 173, 1, 174, 1,
   175, 1, 176, 1, 177, 1, 178, 1,
   179, 1, 180, 1, 181, 1, 182, 1,
   183, 1, 184, 1, 185, 1, 186, 1,
   187, 1, 188, 1, 189, 1, 190, 1,
   191, 1, 192, 1, 193, 1, 194, 1,
   195, 1, 196, 1, 197, 1, 198, 1,
   199, 1, 200, 1, 201, 1, 202, 1,
   203, 1, 204, 1, 205, 1, 206, 1,
   207, 1, 208, 1, 209, 1, 210, 1,
   211, 1, 212, 1, 213, 1, 214, 1,
   215, 1, 216, 1, 217, 1, 218, 1,
   219, 1, 220, 1, 221, 1, 222, 1,
   223, 1, 224, 1, 225, 1, 226, 1,
   227, 1, 228, 1, 229, 1, 230, 1,
   231, 1, 232, 1, 233, 1, 234, 1,
   235, 1, 236, 1, 237, 1, 238, 1,
   239, 1, 240, 1, 241, 1, 242, 1,
   243, 1, 244, 1, 245, 1, 246, 1,
   247, 1, 248, 1, 249, 1, 250, 1,
   251, 1, 252, 1, 253, 1, 254, 1,
   255, 1, 256, 1, 257, 1, 258, 1,
   259, 1, 260, 1, 261, 1, 262, 1,
   263, 1, 264, 1, 265, 1, 266, 1,
   267, 1, 268, 1, 269, 1, 270, 1,
   271, 1, 272, 1, 273, 1, 274, 1,
   275, 1, 276, 1, 277, 1, 278, 1,
   279, 1, 280, 1, 281, 1, 282, 1,
   283, 1, 284, 1, 285, 1, 286, 1,
   287, 1, 288, 1, 289, 1, 290, 1,
   291, 1, 292, 1, 293
};

static const short _skt_translit_iast_nagari_key_offsets[] = {
   0, 4, 5, 6, 7, 8, 12, 13,
   14, 15, 16, 17, 18, 19, 20, 21,
   22, 32, 33, 34, 48, 49, 50, 51,
   52, 56, 57, 58, 59, 60, 64, 65,
   66, 67, 68, 69, 70, 71, 72, 73,
   74, 78, 79, 80, 84, 85, 86, 87,
   88, 146, 151, 153, 155, 157, 159, 161,
   163, 164, 165, 167, 168, 169, 171, 176,
   178, 180, 182, 184, 186, 188, 189, 190,
   192, 193, 194, 196, 197, 209, 213, 214,
   215, 216, 217, 221, 222, 223, 225, 227,
   229, 230, 231, 232, 233, 234, 235, 237,
   239, 257, 262, 263, 264, 265, 266, 271,
   272, 273, 274, 275, 285, 289, 290, 291,
   292, 293, 295, 296, 297, 299, 300, 301,
   302, 303, 304
};

static const unsigned char _skt_translit_iast_nagari_trans_keys[] = {
   141u, 154u, 173u, 186u, 165u, 132u, 165u, 132u,
   141u, 154u, 173u, 186u, 165u, 132u, 165u, 132u,
   129u, 129u, 129u, 129u, 129u, 129u, 140u, 141u,
   164u, 165u, 182u, 183u, 184u, 185u, 186u, 187u,
   129u, 129u, 130u, 131u, 132u, 133u, 134u, 135u,
   154u, 155u, 156u, 157u, 162u, 163u, 172u, 173u,
   129u, 129u, 129u, 129u, 141u, 154u, 173u, 186u,
   165u, 132u, 165u, 132u, 141u, 154u, 173u, 186u,
   165u, 132u, 165u, 132u, 129u, 129u, 129u, 129u,
   129u, 129u, 182u, 183u, 184u, 185u, 129u, 129u,
   154u, 155u, 156u, 157u, 129u, 129u, 129u, 129u,
   39u, 48u, 49u, 50u, 51u, 52u, 53u, 54u,
   55u, 56u, 57u, 65u, 66u, 67u, 68u, 69u,
   71u, 72u, 73u, 74u, 75u, 76u, 77u, 78u,
   79u, 80u, 82u, 83u, 84u, 85u, 86u, 89u,
   97u, 98u, 99u, 100u, 101u, 103u, 104u, 105u,
   106u, 107u, 108u, 109u, 110u, 111u, 112u, 114u,
   115u, 116u, 117u, 118u, 121u, 124u, 195u, 196u,
   197u, 225u, 73u, 85u, 105u, 117u, 195u, 72u,
   104u, 72u, 104u, 72u, 104u, 72u, 104u, 72u,
   104u, 72u, 104u, 204u, 204u, 72u, 104u, 204u,
   204u, 72u, 104u, 73u, 85u, 105u, 117u, 195u,
   72u, 104u, 72u, 104u, 72u, 104u, 72u, 104u,
   72u, 104u, 72u, 104u, 204u, 204u, 72u, 104u,
   204u, 204u, 72u, 104u, 124u, 129u, 137u, 141u,
   145u, 147u, 154u, 161u, 169u, 173u, 177u, 179u,
   186u, 128u, 129u, 170u, 171u, 204u, 204u, 204u,
   204u, 154u, 155u, 170u, 171u, 204u, 204u, 184u,
   185u, 72u, 104u, 72u, 104u, 204u, 204u, 204u,
   204u, 204u, 204u, 72u, 104u, 72u, 104u, 65u,
   69u, 73u, 76u, 79u, 82u, 85u, 97u, 101u,
   105u, 108u, 111u, 114u, 117u, 195u, 196u, 197u,
   225u, 73u, 85u, 105u, 117u, 195u, 204u, 204u,
   204u, 204u, 73u, 85u, 105u, 117u, 195u, 204u,
   204u, 204u, 204u, 129u, 137u, 141u, 147u, 154u,
   161u, 169u, 173u, 179u, 186u, 128u, 129u, 170u,
   171u, 204u, 204u, 204u, 204u, 170u, 171u, 204u,
   204u, 184u, 185u, 204u, 204u, 204u, 204u, 204u,
   204u, 0
};

static const char _skt_translit_iast_nagari_single_lengths[] = {
   4, 1, 1, 1, 1, 4, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1,
   10, 1, 1, 14, 1, 1, 1, 1,
   4, 1, 1, 1, 1, 4, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1,
   4, 1, 1, 4, 1, 1, 1, 1,
   58, 5, 2, 2, 2, 2, 2, 2,
   1, 1, 2, 1, 1, 2, 5, 2,
   2, 2, 2, 2, 2, 1, 1, 2,
   1, 1, 2, 1, 12, 4, 1, 1,
   1, 1, 4, 1, 1, 2, 2, 2,
   1, 1, 1, 1, 1, 1, 2, 2,
   18, 5, 1, 1, 1, 1, 5, 1,
   1, 1, 1, 10, 4, 1, 1, 1,
   1, 2, 1, 1, 2, 1, 1, 1,
   1, 1, 1
};

static const char _skt_translit_iast_nagari_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0
};

static const short _skt_translit_iast_nagari_index_offsets[] = {
   0, 5, 7, 9, 11, 13, 18, 20,
   22, 24, 26, 28, 30, 32, 34, 36,
   38, 49, 51, 53, 68, 70, 72, 74,
   76, 81, 83, 85, 87, 89, 94, 96,
   98, 100, 102, 104, 106, 108, 110, 112,
   114, 119, 121, 123, 128, 130, 132, 134,
   136, 195, 201, 204, 207, 210, 213, 216,
   219, 221, 223, 226, 228, 230, 233, 239,
   242, 245, 248, 251, 254, 257, 259, 261,
   264, 266, 268, 271, 273, 286, 291, 293,
   295, 297, 299, 304, 306, 308, 311, 314,
   317, 319, 321, 323, 325, 327, 329, 332,
   335, 354, 360, 362, 364, 366, 368, 374,
   376, 378, 380, 382, 393, 398, 400, 402,
   404, 406, 409, 411, 413, 416, 418, 420,
   422, 424, 426
};

static const char _skt_translit_iast_nagari_trans_targs[] = {
   48, 48, 48, 48, 48, 57, 48, 48,
   48, 60, 48, 48, 48, 48, 48, 48,
   48, 48, 70, 48, 48, 48, 73, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 86, 87,
   48, 48, 88, 89, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 90, 91, 92, 93, 48,
   48, 94, 95, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 96, 96, 96, 96,
   96, 99, 96, 96, 96, 101, 96, 96,
   96, 96, 96, 96, 96, 96, 104, 96,
   96, 96, 106, 96, 96, 96, 96, 96,
   96, 96, 96, 96, 96, 96, 96, 96,
   96, 96, 117, 118, 96, 96, 96, 96,
   96, 96, 96, 119, 120, 121, 122, 96,
   96, 96, 96, 96, 96, 96, 96, 96,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 49, 50, 51, 52, 48,
   53, 48, 48, 54, 55, 56, 48, 48,
   48, 58, 59, 48, 61, 48, 48, 48,
   62, 63, 64, 65, 48, 66, 48, 48,
   67, 68, 69, 48, 48, 48, 71, 72,
   48, 74, 48, 48, 48, 75, 76, 77,
   82, 85, 48, 48, 48, 48, 48, 0,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 1, 48, 2, 48, 48,
   48, 48, 3, 48, 4, 48, 48, 48,
   48, 48, 48, 48, 48, 5, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 6, 48, 7, 48, 48, 48, 48,
   8, 48, 9, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 78, 79,
   80, 81, 48, 10, 48, 11, 48, 12,
   48, 13, 48, 48, 48, 83, 84, 48,
   14, 48, 15, 48, 16, 19, 48, 48,
   48, 48, 48, 48, 48, 17, 48, 18,
   48, 20, 48, 21, 48, 22, 48, 23,
   48, 48, 48, 48, 48, 48, 48, 97,
   96, 96, 98, 96, 100, 96, 102, 96,
   96, 103, 96, 105, 96, 107, 108, 113,
   116, 96, 96, 96, 96, 96, 24, 96,
   25, 96, 26, 96, 27, 96, 28, 96,
   96, 96, 96, 96, 29, 96, 30, 96,
   31, 96, 32, 96, 33, 96, 96, 96,
   96, 96, 96, 96, 96, 96, 96, 96,
   96, 109, 110, 111, 112, 96, 34, 96,
   35, 96, 36, 96, 37, 96, 114, 115,
   96, 38, 96, 39, 96, 40, 43, 96,
   41, 96, 42, 96, 44, 96, 45, 96,
   46, 96, 47, 96, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 96, 96, 96, 96,
   96, 96, 96, 96, 96, 96, 96, 96,
   96, 96, 96, 96, 96, 96, 96, 96,
   96, 96, 96, 96, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 48, 48, 48, 48, 48,
   48, 48, 48, 96, 96, 96, 96, 96,
   96, 96, 96, 96, 96, 96, 96, 96,
   96, 96, 96, 96, 96, 96, 96, 96,
   96, 96, 96, 96, 96, 0
};

static const short _skt_translit_iast_nagari_trans_actions[] = {
   197, 199, 201, 203, 543, 5, 579, 209,
   547, 5, 581, 213, 549, 225, 227, 229,
   231, 545, 5, 583, 237, 551, 5, 585,
   241, 553, 265, 555, 267, 557, 269, 559,
   271, 561, 273, 563, 275, 565, 0, 0,
   317, 319, 5, 5, 281, 283, 429, 431,
   587, 277, 567, 279, 569, 321, 323, 433,
   435, 437, 439, 5, 5, 5, 5, 441,
   443, 0, 0, 587, 285, 571, 287, 573,
   289, 575, 291, 577, 21, 55, 87, 107,
   183, 5, 187, 19, 169, 5, 187, 65,
   151, 23, 79, 61, 57, 185, 5, 187,
   17, 167, 5, 187, 91, 165, 47, 179,
   101, 157, 7, 155, 85, 163, 13, 177,
   105, 153, 5, 5, 99, 31, 187, 11,
   161, 43, 175, 5, 5, 5, 5, 187,
   67, 159, 35, 171, 77, 181, 51, 173,
   293, 295, 297, 299, 301, 303, 305, 307,
   309, 311, 313, 5, 0, 0, 0, 205,
   0, 341, 207, 0, 0, 5, 351, 353,
   211, 0, 5, 359, 0, 215, 365, 367,
   5, 0, 0, 0, 233, 0, 385, 235,
   0, 0, 5, 395, 397, 239, 0, 5,
   403, 0, 243, 409, 411, 0, 0, 0,
   0, 5, 453, 189, 191, 193, 195, 0,
   455, 325, 327, 493, 329, 331, 495, 333,
   335, 497, 337, 339, 499, 343, 345, 501,
   347, 349, 503, 0, 505, 0, 459, 355,
   357, 507, 0, 509, 0, 461, 361, 363,
   511, 217, 219, 221, 223, 0, 457, 369,
   371, 513, 373, 375, 515, 377, 379, 517,
   381, 383, 519, 387, 389, 521, 391, 393,
   523, 0, 525, 0, 463, 399, 401, 527,
   0, 529, 0, 465, 405, 407, 531, 315,
   491, 245, 247, 249, 413, 251, 253, 255,
   257, 259, 415, 261, 263, 541, 5, 5,
   5, 5, 541, 0, 467, 0, 469, 0,
   471, 0, 473, 417, 419, 5, 5, 541,
   0, 475, 0, 477, 0, 0, 541, 421,
   423, 533, 425, 427, 535, 0, 479, 0,
   481, 0, 483, 0, 485, 0, 487, 0,
   489, 445, 447, 537, 449, 451, 539, 5,
   27, 9, 5, 71, 5, 59, 5, 83,
   75, 5, 53, 5, 69, 0, 0, 0,
   5, 111, 49, 97, 93, 109, 0, 145,
   0, 149, 0, 131, 0, 149, 0, 113,
   73, 103, 89, 15, 0, 147, 0, 149,
   0, 129, 0, 149, 0, 127, 39, 63,
   25, 45, 29, 37, 33, 41, 81, 95,
   149, 5, 5, 5, 5, 149, 0, 141,
   0, 119, 0, 117, 0, 125, 5, 5,
   149, 0, 139, 0, 115, 0, 0, 149,
   0, 123, 0, 137, 0, 121, 0, 133,
   0, 143, 0, 135, 543, 579, 547, 581,
   549, 545, 583, 551, 585, 553, 555, 557,
   559, 561, 563, 565, 587, 567, 569, 587,
   571, 573, 575, 577, 183, 187, 169, 187,
   151, 185, 187, 167, 187, 165, 179, 157,
   155, 163, 177, 153, 187, 161, 175, 187,
   159, 171, 181, 173, 455, 493, 495, 497,
   499, 501, 503, 505, 459, 507, 509, 461,
   511, 457, 513, 515, 517, 519, 521, 523,
   525, 463, 527, 529, 465, 531, 491, 541,
   541, 467, 469, 471, 473, 541, 475, 477,
   541, 533, 535, 479, 481, 483, 485, 487,
   489, 537, 539, 145, 149, 131, 149, 113,
   147, 149, 129, 149, 127, 149, 149, 141,
   119, 117, 125, 149, 139, 115, 149, 123,
   137, 121, 133, 143, 135, 0
};

static const short _skt_translit_iast_nagari_to_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0
};

static const short _skt_translit_iast_nagari_from_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   3, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   3, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0
};

static const short _skt_translit_iast_nagari_eof_trans[] = {
   429, 430, 431, 432, 433, 434, 435, 436,
   437, 438, 439, 440, 441, 442, 443, 444,
   448, 446, 447, 448, 449, 450, 451, 452,
   453, 472, 455, 472, 457, 458, 472, 460,
   472, 462, 463, 464, 465, 466, 467, 468,
   472, 470, 471, 472, 473, 474, 475, 476,
   0, 477, 478, 479, 480, 481, 482, 483,
   484, 485, 486, 487, 488, 489, 490, 491,
   492, 493, 494, 495, 496, 497, 498, 499,
   500, 501, 502, 503, 513, 513, 506, 507,
   508, 509, 513, 511, 512, 513, 514, 515,
   516, 517, 518, 519, 520, 521, 522, 523,
   0, 524, 543, 526, 543, 528, 529, 543,
   531, 543, 533, 543, 543, 536, 537, 538,
   539, 543, 541, 542, 543, 544, 545, 546,
   547, 548, 549
};

static const int skt_translit_iast_nagari_start = 48;
static const int skt_translit_iast_nagari_first_final = 48;
static const int skt_translit_iast_nagari_error = -1;

static const int skt_translit_iast_nagari_en_from_consonant = 96;
static const int skt_translit_iast_nagari_en_main = 48;


#line 1129 "skt_translit_iast_nagari.rl"

#line 426 "skt_translit_iast_nagari.ic"
   {
   cs = skt_translit_iast_nagari_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 1130 "skt_translit_iast_nagari.rl"

#line 436 "skt_translit_iast_nagari.ic"
   {
   int _klen;
   unsigned int _trans;
   const short *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_iast_nagari_actions + _skt_translit_iast_nagari_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 455 "skt_translit_iast_nagari.ic"
      }
   }

   _keys = _skt_translit_iast_nagari_trans_keys + _skt_translit_iast_nagari_key_offsets[cs];
   _trans = _skt_translit_iast_nagari_index_offsets[cs];

   _klen = _skt_translit_iast_nagari_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_iast_nagari_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_iast_nagari_trans_targs[_trans];

   if ( _skt_translit_iast_nagari_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_iast_nagari_actions + _skt_translit_iast_nagari_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 1 "NONE"
   {te = p+1;}
   break;
   case 3:
#line 667 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 4:
#line 640 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 191;
   {cs = 48; goto _again;}
}}
   break;
   case 5:
#line 743 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 6:
#line 705 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 7:
#line 811 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   {cs = 48; goto _again;}
}}
   break;
   case 8:
#line 838 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 163;
   {cs = 48; goto _again;}
}}
   break;
   case 9:
#line 838 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 163;
   {cs = 48; goto _again;}
}}
   break;
   case 10:
#line 781 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 11:
#line 781 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 12:
#line 648 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 191;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 13:
#line 754 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 135;
   {cs = 48; goto _again;}
}}
   break;
   case 14:
#line 686 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 15:
#line 838 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 163;
   {cs = 48; goto _again;}
}}
   break;
   case 16:
#line 762 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 135;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 17:
#line 724 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 18:
#line 613 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 19:
#line 613 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 20:
#line 648 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 191;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 21:
#line 743 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 22:
#line 800 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 139;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 23:
#line 629 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 24:
#line 773 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   {cs = 48; goto _again;}
}}
   break;
   case 25:
#line 724 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 26:
#line 792 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 139;
   {cs = 48; goto _again;}
}}
   break;
   case 27:
#line 819 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 28:
#line 819 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 29:
#line 678 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 129;
   {cs = 48; goto _again;}
}}
   break;
   case 30:
#line 781 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 31:
#line 762 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 135;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 32:
#line 830 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   {cs = 48; goto _again;}
}}
   break;
   case 33:
#line 724 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 34:
#line 678 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 129;
   {cs = 48; goto _again;}
}}
   break;
   case 35:
#line 792 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 139;
   {cs = 48; goto _again;}
}}
   break;
   case 36:
#line 773 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   {cs = 48; goto _again;}
}}
   break;
   case 37:
#line 640 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 191;
   {cs = 48; goto _again;}
}}
   break;
   case 38:
#line 724 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 39:
#line 819 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 40:
#line 800 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 139;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 41:
#line 754 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 135;
   {cs = 48; goto _again;}
}}
   break;
   case 42:
#line 667 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 43:
#line 781 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 44:
#line 773 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   {cs = 48; goto _again;}
}}
   break;
   case 45:
#line 830 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   {cs = 48; goto _again;}
}}
   break;
   case 46:
#line 773 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   {cs = 48; goto _again;}
}}
   break;
   case 47:
#line 686 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 48:
#line 811 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   {cs = 48; goto _again;}
}}
   break;
   case 49:
#line 838 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 163;
   {cs = 48; goto _again;}
}}
   break;
   case 50:
#line 629 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 51:
#line 811 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   {cs = 48; goto _again;}
}}
   break;
   case 52:
#line 705 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 53:
#line 819 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   {cs = 48; goto _again;}
}}
   break;
   case 54:
#line 811 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   {cs = 48; goto _again;}
}}
   break;
   case 55:
#line 846 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   p--;
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 141;
   {cs = 48; goto _again;}
}}
   break;
   case 56:
#line 716 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 57:
#line 697 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   {cs = 48; goto _again;}
}}
   break;
   case 58:
#line 659 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   {cs = 48; goto _again;}
}}
   break;
   case 59:
#line 621 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   {cs = 48; goto _again;}
}}
   break;
   case 60:
#line 716 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 61:
#line 735 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 62:
#line 659 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   {cs = 48; goto _again;}
}}
   break;
   case 63:
#line 716 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 64:
#line 735 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 65:
#line 735 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 66:
#line 716 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 67:
#line 830 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   {cs = 48; goto _again;}
}}
   break;
   case 68:
#line 735 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 69:
#line 697 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   {cs = 48; goto _again;}
}}
   break;
   case 70:
#line 621 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   {cs = 48; goto _again;}
}}
   break;
   case 71:
#line 830 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   {cs = 48; goto _again;}
}}
   break;
   case 72:
#line 855 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   {cs = 48; goto _again;}
}}
   break;
   case 73:
#line 855 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   {cs = 48; goto _again;}
}}
   break;
   case 74:
#line 846 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   p--;
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 141;
   {cs = 48; goto _again;}
}}
   break;
   case 75:
#line 716 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 76:
#line 697 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   {cs = 48; goto _again;}
}}
   break;
   case 77:
#line 659 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   {cs = 48; goto _again;}
}}
   break;
   case 78:
#line 621 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   {cs = 48; goto _again;}
}}
   break;
   case 79:
#line 716 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 80:
#line 735 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 81:
#line 659 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   {cs = 48; goto _again;}
}}
   break;
   case 82:
#line 716 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 83:
#line 735 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 84:
#line 735 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 85:
#line 716 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   {cs = 48; goto _again;}
}}
   break;
   case 86:
#line 830 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   {cs = 48; goto _again;}
}}
   break;
   case 87:
#line 735 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   {cs = 48; goto _again;}
}}
   break;
   case 88:
#line 697 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   {cs = 48; goto _again;}
}}
   break;
   case 89:
#line 621 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   {cs = 48; goto _again;}
}}
   break;
   case 90:
#line 830 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   {cs = 48; goto _again;}
}}
   break;
   case 91:
#line 855 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   {cs = 48; goto _again;}
}}
   break;
   case 92:
#line 855 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   {cs = 48; goto _again;}
}}
   break;
   case 93:
#line 846 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   p--;
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 141;
   {cs = 48; goto _again;}
}}
   break;
   case 94:
#line 161 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
}}
   break;
   case 95:
#line 195 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
}}
   break;
   case 96:
#line 161 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
}}
   break;
   case 97:
#line 195 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
}}
   break;
   case 98:
#line 168 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 99:
#line 202 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 100:
#line 168 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 101:
#line 202 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 102:
#line 144 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 143;
}}
   break;
   case 103:
#line 42 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 135;
}}
   break;
   case 104:
#line 229 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 161;
}}
   break;
   case 105:
#line 178 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 147;
}}
   break;
   case 106:
#line 212 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
}}
   break;
   case 107:
#line 76 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 137;
}}
   break;
   case 108:
#line 161 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
}}
   break;
   case 109:
#line 195 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
}}
   break;
   case 110:
#line 161 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
}}
   break;
   case 111:
#line 195 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
}}
   break;
   case 112:
#line 168 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 113:
#line 202 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 114:
#line 168 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 115:
#line 202 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 116:
#line 144 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 143;
}}
   break;
   case 117:
#line 42 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 135;
}}
   break;
   case 118:
#line 229 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 161;
}}
   break;
   case 119:
#line 178 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 147;
}}
   break;
   case 120:
#line 212 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
}}
   break;
   case 121:
#line 76 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 137;
}}
   break;
   case 122:
#line 15 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 123:
#line 151 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 143;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 124:
#line 49 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 135;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 125:
#line 185 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 147;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 126:
#line 83 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 137;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 127:
#line 15 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 128:
#line 151 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 143;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 129:
#line 49 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 135;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 130:
#line 185 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 147;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 131:
#line 83 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 137;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 132:
#line 32 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 133:
#line 32 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 134:
#line 66 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 135:
#line 66 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 136:
#line 100 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 137:
#line 100 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 138:
#line 134 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 139:
#line 134 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 140:
#line 229 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 161;
}}
   break;
   case 141:
#line 229 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 161;
}}
   break;
   case 142:
#line 117 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 143:
#line 117 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 144:
#line 219 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 145:
#line 219 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}}
   break;
   case 146:
#line 250 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 189;
}}
   break;
   case 147:
#line 271 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 166;
}}
   break;
   case 148:
#line 278 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 167;
}}
   break;
   case 149:
#line 285 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 168;
}}
   break;
   case 150:
#line 292 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 169;
}}
   break;
   case 151:
#line 299 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 170;
}}
   break;
   case 152:
#line 306 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 171;
}}
   break;
   case 153:
#line 313 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 172;
}}
   break;
   case 154:
#line 320 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 173;
}}
   break;
   case 155:
#line 327 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 174;
}}
   break;
   case 156:
#line 334 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 175;
}}
   break;
   case 157:
#line 264 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 165;
}}
   break;
   case 158:
#line 243 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 131;
}}
   break;
   case 159:
#line 243 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 131;
}}
   break;
   case 160:
#line 236 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 130;
}}
   break;
   case 161:
#line 236 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 130;
}}
   break;
   case 162:
#line 525 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 173;
   {cs = 96; goto _again;}
}}
   break;
   case 163:
#line 525 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 173;
   {cs = 96; goto _again;}
}}
   break;
   case 164:
#line 389 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 155;
   {cs = 96; goto _again;}
}}
   break;
   case 165:
#line 389 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 155;
   {cs = 96; goto _again;}
}}
   break;
   case 166:
#line 485 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 167;
   {cs = 96; goto _again;}
}}
   break;
   case 167:
#line 485 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 167;
   {cs = 96; goto _again;}
}}
   break;
   case 168:
#line 365 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 152;
   {cs = 96; goto _again;}
}}
   break;
   case 169:
#line 365 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 152;
   {cs = 96; goto _again;}
}}
   break;
   case 170:
#line 605 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 185;
   {cs = 96; goto _again;}
}}
   break;
   case 171:
#line 405 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 157;
   {cs = 96; goto _again;}
}}
   break;
   case 172:
#line 405 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 157;
   {cs = 96; goto _again;}
}}
   break;
   case 173:
#line 349 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 150;
   {cs = 96; goto _again;}
}}
   break;
   case 174:
#line 349 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 150;
   {cs = 96; goto _again;}
}}
   break;
   case 175:
#line 533 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 174;
   {cs = 96; goto _again;}
}}
   break;
   case 176:
#line 493 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 168;
   {cs = 96; goto _again;}
}}
   break;
   case 177:
#line 509 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 171;
   {cs = 96; goto _again;}
}}
   break;
   case 178:
#line 509 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 171;
   {cs = 96; goto _again;}
}}
   break;
   case 179:
#line 597 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 184;
   {cs = 96; goto _again;}
}}
   break;
   case 180:
#line 469 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 165;
   {cs = 96; goto _again;}
}}
   break;
   case 181:
#line 469 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 165;
   {cs = 96; goto _again;}
}}
   break;
   case 182:
#line 573 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 181;
   {cs = 96; goto _again;}
}}
   break;
   case 183:
#line 541 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 175;
   {cs = 96; goto _again;}
}}
   break;
   case 184:
#line 525 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 173;
   {cs = 96; goto _again;}
}}
   break;
   case 185:
#line 525 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 173;
   {cs = 96; goto _again;}
}}
   break;
   case 186:
#line 389 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 155;
   {cs = 96; goto _again;}
}}
   break;
   case 187:
#line 389 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 155;
   {cs = 96; goto _again;}
}}
   break;
   case 188:
#line 485 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 167;
   {cs = 96; goto _again;}
}}
   break;
   case 189:
#line 485 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 167;
   {cs = 96; goto _again;}
}}
   break;
   case 190:
#line 365 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 152;
   {cs = 96; goto _again;}
}}
   break;
   case 191:
#line 365 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 152;
   {cs = 96; goto _again;}
}}
   break;
   case 192:
#line 605 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 185;
   {cs = 96; goto _again;}
}}
   break;
   case 193:
#line 405 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 157;
   {cs = 96; goto _again;}
}}
   break;
   case 194:
#line 405 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 157;
   {cs = 96; goto _again;}
}}
   break;
   case 195:
#line 349 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 150;
   {cs = 96; goto _again;}
}}
   break;
   case 196:
#line 349 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 150;
   {cs = 96; goto _again;}
}}
   break;
   case 197:
#line 533 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 174;
   {cs = 96; goto _again;}
}}
   break;
   case 198:
#line 493 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 168;
   {cs = 96; goto _again;}
}}
   break;
   case 199:
#line 509 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 171;
   {cs = 96; goto _again;}
}}
   break;
   case 200:
#line 509 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 171;
   {cs = 96; goto _again;}
}}
   break;
   case 201:
#line 597 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 184;
   {cs = 96; goto _again;}
}}
   break;
   case 202:
#line 469 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 165;
   {cs = 96; goto _again;}
}}
   break;
   case 203:
#line 469 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 165;
   {cs = 96; goto _again;}
}}
   break;
   case 204:
#line 573 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 181;
   {cs = 96; goto _again;}
}}
   break;
   case 205:
#line 541 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 175;
   {cs = 96; goto _again;}
}}
   break;
   case 206:
#line 413 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 158;
   {cs = 96; goto _again;}
}}
   break;
   case 207:
#line 413 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 158;
   {cs = 96; goto _again;}
}}
   break;
   case 208:
#line 581 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 182;
   {cs = 96; goto _again;}
}}
   break;
   case 209:
#line 581 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 182;
   {cs = 96; goto _again;}
}}
   break;
   case 210:
#line 445 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 162;
   {cs = 96; goto _again;}
}}
   break;
   case 211:
#line 445 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 162;
   {cs = 96; goto _again;}
}}
   break;
   case 212:
#line 445 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 162;
   {cs = 96; goto _again;}
}}
   break;
   case 213:
#line 445 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 162;
   {cs = 96; goto _again;}
}}
   break;
   case 214:
#line 565 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 179;
   {cs = 96; goto _again;}
}}
   break;
   case 215:
#line 565 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 179;
   {cs = 96; goto _again;}
}}
   break;
   case 216:
#line 373 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 153;
   {cs = 96; goto _again;}
}}
   break;
   case 217:
#line 373 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 153;
   {cs = 96; goto _again;}
}}
   break;
   case 218:
#line 453 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 163;
   {cs = 96; goto _again;}
}}
   break;
   case 219:
#line 453 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 163;
   {cs = 96; goto _again;}
}}
   break;
   case 220:
#line 589 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 183;
   {cs = 96; goto _again;}
}}
   break;
   case 221:
#line 589 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 183;
   {cs = 96; goto _again;}
}}
   break;
   case 222:
#line 429 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 160;
   {cs = 96; goto _again;}
}}
   break;
   case 223:
#line 429 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 160;
   {cs = 96; goto _again;}
}}
   break;
   case 224:
#line 429 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 160;
   {cs = 96; goto _again;}
}}
   break;
   case 225:
#line 429 "skt_translit_iast_nagari.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 160;
   {cs = 96; goto _again;}
}}
   break;
   case 226:
#line 1110 "skt_translit_iast_nagari.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 227:
#line 8 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
}}
   break;
   case 228:
#line 8 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
}}
   break;
   case 229:
#line 127 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 230:
#line 110 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 231:
#line 127 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 232:
#line 110 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 233:
#line 25 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
}}
   break;
   case 234:
#line 25 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
}}
   break;
   case 235:
#line 59 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
}}
   break;
   case 236:
#line 59 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
}}
   break;
   case 237:
#line 93 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
}}
   break;
   case 238:
#line 93 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
}}
   break;
   case 239:
#line 127 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 240:
#line 127 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 241:
#line 110 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 242:
#line 110 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 243:
#line 212 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
}}
   break;
   case 244:
#line 212 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
}}
   break;
   case 245:
#line 257 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 164;
}}
   break;
   case 246:
#line 517 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 172;
   {cs = 96; goto _again;}
}}
   break;
   case 247:
#line 381 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 154;
   {cs = 96; goto _again;}
}}
   break;
   case 248:
#line 477 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 166;
   {cs = 96; goto _again;}
}}
   break;
   case 249:
#line 357 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 151;
   {cs = 96; goto _again;}
}}
   break;
   case 250:
#line 397 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 156;
   {cs = 96; goto _again;}
}}
   break;
   case 251:
#line 341 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 149;
   {cs = 96; goto _again;}
}}
   break;
   case 252:
#line 557 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 178;
   {cs = 96; goto _again;}
}}
   break;
   case 253:
#line 501 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 170;
   {cs = 96; goto _again;}
}}
   break;
   case 254:
#line 549 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 176;
   {cs = 96; goto _again;}
}}
   break;
   case 255:
#line 461 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 164;
   {cs = 96; goto _again;}
}}
   break;
   case 256:
#line 517 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 172;
   {cs = 96; goto _again;}
}}
   break;
   case 257:
#line 381 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 154;
   {cs = 96; goto _again;}
}}
   break;
   case 258:
#line 477 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 166;
   {cs = 96; goto _again;}
}}
   break;
   case 259:
#line 357 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 151;
   {cs = 96; goto _again;}
}}
   break;
   case 260:
#line 397 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 156;
   {cs = 96; goto _again;}
}}
   break;
   case 261:
#line 341 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 149;
   {cs = 96; goto _again;}
}}
   break;
   case 262:
#line 557 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 178;
   {cs = 96; goto _again;}
}}
   break;
   case 263:
#line 501 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 170;
   {cs = 96; goto _again;}
}}
   break;
   case 264:
#line 549 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 176;
   {cs = 96; goto _again;}
}}
   break;
   case 265:
#line 461 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 164;
   {cs = 96; goto _again;}
}}
   break;
   case 266:
#line 437 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 161;
   {cs = 96; goto _again;}
}}
   break;
   case 267:
#line 437 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 161;
   {cs = 96; goto _again;}
}}
   break;
   case 268:
#line 421 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 159;
   {cs = 96; goto _again;}
}}
   break;
   case 269:
#line 421 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 159;
   {cs = 96; goto _again;}
}}
   break;
   case 270:
#line 1110 "skt_translit_iast_nagari.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 271:
#line 8 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
}}
   break;
   case 272:
#line 8 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
}}
   break;
   case 273:
#line 127 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 274:
#line 110 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 275:
#line 127 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 276:
#line 110 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 277:
#line 25 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
}}
   break;
   case 278:
#line 25 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
}}
   break;
   case 279:
#line 59 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
}}
   break;
   case 280:
#line 59 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
}}
   break;
   case 281:
#line 93 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
}}
   break;
   case 282:
#line 93 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
}}
   break;
   case 283:
#line 127 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 284:
#line 127 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}}
   break;
   case 285:
#line 110 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 286:
#line 110 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}}
   break;
   case 287:
#line 212 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
}}
   break;
   case 288:
#line 212 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
}}
   break;
   case 289:
#line 557 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 178;
   {cs = 96; goto _again;}
}}
   break;
   case 290:
#line 549 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 176;
   {cs = 96; goto _again;}
}}
   break;
   case 291:
#line 557 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 178;
   {cs = 96; goto _again;}
}}
   break;
   case 292:
#line 549 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 176;
   {cs = 96; goto _again;}
}}
   break;
   case 293:
#line 1110 "skt_translit_iast_nagari.rl"
   {{p = ((te))-1;}{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 3481 "skt_translit_iast_nagari.ic"
      }
   }

_again:
   _acts = _skt_translit_iast_nagari_actions + _skt_translit_iast_nagari_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 3494 "skt_translit_iast_nagari.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_iast_nagari_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_iast_nagari_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 1131 "skt_translit_iast_nagari.rl"
   if (cs == skt_translit_iast_nagari_en_from_consonant) {
      skt_buf_grow(buf, 3);
      buf->data[buf->size++] = 224;
      buf->data[buf->size++] = 165;
      buf->data[buf->size++] = 141;
   }
   skt_buf_truncate(buf, buf->size);
}
#line 5 "skt_maps.ic"
#line 1 "skt_translit_iast_slp1.ic"

#line 1 "skt_translit_iast_slp1.rl"

#line 639 "skt_translit_iast_slp1.rl"


static void skt_translit_iast_slp1(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_iast_slp1.ic"
static const unsigned char _skt_translit_iast_slp1_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41, 1, 42, 1,
   43, 1, 44, 1, 45, 1, 46, 1,
   47, 1, 48, 1, 49, 1, 50, 1,
   51, 1, 52, 1, 53, 1, 54, 1,
   55, 1, 56, 1, 57, 1, 58, 1,
   59, 1, 60, 1, 61, 1, 62, 1,
   63, 1, 64, 1, 65, 1, 66, 1,
   67, 1, 68, 1, 69, 1, 70, 1,
   71, 1, 72, 1, 73, 1, 74, 1,
   75, 1, 76, 1, 77, 1, 78, 1,
   79, 1, 80, 1, 81, 1, 82, 1,
   83, 1, 84, 1, 85, 1, 86, 1,
   87, 1, 88, 1, 89, 1, 90, 1,
   91, 1, 92, 1, 93, 1, 94, 1,
   95, 1, 96, 1, 97, 1, 98, 1,
   99, 1, 100, 1, 101, 1, 102, 1,
   103, 1, 104, 1, 105, 1, 106, 1,
   107, 1, 108, 1, 109, 1, 110, 1,
   111, 1, 112, 1, 113, 1, 114, 1,
   115, 1, 116, 1, 117, 1, 118, 1,
   119, 1, 120, 1, 121, 1, 122, 1,
   123, 1, 124, 1, 125, 1, 126, 1,
   127, 1, 128, 1, 129, 1, 130, 1,
   131, 1, 132, 1, 133, 1, 134, 1,
   135, 1, 136, 1, 137, 1, 138, 1,
   139, 1, 140, 1, 141, 1, 142, 1,
   143, 1, 144, 1, 145, 1, 146, 1,
   147, 1, 148, 1, 149, 1, 150, 1,
   151, 1, 152, 1, 153, 1, 154, 1,
   155, 1, 156, 1, 157, 1, 158, 1,
   159, 1, 160, 1, 161, 1, 162, 1,
   163, 1, 164, 1, 165, 1, 166, 1,
   167, 1, 168, 1, 169, 1, 170, 1,
   171, 1, 172, 1, 173, 1, 174, 1,
   175, 1, 176, 1, 177, 1, 178, 1,
   179, 1, 180, 1, 181, 1, 182, 1,
   183, 1, 184, 1, 185, 1, 186, 1,
   187, 1, 188, 1, 189, 1, 190, 1,
   191, 1, 192, 1, 193, 1, 194, 1,
   195, 1, 196, 1, 197, 1, 198, 1,
   199, 1, 200, 1, 201, 1, 202, 1,
   203, 1, 204, 1, 205, 1, 206, 1,
   207, 1, 208
};

static const unsigned char _skt_translit_iast_slp1_key_offsets[] = {
   0, 8, 9, 10, 11, 12, 20, 21,
   22, 23, 24, 26, 28, 30, 32, 34,
   36, 46, 48, 50, 52, 54, 68, 70,
   72, 74, 76, 114, 119, 121, 123, 125,
   127, 129, 131, 132, 133, 135, 136, 137,
   139, 144, 146, 148, 150, 152, 154, 156,
   157, 158, 160, 161, 162, 164, 165, 187,
   191, 192, 193, 194, 195, 199, 200, 201,
   202, 204, 206, 208, 211, 214, 215, 216,
   217, 218, 219, 220, 222
};

static const unsigned char _skt_translit_iast_slp1_trans_keys[] = {
   140u, 141u, 153u, 154u, 172u, 173u, 185u, 186u,
   165u, 132u, 165u, 132u, 140u, 141u, 153u, 154u,
   172u, 173u, 185u, 186u, 165u, 132u, 165u, 132u,
   128u, 129u, 128u, 129u, 128u, 129u, 128u, 129u,
   128u, 129u, 128u, 129u, 140u, 141u, 164u, 165u,
   182u, 183u, 184u, 185u, 186u, 187u, 128u, 129u,
   128u, 129u, 128u, 129u, 128u, 129u, 130u, 131u,
   132u, 133u, 134u, 135u, 154u, 155u, 156u, 157u,
   162u, 163u, 172u, 173u, 128u, 129u, 128u, 129u,
   128u, 129u, 128u, 129u, 65u, 66u, 67u, 68u,
   69u, 71u, 72u, 73u, 74u, 75u, 76u, 77u,
   78u, 79u, 80u, 82u, 83u, 84u, 85u, 86u,
   89u, 97u, 98u, 99u, 100u, 103u, 106u, 107u,
   108u, 112u, 114u, 116u, 124u, 195u, 196u, 197u,
   204u, 225u, 73u, 85u, 105u, 117u, 195u, 72u,
   104u, 72u, 104u, 72u, 104u, 72u, 104u, 72u,
   104u, 72u, 104u, 204u, 204u, 72u, 104u, 204u,
   204u, 72u, 104u, 73u, 85u, 105u, 117u, 195u,
   72u, 104u, 72u, 104u, 72u, 104u, 72u, 104u,
   72u, 104u, 72u, 104u, 204u, 204u, 72u, 104u,
   204u, 204u, 72u, 104u, 124u, 128u, 129u, 136u,
   137u, 140u, 141u, 145u, 146u, 147u, 153u, 154u,
   160u, 161u, 168u, 169u, 172u, 173u, 177u, 178u,
   179u, 185u, 186u, 128u, 129u, 170u, 171u, 204u,
   204u, 204u, 204u, 154u, 155u, 170u, 171u, 204u,
   204u, 131u, 184u, 185u, 72u, 104u, 72u, 104u,
   72u, 104u, 204u, 72u, 104u, 204u, 204u, 204u,
   204u, 204u, 204u, 204u, 72u, 104u, 72u, 104u,
   0
};

static const char _skt_translit_iast_slp1_single_lengths[] = {
   8, 1, 1, 1, 1, 8, 1, 1,
   1, 1, 2, 2, 2, 2, 2, 2,
   10, 2, 2, 2, 2, 14, 2, 2,
   2, 2, 38, 5, 2, 2, 2, 2,
   2, 2, 1, 1, 2, 1, 1, 2,
   5, 2, 2, 2, 2, 2, 2, 1,
   1, 2, 1, 1, 2, 1, 22, 4,
   1, 1, 1, 1, 4, 1, 1, 1,
   2, 2, 2, 3, 3, 1, 1, 1,
   1, 1, 1, 2, 2
};

static const char _skt_translit_iast_slp1_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const short _skt_translit_iast_slp1_index_offsets[] = {
   0, 9, 11, 13, 15, 17, 26, 28,
   30, 32, 34, 37, 40, 43, 46, 49,
   52, 63, 66, 69, 72, 75, 90, 93,
   96, 99, 102, 141, 147, 150, 153, 156,
   159, 162, 165, 167, 169, 172, 174, 176,
   179, 185, 188, 191, 194, 197, 200, 203,
   205, 207, 210, 212, 214, 217, 219, 242,
   247, 249, 251, 253, 255, 260, 262, 264,
   266, 269, 272, 275, 279, 283, 285, 287,
   289, 291, 293, 295, 298
};

static const char _skt_translit_iast_slp1_trans_targs[] = {
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 35, 26, 26, 26, 38, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 48, 26, 26, 26, 51, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 65, 66, 26, 26,
   67, 68, 69, 70, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 71, 72, 73, 74, 26, 26, 75,
   76, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 27, 28,
   29, 30, 26, 31, 26, 26, 32, 33,
   34, 26, 26, 26, 36, 37, 26, 39,
   26, 26, 26, 40, 41, 42, 43, 44,
   45, 46, 47, 49, 50, 52, 53, 54,
   55, 60, 63, 64, 26, 26, 26, 26,
   26, 0, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 1, 26, 2,
   26, 26, 26, 26, 3, 26, 4, 26,
   26, 26, 26, 26, 26, 26, 26, 5,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 6, 26, 7, 26, 26,
   26, 26, 8, 26, 9, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 56, 57, 58, 59, 26, 10,
   26, 11, 26, 12, 26, 13, 26, 26,
   26, 61, 62, 26, 14, 26, 15, 26,
   26, 26, 16, 21, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 17, 26, 26,
   26, 18, 26, 19, 26, 20, 26, 22,
   26, 23, 26, 24, 26, 25, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 26, 26, 26, 26, 26, 26, 26,
   26, 0
};

static const short _skt_translit_iast_slp1_trans_actions[] = {
   15, 17, 19, 21, 23, 25, 27, 29,
   375, 5, 377, 61, 379, 5, 381, 73,
   383, 95, 97, 99, 101, 103, 105, 107,
   109, 417, 5, 417, 135, 385, 5, 417,
   141, 387, 193, 195, 389, 197, 199, 391,
   201, 203, 393, 205, 207, 395, 213, 215,
   397, 217, 219, 399, 0, 0, 231, 233,
   5, 5, 5, 5, 259, 261, 417, 239,
   241, 401, 247, 249, 403, 251, 253, 405,
   255, 257, 407, 263, 265, 267, 269, 271,
   273, 5, 5, 5, 5, 291, 293, 0,
   0, 417, 275, 277, 409, 279, 281, 411,
   283, 285, 413, 287, 289, 415, 5, 0,
   0, 0, 43, 0, 49, 51, 0, 0,
   5, 63, 65, 67, 0, 5, 75, 0,
   81, 83, 85, 5, 0, 0, 0, 0,
   0, 0, 5, 0, 5, 0, 0, 0,
   0, 0, 0, 5, 303, 7, 9, 11,
   13, 0, 305, 31, 33, 307, 35, 37,
   309, 39, 41, 311, 45, 47, 313, 53,
   55, 315, 57, 59, 317, 0, 319, 0,
   321, 69, 71, 323, 0, 325, 0, 327,
   77, 79, 329, 87, 89, 91, 93, 0,
   373, 111, 113, 373, 115, 117, 373, 119,
   121, 373, 123, 125, 373, 127, 129, 373,
   131, 133, 373, 0, 373, 0, 331, 137,
   139, 373, 0, 373, 0, 333, 143, 145,
   373, 147, 335, 149, 151, 153, 155, 157,
   159, 161, 163, 165, 167, 169, 171, 173,
   175, 177, 179, 181, 183, 185, 187, 189,
   191, 373, 5, 5, 5, 5, 373, 0,
   337, 0, 339, 0, 341, 0, 343, 209,
   211, 5, 5, 373, 0, 345, 0, 347,
   221, 373, 0, 0, 373, 223, 225, 349,
   227, 229, 351, 235, 237, 0, 353, 243,
   245, 0, 355, 0, 357, 0, 359, 0,
   361, 0, 363, 0, 365, 0, 367, 295,
   297, 369, 299, 301, 371, 375, 377, 379,
   381, 383, 417, 417, 385, 417, 387, 389,
   391, 393, 395, 397, 399, 417, 401, 403,
   405, 407, 417, 409, 411, 413, 415, 305,
   307, 309, 311, 313, 315, 317, 319, 321,
   323, 325, 327, 329, 373, 373, 373, 373,
   373, 373, 373, 373, 331, 373, 373, 333,
   373, 335, 373, 373, 337, 339, 341, 343,
   373, 345, 347, 373, 373, 349, 351, 353,
   355, 357, 359, 361, 363, 365, 367, 369,
   371, 0
};

static const short _skt_translit_iast_slp1_to_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 1, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const short _skt_translit_iast_slp1_from_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 3, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const short _skt_translit_iast_slp1_eof_trans[] = {
   302, 303, 304, 305, 306, 323, 323, 309,
   323, 311, 312, 313, 314, 315, 316, 317,
   323, 319, 320, 321, 322, 323, 324, 325,
   326, 327, 0, 328, 329, 330, 331, 332,
   333, 334, 335, 336, 337, 338, 339, 340,
   365, 365, 365, 365, 365, 365, 365, 365,
   349, 365, 365, 352, 365, 354, 365, 365,
   357, 358, 359, 360, 365, 362, 363, 365,
   365, 366, 367, 368, 369, 370, 371, 372,
   373, 374, 375, 376, 377
};

static const int skt_translit_iast_slp1_start = 26;
static const int skt_translit_iast_slp1_first_final = 26;
static const int skt_translit_iast_slp1_error = -1;

static const int skt_translit_iast_slp1_en_main = 26;


#line 652 "skt_translit_iast_slp1.rl"

#line 310 "skt_translit_iast_slp1.ic"
   {
   cs = skt_translit_iast_slp1_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 653 "skt_translit_iast_slp1.rl"

#line 320 "skt_translit_iast_slp1.ic"
   {
   int _klen;
   unsigned int _trans;
   const unsigned char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_iast_slp1_actions + _skt_translit_iast_slp1_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 339 "skt_translit_iast_slp1.ic"
      }
   }

   _keys = _skt_translit_iast_slp1_trans_keys + _skt_translit_iast_slp1_key_offsets[cs];
   _trans = _skt_translit_iast_slp1_index_offsets[cs];

   _klen = _skt_translit_iast_slp1_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_iast_slp1_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_iast_slp1_trans_targs[_trans];

   if ( _skt_translit_iast_slp1_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_iast_slp1_actions + _skt_translit_iast_slp1_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 1 "NONE"
   {te = p+1;}
   break;
   case 3:
#line 265 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 69;
}}
   break;
   case 4:
#line 318 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 79;
}}
   break;
   case 5:
#line 265 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 69;
}}
   break;
   case 6:
#line 318 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 79;
}}
   break;
   case 7:
#line 110 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 69;
}}
   break;
   case 8:
#line 58 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 69;
}}
   break;
   case 9:
#line 280 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 79;
}}
   break;
   case 10:
#line 329 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 79;
}}
   break;
   case 11:
#line 110 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 69;
}}
   break;
   case 12:
#line 58 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 69;
}}
   break;
   case 13:
#line 280 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 79;
}}
   break;
   case 14:
#line 329 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 79;
}}
   break;
   case 15:
#line 64 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 66;
}}
   break;
   case 16:
#line 64 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 66;
}}
   break;
   case 17:
#line 218 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 67;
}}
   break;
   case 18:
#line 218 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 67;
}}
   break;
   case 19:
#line 53 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 68;
}}
   break;
   case 20:
#line 53 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 68;
}}
   break;
   case 21:
#line 438 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 101;
}}
   break;
   case 22:
#line 168 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 71;
}}
   break;
   case 23:
#line 168 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 71;
}}
   break;
   case 24:
#line 244 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 104;
}}
   break;
   case 25:
#line 335 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 105;
}}
   break;
   case 26:
#line 196 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 74;
}}
   break;
   case 27:
#line 196 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 74;
}}
   break;
   case 28:
#line 233 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 75;
}}
   break;
   case 29:
#line 233 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 75;
}}
   break;
   case 30:
#line 228 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}}
   break;
   case 31:
#line 308 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 109;
}}
   break;
   case 32:
#line 411 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 110;
}}
   break;
   case 33:
#line 298 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 111;
}}
   break;
   case 34:
#line 185 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 80;
}}
   break;
   case 35:
#line 185 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 80;
}}
   break;
   case 36:
#line 89 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}}
   break;
   case 37:
#line 133 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 115;
}}
   break;
   case 38:
#line 223 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 84;
}}
   break;
   case 39:
#line 223 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 84;
}}
   break;
   case 40:
#line 69 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 117;
}}
   break;
   case 41:
#line 394 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 118;
}}
   break;
   case 42:
#line 158 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 121;
}}
   break;
   case 43:
#line 265 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 69;
}}
   break;
   case 44:
#line 318 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 79;
}}
   break;
   case 45:
#line 265 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 69;
}}
   break;
   case 46:
#line 318 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 79;
}}
   break;
   case 47:
#line 110 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 69;
}}
   break;
   case 48:
#line 58 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 69;
}}
   break;
   case 49:
#line 280 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 79;
}}
   break;
   case 50:
#line 329 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 79;
}}
   break;
   case 51:
#line 110 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 69;
}}
   break;
   case 52:
#line 58 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 69;
}}
   break;
   case 53:
#line 280 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 79;
}}
   break;
   case 54:
#line 329 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 79;
}}
   break;
   case 55:
#line 64 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 66;
}}
   break;
   case 56:
#line 64 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 66;
}}
   break;
   case 57:
#line 218 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 67;
}}
   break;
   case 58:
#line 218 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 67;
}}
   break;
   case 59:
#line 53 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 68;
}}
   break;
   case 60:
#line 53 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 68;
}}
   break;
   case 61:
#line 168 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 71;
}}
   break;
   case 62:
#line 168 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 71;
}}
   break;
   case 63:
#line 196 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 74;
}}
   break;
   case 64:
#line 196 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 74;
}}
   break;
   case 65:
#line 233 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 75;
}}
   break;
   case 66:
#line 233 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 75;
}}
   break;
   case 67:
#line 228 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}}
   break;
   case 68:
#line 185 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 80;
}}
   break;
   case 69:
#line 185 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 80;
}}
   break;
   case 70:
#line 89 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}}
   break;
   case 71:
#line 223 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 84;
}}
   break;
   case 72:
#line 223 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 84;
}}
   break;
   case 73:
#line 14 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 46;
}}
   break;
   case 74:
#line 37 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 97;
}}
   break;
   case 75:
#line 372 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 97;
}}
   break;
   case 76:
#line 405 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 101;
}}
   break;
   case 77:
#line 99 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 101;
}}
   break;
   case 78:
#line 121 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 105;
}}
   break;
   case 79:
#line 212 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 105;
}}
   break;
   case 80:
#line 105 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 89;
}}
   break;
   case 81:
#line 286 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 111;
}}
   break;
   case 82:
#line 422 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 111;
}}
   break;
   case 83:
#line 356 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 117;
}}
   break;
   case 84:
#line 399 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 117;
}}
   break;
   case 85:
#line 37 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 97;
}}
   break;
   case 86:
#line 372 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 97;
}}
   break;
   case 87:
#line 405 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 101;
}}
   break;
   case 88:
#line 99 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 101;
}}
   break;
   case 89:
#line 121 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 105;
}}
   break;
   case 90:
#line 212 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 105;
}}
   break;
   case 91:
#line 105 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 89;
}}
   break;
   case 92:
#line 286 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 111;
}}
   break;
   case 93:
#line 422 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 111;
}}
   break;
   case 94:
#line 356 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 117;
}}
   break;
   case 95:
#line 399 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 117;
}}
   break;
   case 96:
#line 201 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 65;
}}
   break;
   case 97:
#line 238 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 65;
}}
   break;
   case 98:
#line 201 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 65;
}}
   break;
   case 99:
#line 238 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 65;
}}
   break;
   case 100:
#line 26 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 73;
}}
   break;
   case 101:
#line 190 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 73;
}}
   break;
   case 102:
#line 26 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 73;
}}
   break;
   case 103:
#line 190 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 73;
}}
   break;
   case 104:
#line 313 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 83;
}}
   break;
   case 105:
#line 313 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 83;
}}
   break;
   case 106:
#line 383 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 85;
}}
   break;
   case 107:
#line 8 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 85;
}}
   break;
   case 108:
#line 383 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 85;
}}
   break;
   case 109:
#line 8 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 85;
}}
   break;
   case 110:
#line 340 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 126;
}}
   break;
   case 111:
#line 94 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 81;
}}
   break;
   case 112:
#line 94 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 81;
}}
   break;
   case 113:
#line 94 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 81;
}}
   break;
   case 114:
#line 94 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 81;
}}
   break;
   case 115:
#line 362 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 72;
}}
   break;
   case 116:
#line 362 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 72;
}}
   break;
   case 117:
#line 249 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}}
   break;
   case 118:
#line 249 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}}
   break;
   case 119:
#line 345 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 120;
}}
   break;
   case 120:
#line 179 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 120;
}}
   break;
   case 121:
#line 249 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}}
   break;
   case 122:
#line 249 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}}
   break;
   case 123:
#line 345 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 120;
}}
   break;
   case 124:
#line 179 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 120;
}}
   break;
   case 125:
#line 323 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 88;
}}
   break;
   case 126:
#line 292 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 88;
}}
   break;
   case 127:
#line 323 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 88;
}}
   break;
   case 128:
#line 292 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 88;
}}
   break;
   case 129:
#line 79 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}}
   break;
   case 130:
#line 79 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}}
   break;
   case 131:
#line 74 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 77;
}}
   break;
   case 132:
#line 74 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 77;
}}
   break;
   case 133:
#line 254 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 78;
}}
   break;
   case 134:
#line 254 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 78;
}}
   break;
   case 135:
#line 389 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 82;
}}
   break;
   case 136:
#line 389 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 82;
}}
   break;
   case 137:
#line 173 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 102;
}}
   break;
   case 138:
#line 127 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 102;
}}
   break;
   case 139:
#line 173 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 102;
}}
   break;
   case 140:
#line 127 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 102;
}}
   break;
   case 141:
#line 259 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 70;
}}
   break;
   case 142:
#line 20 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 70;
}}
   break;
   case 143:
#line 259 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 70;
}}
   break;
   case 144:
#line 20 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 70;
}}
   break;
   case 145:
#line 207 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 122;
}}
   break;
   case 146:
#line 207 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 122;
}}
   break;
   case 147:
#line 270 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 87;
}}
   break;
   case 148:
#line 270 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 87;
}}
   break;
   case 149:
#line 270 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 87;
}}
   break;
   case 150:
#line 270 "skt_translit_iast_slp1.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 87;
}}
   break;
   case 151:
#line 633 "skt_translit_iast_slp1.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 152:
#line 428 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 97;
}}
   break;
   case 153:
#line 443 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 98;
}}
   break;
   case 154:
#line 303 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 99;
}}
   break;
   case 155:
#line 433 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 100;
}}
   break;
   case 156:
#line 138 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 103;
}}
   break;
   case 157:
#line 351 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 106;
}}
   break;
   case 158:
#line 148 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 107;
}}
   break;
   case 159:
#line 416 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 76;
}}
   break;
   case 160:
#line 275 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 161:
#line 143 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 112;
}}
   break;
   case 162:
#line 378 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 114;
}}
   break;
   case 163:
#line 116 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 164:
#line 32 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 116;
}}
   break;
   case 165:
#line 275 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 166:
#line 116 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 167:
#line 367 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 46;
}}
   break;
   case 168:
#line 153 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 65;
}}
   break;
   case 169:
#line 153 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 65;
}}
   break;
   case 170:
#line 48 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 73;
}}
   break;
   case 171:
#line 48 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 73;
}}
   break;
   case 172:
#line 84 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 85;
}}
   break;
   case 173:
#line 84 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 85;
}}
   break;
   case 174:
#line 43 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 113;
}}
   break;
   case 175:
#line 43 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 113;
}}
   break;
   case 176:
#line 275 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 177:
#line 275 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 178:
#line 228 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}}
   break;
   case 179:
#line 228 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}}
   break;
   case 180:
#line 116 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 181:
#line 116 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 182:
#line 89 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}}
   break;
   case 183:
#line 89 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}}
   break;
   case 184:
#line 163 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 119;
}}
   break;
   case 185:
#line 163 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 119;
}}
   break;
   case 186:
#line 633 "skt_translit_iast_slp1.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 187:
#line 428 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 97;
}}
   break;
   case 188:
#line 416 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 76;
}}
   break;
   case 189:
#line 275 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 190:
#line 378 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 114;
}}
   break;
   case 191:
#line 116 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 192:
#line 275 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 193:
#line 116 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 194:
#line 153 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 65;
}}
   break;
   case 195:
#line 153 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 65;
}}
   break;
   case 196:
#line 48 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 73;
}}
   break;
   case 197:
#line 48 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 73;
}}
   break;
   case 198:
#line 84 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 85;
}}
   break;
   case 199:
#line 84 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 85;
}}
   break;
   case 200:
#line 275 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 201:
#line 275 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}}
   break;
   case 202:
#line 228 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}}
   break;
   case 203:
#line 228 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}}
   break;
   case 204:
#line 116 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 205:
#line 116 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 206:
#line 89 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}}
   break;
   case 207:
#line 89 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}}
   break;
   case 208:
#line 633 "skt_translit_iast_slp1.rl"
   {{p = ((te))-1;}{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 1917 "skt_translit_iast_slp1.ic"
      }
   }

_again:
   _acts = _skt_translit_iast_slp1_actions + _skt_translit_iast_slp1_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 1930 "skt_translit_iast_slp1.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_iast_slp1_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_iast_slp1_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 654 "skt_translit_iast_slp1.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 6 "skt_maps.ic"
#line 1 "skt_translit_velthuis_iastc.ic"

#line 1 "skt_translit_velthuis_iastc.rl"

#line 284 "skt_translit_velthuis_iastc.rl"


static void skt_translit_velthuis_iastc(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_velthuis_iastc.ic"
static const char _skt_translit_velthuis_iastc_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41
};

static const char _skt_translit_velthuis_iastc_key_offsets[] = {
   0, 12, 28, 30, 32, 33, 34, 36,
   38, 40, 41, 42, 43
};

static const unsigned char _skt_translit_velthuis_iastc_trans_keys[] = {
   46u, 65u, 70u, 73u, 85u, 90u, 97u, 102u,
   105u, 117u, 122u, 126u, 68u, 72u, 76u, 77u,
   78u, 82u, 83u, 84u, 100u, 104u, 108u, 109u,
   110u, 114u, 115u, 116u, 76u, 108u, 82u, 114u,
   108u, 114u, 65u, 97u, 73u, 105u, 85u, 117u,
   97u, 105u, 117u, 78u, 110u, 126u, 0
};

static const char _skt_translit_velthuis_iastc_single_lengths[] = {
   12, 16, 2, 2, 1, 1, 2, 2,
   2, 1, 1, 1, 3
};

static const char _skt_translit_velthuis_iastc_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iastc_index_offsets[] = {
   0, 13, 30, 33, 36, 38, 40, 43,
   46, 49, 51, 53, 55
};

static const char _skt_translit_velthuis_iastc_trans_targs[] = {
   1, 6, 0, 7, 8, 0, 9, 0,
   10, 11, 0, 12, 0, 0, 0, 2,
   0, 0, 3, 0, 0, 0, 0, 4,
   0, 0, 5, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iastc_trans_actions[] = {
   0, 0, 45, 0, 0, 55, 0, 59,
   0, 0, 65, 0, 73, 5, 7, 0,
   13, 15, 0, 21, 23, 25, 27, 0,
   31, 33, 0, 37, 39, 83, 9, 11,
   75, 17, 19, 77, 29, 79, 35, 81,
   41, 43, 83, 47, 49, 83, 51, 53,
   83, 57, 83, 61, 83, 63, 83, 67,
   69, 71, 83, 83, 75, 77, 79, 81,
   83, 83, 83, 83, 83, 83, 83, 0
};

static const char _skt_translit_velthuis_iastc_to_state_actions[] = {
   1, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iastc_from_state_actions[] = {
   3, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iastc_eof_trans[] = {
   0, 71, 61, 62, 63, 64, 71, 71,
   71, 71, 71, 71, 71
};

static const int skt_translit_velthuis_iastc_start = 0;
static const int skt_translit_velthuis_iastc_first_final = 0;
static const int skt_translit_velthuis_iastc_error = -1;

static const int skt_translit_velthuis_iastc_en_main = 0;


#line 297 "skt_translit_velthuis_iastc.rl"

#line 111 "skt_translit_velthuis_iastc.ic"
   {
   cs = skt_translit_velthuis_iastc_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 298 "skt_translit_velthuis_iastc.rl"

#line 121 "skt_translit_velthuis_iastc.ic"
   {
   int _klen;
   unsigned int _trans;
   const char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_velthuis_iastc_actions + _skt_translit_velthuis_iastc_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 140 "skt_translit_velthuis_iastc.ic"
      }
   }

   _keys = _skt_translit_velthuis_iastc_trans_keys + _skt_translit_velthuis_iastc_key_offsets[cs];
   _trans = _skt_translit_velthuis_iastc_index_offsets[cs];

   _klen = _skt_translit_velthuis_iastc_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_velthuis_iastc_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_velthuis_iastc_trans_targs[_trans];

   if ( _skt_translit_velthuis_iastc_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_velthuis_iastc_actions + _skt_translit_velthuis_iastc_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 149 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 140;
}}
   break;
   case 3:
#line 204 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 164;
}}
   break;
   case 4:
#line 46 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 5:
#line 46 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 6:
#line 122 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 130;
}}
   break;
   case 7:
#line 129 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 134;
}}
   break;
   case 8:
#line 92 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 9:
#line 92 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 10:
#line 163 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 162;
}}
   break;
   case 11:
#line 55 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 172;
}}
   break;
   case 12:
#line 85 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}}
   break;
   case 13:
#line 62 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}}
   break;
   case 14:
#line 76 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 15:
#line 39 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}}
   break;
   case 16:
#line 115 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}}
   break;
   case 17:
#line 176 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 18:
#line 156 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}}
   break;
   case 19:
#line 136 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}}
   break;
   case 20:
#line 14 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 128;
}}
   break;
   case 21:
#line 14 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 128;
}}
   break;
   case 22:
#line 108 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 132;
}}
   break;
   case 23:
#line 20 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 170;
}}
   break;
   case 24:
#line 20 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 170;
}}
   break;
   case 25:
#line 185 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 170;
}}
   break;
   case 26:
#line 185 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 170;
}}
   break;
   case 27:
#line 33 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 154;
}}
   break;
   case 28:
#line 143 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}}
   break;
   case 29:
#line 197 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}}
   break;
   case 30:
#line 218 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}}
   break;
   case 31:
#line 170 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}}
   break;
   case 32:
#line 231 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}}
   break;
   case 33:
#line 8 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 145;
}}
   break;
   case 34:
#line 191 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}}
   break;
   case 35:
#line 224 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 129;
}}
   break;
   case 36:
#line 278 "skt_translit_velthuis_iastc.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 37:
#line 26 "skt_translit_velthuis_iastc.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 38:
#line 211 "skt_translit_velthuis_iastc.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 39:
#line 101 "skt_translit_velthuis_iastc.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 40:
#line 69 "skt_translit_velthuis_iastc.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 41:
#line 278 "skt_translit_velthuis_iastc.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 560 "skt_translit_velthuis_iastc.ic"
      }
   }

_again:
   _acts = _skt_translit_velthuis_iastc_actions + _skt_translit_velthuis_iastc_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 573 "skt_translit_velthuis_iastc.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_velthuis_iastc_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_velthuis_iastc_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 299 "skt_translit_velthuis_iastc.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 7 "skt_maps.ic"
#line 1 "skt_translit_iast_velthuis.ic"

#line 1 "skt_translit_iast_velthuis.rl"

#line 257 "skt_translit_iast_velthuis.rl"


static void skt_translit_iast_velthuis(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_iast_velthuis.ic"
static const char _skt_translit_iast_velthuis_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41, 1, 42, 1,
   43, 1, 44, 1, 45, 1, 46, 1,
   47, 1, 48, 1, 49, 1, 50, 1,
   51
};

static const char _skt_translit_iast_velthuis_key_offsets[] = {
   0, 1, 2, 3, 4, 5, 6, 7,
   8, 16, 32, 40, 41, 42, 43, 44,
   45, 46, 47, 48, 50, 54, 58
};

static const unsigned char _skt_translit_iast_velthuis_trans_keys[] = {
   165u, 132u, 165u, 132u, 165u, 132u, 165u, 132u,
   140u, 141u, 164u, 165u, 182u, 183u, 184u, 185u,
   128u, 129u, 130u, 131u, 132u, 133u, 134u, 135u,
   154u, 155u, 156u, 157u, 162u, 163u, 172u, 173u,
   76u, 82u, 108u, 114u, 195u, 196u, 197u, 225u,
   204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u,
   145u, 177u, 128u, 129u, 170u, 171u, 154u, 155u,
   170u, 171u, 184u, 185u, 0
};

static const char _skt_translit_iast_velthuis_single_lengths[] = {
   1, 1, 1, 1, 1, 1, 1, 1,
   8, 16, 8, 1, 1, 1, 1, 1,
   1, 1, 1, 2, 4, 4, 2
};

static const char _skt_translit_iast_velthuis_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_iast_velthuis_index_offsets[] = {
   0, 2, 4, 6, 8, 10, 12, 14,
   16, 25, 42, 51, 53, 55, 57, 59,
   61, 63, 65, 67, 70, 75, 80
};

static const char _skt_translit_iast_velthuis_trans_targs[] = {
   12, 10, 10, 10, 14, 10, 10, 10,
   16, 10, 10, 10, 18, 10, 10, 10,
   10, 10, 10, 10, 10, 10, 10, 10,
   10, 10, 10, 10, 10, 10, 10, 10,
   10, 10, 10, 10, 10, 10, 10, 10,
   10, 10, 11, 13, 15, 17, 19, 20,
   21, 22, 10, 0, 10, 1, 10, 2,
   10, 3, 10, 4, 10, 5, 10, 6,
   10, 7, 10, 10, 10, 10, 10, 10,
   10, 10, 10, 10, 10, 10, 10, 10,
   8, 9, 10, 10, 10, 10, 10, 10,
   10, 10, 10, 10, 10, 10, 10, 10,
   10, 10, 10, 10, 10, 10, 10, 10,
   10, 0
};

static const char _skt_translit_iast_velthuis_trans_actions[] = {
   5, 103, 7, 95, 5, 103, 9, 97,
   5, 103, 11, 99, 5, 103, 13, 101,
   35, 37, 39, 41, 43, 45, 47, 49,
   103, 51, 53, 55, 57, 59, 61, 63,
   65, 67, 69, 71, 73, 75, 77, 79,
   81, 103, 5, 5, 5, 5, 0, 0,
   0, 5, 83, 0, 93, 0, 85, 0,
   93, 0, 87, 0, 93, 0, 89, 0,
   93, 0, 91, 15, 17, 93, 19, 21,
   23, 25, 93, 27, 29, 31, 33, 93,
   0, 0, 93, 103, 95, 103, 97, 103,
   99, 103, 101, 103, 103, 93, 85, 93,
   87, 93, 89, 93, 91, 93, 93, 93,
   93, 0
};

static const char _skt_translit_iast_velthuis_to_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 1, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_iast_velthuis_from_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 3, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_iast_velthuis_eof_trans[] = {
   93, 85, 93, 87, 93, 89, 93, 91,
   93, 93, 0, 105, 95, 105, 97, 105,
   99, 105, 101, 105, 105, 105, 105
};

static const int skt_translit_iast_velthuis_start = 10;
static const int skt_translit_iast_velthuis_first_final = 10;
static const int skt_translit_iast_velthuis_error = -1;

static const int skt_translit_iast_velthuis_en_main = 10;


#line 270 "skt_translit_iast_velthuis.rl"

#line 133 "skt_translit_iast_velthuis.ic"
   {
   cs = skt_translit_iast_velthuis_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 271 "skt_translit_iast_velthuis.rl"

#line 143 "skt_translit_iast_velthuis.ic"
   {
   int _klen;
   unsigned int _trans;
   const char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_iast_velthuis_actions + _skt_translit_iast_velthuis_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 162 "skt_translit_iast_velthuis.ic"
      }
   }

   _keys = _skt_translit_iast_velthuis_trans_keys + _skt_translit_iast_velthuis_key_offsets[cs];
   _trans = _skt_translit_iast_velthuis_index_offsets[cs];

   _klen = _skt_translit_iast_velthuis_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_iast_velthuis_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_iast_velthuis_trans_targs[_trans];

   if ( _skt_translit_iast_velthuis_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_iast_velthuis_actions + _skt_translit_iast_velthuis_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 1 "NONE"
   {te = p+1;}
   break;
   case 3:
#line 56 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 108;
}}
   break;
   case 4:
#line 106 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 114;
}}
   break;
   case 5:
#line 88 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 108;
}}
   break;
   case 6:
#line 69 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 114;
}}
   break;
   case 7:
#line 14 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 78;
}}
   break;
   case 8:
#line 194 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 110;
}}
   break;
   case 9:
#line 118 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 65;
   buf->data[buf->size++] = 97;
}}
   break;
   case 10:
#line 147 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 97;
}}
   break;
   case 11:
#line 100 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 73;
   buf->data[buf->size++] = 105;
}}
   break;
   case 12:
#line 182 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 105;
   buf->data[buf->size++] = 105;
}}
   break;
   case 13:
#line 124 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 90;
}}
   break;
   case 14:
#line 95 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 122;
}}
   break;
   case 15:
#line 170 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 85;
   buf->data[buf->size++] = 117;
}}
   break;
   case 16:
#line 63 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 117;
   buf->data[buf->size++] = 117;
}}
   break;
   case 17:
#line 200 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 68;
}}
   break;
   case 18:
#line 159 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 100;
}}
   break;
   case 19:
#line 129 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 72;
}}
   break;
   case 20:
#line 50 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 104;
}}
   break;
   case 21:
#line 153 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
}}
   break;
   case 22:
#line 76 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
}}
   break;
   case 23:
#line 56 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 108;
}}
   break;
   case 24:
#line 88 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 108;
}}
   break;
   case 25:
#line 20 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 126;
}}
   break;
   case 26:
#line 20 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 126;
}}
   break;
   case 27:
#line 32 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 77;
}}
   break;
   case 28:
#line 176 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 109;
}}
   break;
   case 29:
#line 165 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}}
   break;
   case 30:
#line 113 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}}
   break;
   case 31:
#line 38 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 78;
}}
   break;
   case 32:
#line 188 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 110;
}}
   break;
   case 33:
#line 26 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
}}
   break;
   case 34:
#line 8 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
}}
   break;
   case 35:
#line 106 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 114;
}}
   break;
   case 36:
#line 69 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 114;
}}
   break;
   case 37:
#line 44 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 83;
}}
   break;
   case 38:
#line 135 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 115;
}}
   break;
   case 39:
#line 82 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 84;
}}
   break;
   case 40:
#line 141 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 116;
}}
   break;
   case 41:
#line 251 "skt_translit_iast_velthuis.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 42:
#line 153 "skt_translit_iast_velthuis.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
}}
   break;
   case 43:
#line 26 "skt_translit_iast_velthuis.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
}}
   break;
   case 44:
#line 76 "skt_translit_iast_velthuis.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
}}
   break;
   case 45:
#line 8 "skt_translit_iast_velthuis.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
}}
   break;
   case 46:
#line 251 "skt_translit_iast_velthuis.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 47:
#line 153 "skt_translit_iast_velthuis.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
}}
   break;
   case 48:
#line 26 "skt_translit_iast_velthuis.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
}}
   break;
   case 49:
#line 76 "skt_translit_iast_velthuis.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
}}
   break;
   case 50:
#line 8 "skt_translit_iast_velthuis.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
}}
   break;
   case 51:
#line 251 "skt_translit_iast_velthuis.rl"
   {{p = ((te))-1;}{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 624 "skt_translit_iast_velthuis.ic"
      }
   }

_again:
   _acts = _skt_translit_iast_velthuis_actions + _skt_translit_iast_velthuis_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 637 "skt_translit_iast_velthuis.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_iast_velthuis_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_iast_velthuis_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 272 "skt_translit_iast_velthuis.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 8 "skt_maps.ic"
#line 1 "skt_translit_velthuis_iast.ic"

#line 1 "skt_translit_velthuis_iast.rl"

#line 276 "skt_translit_velthuis_iast.rl"


static void skt_translit_velthuis_iast(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_velthuis_iast.ic"
static const char _skt_translit_velthuis_iast_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41
};

static const char _skt_translit_velthuis_iast_key_offsets[] = {
   0, 12, 28, 30, 32, 33, 34, 36,
   38, 40, 41, 42, 43
};

static const unsigned char _skt_translit_velthuis_iast_trans_keys[] = {
   46u, 65u, 70u, 73u, 85u, 90u, 97u, 102u,
   105u, 117u, 122u, 126u, 68u, 72u, 76u, 77u,
   78u, 82u, 83u, 84u, 100u, 104u, 108u, 109u,
   110u, 114u, 115u, 116u, 76u, 108u, 82u, 114u,
   108u, 114u, 65u, 97u, 73u, 105u, 85u, 117u,
   97u, 105u, 117u, 78u, 110u, 126u, 0
};

static const char _skt_translit_velthuis_iast_single_lengths[] = {
   12, 16, 2, 2, 1, 1, 2, 2,
   2, 1, 1, 1, 3
};

static const char _skt_translit_velthuis_iast_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iast_index_offsets[] = {
   0, 13, 30, 33, 36, 38, 40, 43,
   46, 49, 51, 53, 55
};

static const char _skt_translit_velthuis_iast_trans_targs[] = {
   1, 6, 0, 7, 8, 0, 9, 0,
   10, 11, 0, 12, 0, 0, 0, 2,
   0, 0, 3, 0, 0, 0, 0, 4,
   0, 0, 5, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iast_trans_actions[] = {
   0, 0, 45, 0, 0, 55, 0, 59,
   0, 0, 65, 0, 73, 5, 7, 0,
   13, 15, 0, 21, 23, 25, 27, 0,
   31, 33, 0, 37, 39, 83, 9, 11,
   75, 17, 19, 77, 29, 79, 35, 81,
   41, 43, 83, 47, 49, 83, 51, 53,
   83, 57, 83, 61, 83, 63, 83, 67,
   69, 71, 83, 83, 75, 77, 79, 81,
   83, 83, 83, 83, 83, 83, 83, 0
};

static const char _skt_translit_velthuis_iast_to_state_actions[] = {
   1, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iast_from_state_actions[] = {
   3, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0
};

static const char _skt_translit_velthuis_iast_eof_trans[] = {
   0, 71, 61, 62, 63, 64, 71, 71,
   71, 71, 71, 71, 71
};

static const int skt_translit_velthuis_iast_start = 0;
static const int skt_translit_velthuis_iast_first_final = 0;
static const int skt_translit_velthuis_iast_error = -1;

static const int skt_translit_velthuis_iast_en_main = 0;


#line 289 "skt_translit_velthuis_iast.rl"

#line 111 "skt_translit_velthuis_iast.ic"
   {
   cs = skt_translit_velthuis_iast_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 290 "skt_translit_velthuis_iast.rl"

#line 121 "skt_translit_velthuis_iast.ic"
   {
   int _klen;
   unsigned int _trans;
   const char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_velthuis_iast_actions + _skt_translit_velthuis_iast_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 140 "skt_translit_velthuis_iast.ic"
      }
   }

   _keys = _skt_translit_velthuis_iast_trans_keys + _skt_translit_velthuis_iast_key_offsets[cs];
   _trans = _skt_translit_velthuis_iast_index_offsets[cs];

   _klen = _skt_translit_velthuis_iast_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_velthuis_iast_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_velthuis_iast_trans_targs[_trans];

   if ( _skt_translit_velthuis_iast_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_velthuis_iast_actions + _skt_translit_velthuis_iast_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 48 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 140;
}}
   break;
   case 3:
#line 21 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 164;
}}
   break;
   case 4:
#line 55 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 184;
}}
   break;
   case 5:
#line 55 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 184;
}}
   break;
   case 6:
#line 210 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 130;
}}
   break;
   case 7:
#line 170 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 134;
}}
   break;
   case 8:
#line 83 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 156;
}}
   break;
   case 9:
#line 83 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 156;
}}
   break;
   case 10:
#line 41 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 162;
}}
   break;
   case 11:
#line 117 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 172;
}}
   break;
   case 12:
#line 14 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}}
   break;
   case 13:
#line 130 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}}
   break;
   case 14:
#line 156 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
}}
   break;
   case 15:
#line 62 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}}
   break;
   case 16:
#line 34 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}}
   break;
   case 17:
#line 97 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
}}
   break;
   case 18:
#line 110 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}}
   break;
   case 19:
#line 90 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}}
   break;
   case 20:
#line 223 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 128;
}}
   break;
   case 21:
#line 223 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 128;
}}
   break;
   case 22:
#line 203 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 132;
}}
   break;
   case 23:
#line 197 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 170;
}}
   break;
   case 24:
#line 197 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 170;
}}
   break;
   case 25:
#line 28 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 170;
}}
   break;
   case 26:
#line 28 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 170;
}}
   break;
   case 27:
#line 177 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 154;
}}
   break;
   case 28:
#line 124 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}}
   break;
   case 29:
#line 76 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}}
   break;
   case 30:
#line 8 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}}
   break;
   case 31:
#line 217 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}}
   break;
   case 32:
#line 143 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}}
   break;
   case 33:
#line 137 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 145;
}}
   break;
   case 34:
#line 104 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}}
   break;
   case 35:
#line 190 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 129;
}}
   break;
   case 36:
#line 270 "skt_translit_velthuis_iast.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 37:
#line 163 "skt_translit_velthuis_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 182;
}}
   break;
   case 38:
#line 183 "skt_translit_velthuis_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 154;
}}
   break;
   case 39:
#line 149 "skt_translit_velthuis_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}}
   break;
   case 40:
#line 69 "skt_translit_velthuis_iast.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}}
   break;
   case 41:
#line 270 "skt_translit_velthuis_iast.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 548 "skt_translit_velthuis_iast.ic"
      }
   }

_again:
   _acts = _skt_translit_velthuis_iast_actions + _skt_translit_velthuis_iast_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 561 "skt_translit_velthuis_iast.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_velthuis_iast_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_velthuis_iast_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 291 "skt_translit_velthuis_iast.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 9 "skt_maps.ic"
#line 1 "skt_translit_iast_iastc.ic"

#line 1 "skt_translit_iast_iastc.rl"

#line 89 "skt_translit_iast_iastc.rl"


static void skt_translit_iast_iastc(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 19 "skt_translit_iast_iastc.ic"
static const char _skt_translit_iast_iastc_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13
};

static const char _skt_translit_iast_iastc_key_offsets[] = {
   0, 4, 8, 9
};

static const unsigned char _skt_translit_iast_iastc_trans_keys[] = {
   182u, 183u, 184u, 185u, 154u, 155u, 156u, 157u,
   225u, 184u, 185u, 0
};

static const char _skt_translit_iast_iastc_single_lengths[] = {
   4, 4, 1, 2
};

static const char _skt_translit_iast_iastc_range_lengths[] = {
   0, 0, 0, 0
};

static const char _skt_translit_iast_iastc_index_offsets[] = {
   0, 5, 10, 12
};

static const char _skt_translit_iast_iastc_trans_targs[] = {
   2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 3, 2, 0, 1, 2, 2,
   2, 2, 0
};

static const char _skt_translit_iast_iastc_trans_actions[] = {
   7, 9, 11, 13, 27, 15, 17, 19,
   21, 27, 5, 23, 0, 0, 25, 27,
   27, 25, 0
};

static const char _skt_translit_iast_iastc_to_state_actions[] = {
   0, 0, 1, 0
};

static const char _skt_translit_iast_iastc_from_state_actions[] = {
   0, 0, 3, 0
};

static const char _skt_translit_iast_iastc_eof_trans[] = {
   17, 17, 0, 18
};

static const int skt_translit_iast_iastc_start = 2;
static const int skt_translit_iast_iastc_first_final = 2;
static const int skt_translit_iast_iastc_error = -1;

static const int skt_translit_iast_iastc_en_main = 2;


#line 102 "skt_translit_iast_iastc.rl"

#line 81 "skt_translit_iast_iastc.ic"
   {
   cs = skt_translit_iast_iastc_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 103 "skt_translit_iast_iastc.rl"

#line 91 "skt_translit_iast_iastc.ic"
   {
   int _klen;
   unsigned int _trans;
   const char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_translit_iast_iastc_actions + _skt_translit_iast_iastc_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 110 "skt_translit_iast_iastc.ic"
      }
   }

   _keys = _skt_translit_iast_iastc_trans_keys + _skt_translit_iast_iastc_key_offsets[cs];
   _trans = _skt_translit_iast_iastc_index_offsets[cs];

   _klen = _skt_translit_iast_iastc_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_translit_iast_iastc_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_translit_iast_iastc_trans_targs[_trans];

   if ( _skt_translit_iast_iastc_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_translit_iast_iastc_actions + _skt_translit_iast_iastc_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 1 "NONE"
   {te = p+1;}
   break;
   case 3:
#line 65 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 4:
#line 31 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 5:
#line 56 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 6:
#line 47 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 7:
#line 8 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 8:
#line 24 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}}
   break;
   case 9:
#line 38 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 10:
#line 15 "skt_translit_iast_iastc.rl"
   {te = p+1;{
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}}
   break;
   case 11:
#line 83 "skt_translit_iast_iastc.rl"
   {te = p+1;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 12:
#line 83 "skt_translit_iast_iastc.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
   case 13:
#line 83 "skt_translit_iast_iastc.rl"
   {{p = ((te))-1;}{
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   }}
   break;
#line 280 "skt_translit_iast_iastc.ic"
      }
   }

_again:
   _acts = _skt_translit_iast_iastc_actions + _skt_translit_iast_iastc_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 293 "skt_translit_iast_iastc.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_translit_iast_iastc_eof_trans[cs] > 0 ) {
      _trans = _skt_translit_iast_iastc_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 104 "skt_translit_iast_iastc.rl"

   skt_buf_truncate(buf, buf->size);
}
#line 10 "skt_maps.ic"

static const skt_translit skt_maps[NUM_SCHEMES][NUM_SCHEMES] = {
   [IAST] = {
      [IAST] = skt_translit_identity,
      [IASTC] = skt_translit_iast_iastc,
      [NAGARI] = skt_translit_iast_nagari,
      [SLP1] = skt_translit_iast_slp1,
      [VELTHUIS] = skt_translit_iast_velthuis,
   },
   [IASTC] = {
      [IAST] = skt_translit_iastc_iast,
      [IASTC] = skt_translit_identity,
   },
   [NAGARI] = {
      [NAGARI] = skt_translit_identity,
   },
   [SLP1] = {
      [IAST] = skt_translit_slp1_iast,
      [IASTC] = skt_translit_slp1_iastc,
      [SLP1] = skt_translit_identity,
   },
   [VELTHUIS] = {
      [IAST] = skt_translit_velthuis_iast,
      [IASTC] = skt_translit_velthuis_iastc,
      [VELTHUIS] = skt_translit_identity,
   },
};

static const char *const skt_maps_description[NUM_SCHEMES][NUM_SCHEMES] = {
   [IAST] = {
      [IAST] =
         ""
         ,
      [IASTC] =
         "Ḷ\tL̥\n"
         "ḷ\tl̥\n"
         "Ḹ\tL̥̄\n"
         "ḹ\tl̥̄\n"
         "Ṛ\tR̥\n"
         "ṛ\tr̥\n"
         "Ṝ\tR̥̄\n"
         "ṝ\tr̥̄\n"
         ,
      [NAGARI] =
         "CONSONANT\tB\tब\n"
         "CONSONANT\tBH\tभ\n"
         "CONSONANT\tBh\tभ\n"
         "CONSONANT\tC\tच\n"
         "CONSONANT\tCH\tछ\n"
         "CONSONANT\tCh\tछ\n"
         "CONSONANT\tD\tद\n"
         "CONSONANT\tDH\tध\n"
         "CONSONANT\tDh\tध\n"
         "CONSONANT\tG\tग\n"
         "CONSONANT\tGH\tघ\n"
         "CONSONANT\tGh\tघ\n"
         "CONSONANT\tH\tह\n"
         "CONSONANT\tJ\tज\n"
         "CONSONANT\tJH\tझ\n"
         "CONSONANT\tJh\tझ\n"
         "CONSONANT\tK\tक\n"
         "CONSONANT\tKH\tख\n"
         "CONSONANT\tKh\tख\n"
         "CONSONANT\tL\tल\n"
         "CONSONANT\tM\tम\n"
         "CONSONANT\tN\tन\n"
         "CONSONANT\tP\tप\n"
         "CONSONANT\tPH\tफ\n"
         "CONSONANT\tPh\tफ\n"
         "CONSONANT\tR\tर\n"
         "CONSONANT\tS\tस\n"
         "CONSONANT\tT\tत\n"
         "CONSONANT\tTH\tथ\n"
         "CONSONANT\tTh\tथ\n"
         "CONSONANT\tV\tव\n"
         "CONSONANT\tY\tय\n"
         "CONSONANT\tb\tब\n"
         "CONSONANT\tbH\tभ\n"
         "CONSONANT\tbh\tभ\n"
         "CONSONANT\tc\tच\n"
         "CONSONANT\tcH\tछ\n"
         "CONSONANT\tch\tछ\n"
         "CONSONANT\td\tद\n"
         "CONSONANT\tdH\tध\n"
         "CONSONANT\tdh\tध\n"
         "CONSONANT\tg\tग\n"
         "CONSONANT\tgH\tघ\n"
         "CONSONANT\tgh\tघ\n"
         "CONSONANT\th\tह\n"
         "CONSONANT\tj\tज\n"
         "CONSONANT\tjH\tझ\n"
         "CONSONANT\tjh\tझ\n"
         "CONSONANT\tk\tक\n"
         "CONSONANT\tkH\tख\n"
         "CONSONANT\tkh\tख\n"
         "CONSONANT\tl\tल\n"
         "CONSONANT\tm\tम\n"
         "CONSONANT\tn\tन\n"
         "CONSONANT\tp\tप\n"
         "CONSONANT\tpH\tफ\n"
         "CONSONANT\tph\tफ\n"
         "CONSONANT\tr\tर\n"
         "CONSONANT\ts\tस\n"
         "CONSONANT\tt\tत\n"
         "CONSONANT\ttH\tथ\n"
         "CONSONANT\tth\tथ\n"
         "CONSONANT\tv\tव\n"
         "CONSONANT\ty\tय\n"
         "CONSONANT\tÑ\tञ\n"
         "CONSONANT\tñ\tञ\n"
         "CONSONANT\tŚ\tश\n"
         "CONSONANT\tś\tश\n"
         "CONSONANT\tḌ\tड\n"
         "CONSONANT\tḌH\tढ\n"
         "CONSONANT\tḌh\tढ\n"
         "CONSONANT\tḍ\tड\n"
         "CONSONANT\tḍH\tढ\n"
         "CONSONANT\tḍh\tढ\n"
         "CONSONANT\tḺ\tळ\n"
         "CONSONANT\tḻ\tळ\n"
         "CONSONANT\tṄ\tङ\n"
         "CONSONANT\tṅ\tङ\n"
         "CONSONANT\tṆ\tण\n"
         "CONSONANT\tṇ\tण\n"
         "CONSONANT\tṢ\tष\n"
         "CONSONANT\tṣ\tष\n"
         "CONSONANT\tṬ\tट\n"
         "CONSONANT\tṬH\tठ\n"
         "CONSONANT\tṬh\tठ\n"
         "CONSONANT\tṭ\tट\n"
         "CONSONANT\tṭH\tठ\n"
         "CONSONANT\tṭh\tठ\n"
         "REST\t'\tऽ\n"
         "REST\t0\t०\n"
         "REST\t1\t१\n"
         "REST\t2\t२\n"
         "REST\t3\t३\n"
         "REST\t4\t४\n"
         "REST\t5\t५\n"
         "REST\t6\t६\n"
         "REST\t7\t७\n"
         "REST\t8\t८\n"
         "REST\t9\t९\n"
         "REST\t|\t।\n"
         "REST\t||\t॥\n"
         "REST\tḤ\tः\n"
         "REST\tḥ\tः\n"
         "REST\tṂ\tं\n"
         "REST\tṃ\tं\n"
         "VIRAMA\t<nil>\t्\n"
         "VOWEL\tAI\tऐ\tै\n"
         "VOWEL\tAU\tऔ\tौ\n"
         "VOWEL\tAi\tऐ\tै\n"
         "VOWEL\tAu\tऔ\tौ\n"
         "VOWEL\tAÍ\tऐ॑\tै॑\n"
         "VOWEL\tAÚ\tऔ॑\tौ॑\n"
         "VOWEL\tAí\tऐ॑\tै॑\n"
         "VOWEL\tAú\tऔ॑\tौ॑\n"
         "VOWEL\tE\tए\tे\n"
         "VOWEL\tI\tइ\tि\n"
         "VOWEL\tL̥\tऌ\tॢ\n"
         "VOWEL\tL̥̄\tॡ\tॣ\n"
         "VOWEL\tO\tओ\tो\n"
         "VOWEL\tR̥\tऋ\tृ\n"
         "VOWEL\tR̥̄\tॠ\tॄ\n"
         "VOWEL\tU\tउ\tु\n"
         "VOWEL\taI\tऐ\tै\n"
         "VOWEL\taU\tऔ\tौ\n"
         "VOWEL\tai\tऐ\tै\n"
         "VOWEL\tau\tऔ\tौ\n"
         "VOWEL\taÍ\tऐ॑\tै॑\n"
         "VOWEL\taÚ\tऔ॑\tौ॑\n"
         "VOWEL\taí\tऐ॑\tै॑\n"
         "VOWEL\taú\tऔ॑\tौ॑\n"
         "VOWEL\te\tए\tे\n"
         "VOWEL\ti\tइ\tि\n"
         "VOWEL\tl̥\tऌ\tॢ\n"
         "VOWEL\tl̥̄\tॡ\tॣ\n"
         "VOWEL\to\tओ\tो\n"
         "VOWEL\tr̥\tऋ\tृ\n"
         "VOWEL\tr̥̄\tॠ\tॄ\n"
         "VOWEL\tu\tउ\tु\n"
         "VOWEL\tÁ\tअ॑\t॑\n"
         "VOWEL\tÉ\tए॑\tे॑\n"
         "VOWEL\tÍ\tइ॑\tि॑\n"
         "VOWEL\tÓ\tओ॑\tो॑\n"
         "VOWEL\tÚ\tउ॑\tु॑\n"
         "VOWEL\tá\tअ॑\t॑\n"
         "VOWEL\té\tए॑\tे॑\n"
         "VOWEL\tí\tइ॑\tि॑\n"
         "VOWEL\tó\tओ॑\tो॑\n"
         "VOWEL\tú\tउ॑\tु॑\n"
         "VOWEL\tĀ\tआ\tा\n"
         "VOWEL\tĀ́\tआ॑\tा॑\n"
         "VOWEL\tā\tआ\tा\n"
         "VOWEL\tā́\tआ॑\tा॑\n"
         "VOWEL\tĪ\tई\tी\n"
         "VOWEL\tĪ́\tई॑\tी॑\n"
         "VOWEL\tī\tई\tी\n"
         "VOWEL\tī́\tई॑\tी॑\n"
         "VOWEL\tŪ\tऊ\tू\n"
         "VOWEL\tŪ́\tऊ॑\tू॑\n"
         "VOWEL\tū\tऊ\tू\n"
         "VOWEL\tū́\tऊ॑\tू॑\n"
         "VOWEL\tḶ\tऌ\tॢ\n"
         "VOWEL\tḶ́\tऌ॑\tॢ॑\n"
         "VOWEL\tḷ\tऌ\tॢ\n"
         "VOWEL\tḷ́\tऌ॑\tॢ॑\n"
         "VOWEL\tḸ\tॡ\tॣ\n"
         "VOWEL\tḹ\tॡ\tॣ\n"
         "VOWEL\tṚ\tऋ\tृ\n"
         "VOWEL\tṚ́\tऋ॑\tॄ॑\n"
         "VOWEL\tṛ\tऋ\tृ\n"
         "VOWEL\tṛ́\tऋ॑\tॄ॑\n"
         "VOWEL\tṜ\tॠ\tॄ\n"
         "VOWEL\tṜ́\tॠ॑\tॄ॑\n"
         "VOWEL\tṝ\tॠ\tॄ\n"
         "VOWEL\tṝ́\tॠ॑\tॄ॑\n"
         "VOWEL_A\tA\tअ\n"
         "VOWEL_A\ta\tअ\n"
         ,
      [SLP1] =
         "A\ta\n"
         "AI\tE\n"
         "AU\tO\n"
         "Ai\tE\n"
         "Au\tO\n"
         "AÌ\t^E\n"
         "AÍ\t/E\n"
         "AÙ\t^O\n"
         "AÚ\t/O\n"
         "Aì\t^E\n"
         "Aí\t/E\n"
         "Aù\t^O\n"
         "Aú\t/O\n"
         "B\tb\n"
         "BH\tB\n"
         "Bh\tB\n"
         "C\tc\n"
         "CH\tC\n"
         "Ch\tC\n"
         "D\td\n"
         "DH\tD\n"
         "Dh\tD\n"
         "E\te\n"
         "G\tg\n"
         "GH\tG\n"
         "Gh\tG\n"
         "H\th\n"
         "I\ti\n"
         "J\tj\n"
         "JH\tJ\n"
         "Jh\tJ\n"
         "K\tk\n"
         "KH\tK\n"
         "Kh\tK\n"
         "L\t/L\n"
         "L̥\tx\n"
         "L̥̄\tX\n"
         "M\tm\n"
         "N\tn\n"
         "O\to\n"
         "P\tp\n"
         "PH\tP\n"
         "Ph\tP\n"
         "R\tr\n"
         "R̥\tf\n"
         "R̥̄\tF\n"
         "S\ts\n"
         "T\tt\n"
         "TH\tT\n"
         "Th\tT\n"
         "U\tu\n"
         "V\tv\n"
         "Y\ty\n"
         "aI\tE\n"
         "aU\tO\n"
         "ai\tE\n"
         "au\tO\n"
         "aÌ\t^E\n"
         "aÍ\t/E\n"
         "aÙ\t^O\n"
         "aÚ\t/O\n"
         "aì\t^E\n"
         "aí\t/E\n"
         "aù\t^O\n"
         "aú\t/O\n"
         "bH\tB\n"
         "bh\tB\n"
         "cH\tC\n"
         "ch\tC\n"
         "dH\tD\n"
         "dh\tD\n"
         "gH\tG\n"
         "gh\tG\n"
         "jH\tJ\n"
         "jh\tJ\n"
         "kH\tK\n"
         "kh\tK\n"
         "l̥\tx\n"
         "l̥̄\tX\n"
         "pH\tP\n"
         "ph\tP\n"
         "r̥\tf\n"
         "r̥̄\tF\n"
         "tH\tT\n"
         "th\tT\n"
         "|\t.\n"
         "||\t..\n"
         "À\t^a\n"
         "Á\t/a\n"
         "È\t^e\n"
         "É\t/e\n"
         "Ì\t^i\n"
         "Í\t/i\n"
         "Ñ\tY\n"
         "Ò\t^o\n"
         "Ó\t/o\n"
         "Ù\t^u\n"
         "Ú\t/u\n"
         "à\t^a\n"
         "á\t/a\n"
         "è\t^e\n"
         "é\t/e\n"
         "ì\t^i\n"
         "í\t/i\n"
         "ñ\tY\n"
         "ò\t^o\n"
         "ó\t/o\n"
         "ù\t^u\n"
         "ú\t/u\n"
         "Ā\tA\n"
         "Ā̀\t^A\n"
         "Ā́\t/A\n"
         "ā\tA\n"
         "ā̀\t^A\n"
         "ā́\t/A\n"
         "Ī\tI\n"
         "Ī̀\t^I\n"
         "Ī́\t/I\n"
         "ī\tI\n"
         "ī̀\t^I\n"
         "ī́\t/I\n"
         "Ś\tS\n"
         "ś\tS\n"
         "Ū\tU\n"
         "Ū̀\t^U\n"
         "Ū́\t/U\n"
         "ū\tU\n"
         "ū̀\t^U\n"
         "ū́\t/U\n"
         "̃\t~\n"
         "Ḍ\tq\n"
         "ḌH\tQ\n"
         "Ḍh\tQ\n"
         "ḍ\tq\n"
         "ḍH\tQ\n"
         "ḍh\tQ\n"
         "Ḥ\tH\n"
         "ḥ\tH\n"
         "Ḷ\tx\n"
         "ḶH\t|\n"
         "Ḷh\t|\n"
         "Ḷ̀\t^x\n"
         "Ḷ́\t/x\n"
         "ḷ\tx\n"
         "ḷH\t|\n"
         "ḷh\t|\n"
         "ḷ̀\t^x\n"
         "ḷ́\t/x\n"
         "Ḹ\tX\n"
         "Ḹ̀\t^X\n"
         "Ḹ́\t/X\n"
         "ḹ\tX\n"
         "ḹ̀\t^X\n"
         "ḹ́\t/X\n"
         "Ḻ\tL\n"
         "ḻ\tL\n"
         "Ṃ\tM\n"
         "ṃ\tM\n"
         "Ṅ\tN\n"
         "ṅ\tN\n"
         "Ṇ\tR\n"
         "ṇ\tR\n"
         "Ṛ\tf\n"
         "Ṛ̀\t^f\n"
         "Ṛ́\t/f\n"
         "ṛ\tf\n"
         "ṛ̀\t^f\n"
         "ṛ́\t/f\n"
         "Ṝ\tF\n"
         "Ṝ̀\t^F\n"
         "Ṝ́\t/F\n"
         "ṝ\tF\n"
         "ṝ̀\t^F\n"
         "ṝ́\t/F\n"
         "Ṣ\tz\n"
         "ṣ\tz\n"
         "Ṭ\tw\n"
         "ṬH\tW\n"
         "Ṭh\tW\n"
         "ṭ\tw\n"
         "ṭH\tW\n"
         "ṭh\tW\n"
         ,
      [VELTHUIS] =
         "L̥\t.L\n"
         "L̥̄\t.Ll\n"
         "R̥\t.R\n"
         "R̥̄\t.Rr\n"
         "l̥\t.l\n"
         "l̥̄\t.ll\n"
         "r̥\t.r\n"
         "r̥̄\t.rr\n"
         "Ñ\t~N\n"
         "ñ\t~n\n"
         "Ā\tAa\n"
         "ā\taa\n"
         "Ī\tIi\n"
         "ī\tii\n"
         "Ś\tZ\n"
         "ś\tz\n"
         "Ū\tUu\n"
         "ū\tuu\n"
         "Ḍ\t.D\n"
         "ḍ\t.d\n"
         "Ḥ\t.H\n"
         "ḥ\t.h\n"
         "Ḷ\t.L\n"
         "ḷ\t.l\n"
         "Ḹ\t.Ll\n"
         "ḹ\t.ll\n"
         "Ṁ\t~~\n"
         "ṁ\t~~\n"
         "Ṃ\t.M\n"
         "ṃ\t.m\n"
         "Ṅ\tF\n"
         "ṅ\tf\n"
         "Ṇ\t.N\n"
         "ṇ\t.n\n"
         "Ṛ\t.R\n"
         "ṛ\t.r\n"
         "Ṝ\t.Rr\n"
         "ṝ\t.rr\n"
         "Ṣ\t.S\n"
         "ṣ\t.s\n"
         "Ṭ\t.T\n"
         "ṭ\t.t\n"
         ,
   },
   [IASTC] = {
      [IAST] =
         "L̥\tḶ\n"
         "L̥̄\tḸ\n"
         "R̥\tṚ\n"
         "R̥̄\tṜ\n"
         "l̥\tḷ\n"
         "l̥̄\tḹ\n"
         "r̥\tṛ\n"
         "r̥̄\tṝ\n"
         ,
      [IASTC] =
         ""
         ,
   },
   [NAGARI] = {
      [NAGARI] =
         ""
         ,
   },
   [SLP1] = {
      [IAST] =
         ".\t|\n"
         "..\t||\n"
         "/A\tā́\n"
         "/E\taí\n"
         "/F\tṝ́\n"
         "/I\tī́\n"
         "/L\tL\n"
         "/O\taú\n"
         "/U\tū́\n"
         "/X\tḹ́\n"
         "/a\tá\n"
         "/e\té\n"
         "/f\tṛ́\n"
         "/i\tí\n"
         "/o\tó\n"
         "/u\tú\n"
         "/x\tḷ́\n"
         "A\tā\n"
         "B\tbh\n"
         "C\tch\n"
         "D\tdh\n"
         "E\tai\n"
         "F\tṝ\n"
         "G\tgh\n"
         "H\tḥ\n"
         "I\tī\n"
         "J\tjh\n"
         "K\tkh\n"
         "L\tḻ\n"
         "M\tṃ\n"
         "N\tṅ\n"
         "O\tau\n"
         "P\tph\n"
         "Q\tḍh\n"
         "R\tṇ\n"
         "S\tś\n"
         "T\tth\n"
         "U\tū\n"
         "W\tṭh\n"
         "X\tḹ\n"
         "Y\tñ\n"
         "^A\tā̀\n"
         "^E\taì\n"
         "^F\tṝ̀\n"
         "^I\tī̀\n"
         "^O\taù\n"
         "^U\tū̀\n"
         "^X\tḹ̀\n"
         "^a\tà\n"
         "^e\tè\n"
         "^f\tṛ̀\n"
         "^i\tì\n"
         "^o\tò\n"
         "^u\tù\n"
         "^x\tḷ̀\n"
         "`A\tā̀\n"
         "`E\taì\n"
         "`F\tṝ̀\n"
         "`I\tī̀\n"
         "`O\taù\n"
         "`U\tū̀\n"
         "`X\tḹ̀\n"
         "`a\tà\n"
         "`e\tè\n"
         "`f\tṛ̀\n"
         "`i\tì\n"
         "`o\tò\n"
         "`u\tù\n"
         "`x\tḷ̀\n"
         "f\tṛ\n"
         "jY\tjñ\n"
         "kz\tkṣ\n"
         "q\tḍ\n"
         "w\tṭ\n"
         "x\tḷ\n"
         "z\tṣ\n"
         "|\tḷh\n"
         "~\t̃\n"
         ,
      [IASTC] =
         ".\t|\n"
         "..\t||\n"
         "/A\tā́\n"
         "/E\taí\n"
         "/F\tṝ́\n"
         "/I\tī́\n"
         "/L\tL\n"
         "/O\taú\n"
         "/U\tū́\n"
         "/X\tḹ́\n"
         "/a\tá\n"
         "/e\té\n"
         "/f\tṛ́\n"
         "/i\tí\n"
         "/o\tó\n"
         "/u\tú\n"
         "/x\tḷ́\n"
         "A\tā\n"
         "B\tbh\n"
         "C\tch\n"
         "D\tdh\n"
         "E\tai\n"
         "F\tr̥̄\n"
         "G\tgh\n"
         "H\tḥ\n"
         "I\tī\n"
         "J\tjh\n"
         "K\tkh\n"
         "L\tḻ\n"
         "M\tṃ\n"
         "N\tṅ\n"
         "O\tau\n"
         "P\tph\n"
         "Q\tḍh\n"
         "R\tṇ\n"
         "S\tś\n"
         "T\tth\n"
         "U\tū\n"
         "W\tṭh\n"
         "X\tl̥̄\n"
         "Y\tñ\n"
         "^A\tā̀\n"
         "^E\taì\n"
         "^F\tṝ̀\n"
         "^I\tī̀\n"
         "^O\taù\n"
         "^U\tū̀\n"
         "^X\tḹ̀\n"
         "^a\tà\n"
         "^e\tè\n"
         "^f\tṛ̀\n"
         "^i\tì\n"
         "^o\tò\n"
         "^u\tù\n"
         "^x\tḷ̀\n"
         "`A\tā̀\n"
         "`E\taì\n"
         "`F\tṝ̀\n"
         "`I\tī̀\n"
         "`O\taù\n"
         "`U\tū̀\n"
         "`X\tḹ̀\n"
         "`a\tà\n"
         "`e\tè\n"
         "`f\tṛ̀\n"
         "`i\tì\n"
         "`o\tò\n"
         "`u\tù\n"
         "`x\tḷ̀\n"
         "f\tr̥\n"
         "jY\tjñ\n"
         "kz\tkṣ\n"
         "q\tḍ\n"
         "w\tṭ\n"
         "x\tl̥\n"
         "z\tṣ\n"
         "|\tḷh\n"
         "~\t̃\n"
         ,
      [SLP1] =
         ""
         ,
   },
   [VELTHUIS] = {
      [IAST] =
         ".D\tḌ\n"
         ".H\tḤ\n"
         ".L\tḶ\n"
         ".LL\tḸ\n"
         ".Ll\tḸ\n"
         ".M\tṂ\n"
         ".N\tṆ\n"
         ".R\tṚ\n"
         ".RR\tṜ\n"
         ".Rr\tṜ\n"
         ".S\tṢ\n"
         ".T\tṬ\n"
         ".d\tḍ\n"
         ".h\tḥ\n"
         ".l\tḷ\n"
         ".ll\tḹ\n"
         ".m\tṃ\n"
         ".n\tṇ\n"
         ".r\tṛ\n"
         ".rr\tṝ\n"
         ".s\tṣ\n"
         ".t\tṭ\n"
         "AA\tĀ\n"
         "Aa\tĀ\n"
         "F\tṄ\n"
         "II\tĪ\n"
         "Ii\tĪ\n"
         "UU\tŪ\n"
         "Uu\tŪ\n"
         "Z\tŚ\n"
         "aa\tā\n"
         "f\tṅ\n"
         "ii\tī\n"
         "uu\tū\n"
         "z\tś\n"
         "~N\tÑ\n"
         "~n\tñ\n"
         "~~\tṁ\n"
         ,
      [IASTC] =
         ".D\tḌ\n"
         ".H\tḤ\n"
         ".L\tL̥\n"
         ".LL\tL̥̄\n"
         ".Ll\tL̥̄\n"
         ".M\tṂ\n"
         ".N\tṆ\n"
         ".R\tR̥\n"
         ".RR\tR̥̄\n"
         ".Rr\tR̥̄\n"
         ".S\tṢ\n"
         ".T\tṬ\n"
         ".d\tḍ\n"
         ".h\tḥ\n"
         ".l\tl̥\n"
         ".ll\tl̥̄\n"
         ".m\tṃ\n"
         ".n\tṇ\n"
         ".r\tr̥\n"
         ".rr\tr̥̄\n"
         ".s\tṣ\n"
         ".t\tṭ\n"
         "AA\tĀ\n"
         "Aa\tĀ\n"
         "F\tṄ\n"
         "II\tĪ\n"
         "Ii\tĪ\n"
         "UU\tŪ\n"
         "Uu\tŪ\n"
         "Z\tŚ\n"
         "aa\tā\n"
         "f\tṅ\n"
         "ii\tī\n"
         "uu\tū\n"
         "z\tś\n"
         "~N\tÑ\n"
         "~n\tñ\n"
         "~~\tṁ\n"
         ,
      [VELTHUIS] =
         ""
         ,
   },
};
#line 49 "skt.c"
#line 1 "skt_sort.ic"

#line 1 "skt_sort.rl"

#line 801 "skt_sort.rl"


void skt_sort_key(struct skt_buf *buf, const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;

#line 18 "skt_sort.ic"
static const unsigned char _skt_sort_key_actions[] = {
   0, 1, 0, 1, 1, 1, 2, 1,
   3, 1, 4, 1, 5, 1, 6, 1,
   7, 1, 8, 1, 9, 1, 10, 1,
   11, 1, 12, 1, 13, 1, 14, 1,
   15, 1, 16, 1, 17, 1, 18, 1,
   19, 1, 20, 1, 21, 1, 22, 1,
   23, 1, 24, 1, 25, 1, 26, 1,
   27, 1, 28, 1, 29, 1, 30, 1,
   31, 1, 32, 1, 33, 1, 34, 1,
   35, 1, 36, 1, 37, 1, 38, 1,
   39, 1, 40, 1, 41, 1, 42, 1,
   43, 1, 44, 1, 45, 1, 46, 1,
   47, 1, 48, 1, 49, 1, 50, 1,
   51, 1, 52, 1, 53, 1, 54, 1,
   55, 1, 56, 1, 57, 1, 58, 1,
   59, 1, 60, 1, 61, 1, 62, 1,
   63, 1, 64, 1, 65, 1, 66, 1,
   67, 1, 68, 1, 69, 1, 70, 1,
   71, 1, 72, 1, 73, 1, 74, 1,
   75, 1, 76, 1, 77, 1, 78, 1,
   79, 1, 80, 1, 81, 1, 82, 1,
   83, 1, 84, 1, 85, 1, 86, 1,
   87, 1, 88, 1, 89, 1, 90, 1,
   91, 1, 92, 1, 93, 1, 94, 1,
   95, 1, 96, 1, 97, 1, 98, 1,
   99, 1, 100, 1, 101, 1, 102, 1,
   103, 1, 104, 1, 105, 1, 106, 1,
   107, 1, 108, 1, 109, 1, 110, 1,
   111, 1, 112, 1, 113, 1, 114, 1,
   115, 1, 116, 1, 117, 1, 118, 1,
   119, 1, 120, 1, 121, 1, 122, 1,
   123, 1, 124, 1, 125, 1, 126, 1,
   127, 1, 128, 1, 129, 1, 130, 1,
   131, 1, 132, 1, 133, 1, 134, 1,
   135, 1, 136, 1, 137, 1, 138, 1,
   139, 1, 140, 1, 141, 1, 142, 1,
   143, 1, 144, 1, 145, 1, 146
};

static const unsigned char _skt_sort_key_key_offsets[] = {
   0, 1, 2, 3, 4, 5, 6, 7,
   8, 16, 30, 37, 38, 91, 92, 96,
   98, 100, 102, 104, 106, 108, 109, 110,
   112, 113, 114, 116, 120, 122, 124, 126,
   128, 130, 132, 133, 134, 136, 137, 138,
   140, 142, 144, 148, 152, 154, 156, 158,
   160, 162
};

static const unsigned char _skt_sort_key_trans_keys[] = {
   165u, 132u, 165u, 132u, 165u, 132u, 165u, 132u,
   140u, 141u, 164u, 165u, 182u, 183u, 184u, 185u,
   130u, 131u, 132u, 133u, 134u, 135u, 154u, 155u,
   156u, 157u, 162u, 163u, 172u, 173u, 175u, 128u,
   139u, 147u, 148u, 168u, 169u, 159u, 13u, 32u,
   45u, 65u, 66u, 67u, 68u, 69u, 71u, 72u,
   73u, 74u, 75u, 76u, 77u, 78u, 79u, 80u,
   82u, 83u, 84u, 85u, 86u, 89u, 97u, 98u,
   99u, 100u, 101u, 103u, 104u, 105u, 106u, 107u,
   108u, 109u, 110u, 111u, 112u, 114u, 115u, 116u,
   117u, 118u, 121u, 194u, 195u, 196u, 197u, 225u,
   226u, 9u, 12u, 10u, 73u, 85u, 105u, 117u,
   72u, 104u, 72u, 104u, 72u, 104u, 72u, 104u,
   72u, 104u, 72u, 104u, 204u, 204u, 72u, 104u,
   204u, 204u, 72u, 104u, 73u, 85u, 105u, 117u,
   72u, 104u, 72u, 104u, 72u, 104u, 72u, 104u,
   72u, 104u, 72u, 104u, 204u, 204u, 72u, 104u,
   204u, 204u, 72u, 104u, 133u, 160u, 145u, 177u,
   128u, 129u, 170u, 171u, 154u, 155u, 170u, 171u,
   184u, 185u, 72u, 104u, 72u, 104u, 72u, 104u,
   72u, 104u, 128u, 129u, 0
};

static const char _skt_sort_key_single_lengths[] = {
   1, 1, 1, 1, 1, 1, 1, 1,
   8, 14, 1, 1, 51, 1, 4, 2,
   2, 2, 2, 2, 2, 1, 1, 2,
   1, 1, 2, 4, 2, 2, 2, 2,
   2, 2, 1, 1, 2, 1, 1, 2,
   2, 2, 4, 4, 2, 2, 2, 2,
   2, 2
};

static const char _skt_sort_key_range_lengths[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 3, 0, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0
};

static const short _skt_sort_key_index_offsets[] = {
   0, 2, 4, 6, 8, 10, 12, 14,
   16, 25, 40, 45, 47, 100, 102, 107,
   110, 113, 116, 119, 122, 125, 127, 129,
   132, 134, 136, 139, 144, 147, 150, 153,
   156, 159, 162, 164, 166, 169, 171, 173,
   176, 179, 182, 187, 192, 195, 198, 201,
   204, 207
};

static const char _skt_sort_key_trans_targs[] = {
   22, 12, 12, 12, 25, 12, 12, 12,
   35, 12, 12, 12, 38, 12, 12, 12,
   45, 46, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 47, 48, 12,
   12, 12, 12, 12, 12, 12, 12, 13,
   12, 12, 14, 15, 16, 17, 12, 18,
   12, 12, 19, 20, 21, 12, 12, 12,
   23, 24, 12, 26, 12, 12, 12, 27,
   28, 29, 30, 12, 31, 12, 12, 32,
   33, 34, 12, 12, 12, 36, 37, 12,
   39, 12, 12, 12, 40, 41, 42, 43,
   44, 49, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 0, 12, 1,
   12, 12, 12, 12, 2, 12, 3, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 4, 12, 5, 12, 12, 12,
   12, 6, 12, 7, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   8, 9, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 10,
   11, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 12, 12, 12, 12, 12,
   12, 12, 12, 0
};

static const short _skt_sort_key_trans_actions[] = {
   5, 289, 47, 281, 5, 285, 31, 277,
   5, 291, 49, 283, 5, 287, 33, 279,
   0, 0, 79, 81, 39, 41, 43, 45,
   293, 75, 77, 99, 101, 139, 141, 27,
   29, 35, 37, 195, 197, 0, 0, 293,
   209, 209, 207, 209, 293, 209, 293, 0,
   209, 207, 0, 0, 0, 0, 51, 0,
   203, 11, 0, 0, 5, 179, 159, 63,
   0, 5, 199, 0, 19, 187, 183, 0,
   0, 0, 0, 53, 0, 205, 13, 0,
   0, 5, 181, 161, 65, 0, 5, 201,
   0, 21, 189, 185, 0, 0, 0, 0,
   5, 5, 209, 211, 209, 273, 55, 67,
   57, 69, 213, 171, 173, 261, 103, 105,
   233, 151, 153, 253, 91, 93, 229, 111,
   113, 237, 83, 85, 225, 0, 269, 0,
   221, 163, 165, 257, 0, 265, 0, 217,
   143, 145, 249, 59, 71, 61, 73, 215,
   175, 177, 263, 107, 109, 235, 155, 157,
   255, 95, 97, 231, 115, 117, 239, 87,
   89, 227, 0, 271, 0, 223, 167, 169,
   259, 0, 267, 0, 219, 147, 149, 251,
   209, 209, 275, 119, 121, 275, 7, 9,
   15, 17, 275, 191, 193, 23, 25, 275,
   0, 0, 275, 131, 133, 245, 135, 137,
   247, 123, 125, 241, 127, 129, 243, 0,
   0, 275, 289, 281, 285, 277, 291, 283,
   287, 279, 293, 293, 293, 293, 273, 213,
   261, 233, 253, 229, 237, 225, 269, 221,
   257, 265, 217, 249, 215, 263, 235, 255,
   231, 239, 227, 271, 223, 259, 267, 219,
   251, 275, 275, 275, 275, 275, 245, 247,
   241, 243, 275, 0
};

static const short _skt_sort_key_to_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0
};

static const short _skt_sort_key_from_state_actions[] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 3, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0
};

static const short _skt_sort_key_eof_trans[] = {
   211, 212, 213, 214, 215, 216, 217, 218,
   222, 222, 222, 222, 0, 223, 224, 225,
   226, 227, 228, 229, 230, 231, 232, 233,
   234, 235, 236, 237, 238, 239, 240, 241,
   242, 243, 244, 245, 246, 247, 248, 249,
   259, 259, 259, 259, 259, 255, 256, 257,
   258, 259
};

static const int skt_sort_key_start = 12;
static const int skt_sort_key_first_final = 12;
static const int skt_sort_key_error = -1;

static const int skt_sort_key_en_main = 12;


#line 813 "skt_sort.rl"

#line 234 "skt_sort.ic"
   {
   cs = skt_sort_key_start;
   ts = 0;
   te = 0;
   act = 0;
   }

#line 814 "skt_sort.rl"

#line 244 "skt_sort.ic"
   {
   int _klen;
   unsigned int _trans;
   const unsigned char *_acts;
   unsigned int _nacts;
   const unsigned char *_keys;

   if ( p == pe )
      goto _test_eof;
_resume:
   _acts = _skt_sort_key_actions + _skt_sort_key_from_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 1:
#line 1 "NONE"
   {ts = p;}
   break;
#line 263 "skt_sort.ic"
      }
   }

   _keys = _skt_sort_key_trans_keys + _skt_sort_key_key_offsets[cs];
   _trans = _skt_sort_key_index_offsets[cs];

   _klen = _skt_sort_key_single_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + _klen - 1;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + ((_upper-_lower) >> 1);
         if ( (*p) < *_mid )
            _upper = _mid - 1;
         else if ( (*p) > *_mid )
            _lower = _mid + 1;
         else {
            _trans += (unsigned int)(_mid - _keys);
            goto _match;
         }
      }
      _keys += _klen;
      _trans += _klen;
   }

   _klen = _skt_sort_key_range_lengths[cs];
   if ( _klen > 0 ) {
      const unsigned char *_lower = _keys;
      const unsigned char *_mid;
      const unsigned char *_upper = _keys + (_klen<<1) - 2;
      while (1) {
         if ( _upper < _lower )
            break;

         _mid = _lower + (((_upper-_lower) >> 1) & ~1);
         if ( (*p) < _mid[0] )
            _upper = _mid - 2;
         else if ( (*p) > _mid[1] )
            _lower = _mid + 2;
         else {
            _trans += (unsigned int)((_mid - _keys)>>1);
            goto _match;
         }
      }
      _trans += _klen;
   }

_match:
_eof_trans:
   cs = _skt_sort_key_trans_targs[_trans];

   if ( _skt_sort_key_trans_actions[_trans] == 0 )
      goto _again;

   _acts = _skt_sort_key_actions + _skt_sort_key_trans_actions[_trans];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 )
   {
      switch ( *_acts++ )
      {
   case 2:
#line 1 "NONE"
   {te = p+1;}
   break;
   case 3:
#line 20 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 2;
   buf->data[buf->size++] = 1;
}}
   break;
   case 4:
#line 25 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 2;
   buf->data[buf->size++] = 2;
}}
   break;
   case 5:
#line 30 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 3;
   buf->data[buf->size++] = 1;
}}
   break;
   case 6:
#line 35 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 3;
   buf->data[buf->size++] = 2;
}}
   break;
   case 7:
#line 40 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 4;
   buf->data[buf->size++] = 1;
}}
   break;
   case 8:
#line 45 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 4;
   buf->data[buf->size++] = 2;
}}
   break;
   case 9:
#line 50 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 5;
   buf->data[buf->size++] = 1;
}}
   break;
   case 10:
#line 55 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 5;
   buf->data[buf->size++] = 2;
}}
   break;
   case 11:
#line 60 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 6;
   buf->data[buf->size++] = 1;
}}
   break;
   case 12:
#line 65 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 6;
   buf->data[buf->size++] = 2;
}}
   break;
   case 13:
#line 80 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 8;
   buf->data[buf->size++] = 1;
}}
   break;
   case 14:
#line 85 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 8;
   buf->data[buf->size++] = 2;
}}
   break;
   case 15:
#line 90 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 9;
   buf->data[buf->size++] = 1;
}}
   break;
   case 16:
#line 95 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 9;
   buf->data[buf->size++] = 2;
}}
   break;
   case 17:
#line 100 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 10;
   buf->data[buf->size++] = 1;
}}
   break;
   case 18:
#line 105 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 10;
   buf->data[buf->size++] = 2;
}}
   break;
   case 19:
#line 120 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 12;
   buf->data[buf->size++] = 1;
}}
   break;
   case 20:
#line 125 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 12;
   buf->data[buf->size++] = 2;
}}
   break;
   case 21:
#line 130 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 13;
   buf->data[buf->size++] = 1;
}}
   break;
   case 22:
#line 135 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 13;
   buf->data[buf->size++] = 2;
}}
   break;
   case 23:
#line 140 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 14;
   buf->data[buf->size++] = 1;
}}
   break;
   case 24:
#line 145 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 14;
   buf->data[buf->size++] = 2;
}}
   break;
   case 25:
#line 150 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 15;
   buf->data[buf->size++] = 1;
}}
   break;
   case 26:
#line 155 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 15;
   buf->data[buf->size++] = 2;
}}
   break;
   case 27:
#line 160 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 1;
}}
   break;
   case 28:
#line 165 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 2;
}}
   break;
   case 29:
#line 170 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 3;
}}
   break;
   case 30:
#line 175 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 4;
}}
   break;
   case 31:
#line 180 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 17;
   buf->data[buf->size++] = 1;
}}
   break;
   case 32:
#line 185 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 17;
   buf->data[buf->size++] = 2;
}}
   break;
   case 33:
#line 190 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 1;
}}
   break;
   case 34:
#line 195 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 2;
}}
   break;
   case 35:
#line 200 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 3;
}}
   break;
   case 36:
#line 205 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 4;
}}
   break;
   case 37:
#line 210 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 19;
   buf->data[buf->size++] = 1;
}}
   break;
   case 38:
#line 215 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 19;
   buf->data[buf->size++] = 2;
}}
   break;
   case 39:
#line 220 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 20;
   buf->data[buf->size++] = 1;
}}
   break;
   case 40:
#line 225 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 20;
   buf->data[buf->size++] = 2;
}}
   break;
   case 41:
#line 240 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 1;
}}
   break;
   case 42:
#line 245 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 2;
}}
   break;
   case 43:
#line 250 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 3;
}}
   break;
   case 44:
#line 255 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 4;
}}
   break;
   case 45:
#line 270 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 1;
}}
   break;
   case 46:
#line 275 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 2;
}}
   break;
   case 47:
#line 280 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 3;
}}
   break;
   case 48:
#line 285 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 4;
}}
   break;
   case 49:
#line 290 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 25;
   buf->data[buf->size++] = 1;
}}
   break;
   case 50:
#line 295 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 25;
   buf->data[buf->size++] = 2;
}}
   break;
   case 51:
#line 310 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 1;
}}
   break;
   case 52:
#line 315 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 2;
}}
   break;
   case 53:
#line 320 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 3;
}}
   break;
   case 54:
#line 325 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 4;
}}
   break;
   case 55:
#line 340 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 1;
}}
   break;
   case 56:
#line 345 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 2;
}}
   break;
   case 57:
#line 350 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 3;
}}
   break;
   case 58:
#line 355 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 4;
}}
   break;
   case 59:
#line 360 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 30;
   buf->data[buf->size++] = 1;
}}
   break;
   case 60:
#line 365 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 30;
   buf->data[buf->size++] = 2;
}}
   break;
   case 61:
#line 380 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 1;
}}
   break;
   case 62:
#line 385 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 2;
}}
   break;
   case 63:
#line 390 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 3;
}}
   break;
   case 64:
#line 395 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 4;
}}
   break;
   case 65:
#line 410 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 1;
}}
   break;
   case 66:
#line 415 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 2;
}}
   break;
   case 67:
#line 420 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 3;
}}
   break;
   case 68:
#line 425 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 4;
}}
   break;
   case 69:
#line 430 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 35;
   buf->data[buf->size++] = 1;
}}
   break;
   case 70:
#line 435 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 35;
   buf->data[buf->size++] = 2;
}}
   break;
   case 71:
#line 450 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 1;
}}
   break;
   case 72:
#line 455 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 2;
}}
   break;
   case 73:
#line 460 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 3;
}}
   break;
   case 74:
#line 465 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 4;
}}
   break;
   case 75:
#line 480 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 1;
}}
   break;
   case 76:
#line 485 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 2;
}}
   break;
   case 77:
#line 490 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 3;
}}
   break;
   case 78:
#line 495 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 4;
}}
   break;
   case 79:
#line 500 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 40;
   buf->data[buf->size++] = 1;
}}
   break;
   case 80:
#line 505 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 40;
   buf->data[buf->size++] = 2;
}}
   break;
   case 81:
#line 520 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 1;
}}
   break;
   case 82:
#line 525 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 2;
}}
   break;
   case 83:
#line 530 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 3;
}}
   break;
   case 84:
#line 535 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 4;
}}
   break;
   case 85:
#line 550 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 1;
}}
   break;
   case 86:
#line 555 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 2;
}}
   break;
   case 87:
#line 560 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 3;
}}
   break;
   case 88:
#line 565 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 4;
}}
   break;
   case 89:
#line 570 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 45;
   buf->data[buf->size++] = 1;
}}
   break;
   case 90:
#line 575 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 45;
   buf->data[buf->size++] = 2;
}}
   break;
   case 91:
#line 580 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 1;
}}
   break;
   case 92:
#line 585 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 2;
}}
   break;
   case 93:
#line 610 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 49;
   buf->data[buf->size++] = 1;
}}
   break;
   case 94:
#line 615 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 49;
   buf->data[buf->size++] = 2;
}}
   break;
   case 95:
#line 620 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 50;
   buf->data[buf->size++] = 1;
}}
   break;
   case 96:
#line 625 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 50;
   buf->data[buf->size++] = 2;
}}
   break;
   case 97:
#line 630 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 51;
   buf->data[buf->size++] = 1;
}}
   break;
   case 98:
#line 635 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 51;
   buf->data[buf->size++] = 2;
}}
   break;
   case 99:
#line 640 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 52;
   buf->data[buf->size++] = 1;
}}
   break;
   case 100:
#line 645 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 52;
   buf->data[buf->size++] = 2;
}}
   break;
   case 101:
#line 650 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 53;
   buf->data[buf->size++] = 1;
}}
   break;
   case 102:
#line 655 "skt_sort.rl"
   {te = p+1;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 53;
   buf->data[buf->size++] = 2;
}}
   break;
   case 103:
#line 792 "skt_sort.rl"
   {te = p+1;}
   break;
   case 104:
#line 793 "skt_sort.rl"
   {te = p+1;}
   break;
   case 105:
#line 794 "skt_sort.rl"
   {te = p+1;{
      skt_buf_grow(buf, 2);
      buf->data[buf->size++] = 0xff;
      buf->data[buf->size++] = *p;
   }}
   break;
   case 106:
#line 10 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 1;
   buf->data[buf->size++] = 1;
}}
   break;
   case 107:
#line 15 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 1;
   buf->data[buf->size++] = 2;
}}
   break;
   case 108:
#line 70 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 7;
   buf->data[buf->size++] = 1;
}}
   break;
   case 109:
#line 75 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 7;
   buf->data[buf->size++] = 2;
}}
   break;
   case 110:
#line 110 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 11;
   buf->data[buf->size++] = 1;
}}
   break;
   case 111:
#line 115 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 11;
   buf->data[buf->size++] = 2;
}}
   break;
   case 112:
#line 230 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 21;
   buf->data[buf->size++] = 1;
}}
   break;
   case 113:
#line 235 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 21;
   buf->data[buf->size++] = 2;
}}
   break;
   case 114:
#line 260 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 23;
   buf->data[buf->size++] = 1;
}}
   break;
   case 115:
#line 265 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 23;
   buf->data[buf->size++] = 2;
}}
   break;
   case 116:
#line 300 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 26;
   buf->data[buf->size++] = 1;
}}
   break;
   case 117:
#line 305 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 26;
   buf->data[buf->size++] = 2;
}}
   break;
   case 118:
#line 330 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 28;
   buf->data[buf->size++] = 1;
}}
   break;
   case 119:
#line 335 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 28;
   buf->data[buf->size++] = 2;
}}
   break;
   case 120:
#line 370 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 31;
   buf->data[buf->size++] = 1;
}}
   break;
   case 121:
#line 375 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 31;
   buf->data[buf->size++] = 2;
}}
   break;
   case 122:
#line 400 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 33;
   buf->data[buf->size++] = 1;
}}
   break;
   case 123:
#line 405 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 33;
   buf->data[buf->size++] = 2;
}}
   break;
   case 124:
#line 440 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 36;
   buf->data[buf->size++] = 1;
}}
   break;
   case 125:
#line 445 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 36;
   buf->data[buf->size++] = 2;
}}
   break;
   case 126:
#line 470 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 38;
   buf->data[buf->size++] = 1;
}}
   break;
   case 127:
#line 475 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 38;
   buf->data[buf->size++] = 2;
}}
   break;
   case 128:
#line 510 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 41;
   buf->data[buf->size++] = 1;
}}
   break;
   case 129:
#line 515 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 41;
   buf->data[buf->size++] = 2;
}}
   break;
   case 130:
#line 540 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 43;
   buf->data[buf->size++] = 1;
}}
   break;
   case 131:
#line 545 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 43;
   buf->data[buf->size++] = 2;
}}
   break;
   case 132:
#line 590 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 1;
}}
   break;
   case 133:
#line 595 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 2;
}}
   break;
   case 134:
#line 600 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 48;
   buf->data[buf->size++] = 1;
}}
   break;
   case 135:
#line 605 "skt_sort.rl"
   {te = p;p--;{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 48;
   buf->data[buf->size++] = 2;
}}
   break;
   case 136:
#line 793 "skt_sort.rl"
   {te = p;p--;}
   break;
   case 137:
#line 794 "skt_sort.rl"
   {te = p;p--;{
      skt_buf_grow(buf, 2);
      buf->data[buf->size++] = 0xff;
      buf->data[buf->size++] = *p;
   }}
   break;
   case 138:
#line 70 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 7;
   buf->data[buf->size++] = 1;
}}
   break;
   case 139:
#line 75 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 7;
   buf->data[buf->size++] = 2;
}}
   break;
   case 140:
#line 110 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 11;
   buf->data[buf->size++] = 1;
}}
   break;
   case 141:
#line 115 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 11;
   buf->data[buf->size++] = 2;
}}
   break;
   case 142:
#line 590 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 1;
}}
   break;
   case 143:
#line 595 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 2;
}}
   break;
   case 144:
#line 600 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 48;
   buf->data[buf->size++] = 1;
}}
   break;
   case 145:
#line 605 "skt_sort.rl"
   {{p = ((te))-1;}{
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 48;
   buf->data[buf->size++] = 2;
}}
   break;
   case 146:
#line 794 "skt_sort.rl"
   {{p = ((te))-1;}{
      skt_buf_grow(buf, 2);
      buf->data[buf->size++] = 0xff;
      buf->data[buf->size++] = *p;
   }}
   break;
#line 1472 "skt_sort.ic"
      }
   }

_again:
   _acts = _skt_sort_key_actions + _skt_sort_key_to_state_actions[cs];
   _nacts = (unsigned int) *_acts++;
   while ( _nacts-- > 0 ) {
      switch ( *_acts++ ) {
   case 0:
#line 1 "NONE"
   {ts = 0;}
   break;
#line 1485 "skt_sort.ic"
      }
   }

   if ( ++p != pe )
      goto _resume;
   _test_eof: {}
   if ( p == eof )
   {
   if ( _skt_sort_key_eof_trans[cs] > 0 ) {
      _trans = _skt_sort_key_eof_trans[cs] - 1;
      goto _eof_trans;
   }
   }

   }

#line 815 "skt_sort.rl"
   skt_buf_truncate(buf, buf->size);
}
#line 50 "skt.c"

skt_translit skt_translit_func(const char *input_scheme,
                               const char *output_scheme)
{
   size_t input = skt_scheme_value(input_scheme);
   size_t output = skt_scheme_value(output_scheme);

   if (input < NUM_SCHEMES && output < NUM_SCHEMES)
      return skt_maps[input][output];
   return 0;
}

const char *skt_map_description(const char *input_scheme,
                                const char *output_scheme)
{
   size_t input = skt_scheme_value(input_scheme);
   size_t output = skt_scheme_value(output_scheme);

   if (input < NUM_SCHEMES && output < NUM_SCHEMES)
      return skt_maps_description[input][output];
   return "";
}
