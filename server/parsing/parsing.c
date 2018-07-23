#include "parsing.h"

#define splitter_line "\n"

int parse_user_login(char *message, user_login *user)
{
    char *element, *username, *password;

    element = strtok(message, splitter_line);
    if(strcmp(element, PROT_USR) != 0)
    {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if(strcmp(element, "Request-method: LOGIN") != 0)
    {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    username = strstr(element, " ");
    remove_spaces(username, username);
    strcpy(user->username, username);

    element = strtok(NULL, splitter_line);
    password = strstr(element, " ");
    remove_spaces(password, password);
    strcpy(user->password, password);

    return SUCCESS;

}

int parse_user_register(char *message, user_login *user, user_permissions *permissions)
{
    char *element;
    char *username, *password, *email, *insert, *search;
    char *endptr;

    element = strtok(message, splitter_line);
    if(strcmp(element, PROT_USR) != 0)
    {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if(strcmp(element, "Request-method: REGISTER") != 0)
    {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    username = strstr(element, " ");
    remove_spaces(username, username);
    strcpy(user->username, username);

    element = strtok(NULL, splitter_line);
    password = strstr(element, " ");
    remove_spaces(password, password);
    strcpy(user->password, password);

    element = strtok(NULL, splitter_line);
    email = strstr(element, " ");
    remove_spaces(email, email);
    strcpy(user->email, email);

    element = strtok(NULL, splitter_line);
    insert = strstr(element, " ");
    remove_spaces(insert, insert);

    int num_insert = strtol(insert, &endptr, 0);
    permissions->can_insert = num_insert;

    element = strtok(NULL, splitter_line);
    search = strstr(element, " ");
    remove_spaces(search, search);
    int num_search = strtol(search, &endptr, 0);
    permissions->can_search = num_search;

    return SUCCESS;
}

int parse_add(char *message, record_db *data) {
    char *element;
    char *name, *lastname, *number, *type, *city;

    element = strtok(message, splitter_line);
    if (strcmp(element, PROT_OPER) != 0) {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if (strcmp(element, "Request-method: ADD") != 0) {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    name = strstr(element, " ");
    remove_spaces(name, name);
    strcpy(data->name, name);

    element = strtok(NULL, splitter_line);
    lastname = strstr(element, " ");
    remove_spaces(lastname, lastname);
    strcpy(data->lastname, lastname);

    element = strtok(NULL, splitter_line);
    number = strstr(element, " ");
    remove_spaces(number, number);
    strcpy(data->number, number);

    element = strtok(NULL, splitter_line);
    type = strstr(element, " ");
    remove_spaces(type, type);
    strcpy(data->type, type);

    element = strtok(NULL, splitter_line);
    city = strstr(element, " ");
    strcpy(data->city, city);
/*
    printf("%s\n", name);
    printf("%s\n", lastname);
    printf("%s\n", number);
    printf("%s\n", type);
    printf("%s\n", city);
*/
    return SUCCESS;
}


int parse_search(char *message, researcher *search)
{
    char *element;
    char *field, *research;

    element = strtok(message, splitter_line);
    if(strcmp(element, PROT_OPER) != 0)
    {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if(strcmp(element, "Request-method: SEARCH") != 0)
    {
        printf("ERRORE\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    field = strstr(element, " ");
    remove_spaces(field, field);
    strcpy(search->column, field);

    element = strtok(NULL, splitter_line);
    research = strstr(element, " ");
    remove_spaces(research, research);
    strcpy(search->user_search, research);

    return SUCCESS;
}