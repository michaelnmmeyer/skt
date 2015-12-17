#include <errno.h>
#include <string.h>
#include "../src/skt.h"
#include "../src/buf.h"
#include "cmd.h"
#include "util.h"

#define SKT_LINE_SIZE 4096

static bool get_line(struct skt_buf *buf, FILE *fp)
{
   skt_buf_clear(buf);

   int c;
   while ((c = getc(fp)) != EOF && c != '\n') {
      if (buf->size == buf->alloc)
         skt_buf_grow(buf, SKT_LINE_SIZE);
      buf->data[buf->size++] = c;
   }
   skt_buf_truncate(buf, buf->size);

   /* Ignore the last line if empty. */
   if (!buf->size) {
      c = getc(fp);
      if (c == EOF)
         return false;
      ungetc(c, fp);
   }
   return true;
}

bool read_line(struct skt_buf *buf, FILE *fp)
{
   static size_t line_no;
   
   if (get_line(buf, fp)) {
      line_no++;
      if (memchr(buf->data, '\0', buf->size))
         die("nul byte at line %zu", line_no);
      return true;
   }
   if (ferror(fp))
      die("io error: %s", strerror(errno));
   return false;
}

void write_line(const char *str)
{
   if (puts(str) == EOF)
      die("io error: %s", strerror(errno));
}
