//#define _GNU_SOURCE
#include "server.h"

int main()
{
    //create_db();
/*
    int num = count_record("City", "c");
    printf("FOUND %d record\n", num);
    record_db test[num];
    search_record("City", "c", test);
    int i;
    for(i=0; i<num; i++)
    {
        printf("TEST: %s -- %ld \n", test[i].lastname, test[i].number);
    }
*/
/*
    user_login *login = malloc(sizeof(user_login));
    user_permissions *permissions = malloc(sizeof(user_permissions));
    strcpy(login->username, "ale96");
    strcpy(login->password, "palma");
    check_login(login, permissions);
*/
/*
    user_login *login = malloc(sizeof(user_login));
    user_permissions *permissions = malloc(sizeof(user_permissions));
    strcpy(login->username, "username");
    strcpy(login->password, "password");
    strcpy(login->email, "");
    permissions->can_search = 0;
    permissions->can_insert = -1;
    register_user(login, permissions);
*/
/*
    record_db *db = malloc(sizeof(record_db));
    strcpy(db->name,"Ornella");
    strcpy(db->lastname,"Vanoni");
    strcpy(db->number, "3287458962");
    strcpy(db->city,"Roma");
    strcpy(db->type,"");
    add_record(db);
*/

    //search_records("Name", "a");

    char message[DIM_LONG];
/*    strcpy(message, "User Protocol\n"
                    "Request-method: LOGIN\n"
                    "Username: ale96\n"
                    "Password: palma");
    parse_user_login(message);
    */

/*    strcpy(message, "User Protocol\n"
                    "Request-method: REGISTER\n"
                    "Username: Alejandro\n"
                    "Password: Palmas\n"
                    "Email: ale@gmail.it\n"
                    "Insert: -1\n"
                    "Search: 0");
    parse_user_register(message);*/

/*
    strcpy(message, "Operation Protocol\n"
                    "Request-method: ADD\n"
                    "Name: Alessandro\n"
                    "Lastname: Palma\n"
                    "Phone-number: 123654789\n"
                    "Number-type: landline\n"
                    "City: ciaone");
    parse_add(message);*/
/*
    strcpy(message, "Operation Protocol\n"
                    "Request-method: SEARCH\n"
                    "Field: Phone number\n"
                    "Content-search: 258");
    parse_search(message);
*/

    child_work();

    return 0;

} 
