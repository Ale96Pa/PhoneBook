CC=gcc
CFLAGS=-lsqlite3

server: server.o server_child.o server_child_work.o helper.o database/db_manager.o database/db_operation.o login/login_server.o services/service.o parsing/parsing.o logging/logging.o
	$(CC) -o server server.o server_child.o server_child_work.o helper.o database/db_manager.o database/db_operation.o login/login_server.o services/service.o parsing/parsing.o logging/logging.o $(CFLAGS)
	rm server.o
	rm server_child.o
	rm server_child_work.o
	rm helper.o
	rm database/db_manager.o
	rm database/db_operation.o
	rm login/login_server.o
	rm services/service.o
	rm parsing/parsing.o
	rm logging/logging.o

clean:
	rm server
