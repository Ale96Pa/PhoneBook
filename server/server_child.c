#include "server.h"

/**
 * This functions are used to create processes (child_make) and to do their work
 * (child_main); in this way there is a modular organization of Server.
 */
pid_t child_make(int i, int listensd, int addrlen)
{
    pid_t pid;

    if ((pid = fork()) > 0)
    {
        return pid;		// Parent process
    }

    pid = getpid();
    child_main(listensd, addrlen);

    return pid;
}

void child_main(int listensd, int addrlen)
{
    int	connsd;
    socklen_t clilen;
    struct sockaddr *cliaddr;

    if ((cliaddr = (struct sockaddr *)malloc(addrlen)) == NULL)
    {
        fprintf(stderr, "Error in malloc\n");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        clilen = addrlen;
        if ((connsd = accept(listensd, cliaddr, &clilen)) < 0)
        {
            perror("Error in accept");
            exit(EXIT_FAILURE);
        }

        child_work(connsd);   // Function that works

        if (close(connsd) == -1)
        {
            perror("Error in close");
            exit(EXIT_FAILURE);
        }
    }
}