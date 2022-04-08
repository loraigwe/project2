//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){

    //to be completed
    twitter_system->users = NULL;
    user *newuser = malloc(sizeof(user));
   
    printf( "Enter your username: " );
    char name[USR_LENGHT];
    // gets(name);
    scanf("%s",name);
    strcpy(newuser->username,name);
    newuser->num_followers=0;
    newuser->num_following=0;
    newuser->next_user = twitter_system->users;
    twitter_system->users = newuser;
    // printf("%s",twitter_system->users->username);


}