#include <string.h>
#include "../src/mem.h"
#include "../src/skt.h"
#include "cmd.h"
#include "kabak.h"

/* Allocate memory in large chunks. */
#define BLOCK_SIZE (1024 * 1024)

struct mapping {
   const char *key;
   const char *value;
};

static struct mapping *keys;
static size_t num_keys;

static const char *copy_string(const char *str, size_t len)
{
   static char *block;
   static size_t avail;

   size_t size = len + 1;
   if (size > avail) {
      avail = size < BLOCK_SIZE ? BLOCK_SIZE : size;
      block = skt_malloc(avail);
   }

   void *copy = block;
   block += size;
   avail -= size;
   return memcpy(copy, str, size);
}

static void save_mapping(const char *key, size_t key_len,
                         const char *val, size_t val_len)
{
   static size_t keys_alloc;

   SKT_GROW(keys, num_keys, keys_alloc, 1, 1024);
   keys[num_keys].key = copy_string(key, key_len);
   keys[num_keys++].value = copy_string(val, val_len);
}

static int compare_keys(const void *xp, const void *yp)
{
   const struct mapping *x = xp, *y = yp;
   return strcmp(x->key, y->key);
}

static void sort(FILE *fp)
{
   struct kb_file strm;
   kb_wrap(&strm, fp);

   struct skt_buf key = SKT_BUF_INIT;
   struct kabak val = KB_INIT;
   int ret;
   while ((ret = kb_get_line(&strm, &val, KB_NFC)) != KB_FINI) {
      if (ret)
         die("cannot process input file: %s", kb_strerror(ret));
      skt_sort_key(&key, val.str, val.len);
      save_mapping(key.data, key.size, val.str, val.len);
   }

   qsort(keys, num_keys, sizeof *keys, compare_keys);
   for (size_t i = 0; i < num_keys; i++)
      if (puts(keys[i].value) == EOF)
         die("I/O error:");
}

int main(int argc, char **argv)
{
   const char help[] =
      #include "skt_sort.ih"
   ;
   parse_options(NULL, help, &argc, &argv);

   FILE *fp = stdin;
   if (argc && strcmp(*argv, "-")) {
      fp = fopen(*argv, "r");
      if (!fp)
         die("cannot open file at '%s':", *argv);
   }
   sort(fp);
   if (fp != stdin)
      fclose(fp);
}
