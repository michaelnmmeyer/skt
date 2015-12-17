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

/* Creates a sort key for a IAST-encoded string.
 * If the provided string doesn't contain nul bytes, the created key won't, too.
 */
void skt_sort_key(struct skt_buf *buf, const char *str, size_t len);

#endif
