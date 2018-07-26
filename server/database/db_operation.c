#define _GNU_SOURCE
#include "database.h"

/**
 * This function insert a new user-record in the DB with elements given in input
 * @Param: table, id, username, email, pw
 * @Return: void
 */
void insert_user(char *table, int id, char *username, char *pw, char *email)
{
	sqlite3 *connection;
	sqlite3_stmt *stmt;
	char *query=NULL;
	int result;

	// Prepare connection and query
	connection = open_connection();
	asprintf(&query, "INSERT OR IGNORE INTO %s VALUES('%d','%s','%s','%s');", table, id, username, pw, email);
	sqlite3_prepare_v2(connection, query, strlen(query), &stmt, NULL);
	result=sqlite3_step(stmt);

	// Check result
	if(result != SQLITE_DONE)
	{
		fprintf(stderr,"Error inserting data in DB %s\n", sqlite3_errmsg(connection));
		exit(FAILURE);
	}

	// Free resources
	sqlite3_finalize(stmt);
	free(query);
	close_connection(connection);
}

/**
 * This function insert a new record in the table phonebook with elements given in input
 * @Param: id, name, lastname, phone-number, city, type of number
 * @Return: void
 */
int insert_record(int id, char *name, char *lastname, char *number, char *city, char *type)
{
	sqlite3 *connection;
	sqlite3_stmt *stmt;
	char *query = NULL;
	int result;

    // Prepare connection and query
    connection = open_connection();
	asprintf(&query,"INSERT OR IGNORE INTO phonebook VALUES('%d','%s','%s','%s', '%s', '%s');", id, name, lastname, number, city, type);
	sqlite3_prepare_v2(connection,query,strlen(query),&stmt,NULL);
	result=sqlite3_step(stmt);

	// Check result
	if(result != SQLITE_DONE)
	{
		fprintf(stderr, "Error inserting data in DB %s\n", sqlite3_errmsg(connection));
        return FAILURE;
	}

	// Free resources
	sqlite3_finalize(stmt);
	free(query);
	close_connection(connection);
    return SUCCESS;
}

/**
 * Delete an element from DB depending from its ID
 * @Param: table, id
 * @Return: void
 */
void delete(char *table, int id)
{
	sqlite3 *connection;
	sqlite3_stmt *stmt;
	char *query = NULL;
	int result;

    // Prepare connection and query
    connection = open_connection();
	asprintf(&query,"DELETE FROM %s WHERE ID='%d';", table, id);
	sqlite3_prepare_v2(connection,query,strlen(query),&stmt,NULL);
	result = sqlite3_step(stmt);

	// Check result
	if(result!=SQLITE_DONE)
	{
		fprintf(stderr,"Error deleting data from DB: %s\n", sqlite3_errmsg(connection));
		exit(FAILURE);
	}

    // Free resources
    sqlite3_finalize(stmt);
	free(query);
	close_connection(connection);
}
/**
 * This function return the value of maximum id to assign the next ID
 *
 * @Return: value of maximum id
 */
int select_max_id(char *table)
{
    sqlite3_stmt *stmt;
    sqlite3 *connection;
    int max_id, result;
    char *query = NULL;

    // Prepare connection and query
    asprintf(&query, "SELECT MAX(ID) FROM %s ", table);
    connection = open_connection();
    result = sqlite3_prepare_v2(connection, query, strlen(query), &stmt, NULL);

    // Check and get result
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare database in function sel_max_id()\n");
        close_connection(connection);
        return -1;
    }
    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW)
        {
            max_id = sqlite3_column_int(stmt,0);
        }
    } while (result == SQLITE_ROW);

    // Free resources
    sqlite3_finalize(stmt);
    free(query);
    close_connection(connection);
    return max_id;
}

/**
 * This function return the number of elements in the DB searched (so the number
 * of record to send to the client
 * @Param: column where search, string insert by user
 * @Return: number of elements searched in the DB
 */
int count_record(char *column, char *user_search)
{
    sqlite3_stmt *stmt;
    sqlite3 *connection;
    int counter, result;
    char *query = NULL;
    char c = '%';

    // Prepare connection and query
    asprintf(&query, "SELECT count(*) FROM phonebook WHERE %s LIKE '%c%s%c'", column, c, user_search, c);
    connection = open_connection();
    result = sqlite3_prepare_v2(connection, query, strlen(query), &stmt, NULL);

    // Check and get result
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare database in function count_record()\n");
        close_connection(connection);
        return -1;
    }
    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW)
        {
            counter = sqlite3_column_int(stmt,0);
        }
    } while (result == SQLITE_ROW);

    // Free resources
    sqlite3_finalize(stmt);
    free(query);
    close_connection(connection);
    return counter;
}
/**
 * This function return the elements in the DB searched (so the records to send to the client
 * @Param: column where search, string insert by user, array of records to send to client
 * @Return: void
 */
void search_record_db(char *column, char *user_search, record_db searched[])
{
    sqlite3 *connection;
    sqlite3_stmt *stmt;
    char *query = NULL;
    int result, i = 0;;
    char c = '%';

    // Prepare connection and query
    connection = open_connection();
    asprintf(&query, "SELECT * FROM phonebook WHERE %s LIKE '%c%s%c'", column, c, user_search, c);
    result = sqlite3_prepare_v2(connection, query, strlen(query), &stmt, NULL);

    // Check and get result
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare database in function search_record()\n");
        close_connection(connection);
        exit(FAILURE);
    }
    do {
        result = sqlite3_step(stmt);

        if (result == SQLITE_ROW)
        {
            searched[i].id = (int)sqlite3_column_int(stmt, 0);
            strcpy(searched[i].name, (char *)sqlite3_column_text(stmt, 1));
            strcpy(searched[i].lastname, (char *)sqlite3_column_text(stmt, 2));
            strcpy(searched[i].number, (char *)sqlite3_column_text(stmt, 3));
            strcpy(searched[i].city, (char *)sqlite3_column_text(stmt, 4));
            strcpy(searched[i].type, (char *)sqlite3_column_text(stmt, 5));
            i++;
        }

    } while (result == SQLITE_ROW);

    // Free resources
    sqlite3_finalize(stmt);
    free(query);
    close_connection(connection);
}

/**
 * This functions do a query in the DB to check the permission
 * of a user given in input
 * @param username: username of user
 * @param password: password of user
 * @return: -1 or 0 basing on success
 */
int check_user_adder(char *username, char *password)
{
    sqlite3 *connection;
    sqlite3_stmt *stmt;
    char *query = NULL;
    int result, exit_code = 0;

    // Prepare connection and query
    connection = open_connection();
    asprintf(&query, "SELECT ID FROM user_insert WHERE Username = '%s' and Password = '%s'", username, password);
    result = sqlite3_prepare_v2(connection, query, strlen(query), &stmt, NULL);

    // Check and get result
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare database in function search_record()\n");
        close_connection(connection);
        return FAILURE;
    }
    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW)
        {
            exit_code = sqlite3_column_int(stmt,0);
        }
    } while (result == SQLITE_ROW);

    // Free resources
    sqlite3_finalize(stmt);
    free(query);
    close_connection(connection);
    return exit_code;
}
int check_user_searcher(char *username, char *password)
{
    sqlite3 *connection;
    sqlite3_stmt *stmt;
    char *query = NULL;
    int result, exit_code = 0;

    // Prepare connection and query
    connection = open_connection();
    asprintf(&query, "SELECT ID FROM user_search WHERE Username = '%s' and Password = '%s'", username, password);
    result = sqlite3_prepare_v2(connection, query, strlen(query), &stmt, NULL);

    // Check and get result
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare database in function search_record()\n");
        close_connection(connection);
        return -1;
    }
    do {
        result = sqlite3_step(stmt) ;
        if (result == SQLITE_ROW)
        {
            exit_code = sqlite3_column_int(stmt,0);
        }
    } while (result == SQLITE_ROW);

    // Free resources
    sqlite3_finalize(stmt);
    free(query);
    close_connection(connection);
    return exit_code;
}