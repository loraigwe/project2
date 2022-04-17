//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include <stdlib.h>


void create_twitter_system(twitter * twitter_system){
    int num;
    //to be completed
    twitter_system->users = NULL;
    
   
    printf("How many users do you want to create: ");
    scanf("%d", &num);

    user *previousPtr = NULL;

    // user *nextPtr  = currentPtr->next_user;

    for (int i =0; i < num; i++){
    user *newuser = malloc(sizeof(user));
    printf( "Enter your username: " );
    char name[USR_LENGHT];
    // gets(name);
    scanf("%s",name);
    strcpy(newuser->username,name);
    newuser->num_followers=0;
    newuser->num_following=0;
    if(previousPtr==NULL){
        newuser->next_user = twitter_system->users;
        twitter_system->users = newuser;
    }
    // else {
    //     previousPtr->next_user = newuser;
    //     newuser->next_user = currentPtr;
    // }
    // printf("%s",twitter_system->users->username);
    // twitter_system->users = previousPtr;
    }
    

}

user *findUser(twitter *twitter_system, char name[USR_LENGHT]){
   printf("*\n");
    user *currentPtr = twitter_system->users;
    while(currentPtr!=NULL){
        if(strcmp(currentPtr->username,name)==0){
            printf("found");
            return currentPtr;
        }
        // printf("%s",currentPtr->username);
        currentPtr = currentPtr->next_user;
    }

    return 0;
}

void follow(user *currUser, twitter *twitter_system)
{

    char c[USR_LENGHT];
    
    
    printf("\nWho would you like to follow?\n");
    scanf("%s",c );

     user* followee = findUser(twitter_system, c);
     if (followee != NULL)
     {
         followee ->num_followers +=1;
         strcpy(followee ->followers, currUser ->username);
         
         currUser-> num_following += 1;
         strcpy(currUser ->following, followee -> username);
         printf("successfully followed");
         

     }
}



void menu(twitter *twitter_system){
   user *current_user = findUser(twitter_system,name);
    printf("Please select from one of the following options:\n");
    printf("--------------------------------------------------------\n");
    printf("|  0: End Twitter System(Exit the program)             |\n");
    printf("|  1: Find user                                     |\n");
    printf("|  2: Get Newest Feeds                                 |\n");
    printf("|  3: Follow a user                                    |\n");
    printf("|  4: Unfollow a user                                  |\n");
    printf("|  5: Delete your account                              |\n");
    printf("|  6: End Turn(move on to next user)                   |\n");
    printf("--------------------------------------------------------\n");
    int option;
    scanf("%d",&option);
    while(option!=0){
        switch (option)
        {
            case 0:
                return;
                break;
            case 1:
                printf("please enter:");
                char name[USR_LENGHT];
                scanf("%s",name);
                findUser(twitter_system,name); 
                break;

            case 2:
              printf("In the making");
              break;

            case 3:
            follow(current_user,twitter_system);
            break;
        // default:
        }
        printf("?\n");
        scanf("%d",&option);
        char c;
        c = getchar();
        }
}