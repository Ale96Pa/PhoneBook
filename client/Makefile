CC=gcc
CFLAGS=-I.

client: client.o helper.o services/service.o login/login_client.o parsing/parsing.o
		$(CC) -o client client.o helper.o services/service.o login/login_client.o parsing/parsing.o
		rm client.o 
		rm helper.o
		rm login/login_client.o
		rm services/service.o
		rm parsing/parsing.o

clean:
	rm client $(objects)
