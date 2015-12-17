#include <string.h>
#include <errno.h>
#include "../src/mem.h"
#include "../src/skt.h"
#include "../src/buf.h"
#include "cmd.h"
#include "util.h"

/* Allocate memory in large chunks. */
#define BLOCK_SIZE (1024 * 1024)

struct mapping {
   const char *key;
   const char *value;
};

static struct mapping *keys;
static size_t num_keys;

static const char *copy_string(const struct skt_buf *buf)
{
   static char *block;
   static size_t avail;
   
   size_t size = buf->size + 1;
   if (size > avail) {
      avail = size < BLOCK_SIZE ? BLOCK_SIZE : size;
      block = skt_malloc(avail);
   }
   
   void *copy = block;
   block += size;
   avail -= size;
   return memcpy(copy, buf->data, size);
}

static void save_mapping(const struct skt_buf *key, const struct skt_buf *value)
{
   static size_t keys_alloc;

   SKT_GROW(keys, num_keys, keys_alloc, 1, 1024);
   keys[num_keys].key = copy_string(key);
   keys[num_keys++].value = copy_string(value);
}

static int compare_keys(const void *xp, const void *yp)
{
   const struct mapping *x = xp, *y = yp;
   return strcmp(x->key, y->key);
}

static void sort(FILE *fp)
{
   struct skt_buf line = SKT_BUF_INIT;
   struct skt_buf key = SKT_BUF_INIT;

   while (read_line(&line, fp)) {
      skt_sort_key(&key, line.data, line.size);
      save_mapping(&key, &line);
   }
   
   qsort(keys, num_keys, sizeof *keys, compare_keys);
   for (size_t i = 0; i < num_keys; i++)
      write_line(keys[i].value);
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
         die("can't open file at '%s': %s", *argv, strerror(errno));
   }
   sort(fp);
   if (fp != stdin)
      fclose(fp);
}
