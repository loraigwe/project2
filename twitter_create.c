//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include <stdlib.h>
#include <stdbool.h>


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
    user *currentPtr = twitter_system->users;
    while(currentPtr!=NULL){
        if(strcmp(currentPtr->username,name)==0){
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
    bool userfollow = false;

    user* userPtr = twitter_system ->users; //print all users if current user has no followers 
    if (currUser->num_following ==0){
        while(userPtr!= NULL)
        {  if (userPtr != currUser)
                printf("%s\n", userPtr ->username);
            userPtr = userPtr->next_user;
        }
    }

    else if (currUser ->num_following >0) //loop through following array, print users the user currently does not follow
    {   
        for (int i=0; i < currUser -> num_followers; i++)
    
        {
            for (int j =0; j < currUser ->num_followers; j++)
            {   
                if (strcmp (userPtr ->username, &currUser->following[i][j]) !=0)
                {
                    printf("%s\n", userPtr ->username);
                    userPtr = userPtr->next_user;
                }
            
            }
        }
    }
    
    printf("\nWho would you like to follow?\n");
    scanf("%s",c );

    
    //check if current user currently follows chosen followee
     if (currUser->num_followers > 0){
    //  if (followee != NULL)
     
         
         for (int i=0; i < currUser->num_following; i++)
        {
            for (int j =0; j < currUser->num_following; j++)
            {
                if (strcmp (c, &currUser->following[i][j]) ==0 )
                {
                    printf("Already followed user\n");
                    userfollow = true;
                    
                }

            }
        }
     }
     //only follow if user exists and is not being followed by current user
         
         if (userfollow == false){
             user* followee = findUser(twitter_system, c);
         followee ->num_followers +=1;
        //  strcpy(followee ->followers, currUser ->username);
         strcpy(followee->followers[(followee->num_followers)-1], currUser ->username);
         
         currUser-> num_following += 1;
        //  strcpy(currUser ->following, followee -> username);
         strcpy(currUser->following[(currUser-> num_following)-1], followee -> username);
         for(int i=0; i<currUser->num_following; i++){
            //  for(int j=0; j<USR_LENGHT; j++){
                //  printf("%s\n",currUser->following[i]);
            //  }
         }
         printf("successfully followed");
     }
     

     

     else
     {
         printf("user not found.\n");
     }
}

void unfollow(user * userPtr,twitter *twitter_system){
    //1.iterates the twitter, find current user, get following list, print following list
    //2.ask which user they want to unfollow, delete the username from following array, no.following decreases
    // user *currentPtr = twitter_system->users;
    char followingName [USR_LENGHT];
    int index = -1;
    printf("Your current following list is:\n");
    for(int i=0; i<userPtr->num_following; i++){
        printf("\n%s\n",userPtr->following[i]);
    }
    if(userPtr->num_following == 0){
        printf("You have not followed anyone yet.\n");
        return;
    }
    printf("Which user do you want to unfollow?\n");
    printf("Please enter the person's username:\n");
    scanf("%s",followingName);
    for(int i=0; i<userPtr->num_following; i++){
        if(strcmp(followingName,userPtr->following[i])==0){
            index = i;
            if(index!=-1){
            for(int j=index; j<userPtr->num_following; j++){
                strcpy(userPtr->following[j],userPtr->following[j+1]);
            }
                userPtr->num_following --;
                printf("unfollowed successfully.\n");
            }
            else if(index == -1){
                printf("You have not followed this user yet.\n");
            }
        }

    }
    index = -1;
    user *followingPtr = findUser(twitter_system,followingName);
    for(int k=0; k<followingPtr->num_followers; k++){
        if(strcmp(userPtr->username,followingPtr->followers[k])==0){
            index = k;
            for(int j=index; j<followingPtr->num_followers; j++){
                strcpy(followingPtr->followers[j],followingPtr->followers[j+1]);
            }
            followingPtr->num_followers --;
        }
        // if(index!=-1){
        // }
    }
    for(int i=0; i<userPtr->num_following; i++){
        printf("%s\n",userPtr->following[i]);
    }
}

void delete (user * currUser, twitter *twitter_system)
{
     //loop through list of Current users following 
     for(int i=0; i<currUser->num_following; i++){
        //  for (int j =0; j < currUser ->num_following; j++) we dont need a second loop to loop through each charater, [i][j] is getting the characters, we just need [i]which is the whole string
        user *followingPtr = findUser(twitter_system,currUser->following[i]);
     
        for(int k=0; k<followingPtr->num_followers; k++){
            if(strcmp(currUser->username,followingPtr->followers[k])==0){
                int index = k;
                for(int j=index; j<followingPtr->num_followers; j++){
                    strcpy(followingPtr->followers[j],followingPtr->followers[j+1]);
                }
                followingPtr->num_followers --;
            }
        }
    }
    // I added this to check if its working 
    //loop through list of current users followers
    for(int i=0; i<currUser->num_followers; i++){
        user *followerPtr = findUser(twitter_system,currUser->followers[i]);
        for(int k=0; k<followerPtr->num_following; k++){
            if(strcmp(currUser->username,followerPtr->following[k])==0){
                int index = k;
                for(int j=index; j<followerPtr->num_following; j++){
                    strcpy(followerPtr->following[j],followerPtr->following[j+1]);
                }
                followerPtr->num_following --;
            }
        }
    }
    
    //check if user to be deleted is at the beggining of the list 
    if (currUser == twitter_system ->users)
    {
        user *tempPtr = currUser; //store value of node to be deleted 
        twitter_system ->users = (*currUser).next_user;
        free (tempPtr);         //delete node 
        return;
    }
    else{

    user *userPrevPtr = twitter_system ->users;
    user *usercurrentPtr = twitter_system->users -> next_user;

//loop through list to get user node before current node of user to be deleted 
    while (usercurrentPtr != NULL && usercurrentPtr != currUser)
    {
        userPrevPtr = usercurrentPtr; //update pointers with each iteration 
        usercurrentPtr = usercurrentPtr ->next_user;
    }

    if (usercurrentPtr != NULL)
    {
        user *tempPtr = currUser;
        userPrevPtr->next_user = currUser->next_user;
        free(tempPtr);
        printf("User succesfully deleted \n");
    }
    }
}

void postTweet (user*currUser, tweet** root)
{
    
    //create newtweet node 
   tweet* newTweetPtr = (tweet*) malloc(sizeof(tweet)); 
   char tweetArray[USR_LENGHT];
  
   printf("Whats on your mind ? \n");
   scanf("%s", tweetArray);
   newTweetPtr ->id =0;

   strcpy(newTweetPtr ->msg, tweetArray);
   strcpy(newTweetPtr ->user, currUser ->username);

//point node to the top 
      newTweetPtr ->next_tweet = *root;  
      (*root) = newTweetPtr; 

}



void menu(twitter *twitter_system){
    void endTurn(twitter *twitter_system);
    char name[USR_LENGHT];
    printf("please enter:");
    tweet* head =(tweet*) malloc(sizeof(tweet));
    scanf("%s",name);
    user *current_user = findUser(twitter_system,name);
    printf("Please select from one of the following options:\n");
    printf("--------------------------------------------------------\n");
    printf("|  0: End Twitter System(Exit the program)             |\n");
    printf("|  1: Post Tweet                                       |\n");
    printf("|  2: Get Newest Feeds                                 |\n");
    printf("|  3: Follow a user                                    |\n");
    printf("|  4: Unfollow a user                                  |\n");
    printf("|  5: Delete your account                              |\n");
    printf("|  6: End Turn(move on to next user)                   |\n");
    printf("|  7: See my following list                            |\n");
    printf("|  8: See my follower list                             |\n");
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
                postTweet(current_user, &head);
                break;

            case 2:
                printf("In the making");
                break;

            case 3:
                follow(current_user,twitter_system);
                break;
            case 4:
                unfollow(current_user,twitter_system);
                break;
            case 5:
                delete(current_user,twitter_system);
                break;
            case 6:
                endTurn(twitter_system);
                break;
            case 7:
                if(current_user->num_following!=0){
                    printf("Your current following list is:\n");
                    for(int i=0; i<current_user->num_following; i++){
                        printf("\n%s\n",current_user->following[i]);
                    }
                }
                else{
                    printf("You have not followed anyone.\n");
                }
                break;
            case 8:
            if(current_user->num_followers!=0){
                printf("Your current followers list is:\n");
                for(int i=0; i<current_user->num_followers; i++){
                    printf("\n%s\n",current_user->followers[i]);
                }
            }
            else {
                printf("You have no followers.\n");
            }
                break;
            default:
                printf("Please enter a valid option!\n");
                scanf("%d",&option);
        }
        printf("?\n");
        scanf("%d",&option);
        char c;
        c = getchar();
        }
}

void endTurn(twitter *twitter_system){
    // printf("please enter:");
    // char name[USR_LENGHT];
    // scanf("%s",name);
    // user * currentUserPtr = findUser(twitter_system,name);
    menu(twitter_system);
}

void printUsers(twitter * twitter_system){
    user *currentPtr = twitter_system->users;
    while(currentPtr!=NULL){
        // if(strcmp(currentPtr->username,name)==0){
        //     printf("found");
        // }
        printf("%s\n",currentPtr->username);
        currentPtr = currentPtr->next_user;
    }
}