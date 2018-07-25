#include "client.h"

#define splitter "\n"
/*
int main()
{

    */
/*
    welcome(login);
    int camp = strcmp(login->username, "ale");

    if(camp == 0){
        not_logged(login, permissions);
    }
*/
/*
    permissions->can_insert = 0;
    permissions->can_search = 0;
    action_from_permission(permissions);
*/
/*
    char message[DIM_LONG], restore[DIM_LONG];
    char *proto, *method;
    strcpy(message, "Operation Protocol\n"
                    "Response-method: SEARCH\n"
                    "Number-record: 2\n"
                    "\n"
                    "Name: Alessandro\n"
                    "Lastname: Palma\n"
                    "Number: 328 9874589\n"
                    "Number-type: mobile\n"
                    "City: Abruzzo\n"
                    "\n"
                    "Name: Ornella\n"
                    "Lastname: Vanoni\n"
                    "Number: 3287458962\n"
                    "Number-type: \n"
                    "City: Roma");

    strcpy(restore, message);

    proto = strtok(restore, splitter);
    method = strtok(NULL, splitter);

    for(;;)
    {
        if(strcmp(method, "Response-method: LOGIN") == 0)
        {
            parse_login_response(message, permissions);
            printf("%d\n%d\n", permissions->can_insert, permissions->can_search);
            //break;
        }
        else if(strcmp(method, "Response-method: REGISTER") == 0)
        {
            int res = parse_register_response(message);
            printf("%d\n", res);
            //break;
        }
        else if(strcmp(method, "Response-method: ADD") == 0)
        {
            int res2 = parse_add_response(message);
            printf("%d\n", res2);
            //break;
        }
        else if(strcmp(method, "Response-method: SEARCH") == 0)
        {
            parse_search_response(message);
            //break;
        }

        //TODO: fare le free
    }
}
*/
int main(int argc, char **argv)
{
    int       conn_s;                // Connection socket
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
/*
    //  Connect to the remote echo server
    if (connect(conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr) ) < 0 )
    {
        fprintf(stderr, "Client: error in connect()\n");
        exit(EXIT_FAILURE);
    }
*/
    // Start client work
    conn_s = 0;
retry:
    welcome(login, conn_s);

    // Read response from server
    //secure_read(conn_s, buffer, DIM_LONG);
    strcpy(buffer, "User Protocol\n"
                   "Response-method: LOGIN\n"
                   "Response: 200 OK\n"
                   "Permission-inset: 0\n"
                   "Permission-search: 0");
    if(parse_login_response(buffer, permissions) == -1)
    {
        if(not_logged(login, permissions, conn_s) == 0)
        {
            //secure_read(conn_s, buffer, DIM_LONG);
            strcpy(buffer, "User Protocol\n"
                           "Response-method: REGISTER\n"
                           "Response: 200 OK");
            int value = parse_register_response(buffer);
            if(value != -1)
            {
                printf("\nSuccessful registration!\n");
                exit(EXIT_SUCCESS);
            } else {
                fprintf(stderr, "\nNOT successful registration, try again\n");
                exit(EXIT_FAILURE);
            }
        } else {
            goto retry;
        }
    }

    int value = action_from_permission(permissions, conn_s);
    if(value == 1)
    {
        strcpy(buffer, "Operation Protocol\n"
                       "Response-method: ADD\n"
                       "Response: 200 OK");
        //secure_read(conn_s, buffer, DIM_LONG);
        if(parse_add_response(buffer) == SUCCESS)
        {
            printf("\nElement added successfully!\n");
            exit(EXIT_SUCCESS);
        } else {
            fprintf(stderr, "\nElement NOT added!\n");
            exit(EXIT_FAILURE);
        }
    }
    else if(value == 2)
    {
        strcpy(buffer, "Operation Protocol\n"
                       "Response-method: SEARCH\n"
                       "Number-record: 2\n\n"
                       "Name: aa\n"
                       "Lastname: aa\n"
                       "Number: aa\n"
                       "Number-type: aa\n"
                       "City: aa\n\n"
                       "Name: bb\n"
                       "Lastname: bb\n"
                       "Number: bb\n"
                       "Number-type: bb\n"
                       "City: bb\n\n");
        //secure_read(conn_s, buffer, DIM_LONG);
        if(parse_search_response(buffer) == FAILURE)
        {
            fprintf(stderr, "\nError: element not found\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "303 BAD REQUEST\n");
        exit(EXIT_FAILURE);
    }

}
