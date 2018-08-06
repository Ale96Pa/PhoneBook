#define _GNU_SOURCE
#include "database.h"

/**
 * This function is used to open a connection
 * @Param: void
 * @Return: opened connection
 */
sqlite3 *open_connection(void)
{
	sqlite3 *connection;
	int error = sqlite3_open("database/PhoneBook.db", &connection);
	if(error != SQLITE_OK)
	{
        fprintf(stderr,"Error opening DB\n");
        exit(EXIT_FAILURE);
	}

	return connection;
}

/**
 * This function close a connection
 * @Param: opened connection
 * @Return: void
 */
void close_connection(sqlite3 *conn)
{
	sqlite3_close(conn);
}

/**
 * This function is used to track the operations in the DB
 */
int callback(void *arg, int argc, char **argv, char **colName)
{
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\t", colName[i], argv[i] ?  : "NULL");
	}
	printf("\t");
	return 0;
}

/**
 * This function create a table for user administrator, who can add records
 * @Param: opened connection
 * @Return: void
 */
void create_table_searcher(sqlite3 *conn)
{
	char *zErrMsg = 0;
	int result;
	char *sql;

	sql = "CREATE TABLE user_search("  \
         "ID INT PRIMARY KEY NOT NULL," \
         "Username TEXT NOT NULL," \
         "Password TEXT NOT NULL," \
         "Email TEXT);";
	result = sqlite3_exec(conn, sql, callback, 0, &zErrMsg);

	if(result != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Table created successfully\n");
	}
	close_connection(conn);
}
/**
 * This function create a table for user standard, who can only view records
 * @Param: opened connection
 * @Return: void
 */
void create_table_adder(sqlite3 *conn)
{
	char *zErrMsg = 0;
	int result;
	char *sql;

	sql = "CREATE TABLE user_insert("  \
         "ID INT PRIMARY KEY NOT NULL," \
         "Username TEXT NOT NULL," \
         "Password TEXT NOT NULL," \
         "Email TEXT);";
	result = sqlite3_exec(conn, sql, callback, 0, &zErrMsg);

	if(result != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Table created successfully\n");
	}
	close_connection(conn);
}
/**
 * This function create a table for the actually phone book
 * @Param: opened connection
 * @Return: void
 */
void create_table_phonebook(sqlite3 *conn)
{
	char *zErrMsg = 0;
	int result;
	char *sql;

	sql = "CREATE TABLE phonebook("  \
         "ID INT NOT NULL," \
         "Name TEXT NOT NULL," \
         "Lastname TEXT," \
	 	 "Number TEXT NOT NULL," \
         "City TEXT," \
         "Type TEXT," \
		 "PRIMARY KEY (Name, Lastname, Number, City));";
	result = sqlite3_exec(conn, sql, callback, 0, &zErrMsg);

	if(result != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Table created successfully\n");
	}
	close_connection(conn);
}

/**
 * This function create the whole database
 * @Param: void
 * @Return: void
 */
void create_db(void)
{
	sqlite3 *connection;
	connection = open_connection();
	create_table_searcher(connection);
	connection = open_connection();
	create_table_adder(connection);
	connection = open_connection();
	create_table_phonebook(connection);
}