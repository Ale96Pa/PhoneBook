#include "basic.h"
#include "parsing/parsing.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUMBER_CHILD 7
#define SERV_PORT 5193
#define BACKLOG 10

pid_t child_make(int i, int listensd, int addrlen);
void child_main(int listensd, int addrlen);
void child_work(int connsd);