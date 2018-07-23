#include "login_client.h"

//TODO: TUtti controllo errori

void start_login(user_login *user)
{
    memset(user->username, 0, DIM_SHORT);
    memset(user->password, 0, DIM_SHORT);

    printf("LOGIN\n");
    printf("Insert username: ");
    fgets(user->username, DIM_SHORT, stdin);
    user->username[strcspn(user->username, "\n")] = 0;

    printf("Insert password: ");
    fgets(user->password, DIM_SHORT, stdin);
    user->password[strcspn(user->password, "\n")] = 0;

}

void parse_login(/*socket,*/)
{
    //Prendi stringa di risposta dalla socket

}