#include "server.h"

static size_t nChildren;
static uint16_t servPort;
static pid_t *pids;

//TODO: segnali + gestisci chiusura server


/**
 * This is the main  function of Server; here we inizialize the connection,
 * finding the socket descriptor to pass to other functions that work.
 *
 * @Param (cmd line): argv[1] == port number
 *                    argv[2] == number of child processes
 * @Return: EXIT_FAILURE or EXIT_SUCCESS
 */
int main(int argc, char *argv[]) {
    int listensd, i;
    struct sockaddr_in servaddr;
    socklen_t addrLen;

    // Check and set values for the Server installation
    if (argc == 1) {
        servPort = SERV_PORT;
        nChildren = NUMBER_CHILD;
    } else if (argc == 2) {
        if ((servPort = (uint16_t) atoi(argv[1])) <= 0) {
            fprintf(stderr, "Error on assign port number\n"
                            "Instruction: ./server <port_number> <number_child>\n");
            exit(EXIT_FAILURE);
        }
        nChildren = NUMBER_CHILD;
    } else if (argc == 3) {
        if ((servPort = (uint16_t) atoi(argv[1])) <= 0) {
            fprintf(stderr, "Error on assign port number\n"
                            "Instruction: ./server <port_number> <number_child>\n");
            exit(EXIT_FAILURE);
        }
        if ((nChildren = (size_t) atoi(argv[2])) <= 0) {
            fprintf(stderr, "Error on assign number of child\n"
                            "Instruction: ./server <port_number> <number_child>\n");
            exit(EXIT_FAILURE);
        }
        if (nChildren >= 10) {
            fprintf(stderr, "Error: maximum number of children is 10\n"
                            "Instruction: ./server <port_number> <number_child>\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Error on running server\nInstruction: ./server <port_number> <number_child>\n");
        exit(EXIT_FAILURE);
    }

    // Put the server listening to request
    if ((listensd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error in socket\n");
        exit(EXIT_FAILURE);
    }

    int tr=1;
    // kill "Address already in use" error message
    if (setsockopt(listensd, SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int)) == -1)
    {
        perror("Error in setsockoption\n");
        exit(EXIT_FAILURE);
    }

    memset((void *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(servPort);
    addrLen = sizeof(servaddr);

    // Assign an IP address
    if ((bind(listensd, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0)
    {
        perror("Error in bind\n");
        exit(EXIT_FAILURE);
    }

    // Keep server listening to request
    if (listen(listensd, BACKLOG) < 0 )
    {
        perror("Error in listen\n");
        exit(EXIT_FAILURE);
    }

    // Allocation and creation of children processes
    pids = (pid_t *)calloc(nChildren, sizeof(pid_t));
    if (pids == NULL)
    {
        fprintf(stderr, "Error in calloc\n");
        exit(EXIT_FAILURE);
    }

    for (i=0; i < nChildren; i++)
    {
        pids[i] = child_make(i, listensd, addrLen);
    }

    //When SIGINT arrives (pressing of Ctrl-C) parents and children ends
/*    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        fprintf(stderr, "Error in signal\n");
        exit(1);
    }
*/
    for (;;)
        pause();

}
