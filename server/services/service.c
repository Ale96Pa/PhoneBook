#include "service.h"

void register_user(user_login *user, user_permissions *permissions)
{
    int id_searcher, id_adder;
    int exit_code = 0;
    char message[DIM_LONG];
    char final_code[DIM_SHORT];

    if(permissions->can_search != -1)
    {
        id_searcher = select_max_id("user_search")+1;
        insert_user("user_search", id_searcher, user->username, user->password, user->email);
        exit_code++;
    }
    if(permissions->can_insert != -1)
    {
        id_adder = select_max_id("user_insert")+1;
        insert_user("user_insert", id_adder, user->username, user->password, user->email);
        exit_code++;
    }

    switch (exit_code) {
        case 0:
            strcpy(final_code, "300 BAD REQUEST");
            break;
        default:
            strcpy(final_code, "200 OK");
            break;
    }

    memset(message, 0, DIM_LONG);
    strcat(message, PROT_USR);
    strcat(message, "\n");
    strcat(message, PROT_USR_REGISTER);
    strcat(message, "\n");
    strcat(message, "Response: ");
    strcat(message, final_code);
    strcat(message, "\n");
    //TODO: SEND to client

    printf("\n%s\n", message);
}

void add_record(record_db *data)
{
    int ID, exit_code;
    char message[DIM_LONG];
    char final_code[DIM_SHORT];

    ID = select_max_id("phonebook");
    data->id = ID+1;

    exit_code = insert_record(data->id, data->name, data->lastname, data->number, data->city, data->type);
    switch (exit_code) {
        case -1:
            strcpy(final_code, "300 BAD REQUEST");
            break;
        default:
            strcpy(final_code, "200 OK");
            break;
    }

    memset(message, 0, DIM_LONG);
    strcat(message, PROT_OPER);
    strcat(message, "\n");
    strcat(message, PROT_OPER_ADD);
    strcat(message, "\n");
    strcat(message, "Response: ");
    strcat(message, final_code);
    strcat(message, "\n");
    //TODO: SEND to client

    printf("\n%s\n", message);

}

//TODO: Aumenta notevolmente la dimensione del messaggio (in proporzione al numero di record)
void search_records(char *column, char *research)
{
    int num, i;
    char message[DIM_LONG], number[DIM_SHORT];
    memset(message, 0, DIM_LONG);

    num = count_record(column, research);
    record_db results[num];
    search_record_db(column, research, results);

    strcat(message, PROT_OPER);
    strcat(message, "\n");
    strcat(message, PROT_OPER_SEARCH);
    strcat(message, "\n");
    strcat(message, "Number-record: ");
    sprintf(number, "%d", num);
    strcat(message, number);
    strcat(message, "\n\n");

    for(i=0; i<num; i++)
    {
        strcat(message, "Name: ");
        strcat(message, results[i].name);
        strcat(message, "\n");
        strcat(message, "Lastname: ");
        strcat(message, results[i].lastname);
        strcat(message, "\n");
        strcat(message, "Number: ");
        strcat(message, results[i].number);
        strcat(message, "\n");
        strcat(message, "Number-type: ");
        strcat(message, results[i].type);
        strcat(message, "\n");
        strcat(message, "City: ");
        strcat(message, results[i].city);
        strcat(message, "\n\n");
    }

    //TODO: invia al client
    printf("\n%s\n", message);
}