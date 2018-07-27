#include "server.h"

#define splitter "\n"

/**
 * This function implements the only and full work of a child in the server
 * @param sockfd
 */
void child_work(int sockfd, struct sockaddr *cliaddr)
{
#ifdef DB
    create_db();
#endif
    struct sockaddr_in *client = (struct sockaddr_in *)cliaddr;
    char message[DIM_LONG], restore[DIM_LONG];
    char *proto, *method;

    user_login *login = malloc(sizeof(user_login));
    user_permissions *permissions = malloc(sizeof(user_permissions));
    record_db *data = malloc(sizeof(record_db));
    researcher *research = malloc(sizeof(researcher));

    secure_read(sockfd, message, DIM_LONG);

    strcpy(restore, message);
    proto = strtok(restore, splitter);
    method = strtok(NULL, splitter);


    // Receive request for login in the socket
    if(strcmp(method, "Request-method: LOGIN") == 0)
    {
    again:
        if(parse_user_login(message, login) == FAILURE)
        {
            fprintf(stderr, "Error\n");
            exit(EXIT_FAILURE);
        }

        if(check_login(login, permissions, sockfd) == SUCCESS)
        {
            free(login);
            free(permissions);
            printf("Client: %s --->  ", inet_ntoa(client->sin_addr));
            printf("Successful login\n\n");
            memset(message, 0, DIM_LONG);
            secure_read(sockfd, message, DIM_LONG);

            strcpy(restore, message);
            proto = strtok(restore, splitter);
            method = strtok(NULL, splitter);

            // Receive request for insert in the socket
            if(strcmp(method, "Request-method: ADD") == 0)
            {
                free(research);
                printf("Client: %s --->  ", inet_ntoa(client->sin_addr));
                printf("Insert requested ... ");
                if(parse_add(message, data) == FAILURE)
                {
                    fprintf(stderr, "Error\n");
                    exit(EXIT_FAILURE);
                }

                add_record(data, sockfd);
                printf("Successful insert\n\n");
                free(data);
                exit(EXIT_SUCCESS);
            }

            // Receive request for search in the socket
            else if(strcmp(method, "Request-method: SEARCH") == 0)
            {
                free(data);
                printf("Client: %s --->  ", inet_ntoa(client->sin_addr));
                printf("Research requested ... ");
                if(parse_search(message, research) == FAILURE)
                {
                    fprintf(stderr, "Error\n");
                    exit(EXIT_FAILURE);
                }

                search_records(research->column, research->user_search, sockfd);
                printf("Successful research\n\n");
                free(research);
                exit(EXIT_SUCCESS);

            } else {
                fprintf(stderr, "Client: %s --->  303 BAD REQUEST", inet_ntoa(client->sin_addr));
                exit(EXIT_FAILURE);
            }

        } else {
            free(research);
            free(data);
            printf("Client: %s --->  ", inet_ntoa(client->sin_addr));
            printf("Unsuccessful login\n\n");
            memset(message, 0, DIM_LONG);
            secure_read(sockfd, message, DIM_LONG);

            strcpy(restore, message);
            proto = strtok(restore, splitter);
            method = strtok(NULL, splitter);

            // Receive request for registration of a new user
            if(strcmp(method, "Request-method: REGISTER") == 0)
            {
                printf("Client: %s --->  ", inet_ntoa(client->sin_addr));
                printf("Registration requested\n");
                if(parse_user_register(message, login, permissions) == FAILURE)
                {
                    fprintf(stderr, "Error\n");
                    exit(EXIT_FAILURE);
                }

                register_user(login, permissions, sockfd);
                printf("Successful registration\n\n");
                free(login);
                free(permissions);
                exit(EXIT_SUCCESS);
            }
            else if(strcmp(method, "Request-method: LOGIN") == 0)
                goto again;
            else
            {
                fprintf(stderr, "Client: %s --->  303 BAD REQUEST", inet_ntoa(client->sin_addr));
                exit(EXIT_FAILURE);
            }
        }
    }
}