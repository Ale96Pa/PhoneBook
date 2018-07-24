#include "../basic.h"
#include "../services/service.h"

int parse_login_response(char *message, user_permissions *permissions);
int parse_register_response(char *message);
int parse_add_response(char *message);
int parse_search_response(char *message);