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
    user *currentPtr = twitter_system->users;
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
    else {
        previousPtr->next_user = newuser;
        newuser->next_user = currentPtr;
    }
    // printf("%s",twitter_system->users->username);
    // twitter_system->users = previousPtr;
    }
    

}