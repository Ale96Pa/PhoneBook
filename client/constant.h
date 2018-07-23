#define DIM_SHORT 64
#define DIM_MEDIUM 256
#define DIM_LONG 2048

#define FAILURE -1
#define SUCCESS 0

#define INSTRUCTION "\nWelcome to your phonebook!\nDo you want login? (y/n)"
#define NOT_LOGGED "\nImpossible login!\nYou insert wrong data or you aren't registered.\nDo you want register? (y/n)"
#define PERMISSION_ADD "\nYou only can INSERT a new contact.Do you want to do? (y/n)\t"
#define PERMISSION_SEARCH "\nYou only can SEARCH a contact. Do you want to do? (y/n)\t"
#define PERMISSION_ALL "\nYou can both INSERT or SEARCH a contact. What do you want to do?\nInsert (type 1)\nSearch (type 2)\nExit   (other)\n"

#define PROT_USR "User Protocol"
#define PROT_USR_LOGIN "Request-method: LOGIN"
#define PROT_USR_REGISTER "Request-method: REGISTER"

#define PROT_OPER "Operation Protocol"
#define PROT_OPER_ADD "Request-method: ADD"
#define PROT_OPER_SEARCH "Request-method: SEARCH"