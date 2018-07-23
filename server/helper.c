#include "basic.h"

void remove_spaces(char *restrict str_trimmed, const char *restrict str_untrimmed)
{
    while (*str_untrimmed != '\0')
    {
        if(!isspace(*str_untrimmed))
        {
            *str_trimmed = *str_untrimmed;
            str_trimmed++;
        }
        str_untrimmed++;
    }
    *str_trimmed = '\0';
}

/**
 *
 * @param sockd
 * @param vptr
 * @param maxlen
 * @return
 */
ssize_t read_line(int sockd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    for ( n = 1; n < maxlen; n++ ) {
        rc = read(sockd, &c, 1);
        if ( rc == 1 ) {
            *buffer++ = c;
            if ( c == '\n' ) break;
        }
        else
        if ( rc == 0 ) {
            if ( n == 1 ) return 0;
            else break;
        }
        else {
            if ( errno == EINTR ) continue;
            return -1;
        }
    }
    *buffer = 0;
    return n;
}


/**
 *
 * @param sockd
 * @param vptr
 * @param n
 * @return
 */
ssize_t write_line(int sockd, const void *vptr, size_t n)
{
    size_t      nleft;
    ssize_t     nwritten;
    const char *buffer;

    buffer = vptr;
    nleft  = n;

    while ( nleft > 0 )
    {
        if ( (nwritten = write(sockd, buffer, nleft)) <= 0 )
        {
            if ( errno == EINTR ) nwritten = 0;
            else return -1;
        }
        nleft  -= nwritten;
        buffer += nwritten;
    }
    return n;
}