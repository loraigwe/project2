#include "functionality.h"
#include "twitter_create.h"
#include <stdlib.h>
#include<stdio.h>
#include<string.h>

//find the current user in the system, return the pointer?
user* findUser(twitter *twitter_system,char name[USR_LENGHT]){
    user *previousPtr = NULL;
    user *currentPtr = twitter_system->users;
    if(currentPtr==NULL){
        printf("There is no user in the system.\n");
    }
    else{
        while(currentPtr!=NULL && strcmp(name,currentPtr->username)){
            previousPtr = currentPtr;
            currentPtr = currentPtr->next_user;
        }
        return (currentPtr);
    }
}

//Unfollow(5)- allows a user to unfollow a valid user that s/he is following (search in the system to find that user the current user wish to follow, search in the current user’s following list). It should first retrieve and print the usernames of the users that the current user is following, this allow the current user to select a valid username if available.
void unfollow(twitter *twitter_system, char name[USR_LENGHT]){
    //1.iterates the twitter, find current user, get following list, print following list
    //2.ask which user they want to unfollow, delete the username from following array, no.following decreases

}
//EndTurn(2.5) - tells the twitter system to move to the next user
void endTurn(user *currentUserPtr){
    // 1.

}
//- post tweet- follow- unfollow- delete- endturn- end twitter- getnewsfeed
void menu(twitter *twitter_system, char name[USR_LENGHT]){
   user *current_user = findUser(twitter_system,name);
    printf("Please select from one of the following options:");
    printf("--------------------------------------------------------\n");
    printf("|  0: End Twitter System(Exit the program)             |\n");
    printf("|  1: Post a tweet                                     |\n");
    printf("|  2: Get Newest Feeds                                 |\n");
    printf("|  3: Follow a user                                    |\n");
    printf("|  4: Unfollow a user                                  |\n");
    printf("|  5: Delete your account                              |\n");
    printf("|  6: End Turn(move on to next user)                   |\n");
    printf("--------------------------------------------------------\n");
    int option;
    scanf("%d",option);
    // while(option>=0 && option<=4){
    while(option){
        switch (option)
        {
        case 0:
            /* code */
            menu(&twitter_system,name);
            break;
        case 1:
            menu(&twitter_system,name);
            break;
        case 2:
            menu(&twitter_system,name);
            break;
        case 3:
            menu(&twitter_system,name);
            break;
        case 4:
            unfollow(&twitter_system,name);
            menu(&twitter_system,name);
            break;
        case 5:
            menu(&twitter_system,name);
            break;
        case 6:
            endTurn(name);
            menu(&twitter_system,name);
            break;
        default:
            printf("Invalid option!\n");
            scanf("%d",option);
            break;
        }
    }
}