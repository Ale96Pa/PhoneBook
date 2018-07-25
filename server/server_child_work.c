#include "server.h"

#define splitter "\n"

/**
 * This function implements the only and full work of a child in the server
 * @param sockfd
 */
void child_work(int sockfd)
{
    char message[DIM_LONG], restore[DIM_LONG];
    char *proto, *method;
    user_login *login = malloc(sizeof(user_login));
    user_permissions *permissions = malloc(sizeof(user_permissions));
    record_db *data = malloc(sizeof(record_db));
    researcher *research = malloc(sizeof(researcher));

    for(;;)
    {
        secure_read(sockfd, message, DIM_LONG);
        strcpy(restore, message);

        proto = strtok(restore, splitter);
        method = strtok(NULL, splitter);

        // Receive request for login in the socket
        if(strcmp(method, "Request-method: LOGIN") == 0)
        {
            free(research);
            free(data);
            if(parse_user_login(message, login) == FAILURE)
            {
                fprintf(stderr, "Error\n");
                exit(EXIT_FAILURE);
            }
            check_login(login, permissions, sockfd);
            exit(EXIT_SUCCESS);
        }
        // Receive request for login in the socket
        else if(strcmp(method, "Request-method: REGISTER") == 0)
        {
            free(research);
            free(data);
            if(parse_user_register(message, login, permissions) == FAILURE)
            {
                fprintf(stderr, "Error\n");
                exit(EXIT_FAILURE);
            }
            register_user(login, permissions, sockfd);
            exit(EXIT_SUCCESS);
        }
        // Receive request for login in the socket
        else if(strcmp(method, "Request-method: ADD") == 0)
        {
            free(login);
            free(permissions);
            free(research);
            if(parse_add(message, data) == FAILURE)
            {
                fprintf(stderr, "Error\n");
                exit(EXIT_FAILURE);
            }
            add_record(data, sockfd);
            exit(EXIT_SUCCESS);
        }
        // Receive request for login in the socket
        else if(strcmp(method, "Request-method: SEARCH") == 0)
        {
            free(login);
            free(permissions);
            free(data);
            if(parse_search(message, research) == FAILURE)
            {
                fprintf(stderr, "Error\n");
                exit(EXIT_FAILURE);
            }
            search_records(research->column, research->user_search, sockfd);
            exit(EXIT_SUCCESS);
        } else {
            fprintf(stderr, "303 BAD REQUEST\n");
            exit(EXIT_FAILURE);
        }
    }
}