#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "constant.h"

void remove_spaces(char* restrict str_trimmed, const char* restrict str_untrimmed);
ssize_t read_line(int sockd, void *vptr, size_t maxlen);
ssize_t write_line(int sockd, const void *vptr, size_t n);
ssize_t secure_read();
ssize_t secure_write();
