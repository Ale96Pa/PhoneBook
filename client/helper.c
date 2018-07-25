#include "basic.h"

/**
 * This function is used to remove spaces from a string
 * @param str_trimmed: string cleaned
 * @param str_untrimmed: string to clean
 */
void remove_spaces(char* restrict str_trimmed, const char* restrict str_untrimmed)
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
 * @param fd
 * @param buffer
 * @param size
 */
int secure_read(int fd, char *buffer, unsigned long size)
{
    {
        unsigned long res_r;
        ssize_t effective_read;

        res_r = 0;
        while (size > res_r) {
            effective_read = read(fd, buffer, size - res_r);
            if (effective_read == -1)
            {
                fprintf(stderr, "Error while reading\n");
                exit(EXIT_FAILURE);
            }
            if (effective_read == 0)
                return res_r;
            res_r += effective_read;
            buffer += effective_read;
        }
        return res_r;
    }
}

/**
 *
 * @param fd
 * @param buffer
 * @param size
 */
void secure_write(int fd, char *buffer, unsigned long size)
{
    ssize_t effective_write;

    while (size > 0) {
        effective_write = write(fd, buffer, size);
        if (effective_write == -1)
        {
            fprintf(stderr, "Error while writing\n");
            exit(EXIT_FAILURE);
        }
        size -= effective_write;
        buffer += effective_write;
    }
}


/**
 * This function is used to read a line
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
 * This function is used to write a line
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