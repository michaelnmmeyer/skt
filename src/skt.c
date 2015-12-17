#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "skt.h"
#include "buf.h"

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

#include "gen/skt_maps.ic"
#include "gen/skt_sort.ic"

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
