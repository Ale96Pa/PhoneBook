#include <pthread.h>
#include <syslog.h>
#include "../basic.h"

#define LOG_FILE  "/logServer.txt"

void logging(char *host, char *request, char *response);