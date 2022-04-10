#include "twitter_create.h"

void endTurn(user *currentUserPtr);
void menu(twitter *twitter_system,char name[USR_LENGHT] );
user* findUser(twitter *twitter_system,char name[USR_LENGHT]);
void unfollow(twitter *twitter_system,char name[USR_LENGHT]);