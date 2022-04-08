#include <stdio.h>
<<<<<<< HEAD
#include "twitter_create.h"
#include "twitter_create.c"


=======
#include "twitter_create.c"
>>>>>>> 3e781a420e9ccd0d9eb08e4929daa8c9ea7be31e


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);

    //implement here the code to print the users
    // for each user you need to print the username, the number of followers and the number of users that the current user is following
    user *previousPtr = NULL;
    user *currentPtr = twitter_system.users;
    user *nextPtr = currentPtr->next_user;

    // while(nextPtr!=NULL){
        printf("%s",currentPtr->username);
    // }



}
