#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "social.h"#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "social.h"

// GLOBAL VARIABLES
int individual_count = 0;
int biz_count = 0;
int grp_count = 0;
int org_count = 0;

void displayOptions(int option)
{
    for (int i = 0; i < 20; i++)
        printf("-");
    if (option == 2)
        printf("\n 1. Individual \n 2. Business \n 3. Group \n 4. Organisation \n ");
    if (option == 1)
        printf("\n 1. Create Profile \n 2. Delete Profile 3. \n Search for a Profile \n");
    for (int i = 0; i < 20; i++)
        printf("-");
    printf("\n");
}

int countDigits(int number)
{
    int count = 0;

    // Handle the case when the number is 0
    if (number == 0)
    {
        return 1; // 0 has one digit
    }

    // Count digits using a loop
    while (number != 0)
    {
        number = number / 10;
        count++;
    }

    return count;
}

int createID(int type)
{
    int output_id, digit_count = 0;
    switch (type)
    {
    case 1:
        digit_count = countDigits(individual_count);
        output_id = (int)pow(10, digit_count) + individual_count;
        individual_count++;
        break;

    case 2:
        digit_count = countDigits(biz_count);
        output_id = 2 * (int)pow(10, digit_count) + biz_count;
        biz_count++;
        break;

    case 3:
        digit_count = countDigits(grp_count);
        output_id = 3 * (int)pow(10, digit_count) + grp_count;
        grp_count++;
        break;

    case 4:
        digit_count = countDigits(org_count);
        output_id = 4 * (int)pow(10, digit_count) + org_count;
        org_count++;
        break;

    default:
        return -1;
    }

    return output_id;
}

int isNumberInArray(int *array, int size, int number)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == number)
        {
            return 1; // Number found in the array
        }
    }
    return 0; // Number not found in the array
}

int removeFirstDigit(int num)
{
    int temp = num;
    int numDigits = countDigits(num);

    // Remove the first digit
    int divisor = 1;
    for (int i = 1; i < numDigits; i++)
    {
        divisor *= 10;
    }

    int result = (num % divisor);

    return result;
}

individual *getIndividualById(int id)
{
    int serialNum = removeFirstDigit(id);
    return individual_list[serialNum];
}

business *getBizById(int id)
{
    int serialNum = removeFirstDigit(id);
    return biz_list[serialNum];
}

organisation *getOrgById(int id)
{
    int serialNum = removeFirstDigit(id);
    return org_list[serialNum];
}

group *getGrpById(int id)
{
    int serialNum = removeFirstDigit(id);
    return grp_list[serialNum];
}

void searchProfile(int type, char *targetName, int *resultCount, int **resultIds)
{

    *resultCount = 0;
    switch (type)
    {
    case typeIndividual:
    {
        for (int i = 0; i < individual_count; i++)
        {
            if (strcmp(individual_list[i]->ind.name, targetName) == 0)
            {
                (*resultCount)++;
                *resultIds = realloc(*resultIds, (*resultCount) * sizeof(int));

                (*resultIds)[(*resultCount) - 1] = individual_list[i]->ind.id;
            }
        }
        break;
    }
    case typeBusiness:
    {
        for (int i = 0; i < biz_count; i++)
        {
            if (strcmp(biz_list[i]->biz.name, targetName) == 0)
            {
                (*resultCount)++;
                *resultIds = realloc(*resultIds, (*resultCount) * sizeof(int));

                (*resultIds)[(*resultCount) - 1] = biz_list[i]->biz.id;
            }
        }
        break;
    }
    case typeGroup:
    {
        for (int i = 0; i < grp_count; i++)
        {
            if (strcmp(grp_list[i]->grps.name, targetName) == 0)
            {
                (*resultCount)++;
                *resultIds = realloc(*resultIds, (*resultCount) * sizeof(int));

                (*resultIds)[(*resultCount) - 1] = grp_list[i]->grps.id;
            }
        }
        break;
    }
    case typeOrganisation:
    {
        for (int i = 0; i < org_count; i++)
        {
            if (strcmp(org_list[i]->org.name, targetName) == 0)
            {
                (*resultCount)++;
                *resultIds = realloc(*resultIds, (*resultCount) * sizeof(int));

                (*resultIds)[(*resultCount) - 1] = org_list[i]->org.id;
            }
        }
        break;
    }
    default:
    {
        return;
        break;
    }
    }
}

date getCurrentDate()
{
    time_t currentDate;
    struct tm *localDate;
    date today;

    // Get the current date
    time(&currentDate);

    // Convert the current date to the local date
    localDate = localtime(&currentDate);

    // Populate the Date struct
    today.day = localDate->tm_mday;
    today.month = localDate->tm_mon + 1;    // tm_mon is 0-indexed, so add 1
    today.year = localDate->tm_year + 1900; // tm_year is years since 1900

    return today;
}

void displayMultipleIndividuals(int resultCount, int *resultIds)
{
    printf("Multiple individuals with the same name were found.\n");
    printf("Choose the correct user based on their details: \n");

    for (int j = 0; j < resultCount; j++)
    {
        individual *person = getIndividualById(resultIds[j]);
        for (int k = 0; k <= 20; k++)
            printf("--");
        printf("\n");
        printf("%d. Name - %s \n ID - %d\n", j + 1, person->ind.name, resultIds[j]);
        int day = person->ind.creationDate.day;
        int month = person->ind.creationDate.month;
        int year = person->ind.creationDate.year;
        int birthDay = person->birthday.day;
        int birthMonth = person->birthday.month;
        int birthYear = person->birthday.year;
        printf(" Profile Creation date: %d/%d/%d\n", day, month, year);
        printf(" Birthday : %d/%d/%d\n", birthDay, birthMonth, birthYear);
        for (int k = 0; k <= 20; k++)
            printf("--");
    }
}

void displayMultipleBusinesses(int resultCount, int *resultIds)
{
    printf("Multiple businesses under the same name were found:\n");
    printf("Choose the correct one based on their details: \n");

    for (int j = 0; j < resultCount; j++)
    {
        int businessId = resultIds[j];
        business *currentBusiness = getBizById(businessId);

        for (int k = 0; k <= 20; k++)
            printf("--");
        printf("\n");
        printf("%d. Business Details:\n", j + 1);
        printf("Name: %s\n", currentBusiness->biz.name);
        printf("ID: %d\n", currentBusiness->biz.id);
        printf("Creation Date: %d/%d/%d\n", currentBusiness->biz.creationDate.day,
               currentBusiness->biz.creationDate.month, currentBusiness->biz.creationDate.year);
        printf("Location: (%.2f, %.2f)\n", currentBusiness->location.x, currentBusiness->location.y);

        printf("Owners:\n");
        for (int k = 0; k < currentBusiness->ownerCount; k++)
        {
            printf("   %s\n", currentBusiness->owners[k]->ind.name);
        }
        free(currentBusiness->biz.name);
    }
}

void addIndividual(basic *basicProfileDetails)
{
    individual *individual_profile;
    individual_profile = (individual *)malloc(sizeof(individual));

    if (individual_profile == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Storing it in 'individuals' list
    individual_list[individual_count] = individual_profile;

    // Creating and assigning a unique ID
    individual_profile->ind.id = createID(typeIndividual);

    // Storing name
    individual_profile->ind.name = basicProfileDetails->name;

    // Storing Creation Date
    individual_profile->ind.creationDate = basicProfileDetails->creationDate;

    // Storing birthday
    while (true)
    {
        char choice;
        printf("\nWould you like to add your birthdate to your profile? \n Enter 'y' for yes and 'n' for no\n");
        scanf(" %c", &choice);
        date birthDay;
        if (choice == 'y' || choice == 'Y')
        {
            int day, month, year;
            printf("Enter day : \n");
            scanf("%d", &day);
            printf("Enter month: \n");
            scanf("%d", &month);
            printf("Enter year: \n");
            scanf("%d", &year);
            int currYear = basicProfileDetails->creationDate.year;
            if (day > 31 || day < 1 || month < 1 || month > 12 || year > currYear || year < 1)
            {
                printf("Enter a valid birthdate! \n");
                continue;
            }
            else
            {
                birthDay.day = day;
                birthDay.month = month;
                birthDay.year = year;

                individual_profile->birthday = birthDay;
                break;
            }
        }
        else if (choice == 'n' || choice == 'N')
        {
            birthDay.day = -1;
            birthDay.month = -1;
            birthDay.year = -1;
            individual_profile->birthday = birthDay;

            break;
        }
        else
        {
            printf("\nInvalid input choice\n");
            continue;
        }
    }
    printf("Individual profile added!\n");
}

void storeCustomers(business *biz_profile, int customerCount)
{
    if (customerCount < 0)
    {
        printf("Invalid input for customerCount\n");
        return;
    }

    for (int i = 0; i < customerCount; i++)
    {
        char customerName[limit];
        printf("Enter the name of customer %d:\n", i + 1);
        scanf("%s", customerName);

        int *resultIds = NULL;
        int resultCount;

        searchProfile(typeIndividual, customerName, &resultCount, &resultIds);

        if (resultCount == 0)
        {
            printf("No such customer found in the database! Add the customer into the database first.\n");
        }
        else if (resultCount == 1)
        {
            printf("Customer profile found in the database. Added %s as a customer.\n", customerName);
            // Search by ID, return pointer
            biz_profile->customers[i] = getIndividualById(resultIds[0]);
        }
        else
        {
            displayMultipleIndividuals(resultCount, resultIds);
            int sameNameCustomerCount;
            printf("How many of these are customers of this business?\n");
            scanf("%d", &sameNameCustomerCount);

            // Validate user input
            while (true)
            {
                if (sameNameCustomerCount < 0 || sameNameCustomerCount > resultCount)
                {
                    printf("Invalid input for sameNameCustomerCount\n");
                    continue;
                }
                else
                    break;
            }

            printf("Enter the id(s) of the customer(s) from the list:\n");
            for (int k = 0; k < sameNameCustomerCount; k++)
            {
                int id;
                // Validate the id and handle errors if necessary
                while (true)
                {
                    scanf("%d", &id);
                    if (isNumberInArray(resultIds, resultCount, id) == 1)
                    {
                        break;
                    }
                    else
                        continue;
                }

                biz_profile->customers[i] = getIndividualById(id);
                i++;
            }
            printf("Customers added!\n");
        }
        free(resultIds);
    }
}

void storeOwners(business *biz_profile, int ownerCount)
{
    for (int i = 0; i < ownerCount; i++)
    {
        char ownerName[limit];
        printf("Enter the name of the owner %d :\n", i + 1);
        scanf("%s", ownerName);

        int *resultIds = NULL;
        int resultCount;

        searchProfile(typeIndividual, ownerName, &resultCount, &resultIds);

        if (resultCount == 0)
        {
            printf("No such individual found in the database! Add the individual into the database first. \n");
        }
        else if (resultCount == 1)
        {
            printf("Individual Profile found in the database. Added %s as owner \n", ownerName);
            // Search by ID, return pointer
            biz_profile->owners[i] = getIndividualById(resultIds[0]);
        }
        else
        {
            displayMultipleIndividuals(resultCount, resultIds);
            int sameNameOwnerCount;
            while (true)
            {
                printf("How many of these are owners of this business? \n");
                scanf("%d", &sameNameOwnerCount);
                if (sameNameOwnerCount < 0 || sameNameOwnerCount > resultCount)
                {
                    printf("Invalid input for sameNameOwnerCount. Please give a valid input.\n");
                    continue;
                }
                else
                    break;
            }

            printf("Enter the id(s) of the owner(s) from the list : \n");
            for (int j = 0; j < sameNameOwnerCount; j++)
            {
                int id;

                while (true)
                {
                    scanf("%d", &id);
                    if (getIndividualById(id) == NULL)
                    {
                        printf("Invalid individual ID entered. Please try again.\n");
                        continue;
                    }
                    else
                        break;
                }

                biz_profile->owners[i] = getIndividualById(id);
                i++;
            }
            printf("Owners added!");
        }
        free(resultIds);
    }
}

void addBusiness(basic *basicProfileDetails)
{
    business *biz_profile;
    biz_profile = (business *)malloc(sizeof(business));

    if (biz_profile == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Storing it in 'business' list
    biz_list[biz_count] = biz_profile;

    // Creating and assigning a unique ID
    biz_profile->biz.id = createID(typeBusiness);

    // Storing name
    biz_profile->biz.name = basicProfileDetails->name;

    // Storing Creation Date
    biz_profile->biz.creationDate = basicProfileDetails->creationDate;

    // Storing location coordinates
    printf("\nEnter location coordinates of the business\n");
    printf("Enter x coordinates: ");
    float x, y;
    scanf("%f", &x);
    printf("Enter y coordinates: ");
    scanf("%f", &y);

    biz_profile->location.x = x;
    biz_profile->location.y = y;

    // Storing owners
    printf("How many owners does this business have?\n");
    int ownerCount;
    scanf("%d", &ownerCount);
    biz_profile->ownerCount = ownerCount;

    storeOwners(biz_profile, ownerCount);

    // Storing Customers
    int customerCount;
    printf("How many customers does this business have?\n");
    scanf("%d", &customerCount);

    storeCustomers(biz_profile, customerCount);

    printf("Business profile added!\n");
}

void storeGroupMembers(group *grp_profile, int memberCount)
{
    for (int i = 0; i < grp_profile->indMemberCount; i++)
    {
        char memberName[limit];
        printf("Enter the name of individual member %d:\n", i + 1);
        scanf("%s", memberName);

        int *resultIds = NULL;
        int resultCount;
        searchProfile(typeIndividual, memberName, &resultCount, &resultIds);

        if (resultCount == 0)
        {
            printf("No such individual found in the database! Add the individual into the database first. \n");
        }
        else if (resultCount == 1)
        {
            printf("Individual Profile found in the database. Added %s as owner \n", memberName);
            // Search by ID, return pointer
            grp_profile->members[i] = getIndividualById(resultIds[0]);
        }
        else
        {
            displayMultipleIndividuals(resultCount, resultIds);
            int sameNameMemberCount;
            printf("How many of these are members of this business? \n");
            scanf("%d", &sameNameMemberCount);
            printf("Enter the id(s) of the member(s) from the list : \n");
            for (int j = 0; j < sameNameMemberCount; j++)
            {
                int id;
                scanf("%d", &id);
                grp_profile->members[i] = getIndividualById(id);
                i++;
            }
            printf("Member(s) added!");
        }
        free(resultIds);
    }
}

void storeOrgMembers(organisation *org_profile, int memberCount)
{
    for (int i = 0; i < memberCount; i++)
    {
        char memberName[limit];
        printf("Enter the name of individual member %d:\n", i + 1);
        scanf("%s", memberName);

        int *resultIds = NULL;
        int resultCount;
        searchProfile(typeIndividual, memberName, &resultCount, &resultIds);

        if (resultCount == 0)
        {
            printf("No such individual found in the database! Add the individual into the database first.\n");
        }
        else if (resultCount == 1)
        {
            printf("Individual Profile found in the database. Added %s as a member.\n", memberName);
            // Search by ID, return pointer
            org_profile->members[i] = getIndividualById(resultIds[0]);
        }
        else
        {
            displayMultipleIndividuals(resultCount, resultIds);
            int sameNameMemberCount;
            printf("How many of these are members of this organization?\n");
            scanf("%d", &sameNameMemberCount);

            // Validate user input
            while (sameNameMemberCount < 0 || sameNameMemberCount > resultCount)
            {
                printf("Invalid input for sameNameMemberCount. Please give a valid input.\n");
                scanf("%d", &sameNameMemberCount);
            }

            printf("Enter the id(s) of the member(s) from the list:\n");
            for (int j = 0; j < sameNameMemberCount; j++)
            {
                int id;
                // Validate the id and handle errors if necessary
                while (true)
                {
                    scanf("%d", &id);
                    if (isNumberInArray(resultIds, resultCount, id) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("Invalid ID entered. Please try again.\n");
                    }
                }

                org_profile->members[i] = getIndividualById(id);
                i++;
            }
            printf("Members added!\n");
        }
        free(resultIds);
    }
}

void storeBizMembers(group *grp_profile, int bizMemberCount)
{
    for (int i = 0; i < grp_profile->bizMemberCount; i++)
    {
        char bizName[limit];
        printf("Enter the name of business %d:\n", i + 1);
        scanf("%s", bizName);

        int *resultIds = NULL;
        int resultCount;
        searchProfile(typeBusiness, bizName, &resultCount, &resultIds);

        if (resultCount == 0)
        {
            printf("No such business profile found in the database! Add the business into the database first. \n");
        }
        else if (resultCount == 1)
        {
            printf("Business Profile found in the database. Added %s as member \n", bizName);
            // Search by ID, return pointer
            grp_profile->bizMembers[i] = getBizById(resultIds[0]);
        }
        else
        {
            displayMultipleBusinesses(resultCount, resultIds);
            int sameNameBusinessCount;
            printf("How many of these are members of this business? \n");
            scanf("%d", &sameNameBusinessCount);
            printf("Enter the id(s) of the member(s) from the list : \n");
            for (int j = 0; j < sameNameBusinessCount; j++)
            {
                int id;
                scanf("%d", &id);
                grp_profile->bizMembers[i] = getBizById(id);
                i++;
            }
            printf("Member(s) added!");
        }
        free(resultIds);
    }
}

void addGroup(basic *basicProfileDetails)
{
    group *group_profile;
    group_profile = (group *)malloc(sizeof(group));

    if (group_profile == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Storing it in 'groups' list
    grp_list[grp_count] = group_profile;

    // Creating and assigning a unique ID
    group_profile->grps.id = createID(typeGroup);

    // Storing name
    group_profile->grps.name = strdup(basicProfileDetails->name);
    // Using strdup to duplicate the string and allocate memory for the group name

    // Storing Creation Date
    group_profile->grps.creationDate = basicProfileDetails->creationDate;

    // Storing individual members
    printf("How many members does this group have?\n");
    int memberCount;
    scanf("%d", &memberCount);
    group_profile->indMemberCount = memberCount;

    storeGroupMembers(group_profile, memberCount);

    // Storing business members
    int bizMemberCount;
    printf("How many businesses are a part of this group as members?\n");
    scanf("%d", &bizMemberCount);

    storeBizMembers(group_profile, bizMemberCount);

    printf("Business profile added!\n");
}

void addOrganisation(basic *basicProfileDetails)
{
    organisation *orgProfile;
    orgProfile = (organisation *)malloc(sizeof(organisation));

    if (orgProfile == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Storing it in 'organisations' list
    org_list[org_count] = orgProfile;

    // Creating and assigning a unique ID
    orgProfile->org.id = createID(typeOrganisation);

    // Storing name
    orgProfile->org.name = strdup(basicProfileDetails->name);

    // Storing Creation Date
    orgProfile->org.creationDate = basicProfileDetails->creationDate;

    // Storing location coordinates
    printf("\nEnter location coordinates of the organisation\n");
    printf("Enter x coordinates: ");
    float x, y;
    scanf("%f", &x);
    printf("Enter y coordinates: ");
    scanf("%f", &y);

    orgProfile->location.x = x;
    orgProfile->location.y = y;

    // Storing members
    printf("How many members does this organisation have?\n");
    int memberCount;
    scanf("%d", &memberCount);
    orgProfile->memberCount = memberCount;

    storeOrgMembers(orgProfile, memberCount);

    printf("Organisation profile added!\n");
}

void createProfile(int type)
{
    printf("\n----- Enter the required details -----\n ");

    basic *basicProfileDetails;
    basicProfileDetails = (basic *)malloc(sizeof(basic));

    char name[limit];

    // Entering Name
    printf("Enter Name : ");
    scanf("%s", name);
    basicProfileDetails->name = strdup(name);

    if (basicProfileDetails->name == NULL)
    {
        fprintf(stderr, "Memory allocation failed. No name input detected\n");
        free(basicProfileDetails);
        return;
    }

    // Storing date
    basicProfileDetails->creationDate = getCurrentDate();

    switch (type)
    {
    case typeIndividual:
    {
        addIndividual(basicProfileDetails);
        break;
    }

    case typeBusiness:
    {
        addBusiness(basicProfileDetails);
        break;
    }
    case typeGroup:
    {
        addGroup(basicProfileDetails);

        break;
    }
    case typeOrganisation:
    {
        addOrganisation(basicProfileDetails);
        break;
    }
    default:
    {
        printf("Invalid input!");
        return;
    }
    }
    return;
}

void deleteProfile()
{
    printf("Which type of profile would you like to delete?\n");
    printf("1. Individual\n");
    printf("2. Business\n");
    printf("3. Group\n");
    printf("4. Organization\n");

    int choice;
    scanf("%d", &choice);

    char profileName[limit];
    printf("Enter the name of the profile you want to delete:\n");
    scanf("%s", profileName);

    int *resultIds = NULL;
    int resultCount;

    // Search for profiles with the given name and type
    switch (choice)
    {
    case 1:
        searchProfile(typeIndividual, profileName, &resultCount, &resultIds);
        break;
    case 2:
        searchProfile(typeBusiness, profileName, &resultCount, &resultIds);
        break;
    case 3:
        searchProfile(typeGroup, profileName, &resultCount, &resultIds);
        break;
    case 4:
        searchProfile(typeOrganisation, profileName, &resultCount, &resultIds);
        break;
    default:
        printf("Invalid choice.\n");
        return;
    }

    if (resultCount == 0)
    {
        printf("No matching profile found.\n");
    }
    else if (resultCount == 1)
    {
        // Delete the single matching profile
        deleteProfileById(resultIds[0]);
        printf("Profile deleted successfully.\n");
    }
    else
    {
        // Display multiple matching profiles and let the user choose
        displayMultipleProfiles(resultCount, resultIds);
        int deleteChoice;
        printf("Enter the number corresponding to the profile you want to delete:\n");
        scanf("%d", &deleteChoice);

        if (deleteChoice >= 1 && deleteChoice <= resultCount)
        {
            // Delete the selected profile
            deleteProfileById(resultIds[deleteChoice - 1]);
            printf("Profile deleted successfully.\n");
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    free(resultIds);
}


void Create()
{
    int type;
    printf("What type of profile would you like to create ? : ");
    printf("\n(Enter the respective code)\n");
    displayOptions(2);

    scanf("%d", &type);
    createProfile(type);
}

int main()
{
    // while(1){
    printf("What would you like to do?\n");
    displayOptions(1);
    Create();

    // }

    // printf("test name : %s", individual_list[0]->ind.name);
}


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

