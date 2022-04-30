#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include <stdlib.h>
#include <stdbool.h>

void create_twitter_system(twitter * twitter_system){
    int num;
    twitter_system->users = NULL;
    twitter_system ->count_user =0;
    
    printf("How many users do you want to create: ");
    scanf("%d", &num);
    char c;
    c = getchar();

    user *previousPtr = NULL;

    for (int i =0; i < num; i++){
    user *newuser = malloc(sizeof(user));
    printf( "Enter your username: " );
    char name[USR_LENGHT];
    gets(name);
    strcpy(newuser->username,name);
    newuser->num_followers=0;
    newuser->num_following=0;
    twitter_system ->count_user +=1;

    if(previousPtr==NULL){
        newuser->next_user = twitter_system->users;
        twitter_system->users = newuser;
    }
    twitter_system->count_tweet = 0;
    twitter_system->tweets = NULL;
    }

}

user *findUser(twitter *twitter_system, char name[USR_LENGHT]){
    user *currentPtr = twitter_system->users;
    while(currentPtr!=NULL){
        if(strcmp(currentPtr->username,name)==0){
            return currentPtr;
        }
        
        currentPtr = currentPtr->next_user;
    }

    return NULL;
}

void follow(user *currUser, twitter *twitter_system)
{
    char c[USR_LENGHT];
    bool userfollow = false;
    int userCount =0;

// every user begins with no followers. print all users except current user 
    user* userPtr = twitter_system ->users;  
    if (currUser->num_following ==0){
        while(userPtr!= NULL)
        {  if (userPtr != currUser)
                {printf("%s\n", userPtr ->username);
                userCount +=1;}
            userPtr = userPtr->next_user;
        }
    }

    else if (currUser->num_following == twitter_system->count_user -1)
    {
        printf("All users followed.\n");
        return;
    }

     //loop through following array, print users the user currently does not follow
    while (userPtr !=NULL)
    {   
            for (int j =0; j < currUser ->num_following; j++)
            {   
                // if (strcmp (userPtr ->username, &currUser->following[i][j]) !=0) following[i] is the whole string
                if ((strcmp (userPtr ->username, currUser->following[j]) !=0) && strcmp (userPtr->username, currUser ->username) !=0)
                {
                    printf("%s\n", userPtr ->username);
                   
                }
                userPtr = userPtr->next_user;
            
            }
    }
     

     
    printf("\nWho would you like to follow?\n");
    gets(c);

    
    //check if current user currently follows chosen followee
     if (currUser->num_following > 0){
            for (int j =0; j < currUser->num_following; j++)
            {
                if (strcmp (c, currUser->following[j]) ==0 )
                {
                    printf("Already followed user\n");
                    userfollow = true;
                    
                }
            }
        }
     
     //only follow if user exists and is not being followed by current user
         
         if (userfollow == false){
             user* followee = findUser(twitter_system, c);
             if (followee == NULL)
             {
                 printf("User not found\n");
                 printf("Kindly select another menu option\n");
                  return;
                 
             }

             else if ( strcmp(followee -> username, currUser ->username) ==0)
             {
                 printf("Can not follow current user\n ");
                  return;
                 
             }
             else{
         followee ->num_followers +=1;
         strcpy(followee->followers[(followee->num_followers)-1], currUser ->username);
         
         currUser-> num_following += 1;
         strcpy(currUser->following[(currUser-> num_following)-1], followee -> username);
         printf("successfully followed");
         printf("\n");
         printf("My following list:\n");
         for(int i=0; i<currUser->num_following; i++){
                 printf("%s\n",currUser->following[i]);
         }
         printf("\n");
         printf("%s 's follower list:\n",followee->username);
         for(int j=0; j<followee->num_followers; j++){
            printf("%s\n", followee->followers[j]);
         } 
     }
     
}
}

void unfollow(user * userPtr,twitter *twitter_system){
    //1.iterates the twitter, find current user, get following list, print following list
    //2.ask which user they want to unfollow, delete the username from following array, no.following decreases
    // user *currentPtr = twitter_system->users;
    char followeeName [USR_LENGHT];
    int index = -1;
    for(int i=0; i<userPtr->num_following; i++){
        printf("\n%s\n",userPtr->following[i]);
    }
    if(userPtr->num_following == 0){
        printf("You have not followed anyone yet.\n");
        return;
    }
    printf("Which user do you want to unfollow?\n");
    printf("Please enter the person's username:\n");
    gets(followeeName);
    for(int i=0; i<userPtr->num_following; i++){
        if(strcmp(followeeName,userPtr->following[i])==0){
            index = i;
            for(int j=index; j<userPtr->num_following; j++){
                strcpy(userPtr->following[j],userPtr->following[j+1]);
            }
                userPtr->num_following --;
                printf("unfollowed successfully.\n");
        }
        else {
            printf("You have not followed this user.\n");
        }

    }
    index = -1;
    user *followeePtr = findUser(twitter_system,followeeName);
    for(int k=0; k<followeePtr->num_followers; k++){
        if(strcmp(userPtr->username,followeePtr->followers[k])==0){
            index = k;
            for(int j=index; j<followeePtr->num_followers; j++){
                strcpy(followeePtr->followers[j],followeePtr->followers[j+1]);
            }
            followeePtr->num_followers --;
        }
    }
    printf("\n");
    printf("My following list:\n");
    for(int i=0; i<userPtr->num_following; i++){
        printf("%s\n",userPtr->following[i]);
    }
    printf("\n");
    printf("%s 's follower list:\n",followeePtr->username);
    for(int j=0; j<followeePtr->num_followers; j++){
        printf("%s\n", followeePtr->followers[j]);
    }
}


//function that takes a pointer to current user and deletes all information regarding user 
void delete (user * currUser, twitter *twitter_system)
{
    tweet *tweetHead = twitter_system -> tweets;

     //loop through list of Current users following 
     for(int i=0; i<currUser->num_following; i++){

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

       //place pointer at the beginning of tweet stack 
        tweet*prevTweetPtr = twitter_system ->tweets;
        tweet *currTweetPtr = twitter_system ->tweets->next_tweet;
        tweet *temptweetPtr;

      // if curr user to be deleted is at the beginning of the tweet stack remove stack head
        if (strcmp(prevTweetPtr ->user, currUser ->username) ==0)
        {
            twitter_system ->tweets = currTweetPtr;
            free(prevTweetPtr);
        }

        else
        {   // loop through stack and get previous node pointer 
            while (currTweetPtr != NULL && (strcmp(currTweetPtr ->user, currUser ->username ) !=0))
            {
               prevTweetPtr = currTweetPtr;
               currTweetPtr = currTweetPtr ->next_tweet;
            }

            if (currTweetPtr != NULL)
            {
                temptweetPtr = currTweetPtr;
                prevTweetPtr ->next_tweet = currTweetPtr ->next_tweet;
                free(temptweetPtr);
            }
        }

    user *userPrevPtr = twitter_system ->users;
    user *usercurrentPtr = twitter_system->users -> next_user;



//loop through list to get user node before current node of user to be deleted 
    while (usercurrentPtr != NULL && usercurrentPtr != currUser)
    {
        userPrevPtr = usercurrentPtr; //update pointers with each iteration 
        usercurrentPtr = usercurrentPtr ->next_user;
    }

    //delete node when curr user has been found
    if (usercurrentPtr != NULL)
    {
        user *tempPtr = currUser;
        userPrevPtr->next_user = currUser->next_user;
        free(tempPtr);
        printf("User succesfully deleted \n");
        
    }
    }

    // call menu function after succesfully deleting user
    menu(twitter_system);

}



void postTweet (user*currUser,twitter *twitter_system)
{

    twitter_system ->count_tweet ++;
    // creates pointer to new node 
    tweet* newTweetPtr =  malloc(sizeof(tweet)); 

//copy tweet and username into tweet array
    newTweetPtr ->id = twitter_system->count_tweet;
    printf("tweet ?\n");
    fgets(newTweetPtr->msg, TWEET_LENGTH, stdin);
    strcpy(newTweetPtr ->user, currUser ->username);

//update head to newnode
    newTweetPtr ->next_tweet = twitter_system->tweets;  
    twitter_system->tweets = newTweetPtr; 

}

bool checkFollowingTweet(user *currUser, tweet * tweetPtr){
    for(int i=0; i<currUser->num_following; i++){
        if(strcmp(tweetPtr->user,currUser->following[i])==0){
            return true;
        }
    }
    return false;

}

void getNewsfeed (user *currUser, twitter *twitter_system)
{

    tweet *startTweetPtr = twitter_system->tweets; // points to head node of tweet
    tweet *currentTweetPtr = startTweetPtr; // points to the start
    int limit = 10; // max length of recent tweet array
    
    // if current user has not following anyone, only prints current user's tweets
    if(currUser->num_following == 0){
        while(currentTweetPtr!=NULL){
            if(strcmp(currUser->username,currentTweetPtr->user)==0){
                printf("ID: %d \n",currentTweetPtr->id);
                printf("User: %s\n", currentTweetPtr->user);
                printf("Content: %s \n",currentTweetPtr->msg);
            }
            currentTweetPtr = currentTweetPtr->next_tweet;
        }
    }
    // // else iterates
    else {
        int i = 0;
        currentTweetPtr = startTweetPtr;
        while(currentTweetPtr!=NULL && i<limit){
            if(strcmp(currUser->username,currentTweetPtr->user)==0 || checkFollowingTweet(currUser,currentTweetPtr)==true){
                printf("ID: %d \n",currentTweetPtr->id);
                printf("User: %s\n", currentTweetPtr->user);
                printf("Content: %s \n",currentTweetPtr->msg);
                i++;
            }
            currentTweetPtr = currentTweetPtr->next_tweet;
        }
    }
}

void endTwitter (twitter *twitter_system)
{
    printf("Twitter succesfully terminated");
    free (twitter_system);
    exit;
}

void menu(twitter *twitter_system){
    void endTurn(twitter *twitter_system);
    printf("please enter:");
    char name[USR_LENGHT];
    gets(name);
    if(findUser(twitter_system,name)==NULL){
        printf("User doesn't exit, please enter a valid username.\n");
        menu(twitter_system);
    }
    user * current_user = findUser(twitter_system,name);
    tweet *currentTweet = NULL;
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
    printf("|  9: See all tweets                                   |\n");
    printf("|  10: See all users                                   |\n");
    printf("--------------------------------------------------------\n");
    int option;
    scanf("%d",&option);
    char c = getchar();
    while(option){
        switch (option)
        {
            case 0:
                endTwitter(twitter_system);
                break;
            case 1:
                postTweet(current_user,twitter_system);
                break;
            case 2:
                getNewsfeed(current_user,twitter_system);
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
            case 9:
            currentTweet = twitter_system->tweets;
            while(currentTweet!=NULL){
                printf("ID: %d \n",currentTweet->id);
                printf("User: %s\n", currentTweet->user);
                printf("Content: %s \n",currentTweet->msg);
                printf("%p\n",currentTweet->next_tweet);
                currentTweet = currentTweet->next_tweet;
            }
            break;
            case 10:
                printUsers(twitter_system);
                break;
            default:
                printf("Please enter a valid option!\n");
                break;
        }
        printf("?\n");
        scanf("%d",&option);
        char a = getchar();
        }
}

void endTurn(twitter *twitter_system){
    menu(twitter_system);
}

void printUsers(twitter * twitter_system){
    user *currentPtr = twitter_system->users;
    while(currentPtr!=NULL){
        printf("%s\n",currentPtr->username);
        currentPtr = currentPtr->next_user;
    }
}