#include "basic.h"
#include "parsing/parsing.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>

#define BACKLOG 10
#define MAX_LINE 256