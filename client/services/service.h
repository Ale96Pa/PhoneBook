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

void welcome(user_login *login, int sockd);
int not_logged(user_login *registration, user_permissions *permissions, int sockd);
void register_user(user_login *user, user_permissions *permissions, int sockd);
int send_credentials(user_login *user, user_permissions *permissions, char *method, int sockd);

int action_from_permission(user_permissions *permissions, int sockd);
void insert_contact(record_db *contact, int sockd);
void search_contact(research *search, int sockd);
