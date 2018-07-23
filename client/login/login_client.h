#include "../basic.h"

typedef struct user_login {
    char username[DIM_SHORT];
    char password[DIM_SHORT];
    char email[DIM_MEDIUM];
} user_login;

typedef struct user_permissions {
    int can_search;
    int can_insert;
} user_permissions;

void start_login(user_login *login);
