#include "server.h"

#define splitter "\n"

void child_work(int sockfd)
{
    char message[DIM_LONG], restore[DIM_LONG];
    char *proto, *method;
    user_login *login = malloc(sizeof(user_login));
    user_permissions *permissions = malloc(sizeof(user_permissions));
    record_db *data = malloc(sizeof(record_db));
    researcher *research = malloc(sizeof(researcher));

/*
    strcpy(message, "Operation Protocol\n"
                    "Request-method: SEARCH\n"
                    "Field: Number\n"
                    "Content-search: 32");
*/

    for(;;)
    {
        //TODO: PRENDI QUELLO IN sockfd  E METTILO IN message
        strcpy(restore, message);

        proto = strtok(restore, splitter);
        method = strtok(NULL, splitter);

        //Receive message for login in the socket
        if(strcmp(method, "Request-method: LOGIN") == 0)
        {
            parse_user_login(message, login);
            check_login(login, permissions);
            //printf("%s\n%s\n", login->username, login->password);
            //break;
        }
        else if(strcmp(method, "Request-method: REGISTER") == 0)
        {
            parse_user_register(message, login, permissions);
            register_user(login, permissions);
            //printf("%s\n%s\n%s\n%d\n%d\n", login->username,login->password, login->email, permissions->can_insert, permissions->can_search);
            //break;
        }
        else if(strcmp(method, "Request-method: ADD") == 0)
        {
            parse_add(message, data);
            add_record(data);
            //printf("%d\n%s\n%s\n%s\n%s\n%s\n", data->id, data->name, data->lastname, data->number, data->type, data->city);
            //break;

        }
        else if(strcmp(method, "Request-method: SEARCH") == 0)
        {
            parse_search(message, research);
            search_records(research->column, research->user_search);
            //break;
        }

        //TODO: fare le free
    }

}