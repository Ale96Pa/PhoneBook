#include "service.h"

/**
 * This function is used to start the client and explain the main
 * instruction
 * @param login: struct used to do the login
 */
void welcome(user_login *login)
{
    char response[DIM_SKINNY];  // User response

    printf("%s ", INSTRUCTION);
    fgets(response, DIM_SHORT, stdin);
    response[strcspn(response, "\n")] = 0;
    // This instruction deletes the "\n" captured with fgets

    int compare_lower = strcmp(response, "y");
    int compare_upper = strcmp(response, "Y");
    if (compare_lower == 0 || compare_upper == 0)
    {
        start_login(login);
        send_credentials(login, NULL, "LOGIN");
    } else {
        printf("LOGOUT: see you soon!\n");
        exit(EXIT_SUCCESS);
    }
}

/**
 * This function sends the credentials of login or registration
 * (depending on instruction) to the server
 * @param user: struct with user credential
 * @param permissions: struct with user permissions
 * @param method: LOGIN or REGISTER
 */
int send_credentials(user_login *user, user_permissions *permissions, char *method)
{
    char message[DIM_LONG];                                 // Message to sent
    char value_insert[DIM_SHORT], value_search[DIM_SHORT];  // Values of permissions
    int isLogin = strcmp(method, "LOGIN");
    int isRegister = strcmp(method, "REGISTER");
    memset(message, 0, DIM_LONG);

    if(isLogin == 0)
    {
        strcat(message, PROT_USR);
        strcat(message, "\n");
        strcat(message, PROT_USR_LOGIN);
        strcat(message, "\n");
        strcat(message, "Username: ");
        strcat(message, user->username);
        strcat(message, "\n");
        strcat(message, "Password: ");
        strcat(message, user->password);
        strcat(message, "\n");
    }
    else if (isRegister == 0)
    {
        strcat(message, PROT_USR);
        strcat(message, "\n");
        strcat(message, PROT_USR_REGISTER);
        strcat(message, "\n");
        strcat(message, "Username: ");
        strcat(message, user->username);
        strcat(message, "\n");
        strcat(message, "Password: ");
        strcat(message, user->password);
        strcat(message, "\n");
        strcat(message, "Email: ");
        strcat(message, user->email);
        strcat(message, "\n");
        strcat(message, "Insert: ");
        sprintf(value_insert, "%d", permissions->can_insert);
        strcat(message, value_insert);
        strcat(message, "\n");
        strcat(message, "Search: ");
        sprintf(value_search, "%d", permissions->can_search);
        strcat(message, value_search);
        strcat(message, "\n");
    }
    else
    {
        fprintf(stderr, "Error in send_credential: 303 BAD REQUEST\n");
        return FAILURE;
    }

    //TODO: invia al server
    printf("\n%s\n", message);

    return SUCCESS;
}

/**
 * This function controls the registration of a user and it interfaces
 * itself with user
 * @param user: struct in which save credentials
 * @param permissions: struct in which save permissions
 */
void register_user(user_login *user, user_permissions *permissions)
{
    char response_search[DIM_SKINNY];       // Permission to search
    char response_insert[DIM_SKINNY];       // Permission to insert
    memset(user->username, 0, DIM_SHORT);
    memset(user->password, 0, DIM_SHORT);
    memset(user->email, 0, DIM_MEDIUM);

    printf("*** REGISTRATION: insert your data ***\n");
    printf("Insert username: ");
    fgets(user->username, DIM_SHORT, stdin);
    user->username[strcspn(user->username, "\n")] = 0;
    // This instruction deletes the "\n" captured with fgets

    printf("Insert password: ");
    fgets(user->password, DIM_SHORT, stdin);
    user->password[strcspn(user->password, "\n")] = 0;

    printf("Insert email: ");
    fgets(user->email, DIM_MEDIUM, stdin);
    user->email[strcspn(user->email, "\n")] = 0;

    printf("Allow research? (y/n)  ");
    fgets(response_search, DIM_SHORT, stdin);
    response_search[strcspn(response_search, "\n")] = 0;

    int compare_lower_search = strcmp(response_search, "y");
    int compare_upper_search = strcmp(response_search, "Y");
    if (compare_lower_search == 0 || compare_upper_search == 0) {
        permissions->can_search = 0;
    } else {
        permissions->can_search = -1;
    }

    printf("Allow inserting data? (y/n)  ");
    fgets(response_insert, DIM_SHORT, stdin);
    response_insert[strcspn(response_insert, "\n")] = 0;

    int compare_lower_insert = strcmp(response_insert, "y");
    int compare_upper_insert = strcmp(response_insert, "Y");
    if (compare_lower_insert == 0 || compare_upper_insert == 0) {
        permissions->can_insert = 0;
    } else {
        permissions->can_insert = -1;
    }

    if(send_credentials(user, permissions, "REGISTER") == -1)
        fprintf(stderr, "Error in register_user: DATA NOT SENT\n");
}

/**
 * This function controls the case when a user in not logged after a login
 * @param login: struct in which save credentials
 * @param permissions: struct in which save permissions
 */
void not_logged(user_login *login, user_permissions *permissions)
{
    char response[DIM_SKINNY];      // Response of user

    printf("%s  ", NOT_LOGGED);
    fgets(response, DIM_SHORT, stdin);
    response[strcspn(response, "\n")] = 0;

    int compare_lower = strcmp(response, "y");
    int compare_upper = strcmp(response, "Y");
    if (compare_lower == 0 || compare_upper == 0)
        register_user(login, permissions);
    else
        welcome(login);
}

/**
 * This function asks to the user the data to insert in the phone-book
 * and sends the message to the server
 * @param contact: struct in which save data to send to the server
 */
void insert_contact(record_db *contact)
{
    char message[DIM_LONG];         // Message to send to the server

    printf("*** INSERT a new contact writing the field one by one ***\n");

    printf("Name:  ");
    fgets(contact->name, sizeof(contact->name), stdin);
    contact->name[strcspn(contact->name, "\n")] = 0;
    if(contact->name == NULL)
        strcpy(contact->name, "");

    printf("Lastname:  ");
    fgets(contact->lastname, sizeof(contact->lastname), stdin);
    contact->lastname[strcspn(contact->lastname, "\n")] = 0;

    printf("Phone number:  ");
    fgets(contact->number, DIM_SHORT, stdin);
    contact->number[strcspn(contact->number, "\n")] = 0;
    if(contact->number == NULL)
        strcpy(contact->number, "");

    printf("Number type (mobile or landline):  ");
    fgets(contact->type, DIM_SHORT, stdin);
    contact->type[strcspn(contact->type, "\n")] = 0;

    printf("City:  ");
    fgets(contact->city, DIM_MEDIUM, stdin);
    contact->city[strcspn(contact->city, "\n")] = 0;

    memset(message, 0, DIM_LONG);
    strcat(message, PROT_OPER);
    strcat(message, "\n");
    strcat(message, PROT_OPER_ADD);
    strcat(message, "\n");
    strcat(message, "Name: ");
    strcat(message, contact->name);
    strcat(message, "\n");
    strcat(message, "Lastname: ");
    strcat(message, contact->lastname);
    strcat(message, "\n");
    strcat(message, "Number: ");
    remove_spaces(contact->number, contact->number);
    strcat(message, contact->number);
    strcat(message, "\n");
    strcat(message, "Type: ");
    strcat(message, contact->type);
    strcat(message, "\n");
    strcat(message, "City: ");
    strcat(message, contact->city);
    strcat(message, "\n");

    //todo: invia al server
    printf("\n%s\n", message);
}

/**
 * This functions asks the user the element for the research and
 * sends the message to the server
 * @param search: struct that represents user research
 */
void search_contact(research *search)
{
    char response[DIM_SKINNY];      // User response
    char research[DIM_MEDIUM];      // User research
    int type_search;                // Field to search
    char *endptr;                   // Pointer for strtol functions
    char message[DIM_LONG];         // Message to sent to server

retry:
    printf("Based on what you want to research?\n"
           "Name (1), Lastname (2), Phone number (3), Number type (4), City (5)\nExit (0)\n");
    fgets(response, 10, stdin);
    type_search = strtol(response, &endptr, 0);

    switch (type_search) {
        case 0:
            printf("LOGOUT: see you soon!\n");
            exit(SUCCESS);
        case 1:
            printf("Insert NAME:  ");
            fgets(research, DIM_MEDIUM, stdin);
            sprintf(search->field, "%s", "Name");
            break;
        case 2:
            printf("Insert LASTNAME:  ");
            fgets(research, DIM_MEDIUM, stdin);
            sprintf(search->field, "%s", "Lastname");
            break;
        case 3:
            printf("Insert PHONE NUMBER:  ");
            fgets(research, DIM_MEDIUM, stdin);
            sprintf(search->field, "%s", "Number");
            break;
        case 4:
            printf("Insert NUMBER TYPE:  ");
            fgets(research, DIM_MEDIUM, stdin);
            sprintf(search->field, "%s", "Type");
            break;
        case 5:
            printf("Insert CITY:  ");
            fgets(research, DIM_MEDIUM, stdin);
            sprintf(search->field, "%s", "City");
            break;
        default:
            printf("INVALID INSERT!!\nYour insert is not a valid option, insert a number from 0 to 5\n\n");
            goto retry;
    }

    research[strcspn(research, "\n")] = 0;
    sprintf(search->content, "%s", research);

    memset(message, 0, DIM_LONG);
    strcat(message, PROT_OPER);
    strcat(message, "\n");
    strcat(message, PROT_OPER_SEARCH);
    strcat(message, "\n");
    strcat(message, "Field: ");
    strcat(message, search->field);
    strcat(message, "\n");
    strcat(message, "Content-search: ");
    strcat(message, research);
    strcat(message, "\n");

    //todo: invia al server
    printf("\n%s\n", message);
}

/**
 * This funtion asks the user what does he want to do, based
 * on his permissions
 * @param permissions: user permissions
 */
void action_from_permission(user_permissions *permissions)
{
    char response[DIM_SKINNY];                          // User response
    record_db *contact = malloc(sizeof(record_db));     // Struct used for insert
    research *search = malloc(sizeof(research));        // Struct used for search

    // User has ALL permissions
    if(permissions->can_search != -1 && permissions->can_insert != -1)
    {
        printf(PERMISSION_ALL);
        fgets(response, DIM_SHORT, stdin);
        response[strcspn(response, "\n")] = 0;
        // This instruction deletes the "\n" captured with fgets

        if(strcmp(response, "1") == 0)
            insert_contact(contact);
        else if (strcmp(response, "2") == 0)
            search_contact(search);
        else {
            printf("LOGOUT: see you soon!\n");
            free(contact);
            free(search);
            exit(SUCCESS);
        }
    }

    // User can only INSERT
    if(permissions->can_insert != -1 && permissions->can_search == -1)
    {
        printf(PERMISSION_ADD);
        fgets(response, DIM_SHORT, stdin);
        response[strcspn(response, "\n")] = 0;

        int compare_lower_insert = strcmp(response, "y");
        int compare_upper_insert = strcmp(response, "Y");
        if (compare_lower_insert == 0 || compare_upper_insert == 0)
            insert_contact(contact);
        else {
            printf("LOGOUT: see you soon!\n");
            free(contact);
            free(search);
            exit(SUCCESS);
        }
    }

    // User can only SEARCH
    if(permissions->can_insert == -1 && permissions->can_search != -1)
    {
        printf(PERMISSION_SEARCH);
        fgets(response, DIM_SHORT, stdin);
        response[strcspn(response, "\n")] = 0;

        int compare_lower_search = strcmp(response, "y");
        int compare_upper_search = strcmp(response, "Y");
        if (compare_lower_search == 0 || compare_upper_search == 0)
            search_contact(search);
        else {
            printf("LOGOUT: see you soon!\n");
            free(contact);
            free(search);
            exit(SUCCESS);
        }
    }
}