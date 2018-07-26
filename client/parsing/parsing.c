#include "parsing.h"

#define splitter_line "\n"

/**
 * This function is used to parse the server response after the login
 * @param message: message from server
 * @param permissions: permission set based on user login
 * @return: 0 for success, -1 for failure
 */
int parse_login_response(char *message, user_permissions *permissions)
{
    char *element;                                  // String used to tokenize
    char *permission_insert, *permission_search;    // String used for permissions
    char *result_code;                              // Code sent by server

    element = strtok(message, splitter_line);
    if(strcmp(element, PROT_USR) != 0)
    {
        fprintf(stderr, "Error in parse_login: BAD PROTOCOL\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if(strcmp(element, "Response-method: LOGIN") != 0)
    {
        fprintf(stderr, "Error in parse_login: BAD METHOD\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    result_code = strstr(element, " ");
    remove_spaces(result_code, result_code);
    if(strcmp(result_code, "200OK") == 0)
    {
        element = strtok(NULL, splitter_line);
        permission_insert = strstr(element, " ");
        remove_spaces(permission_insert, permission_insert);
        if(strcmp(permission_insert, "0") == 0)
            permissions->can_insert = 0;
        else
            permissions->can_insert = -1;

        element = strtok(NULL, splitter_line);
        permission_search = strstr(element, " ");
        remove_spaces(permission_search, permission_search);
        if(strcmp(permission_search, "0") == 0)
            permissions->can_search = 0;
        else
            permissions->can_search = -1;

        return SUCCESS;
    } else {
        printf("NOT FOUND!\n");
        permissions->can_insert = -1;
        permissions->can_search = -1;
        return FAILURE;
    }
}

/**
 * This function is used to parse the server response after the registration of a user
 * @param message: message sent by server
 * @return: 0 for success, -1 for failure
 */
int parse_register_response(char *message)
{
    char *element;      // String used to tokenize
    char *result_code;  // Code sent by server

    element = strtok(message, splitter_line);
    if(strcmp(element, PROT_USR) != 0)
    {
        fprintf(stderr, "Error in parse_register: BAD PROTOCOL\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if(strcmp(element, "Response-method: REGISTER") != 0)
    {
        fprintf(stderr, "Error in parse_register: BAD METHOD\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    result_code = strstr(element, " ");
    remove_spaces(result_code, result_code);
    if(strcmp(result_code, "200OK") == 0)
        return SUCCESS;
    else
        return FAILURE;
}

/**
 * This function is used to parse the server response after the registration of a record
 * @param message: message sent by server
 * @return: 0 for success, -1 for failure
 */
int parse_add_response(char *message)
{
    char *element;      // String used to tokenize
    char *result_code;  // Result code sent by server

    element = strtok(message, splitter_line);
    if(strcmp(element, PROT_OPER) != 0)
    {
        fprintf(stderr, "Error in parse_add: BAD PROTOCOL\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if(strcmp(element, "Response-method: ADD") != 0)
    {
        fprintf(stderr, "Error in parse_add: BAD METHOD\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    result_code = strstr(element, " ");
    remove_spaces(result_code, result_code);
    if(strcmp(result_code, "200OK") == 0)
        return SUCCESS;
    else
        return FAILURE;
}

/**
 * This function is used to parse the server response after the searching of records
 * @param message: message sent by server
 * @return: 0 for success, -1 for failure
 */
int parse_search_response(char *message)
{
    char *element, *num;    // Strings used to tokenize
    char *endptr;           // Pointer for strtol function
    int num_record, i;

    element = strtok(message, splitter_line);
    if(strcmp(element, PROT_OPER) != 0)
    {
        fprintf(stderr, "Error in parse_search: BAD PROTOCOL\n");
        return FAILURE;
    }

    element = strtok(NULL, splitter_line);
    if(strcmp(element, "Response-method: SEARCH") != 0)
    {
        fprintf(stderr, "Error in parse_search: BAD METHOD\n");
        return FAILURE;
    }

    // Find how many records there are
    element = strtok(NULL, splitter_line);
    num = strstr(element, " ");
    remove_spaces(num, num);
    num_record = strtol(num, &endptr, 0);

    record_db data[num_record];        // Array of record_db sent by server

    printf(BLUE "\n\nDATA FOUND\n" RESET);
    printf(BLUE "*************************************\n" RESET);
    for(i=0; i<num_record; i++)
    {
        printf(RED);
        printf("Contact %d\n", i+1 );
        printf(RESET);
        element = strtok(NULL, splitter_line);
        strcpy(data[i].name, strstr(element, " "));
        remove_spaces(data[i].name, data[i].name);
        printf(YELLOW "Name: %s\n", data[i].name);

        element = strtok(NULL, splitter_line);
        strcpy(data[i].lastname, strstr(element, " "));
        remove_spaces(data[i].lastname, data[i].lastname);
        printf("Lastname: %s\n", data[i].lastname);

        element = strtok(NULL, splitter_line);
        strcpy(data[i].number, strstr(element, " "));
        remove_spaces(data[i].number, data[i].number);
        printf("Number: %s\n", data[i].number);

        element = strtok(NULL, splitter_line);
        strcpy(data[i].type, strstr(element, " "));
        remove_spaces(data[i].type, data[i].type);
        printf("Type: %s\n", data[i].type);

        element = strtok(NULL, splitter_line);
        strcpy(data[i].city, strstr(element, " "));
        remove_spaces(data[i].city, data[i].city);
        printf("City: %s\n", data[i].city);
        printf(BLUE "*************************************\n" RESET);
    }

    exit(EXIT_SUCCESS);
}