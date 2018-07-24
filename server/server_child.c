#include "server.h"

/**
 * This functions are used to create processes (child_make) and to do their work
 * (child_main); in this way there is a modular organization of Server.
 */
pid_t child_make(int i, int listensd, int addrlen)
{
    pid_t	pid;
    void	child_main(int, int, int);

    if ( (pid = fork()) > 0)
        return(pid);		/* processo padre */

    child_main(i, listensd, addrlen);	/* non ritorna mai */
}

void child_main(int i, int listensd, int addrlen)
{
    int	connsd;
    void	web_child(int);
    socklen_t clilen;
    struct sockaddr *cliaddr;

    if ( (cliaddr = (struct sockaddr *)malloc(addrlen)) == NULL) {
        fprintf(stderr, "errore in malloc");
        exit(1);
    }

    printf("child %ld starting\n", (long) getpid());
    for ( ; ; ) {
        clilen = addrlen;
        if ( (connsd = accept(listensd, cliaddr, &clilen)) < 0) {
            perror("errore in accept");
            exit(1);
        }
        child_work(connsd);		/* processa la richiesta */
        if (close(connsd) == -1) {
            perror("errore in close");
            exit(1);
        }
    }
}