#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../src/skt.h"
#include "../src/buf.h"
#include "cmd.h"
#include "util.h"

static void translit_argv(skt_translit translit, char **argv)
{
   struct skt_buf buf = SKT_BUF_INIT;
   
   for (size_t i = 0; argv[i]; i++) {
      const char *str = argv[i];
      translit(&buf, str, strlen(str));
      if (fputs(buf.data, stdout) == EOF || putchar(argv[i + 1] ? ' ' : '\n') == EOF)
         die("io error: %s", strerror(errno));
   }
}

static void translit_stdin(skt_translit translit)
{
   struct skt_buf line = SKT_BUF_INIT;
   struct skt_buf output = SKT_BUF_INIT;
   
   while (read_line(&line, stdin)) {
      translit(&output, line.data, line.size);
      write_line(output.data);
   }
}

noreturn static void display_mappings(void)
{
	const char *const *schemes = skt_schemes;
	
   for (size_t i = 0; schemes[i]; i++)
      for (size_t j = 0; schemes[j]; j++)
         if (i != j && skt_translit_func(schemes[i], schemes[j]))
            printf("%s\t%s\n", schemes[i], schemes[j]);
   
   exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
   const char *input_scheme = "velthuis";
   const char *output_scheme = "iast";
   bool describe_mapping = false;
   
   struct option options[] = {
      {'i', "input-scheme",  OPT_STR(input_scheme)     },
      {'o', "output-scheme", OPT_STR(output_scheme)    },
      {'l', "list",          OPT_FUNC(display_mappings)},
      {'d', "describe",      OPT_BOOL(describe_mapping)},
      {'\0', NULL,           OPT_FUNC(0)               },
   };
   const char help[] =
      #include "skt_translit.ih"
   ;
   
   parse_options(options, help, &argc, &argv);
   
   skt_translit func = skt_translit_func(input_scheme, output_scheme);
   if (!func)
      die("no mapping for '%s' -> '%s'", input_scheme, output_scheme);

   if (describe_mapping) {
      fputs(skt_map_description(input_scheme, output_scheme), stdout);
   } else if (argc) {
      translit_argv(func, argv);
   } else {
      translit_stdin(func);
   }
}
