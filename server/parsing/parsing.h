#include "../basic.h"
#include "../services/service.h"

typedef struct researcher {
    char column[DIM_SHORT];
    char user_search[DIM_SHORT];
} researcher;

int parse_user_login(char *message, user_login *user);
int parse_user_register(char *message, user_login *user, user_permissions *permissions);
int parse_add(char *message, record_db *data);
int parse_search(char *message, researcher *search);
