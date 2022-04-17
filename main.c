#include <stdio.h>
#include "twitter_create.c"


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);

    //implement here the code to print the users
    // for each user you need to print the username, the number of followers and the number of users that the current user is following
    // user *previousPtr = NULL;
    // user *currentPtr = twitter_system.users;
    // user *nextPtr = currentPtr->next_user;

    // while(twitter_system.users!=NULL){
    //     printf("%s\n",twitter_system.users->username);
    //     twitter_system.users = twitter_system.users->next_user;
    // }
    user *userStartPtr = twitter_system.users;
    printUsers(userStartPtr);
    menu(&twitter_system);


}
