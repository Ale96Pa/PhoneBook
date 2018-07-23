#include "login_server.h"

/**
 *
 * @param login
 * @param permissions
 */
void check_login(user_login *login, user_permissions *permissions)
{
    char *username = login->username;
    char *password = login->password;
    int id_add, id_search, check_count=0;
    char message[DIM_LONG];
    char permission_insert[DIM_SHORT], permission_search[DIM_SHORT], final_code[DIM_SHORT];

    permissions->can_insert = -1;
    strcpy(permission_insert, "-1");
    permissions->can_search = -1;
    strcpy(permission_search, "-1");

    if((id_add = check_user_adder(username, password)) > 0)
    {
        permissions->can_insert = 0;
        strcpy(permission_insert, "0");
        check_count++;
    }
    if((id_search = check_user_searcher(username, password)) > 0)
    {
        permissions->can_search = 0;
        strcpy(permission_search, "0");
        check_count++;
    }

    if(check_count <= 0)
        strcpy(final_code, "404 NOT FOUND");
    else
        strcpy(final_code, "200 OK");

    memset(message, 0, DIM_LONG);
    strcat(message, PROT_USR);
    strcat(message, "\n");
    strcat(message, PROT_USR_LOGIN);
    strcat(message, "\n");
    strcat(message, "Response: ");
    strcat(message, final_code);
    strcat(message, "\n");
    strcat(message, "Permission-insert: ");
    strcat(message, permission_insert);
    strcat(message, "\n");
    strcat(message, "Permission-search: ");
    strcat(message, permission_search);
    strcat(message, "\n");

    //TODO: INVIA STRINGA AL CLIENT !
    printf("\n%s\n", message);
}