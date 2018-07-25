#include "../basic.h"
#include "../login/login_server.h"

void add_record(record_db *record_db, int sockd);
void search_records(char *column, char *research, int sockd);
void register_user(user_login *user, user_permissions *permissions, int sockd);