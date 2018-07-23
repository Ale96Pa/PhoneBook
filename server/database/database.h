#define _GNU_SOURCE
#include <sqlite3.h>
#include "../basic.h"

typedef struct record_db {
    int id;
    char name[DIM_MEDIUM];
    char lastname[DIM_MEDIUM];
    char number[DIM_SHORT];
    char city[DIM_MEDIUM];
    char type[DIM_SHORT];
} record_db;

sqlite3 *open_connection(void);
void close_connection(sqlite3 *connection);
void create_table_adder(sqlite3 *connection);
void create_table_searcher(sqlite3 *connection);
void create_table_phonebook(sqlite3 *connection);
void create_db(void);

void insert_user(char *table, int id, char *username, char *pw, char *email);
int insert_record(int id, char *name, char *lastname, char *number, char *city, char *type);
void delete(char *table, int id);
int select_max_id(char *table);
int count_record(char *column, char *user_search);
void search_record_db(char *column, char *user_search, record_db searched[]);

int check_user_adder(char *username, char *password);
int check_user_searcher(char *username, char *password);