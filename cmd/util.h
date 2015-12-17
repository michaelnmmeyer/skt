#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

struct skt_buf;

bool read_line(struct skt_buf *, FILE *);

void write_line(const char *);

#endif
