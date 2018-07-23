#include "service.h"

//TODO: TUTTI CONTROLLI DEGLI ERRORI

/**
 *
 * @param login
 */
void welcome(user_login *login)
{
    char response[10];
    printf("%s  ", INSTRUCTION);
    fgets(response, DIM_SHORT, stdin);
    response[strcspn(response, "\n")] = 0;

    int compare_lower = strcmp(response, "y");
    int compare_upper = strcmp(response, "Y");
    if (compare_lower == 0 || compare_upper == 0) {
        printf("\n");
    } else {
        printf("logout\n");
        exit(0);
    }

    start_login(login);
    send_credentials(login, NULL, "LOGIN");

}

/**
 *
 * @param user
 */
void send_credentials(user_login *user, user_permissions *permissions, char *method)
{
    int isLogin = strcmp(method, "LOGIN");
    int isRegister = strcmp(method, "REGISTER");
    char message[DIM_LONG], value_insert[DIM_SHORT], value_search[DIM_SHORT];
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
        printf("ERROR\n");
        //ERROR
    }
    //TODO: invia al server

    printf("\n%s\n", message);
}

/**
 *
 */
void register_user(user_login *user, user_permissions *permissions)
{
    char response_search[10];
    char response_insert[10];
    memset(user->username, 0, DIM_SHORT);
    memset(user->password, 0, DIM_SHORT);
    memset(user->email, 0, DIM_MEDIUM);

    printf("\nREGISTRATION: insert your data\n");
    printf("Insert username: ");
    fgets(user->username, DIM_SHORT, stdin);
    user->username[strcspn(user->username, "\n")] = 0;

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

    send_credentials(user, permissions, "REGISTER");
}

/**
 * Function in case the user is not logged for bad credentials or because he isn't registered
 */
void not_logged(user_login *login, user_permissions *permissions)
{
    char response[10];
    printf("%s  ", NOT_LOGGED);

    fgets(response, DIM_SHORT, stdin);
    response[strcspn(response, "\n")] = 0;

    int compare_lower = strcmp(response, "y");
    int compare_upper = strcmp(response, "Y");
    if (compare_lower == 0 || compare_upper == 0) {
        register_user(login, permissions);
    } else {
        welcome(login);
    }
}

/**
 * Function used to send to the server the record to add
 */
void insert_contact(record_db *contact)
{
    char message[DIM_LONG];
    char real_number[DIM_SHORT];

    printf("INSERT a new contact writing the field one by one\n");

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
    remove_spaces(real_number, contact->number);
    strcat(message, real_number);
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
 * Function used to send to the server the element to do a search
 */
void search_contact(research *search)
{
    char response[10];
    char research[DIM_MEDIUM];
    int type_search;
    char *endptr;
    char message[DIM_LONG];

retry:
    printf("Based on what you want to research?\n"
           "Name (1), Lastname (2), Phone number (3), Number type (4), City (5)\nExit (0)\n");
    fgets(response, 10, stdin);
    type_search = strtol(response, &endptr, 0);

    switch (type_search) {
        case 0:
            printf("LOGOUT\n");
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
            sprintf(search->field, "%s", "Phone number");
            break;
        case 4:
            printf("Insert NUMBER TYPE:  ");
            fgets(research, DIM_MEDIUM, stdin);
            sprintf(search->field, "%s", "Number type");
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
    //TODO: funzione che visualizza risultato
    printf("\n%s\n", message);
}


/**
 * Basing on permission, this function start the possible actions
 * @param user
 * @param permissions
 */
void action_from_permission(user_permissions *permissions)
{
    char response[10];
    record_db *contact = malloc(sizeof(record_db));
    research *search = malloc(sizeof(research));

    //todo: PARSA STRINGA DEL SERVER PER VEDERE PERMISSIONS

    if(permissions->can_search != -1 && permissions->can_insert != -1)
    {
        printf(PERMISSION_ALL);
        fgets(response, DIM_SHORT, stdin);
        response[strcspn(response, "\n")] = 0;

        if(strcmp(response, "1") == 0)
        {
            insert_contact(contact);
        }
        else if (strcmp(response, "2") == 0)
        {
            search_contact(search);
        } else {
            printf("LOGOUT\n");
            exit(SUCCESS);
        }
    }
    if(permissions->can_insert != -1 && permissions->can_search == -1)
    {
        printf(PERMISSION_ADD);
        fgets(response, DIM_SHORT, stdin);
        response[strcspn(response, "\n")] = 0;
        int compare_lower_insert = strcmp(response, "y");
        int compare_upper_insert = strcmp(response, "Y");
        if (compare_lower_insert == 0 || compare_upper_insert == 0) {
            insert_contact(contact);
        } else {
            printf("LOGOUT\n");
            exit(SUCCESS);
        }
    }
    if(permissions->can_insert == -1 && permissions->can_search != -1)
    {
        printf(PERMISSION_SEARCH);
        fgets(response, DIM_SHORT, stdin);
        response[strcspn(response, "\n")] = 0;
        int compare_lower_search = strcmp(response, "y");
        int compare_upper_search = strcmp(response, "Y");
        if (compare_lower_search == 0 || compare_upper_search == 0) {
            search_contact(search);
        } else {
            printf("LOGOUT\n");
            exit(SUCCESS);
        }
    }

    //todo: fare le free
}

//TODO: fare funzione che visualizza risultato in base al protocollo