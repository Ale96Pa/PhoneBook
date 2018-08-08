#include "client.h"

#define splitter "\n"

int conn_s; // Connection socket

/**
 * This function is used to capture different signals
 * @param signal
 * @param conn_s
 */
void signal_handler(int signal) {

    switch (signal) {

        case SIGHUP:
            printf(RED "\nSignal SIGHUP received: terminal closing!\n\n" RESET);
            if ( close(conn_s) < 0 )
                fprintf(stderr, "Error in close\n");
            exit(EXIT_FAILURE);

        case SIGINT:
            printf(RED "\nYou forced quit with signal SIGINT!\n\n" RESET);
            if ( close(conn_s) < 0 )
                fprintf(stderr, "Error in close\n");
            exit(EXIT_FAILURE);

        case SIGQUIT:
            printf(RED "\nYou forced quit with signal SIGQUIT!\n\n" RESET);
            if ( close(conn_s) < 0 )
                fprintf(stderr, "Error in close\n");
            exit(EXIT_FAILURE);

        case SIGILL:
            printf(RED "\nSignal SIGILL received: Illegal instruction!\n\n" RESET);
            if ( close(conn_s) < 0 )
                fprintf(stderr, "Error in close\n");
            exit(EXIT_FAILURE);

        case SIGSEGV:
            printf(RED "\nSignal SIGSEGV received: Server has crashed!\n\n" RESET);
            if ( close(conn_s) < 0 )
                fprintf(stderr, "Error in close\n");
            exit(EXIT_FAILURE);

        case SIGTERM:
            printf(RED "\nSignal SIGTERM received!\n\n" RESET);
            if ( close(conn_s) < 0 )
                fprintf(stderr, "Error in close\n");
            exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    short int port;                  // Port number
    struct    sockaddr_in servaddr;  // Socket address structure
    char      buffer[DIM_LONG];      // Character buffer
    char     *server_address;        // Holds remote IP address
    char     *server_port;           // Holds remote port
    char     *endptr;                // Pointer for strtol function
    struct	  hostent *he;
    char method[DIM_SHORT];
    he=NULL;

    user_login *login = malloc(sizeof(user_login));
    user_permissions *permissions = malloc(sizeof(user_permissions));

    if(argc != 3)
    {
        fprintf(stderr, "Configuration error.\nUsage: ./client <ip_address_server> <port_number_server>\n");
        exit(EXIT_FAILURE);
    }
    server_address = argv[1];
    server_port = argv[2];

    //  Set the remote port
    port = strtol(server_port, &endptr, 0);
    if ( *endptr )
    {
        fprintf(stderr, "Client: port not recognized\n");
        exit(EXIT_FAILURE);
    }

    //  Create the listening socket
    if ((conn_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        fprintf(stderr, "Client: error in creation socket\n");
        exit(EXIT_FAILURE);
    }

    /*  Set all bytes in socket address structure to
        zero, and fill in the relevant data members   */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    //  Set the remote IP address
    if ( inet_aton(server_address, &servaddr.sin_addr) <= 0 )
    {
        printf("Client: Invalid IP address\nClient: resolution name...");

        if ((he = gethostbyname(server_address)) == NULL)
        {
            printf(" failed\n");
            exit(EXIT_FAILURE);
        }
        printf(" ok\n\n");
        servaddr.sin_addr = *((struct in_addr *)he->h_addr);
    }

    //  Connect to the remote echo server
    if (connect(conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr) ) < 0 )
    {
        fprintf(stderr, "Client: error in connect()\n");
        exit(EXIT_FAILURE);
    }

    // Signals management
    signal(SIGHUP, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGILL, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGTERM, signal_handler);


    // Start client work
retry:
    memset(buffer, 0, DIM_LONG);
    welcome(login, conn_s);

    // Read response from server
    secure_read(conn_s, buffer, DIM_LONG);

    if (parse_login_response(buffer, permissions) == -1)
    {
        memset(buffer, 0, DIM_LONG);
        if (not_logged(login, permissions, conn_s) == 0)
        {
            secure_read(conn_s, buffer, DIM_LONG);

            int value = parse_register_response(buffer);
            if (value != -1)
            {
                printf(GREEN "\nSuccessful registration!\n" RESET);
                exit(EXIT_SUCCESS);
            } else {
                fprintf(stderr, "\nNOT successful registration, try again!\nMaybe you don't insert any permissions\n");
                exit(EXIT_FAILURE);
            }
        } else {
            goto retry;
        }
    }

    memset(buffer, 0, DIM_LONG);
    int value = action_from_permission(permissions, conn_s);
    if (value == 1)
    {
        secure_read(conn_s, buffer, DIM_LONG);

        if (parse_add_response(buffer) == SUCCESS) {
            printf(GREEN "\nElement added successfully!\n" RESET);
            exit(EXIT_SUCCESS);
        } else {
            fprintf(stderr, "\nElement NOT added!\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (value == 2)
    {
        secure_read(conn_s, buffer, DIM_LONG);

        if (parse_search_response(buffer) == FAILURE)
        {
            fprintf(stderr, "\nError: element not found\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "303 BAD REQUEST\n");
        exit(EXIT_FAILURE);
    }
}
