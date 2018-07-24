#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#include "constant.h"

void remove_spaces(char *restrict str_trimmed, const char *restrict str_untrimmed);
ssize_t read_line(int sockd, void *vptr, size_t maxlen);
ssize_t write_line(int sockd, const void *vptr, size_t n);

void my_lock_init(char *pathname);
void my_lock_wait();
void my_lock_release();
