#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "social.h"

void displayOptions(){
    for(int i=0;i<20;i++) printf("-");
    printf("\n 1. Individual \n 2. Business \n 3. Group \n 4. Organisation \n ");
    for(int i=0;i<20;i++) printf("-");
    printf("\n");

}

int countDigits(int number){
     int count = 0;

    // Handle the case when the number is 0
    if (number == 0) {
        return 1; // 0 has one digit
    }

    // Count digits using a loop
    while (number != 0) {
        number = number / 10;
        count++;
    }

    return count;
}

int createID(int type){
    int output_id, digit_count=0;
    switch(type){
        case 1: 
            digit_count = countDigits(individual_count);
            output_id = (int)pow(10, digit_count) + individual_count;
            individual_count++;
            break;
        
        case 2: 
            digit_count = countDigits(biz_count);
            output_id = 2*(int)pow(10, digit_count) + biz_count;
            biz_count++;
            break;
        
        case 3: 
            digit_count = countDigits(grp_count);
            output_id = 3*(int)pow(10, digit_count) + grp_count;
            grp_count++;
            break;
        
        case 4: 
            digit_count = countDigits(org_count);
            output_id = 4*(int)pow(10, digit_count) + org_count;
            org_count++;
            break;
        
        default: return -1;
    }

    return output_id;
}

int searchEntity(int type, char *name){}

date getCurrentDate() {
    time_t currentDate;
    struct tm *localDate;
    date today;

    // Get the current date
    time(&currentDate);

    // Convert the current date to the local date
    localDate = localtime(&currentDate);

    // Populate the Date struct
    today.day = localDate->tm_mday;
    today.month = localDate->tm_mon + 1; // tm_mon is 0-indexed, so add 1
    today.year = localDate->tm_year + 1900; // tm_year is years since 1900

    return today;
}

void createProfile(int type){
    printf("\n----- Enter the required details -----\n ");

    basic *basicProfileDetails;
    basicProfileDetails = (basic*)malloc(sizeof(basic));

    char name[limit];

    //Entering Name
    printf("Enter Name : ");
    scanf("%s", name);
    basicProfileDetails->name = strdup(name);
            
    if (basicProfileDetails->name == NULL) {
        fprintf(stderr, "Memory allocation failed. No name input detected\n");
        free(basicProfileDetails);
        return;
    }

    //Storing date
    basicProfileDetails->creationDate = getCurrentDate();

    //Storing content
    char content[limit];
    printf("Enter content \n");
    scanf("%s", content);
    basicProfileDetails->content = strdup(content);


    switch(type){
        case 1:{ //individual
            individual *individual_profile;
            individual_profile = (individual *)malloc(sizeof(individual));

            //Storing it in 'individuals' list
            individual_list[individual_count] = individual_profile;

            //Creating and assigning an unique ID
            individual_profile->ind.id = createID(type);

            //Storing name
            individual_profile->ind.name = basicProfileDetails->name;

            //Storing Creation Date
            individual_profile->ind.creationDate = basicProfileDetails->creationDate;

            //Storing content
            individual_profile->ind.content = basicProfileDetails->content;

            //Storing birthday
            while(1){
                char choice;
                printf("\nWould you like to add your birthdate to your profile? \n Enter 'y' for yes and 'n' for no\n");
                scanf(" %c",&choice);
                if(choice == 'y' || choice == 'Y'){
                    date birthDay;
                    int day,month,year;
                    printf("Enter day : \n");
                    scanf("%d", &day);
                    printf("Enter month: \n");
                    scanf("%d", &month);
                    printf("Enter year: \n");
                    scanf("%d", &year);
                    int currYear = basicProfileDetails->creationDate.year;
                    if(day>31 || day< 1 || month<1 || month>12 || year> currYear || year < 1 ){
                        printf("Enter a valid birthdate! \n");
                        continue;
                    }
                    else {
                        birthDay.day = day;
                        birthDay.month = month;
                        birthDay.year = year;

                        individual_profile->birthday = birthDay;
                        break;
                    }
                    

                }
                else if(choice == 'n' || choice == 'N'){
                    break;
                }
                else {
                    printf("\nInvalid input choice\n");
                    continue;
                }
            }


            break;
        }
        case 2:{ //business
            business *biz_profile;
            biz_profile = (business *)malloc(sizeof(business));

            biz_list[biz_count] = biz_profile;

            biz_profile->biz.id = createID(type);

            biz_profile->biz.name = basicProfileDetails->name;

            biz_profile->biz.creationDate = basicProfileDetails->creationDate;

            biz_profile->biz.content = basicProfileDetails->content;

            printf("\nEnter location coordinates of the business\n");
            printf("Enter x coordinates: ");
            float x,y;
            scanf("%f", &x);
            printf("Enter y coordinates: ");
            scanf("%f", &y);

            biz_profile->location.x = x;
            biz_profile->location.y = y;

            
            printf("How many owners does this business have?");
            int ownerCount;
            scanf("%d", ownerCount);
            for(int i=1;i<=ownerCount;i++){
                char ownerName[limit];
                printf("Enter the name of the owner %d :\n", i);
                scanf("%s", ownerName);
                //------------------------------------searchEntity(1, ownerName);
                
            }
            

            

            

            break;
        }
        case 3:{
            group *grp_profile;
            grp_profile = (group *)malloc(sizeof(group));

            grp_list[grp_count] = grp_profile;

            grp_profile->grps.id= createID(type);

            grp_profile->grps.name = basicProfileDetails->name;

            grp_profile->grps.creationDate = basicProfileDetails->creationDate;

            grp_profile->grps.content = basicProfileDetails->content;
            
            break;
        }
        case 4:{
            organisation *org_profile;
            org_profile = (organisation *)malloc(sizeof(organisation));

            org_list[org_count] = org_profile;

            org_profile->org.id = createID(type);

            org_profile->org.name = basicProfileDetails->name;

            org_profile->org.creationDate = basicProfileDetails->creationDate;

            printf("\nEnter location coordinates of the business\n");
            printf("Enter x coordinates: ");
            float x,y;
            scanf("%f", &x);
            printf("Enter y coordinates: ");
            scanf("%f", &y);

            org_profile->location.x = x;
            org_profile->location.y = y;

            org_profile->org.content = basicProfileDetails->content;

            break;
        }
        default: {
            printf("Invalid input!");
            return;
        }
    }
    return;
}

int main(){
    int type;
    printf("What type of profile would you like to create ? : ");
    printf("\n(Enter the respective code)\n");
    displayOptions();
    
    scanf("%d", &type);
    createProfile(type);


    // printf("test name : %s", individual_list[0]->ind.name);



    
    


}

