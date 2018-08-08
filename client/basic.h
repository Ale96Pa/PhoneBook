#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "constant.h"

void remove_spaces(char* str_trimmed, const char* str_untrimmed);
ssize_t read_line(int sockd, void *vptr, size_t maxlen);
ssize_t write_line(int sockd, const void *vptr, size_t n);
void secure_read(int fd, char *buffer, unsigned long size);
void secure_write(int fd, char *buffer, unsigned long size);
