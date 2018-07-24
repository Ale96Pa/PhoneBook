#include "../basic.h"
#include "../login/login_client.h"

typedef struct record_db {
    int id;
    char name[DIM_MEDIUM];
    char lastname[DIM_MEDIUM];
    char number[DIM_SHORT];
    char city[DIM_MEDIUM];
    char type[DIM_SHORT];
} record_db;

typedef struct research {
    char field[DIM_SHORT];
    char content[DIM_MEDIUM];
} research;

void welcome(user_login *login);
void not_logged(user_login *registration, user_permissions *permissions);
void register_user(user_login *user, user_permissions *permissions);
int send_credentials(user_login *user, user_permissions *permissions, char *method);

void action_from_permission(user_permissions *permissions);
void insert_contact(record_db *contact);
void search_contact(research *search);
