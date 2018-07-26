#include "login_client.h"

/**
 * This function starts the login interface for the client
 * @param user: struct used to save user credentials
 */
void start_login(user_login *user)
{
    memset(user->username, 0, DIM_SHORT);
    memset(user->password, 0, DIM_SHORT);

    printf(YELLOW "\n******* LOGIN INTERFACE *******\n" RESET);
    printf(YELLOW "Insert username: " RESET);
    fgets(user->username, DIM_SHORT, stdin);
    user->username[strcspn(user->username, "\n")] = 0;
    //This instruction is used to remove the "\n" captured with fgets

    printf(YELLOW "Insert password: " RESET);
    fgets(user->password, DIM_SHORT, stdin);
    user->password[strcspn(user->password, "\n")] = 0;
    //This instruction is used to remove the "\n" captured with fgets
}