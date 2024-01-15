#include <stdio.h>
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

    displaySeparatorWithType(limit);
    if (option == 2)
        printf("\n 1. Individual \n 2. Business \n 3. Group \n 4. Organisation \n ");
    if (option == 1)
        printf("\n 1. Create Profile \n 2. Delete Profile \n 3. Search for a Profile \n 4. Print One-Hops \n 5. Create and Post Content\n 6. Search for content \n 7. Print Linked Individual");

    displaySeparatorWithType(limit);
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

    business *currentBusiness;

    for (int j = 0; j < resultCount; j++)
    {
        int businessId = resultIds[j];
        currentBusiness = getBizById(businessId);

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
        for (int k = 0; k <= 20; k++)
            printf("--");
    }
    free(currentBusiness->biz.name);
}

void displayMultipleGroups(int resultCount, int *resultIds)
{
    printf("Multiple groups under the same name were found:\n");
    printf("Choose the correct one based on their details: \n");

    group *currentGroup; // Declare outside the loop

    for (int j = 0; j < resultCount; j++)
    {
        int groupId = resultIds[j];
        currentGroup = getGrpById(groupId);

        for (int k = 0; k <= 20; k++)
            printf("--");
        printf("\n");
        printf("%d. Group Details:\n", j + 1);
        printf("Name: %s\n", currentGroup->grps.name);
        printf("ID: %d\n", currentGroup->grps.id);
        printf("Creation Date: %d/%d/%d\n", currentGroup->grps.creationDate.day,
               currentGroup->grps.creationDate.month, currentGroup->grps.creationDate.year);

        printf("Individual Members:\n");
        for (int k = 0; k < currentGroup->indMemberCount; k++)
        {
            printf("   %s\n", currentGroup->members[k]->ind.name);
        }

        printf("Business Members:\n");
        for (int k = 0; k < currentGroup->bizMemberCount; k++)
        {
            printf("   %s\n", currentGroup->bizMembers[k]->biz.name);
        }
        for (int k = 0; k <= 20; k++)
            printf("--");
    }

    // Free memory for the last group name outside the loop
    free(currentGroup->grps.name);
}

void displayMultipleOrganisations(int resultCount, int *resultIds)
{
    printf("Multiple organisations under the same name were found:\n");
    printf("Choose the correct one based on their details: \n");

    organisation *currentOrganisation; // Declare outside the loop

    for (int j = 0; j < resultCount; j++)
    {
        int orgId = resultIds[j];
        currentOrganisation = getOrgById(orgId);

        for (int k = 0; k <= 20; k++)
            printf("--");
        printf("\n");
        printf("%d. Organisation Details:\n", j + 1);
        printf("Name: %s\n", currentOrganisation->org.name);
        printf("ID: %d\n", currentOrganisation->org.id);
        printf("Creation Date: %d/%d/%d\n", currentOrganisation->org.creationDate.day,
               currentOrganisation->org.creationDate.month, currentOrganisation->org.creationDate.year);

        printf("Location: (%.2f, %.2f)\n", currentOrganisation->location.x, currentOrganisation->location.y);

        printf("Members:\n");
        for (int k = 0; k < currentOrganisation->memberCount; k++)
        {
            printf("   %s\n", currentOrganisation->members[k]->ind.name);
        }
        for (int k = 0; k <= 20; k++)
            printf("--");
    }

    // Free memory for the last organisation name outside the loop
    free(currentOrganisation->org.name);
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

    // Initialising Content Count
    individual_profile->ind.contentCount = 0;

    // Initialising Linked Group Count
    individual_profile->linkedGrpsCount = 0;

    // Initialising Linked Organisations Count
    individual_profile->linkedOrgsCount = 0;

    // Initialising Count of the businesses this individual owns
    individual_profile->ownerOfCount = 0;

    // Initialising Count of the businesses this individual is a customer of
    individual_profile->customerOfCount = 0;

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
            individual *person = getIndividualById(resultIds[0]);
            printf("Customer profile found in the database. Added %s as a customer.\n", customerName);
            // Search by ID, return pointer
            biz_profile->customers[i] = person;
            person->customerOf[person->customerOfCount] = biz_profile;
            person->customerOfCount++;
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
                individual *person = getIndividualById(id);
                biz_profile->customers[i] = person;
                person->customerOf[person->customerOfCount] = biz_profile;
                person->customerOfCount++;
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
            individual *person = getIndividualById(resultIds[0]);
            printf("Individual Profile found in the database. Added %s as owner \n", ownerName);
            // Search by ID, return pointer
            biz_profile->owners[i] = getIndividualById(resultIds[0]);
            person->ownerOf[person->ownerOfCount] = biz_profile;
            person->ownerOfCount++;
            ownerCount++;
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
                individual *person = getIndividualById(id);
                biz_profile->owners[i] = person;
                person->ownerOf[person->ownerOfCount] =  biz_profile;
                person->ownerOfCount++;
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
            individual *member = getIndividualById(resultIds[0]);
            grp_profile->members[i] = member;
            member->linkedGrps[member->linkedGrpsCount] = grp_profile;
            member->linkedGrpsCount++;
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
                individual *member = getIndividualById(id);
                grp_profile->members[i] = member;
                member->linkedGrps[member->linkedGrpsCount] = grp_profile;
                member->linkedGrpsCount++;
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
            individual *member = getIndividualById(resultIds[0]);
            printf("Individual Profile found in the database. Added %s as a member.\n", memberName);
            // Search by ID, return pointer
            org_profile->members[i] = getIndividualById(resultIds[0]);
            member->linkedOrgsCount++;
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
                individual *member = getIndividualById(id);
                org_profile->members[i] = getIndividualById(id);
                member->linkedOrgs[member->linkedOrgsCount] = org_profile;
                member->linkedOrgsCount++;
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
            business *biz = getBizById(resultIds[0]);
            printf("Business Profile found in the database. Added %s as member \n", bizName);
            // Search by ID, return pointer
            grp_profile->bizMembers[i] = biz;
            grp_profile->bizMemberCount++;
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
                business *biz = getBizById(id);
                grp_profile->bizMembers[i] = biz;
                grp_profile->bizMemberCount++;
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

    //Initialising
    group_profile->bizMemberCount = 0;
    group_profile->indMemberCount = 0;

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

    printf("Group profile added!\n");
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

    //Initialising
    orgProfile->memberCount = 0;

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

void deleteIndividual(int serialNum)
{
    if (individual_list[serialNum] != NULL)
    {
        free(individual_list[serialNum]);
        individual_list[serialNum] = NULL;
        printf("Individual profile at serial number %d deleted successfully.\n", serialNum);
    }
    else
    {
        printf("No individual profile found at serial number %d.\n", serialNum);
    }
}

void deleteBusiness(int serialNum)
{
    if (biz_list[serialNum] != NULL)
    {
        free(biz_list[serialNum]);
        biz_list[serialNum] = NULL;
        printf("Business profile at serial number %d deleted successfully.\n", serialNum);
    }
    else
    {
        printf("No business profile found at serial number %d.\n", serialNum);
    }
}

void deleteGroup(int serialNum)
{
    if (grp_list[serialNum] != NULL)
    {
        free(grp_list[serialNum]);
        grp_list[serialNum] = NULL;
        printf("Group profile at serial number %d deleted successfully.\n", serialNum);
    }
    else
    {
        printf("No group profile found at serial number %d.\n", serialNum);
    }
}

void deleteOrganisation(int serialNum)
{
    if (org_list[serialNum] != NULL)
    {
        free(org_list[serialNum]);
        org_list[serialNum] = NULL;
        printf("Organization profile at serial number %d deleted successfully.\n", serialNum);
    }
    else
    {
        printf("No organization profile found at serial number %d.\n", serialNum);
    }
}

void deleteProfileById(int id, int type)
{
    int serialNum = removeFirstDigit(id);
    switch (type)
    {
    case 1:
    {
        deleteIndividual(serialNum);
        break;
    }
    case 2:
    {
        deleteBusiness(serialNum);
        break;
    }
    case 3:
    {
        deleteGroup(serialNum);
        break;
    }
    case 4:
    {
        deleteOrganisation(serialNum);
        break;
    }
    }
}

void displayMultipleProfiles(int resultCount, int *resultIds, int choice)
{
    switch (choice)
    {
    case 1:
        displayMultipleIndividuals(resultCount, resultIds);
        break;
    case 2:
        displayMultipleBusinesses(resultCount, resultIds);
        break;
    case 3:
        displayMultipleGroups(resultCount, resultIds);
        break;
    case 4:
        displayMultipleOrganisations(resultCount, resultIds);
        break;
    }
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
        deleteProfileById(resultIds[0], choice);
        printf("Profile deleted successfully.\n");
    }
    else
    {
        // Display multiple matching profiles and let the user choose
        displayMultipleProfiles(resultCount, resultIds, choice);
        int deleteChoice;
        printf("Enter the number corresponding to the profile you want to delete:\n");
        scanf("%d", &deleteChoice);

        if (deleteChoice >= 1 && deleteChoice <= resultCount)
        {
            // Delete the selected profile
            deleteProfileById(resultIds[deleteChoice - 1], choice);
            printf("Profile deleted successfully.\n");
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    free(resultIds);
}

void listIndividuals()
{
    displaySeparatorWithType(typeIndividual);
    for (int i = 0; i < individual_count; i++)
    {
        printf("ID: %d, Name: %s\n", individual_list[i]->ind.id, individual_list[i]->ind.name);
    }
    displaySeparatorWithType(limit);
}

void listGroups()
{
    displaySeparatorWithType(typeGroup);
    for (int i = 0; i < grp_count; i++)
    {
        printf("ID: %d, Name: %s\n", grp_list[i]->grps.id, grp_list[i]->grps.name);
    }
    displaySeparatorWithType(limit);
}

void listOrganisations()
{
    displaySeparatorWithType(typeOrganisation);
    for (int i = 0; i < org_count; i++)
    {
        printf("ID: %d, Name: %s\n", org_list[i]->org.id, org_list[i]->org.name);
    }
    displaySeparatorWithType(limit);
}

void listBusinesses()
{
    printf("List of Businesses:\n");
    for (int i = 0; i < biz_count; i++)
    {
        printf("ID: %d, Name: %s, ", biz_list[i]->biz.id, biz_list[i]->biz.name);
        printf("Owners: ");
        for (int j = 0; j < biz_list[i]->ownerCount; j++)
        {
            if (biz_list[i]->owners[j] == NULL)
            {
                printf("none / Owner-profile might be deleted");
            }
            printf("%s, ", biz_list[i]->owners[j]->ind.name);
        }
    }
}

void displaySeparatorWithType(int profileType)
{
    const char *typeName;

    switch (profileType)
    {
    case typeIndividual:
        typeName = "INDIVIDUAL";
        break;
    case typeBusiness:
        typeName = "BUSINESS";
        break;
    case typeGroup:
        typeName = "GROUP";
        break;
    case typeOrganisation:
        typeName = "ORGANISATION";
        break;
    default:
        typeName = "";
    }

    int length = strlen(typeName);
    int totalWidth = 40; // Adjust as needed
    int remainingWidth = (totalWidth - length) / 2;

    printf("\n");
    for (int i = 0; i < remainingWidth; i++)
    {
        printf("*");
    }
    if (length != 0)
    {
        printf(" %s ", typeName);
    }
    else
        printf("**");

    for (int i = 0; i < remainingWidth; i++)
    {
        printf("*");
    }
    printf("\n");
}

void searchProfileByName(const char *name)
{
    printf("Search Results for \"%s\":\n", name);

    // Search and display individuals
    displaySeparatorWithType(typeIndividual);
    for (int i = 0; i < individual_count; i++)
    {
        if (strcmp(individual_list[i]->ind.name, name) == 0)
        {
            printf("ID: %d, Name: %s\n", individual_list[i]->ind.id, individual_list[i]->ind.name);
        }
    }

    // Search and display businesses
    displaySeparatorWithType(typeBusiness);
    for (int i = 0; i < biz_count; i++)
    {
        if (strcmp(biz_list[i]->biz.name, name) == 0)
        {
            printf("ID: %d, Name: %s\n", biz_list[i]->biz.id, biz_list[i]->biz.name);
        }
    }

    // Search and display groups
    displaySeparatorWithType(typeGroup);
    for (int i = 0; i < grp_count; i++)
    {
        if (strcmp(grp_list[i]->grps.name, name) == 0)
        {
            printf("ID: %d, Name: %s\n", grp_list[i]->grps.id, grp_list[i]->grps.name);
        }
    }

    // Search and display organisations
    displaySeparatorWithType(typeOrganisation);
    for (int i = 0; i < org_count; i++)
    {
        if (strcmp(org_list[i]->org.name, name) == 0)
        {
            printf("ID: %d, Name: %s\n", org_list[i]->org.id, org_list[i]->org.name);
        }
    }
}

void searchIndividualsByBirthday(const date birthday)
{
    printf("Search Results for Individuals with Birthday %d-%d-%d:\n",
           birthday.day, birthday.month, birthday.year);

    for (int i = 0; i < limit; i++)
    {
        if (individual_list[i] != NULL &&
            individual_list[i]->birthday.day == birthday.day &&
            individual_list[i]->birthday.month == birthday.month &&
            individual_list[i]->birthday.year == birthday.year)
        {
            // Display information for the matched individual
            printf("Individual ID: %d, Name: %s, Birthday: %d-%d-%d\n",
                   individual_list[i]->ind.id,
                   individual_list[i]->ind.name,
                   individual_list[i]->birthday.day,
                   individual_list[i]->birthday.month,
                   individual_list[i]->birthday.year);
        }
    }
}

void search()
{
    printf("How would like to search for a profile?\n");
    printf("1. By name \n 2. By type \n 3. By Birthday (for individuals only)\n");
    int searchType;
    scanf("%d", &searchType);

    switch (searchType)
    {
    case 1:
    {
        char name[limit];
        printf("Enter Name: ");
        scanf("%s", name);
        searchProfileByName(name);
        break;
        break;
    }
    case 2:
    {
        listProfiles();
        break;
    }
    case 3:
    {
        int day, month, year;
        while (true)
        {
            printf("Enter day : \n");
            scanf("%d", &day);
            printf("Enter month: \n");
            scanf("%d", &month);
            printf("Enter year: \n");
            scanf("%d", &year);
            int currYear = getCurrentDate().year;
            if (day > 31 || day < 1 || month < 1 || month > 12 || year > currYear || year < 1)
            {
                printf("Enter a valid birthdate! \n");
                continue;
            }
            else
                break;
        }
        date birthday;
        birthday.day = day;
        birthday.month = month;
        birthday.year = year;
        searchIndividualsByBirthday(birthday);
        break;
        break;
    }
    default:
        printf("Invalid input. Please provide an valid input \n");
        break;
    }
}

void listProfiles()
{
    printf("List of which type of profiles would you like to see?\n");
    displayOptions(2);
    int type;
    scanf("%d", &type);
    switch (type)
    {
    case 1:
    {
        listIndividuals();
        break;
    }
    case 2:
    {
        listBusinesses();
        break;
    }
    case 3:
    {
        listGroups();
        break;
    }
    case 4:
    {
        listOrganisations();
        break;
    }
    default:
    {
        printf("Invalid Input.\n");
    }
    }
}

void createContentForInd()
{
    int id;
    listIndividuals();
    printf("Enter ID of the individual for which you'd like to add content:\n");
    scanf("%d", &id);

    individual *person = getIndividualById(id);

    if (person != NULL)
    {
        char buffer[limit];
        printf("Individual found. Enter content: ");

        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Remove the trailing newline character
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
            {
                buffer[len - 1] = '\0';
            }

            // Dynamic memory allocation for content
            person->ind.content[person->ind.contentCount] = strdup(buffer);
            if (person->ind.content[person->ind.contentCount] != NULL)
            {
                // Increment the count of stored content
                person->ind.contentCount++;
                printf("Content added successfully\n");
            }
            else
            {
                printf("Memory allocation error\n");
            }
        }
        else
        {
            printf("Error reading input\n");
        }
    }
    else
    {
        printf("Invalid individual or ID\n");
    }
}

void createContentForBiz()
{
    int id;
    listBusinesses();
    printf("Enter ID of the business for which you'd like to add content:\n");
    scanf("%d", &id);

    business *biz = getBizById(id);

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    if (biz != NULL)
    {
        char buffer[limit];
        printf("Business found. Enter content: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Remove the trailing newline character
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
            {
                buffer[len - 1] = '\0';
            }

            // Dynamic memory allocation for content
            biz->biz.content[biz->biz.contentCount] = strdup(buffer);
            if (biz->biz.content[biz->biz.contentCount] != NULL)
            {
                // Increment the count of stored content
                biz->biz.contentCount++;
                printf("Content added successfully\n");
            }
            else
            {
                printf("Memory allocation error\n");
            }
        }
        else
        {
            printf("Error reading input\n");
        }
    }
    else
    {
        printf("Invalid Business or ID\n");
    }
}

void createContentForGrp()
{
    int id;
    listGroups();
    printf("Enter ID of the group for which you'd like to add content:\n");
    scanf("%d", &id);

    group *grp = getGrpById(id);

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    if (grp != NULL)
    {
        char buffer[limit];
        printf("Group found. Enter content: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Remove the trailing newline character
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
            {
                buffer[len - 1] = '\0';
            }

            // Dynamic memory allocation for content
            grp->grps.content[grp->grps.contentCount] = strdup(buffer);
            if (grp->grps.content[grp->grps.contentCount] != NULL)
            {
                // Increment the count of stored content
                grp->grps.contentCount++;
                printf("Content added successfully\n");
            }
            else
            {
                printf("Memory allocation error\n");
            }
        }
        else
        {
            printf("Error reading input\n");
        }
    }
    else
    {
        printf("Invalid Business or ID\n");
    }
}

void createContentForOrg()
{
    int id;
    listOrganisations();
    printf("Enter ID of the Organisation for which you'd like to add content:\n");
    scanf("%d", &id);

    organisation *org = getOrgById(id);

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    if (org != NULL)
    {
        char buffer[limit];
        printf("Organisation found. Enter content: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Remove the trailing newline character
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
            {
                buffer[len - 1] = '\0';
            }

            // Dynamic memory allocation for content
            org->org.content[org->org.contentCount] = strdup(buffer);
            if (org->org.content[org->org.contentCount] != NULL)
            {
                // Increment the count of stored content
                org->org.contentCount++;
                printf("Content added successfully\n");
            }
            else
            {
                printf("Memory allocation error\n");
            }
        }
        else
        {
            printf("Error reading input\n");
        }
    }
    else
    {
        printf("Invalid Business or ID\n");
    }
}

void createContentForType(int type)
{
    switch (type)
    {
    case 1:
    {
        createContentForInd();
        break;
    }
    case 2:
    {
        createContentForBiz();
        break;
    }
    case 3:
    {
        createContentForGrp();
        break;
    }
    case 4:
    {
        createContentForOrg();
        break;
    }
    default:
    {
        printf("Invalid input");
        break;
    }
    }
}

void createContent()
{
    printf("Enter the type of profile for which you'll like to add content.\n");
    displayOptions(2);
    int type;
    scanf("%d", &type);
    createContentForType(type);
}

void searchProfilesBySubstring(char *substring)
{
    printf("Search Results for Substring '%s':\n", substring);

    // Search in individual profiles
    for (int i = 0; i < individual_count; i++)
    {
        for (int j = 0; i < individual_list[i]->ind.contentCount; j++)
        {
            if (strstr(individual_list[i]->ind.content[j], substring) != NULL)
            {
                printf("Individual ID: %d, Name: %s\n", individual_list[i]->ind.id, individual_list[i]->ind.name);
                printf("Full Content: %s\n\n", individual_list[i]->ind.content[j]);
            }
        }
    }

    // Search in business profiles
    for (int i = 0; i < biz_count; i++)
    {
        for (int j = 0; j < biz_list[i]->biz.contentCount; j++)
        {
            if (strstr(biz_list[i]->biz.content[j], substring) != NULL)
            {
                printf("Business ID: %d, Name: %s\n", biz_list[i]->biz.id, biz_list[i]->biz.name);
                printf("Full Content: %s\n\n", biz_list[i]->biz.content[j]);
            }
        }
    }

    // Search in group profiles
    for (int i = 0; i < grp_count; i++)
    {
        for (int j = 0; j < grp_list[i]->grps.contentCount; j++)
        {
            if (strstr(grp_list[i]->grps.content[j], substring) != NULL)
            {
                printf("Group ID: %d, Name: %s\n", grp_list[i]->grps.id, grp_list[i]->grps.name);
                printf("Full Content: %s\n\n", grp_list[i]->grps.content[j]);
            }
        }
    }

    // Search in organization profiles
    for (int i = 0; i < org_count; i++)
    {
        for (int j = 0; j < org_list[i]->org.contentCount; j++)
        {
            if (strstr(org_list[i]->org.content[j], substring) != NULL)
            {
                printf("Organization ID: %d, Name: %s\n", org_list[i]->org.id, org_list[i]->org.name);
                printf("Full Content: %s\n\n", org_list[i]->org.content[j]);
            }
        }
    }
}

void searchContent()
{
    printf("Enter substring to search for content:\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    char buffer[limit];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // Remove the trailing newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        searchProfilesBySubstring(buffer);
    }
}

void getSameGroupOrOrgIndividuals(individual *person)
{
    if (person != NULL)
    {
        printf("Individual ID: %d, Name: %s\n", person->ind.id, person->ind.name);
        printf("Sharing same group and/or organization with:\n");

        // Check for individuals in the same group
        for (int i = 0; i < person->linkedGrpsCount; i++)
        {
            group *grp = person->linkedGrps[i];
            for (int j = 0; j < grp->indMemberCount; j++)
            {
                if (grp->members[j] != person)
                {
                    printf("ID: %d, Name: %s\n", grp->members[j]->ind.id, grp->members[j]->ind.name);
                }
            }
        }

        // Check for individuals in the same organization
        for (int i = 0; i < person->linkedOrgsCount; i++)
        {
            organisation *org = person->linkedOrgs[i];
            for (int j = 0; j < org->memberCount; j++)
            {
                if (org->members[j] != person)
                {
                    printf("ID: %d, Name: %s\n", org->members[j]->ind.id, org->members[j]->ind.name);
                }
            }
        }
    }
    else
    {
        printf("Invalid individual\n");
    }
}

void searchForLinkedIndividuals()
{
    char name[limit];
    printf("Enter the name of the individual:\n");
    scanf("%s", name);

    int *resultIds = NULL;
    int resultCount;

    searchProfile(typeIndividual, name, &resultCount, &resultIds);

    if (resultCount == 0)
    {
        printf("No such individual found in the database! Add the individual into the database first. \n");
    }
    else if (resultCount == 1)
        {
            printf("Individual Profile found in the database");
            // Search by ID, return pointer
            getSameGroupOrOrgIndividuals(getIndividualById(resultIds[0]));
        }
        else{
            displayMultipleIndividuals(resultCount, resultIds);
            printf("Enter the id of the owner(s) from the list : \n");
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
            individual *person = getIndividualById(id);
            getSameGroupOrOrgIndividuals(person);   
        }
    
}

void printLinksForInd() {
    int id;
    listIndividuals(); 
    printf("Enter ID of the individual for which you'd like to print links:\n");
    scanf("%d", &id);

    individual *person = NULL;

    // Search for the individual with the specified ID
    for (int i = 0; i < individual_count; i++) {
        if (individual_list[i] != NULL && individual_list[i]->ind.id == id) {
            person = individual_list[i];
            break;
        }
    }

    if (person != NULL) {
        displaySeparatorWithType(limit);
        printf("Links for Individual ID: %d, Name: %s\n", person->ind.id, person->ind.name);

        // Print links to groups
        displaySeparatorWithType(typeGroup);
        for (int i = 0; i < person->linkedGrpsCount; i++) {
            printf("- Group ID: %d, Name: %s\n", person->linkedGrps[i]->grps.id, person->linkedGrps[i]->grps.name);
        }

        displaySeparatorWithType(typeOrganisation);
        for (int i = 0; i < person->linkedOrgsCount; i++) {
            printf("- Organization ID: %d, Name: %s\n", person->linkedOrgs[i]->org.id, person->linkedOrgs[i]->org.name);
        }

        //Print owned businesses
        displaySeparatorWithType(typeBusiness);
        printf("Businesses owned:\n");
        for(int i=0;i<person->ownerOfCount;i++){
            printf("- Business ID: %d, Name: %s\n", person->ownerOf[i]->biz.id, person->ownerOf[i]->biz.name);
        }
        printf("\nCustomer to \n");
        for(int i=0;i<person->customerOfCount;i++){
            printf("- Business ID: %d, Name: %s\n", person->customerOf[i]->biz.id, person->customerOf[i]->biz.name);
        }


    } else {
        printf("Individual not found.\n");
    }
}

void printLinksForBiz() {
    int id;
    listBusinesses(); // Assuming this function lists all profiles
    printf("Enter ID of the business for which you'd like to print links:\n");
    scanf("%d", &id);

    business *biz = NULL;

    // Search for the business with the specified ID
    for (int i = 0; i < limit; i++) {
        if (biz_list[i] != NULL && biz_list[i]->biz.id == id) {
            biz = biz_list[i];
            break;
        }
    }

    if (biz != NULL) {
        displaySeparatorWithType(typeIndividual);
        printf("Customers of Business ID: %d, Name: %s\n", biz->biz.id, biz->biz.name);

        // Print links to individual customers
        for (int i = 0; i < biz->customerCount; i++) {
            printf("- Individual ID: %d, Name: %s\n", biz->customers[i]->ind.id, biz->customers[i]->ind.name);
        }

        printf("Owners of Business ID: %d, Name: %s\n", biz->biz.id, biz->biz.name);

        // Print links to individual owners
        for (int i = 0; i < biz->ownerCount; i++) {
            printf("- Individual ID: %d, Name: %s\n", biz->owners[i]->ind.id, biz->owners[i]->ind.name);
        }

        displaySeparatorWithType(typeGroup);
        printf("Member groups of Business ID: %d, Name: %s\n", biz->biz.id, biz->biz.name);

        // Print links to groups
        for (int i = 0; i < biz->memberOfCount; i++) {
            printf("- Group ID: %d, Name: %s\n", biz->memberOf[i]->grps.id, biz->memberOf[i]->grps.name);
        }
    } else {
        printf("Business not found.\n");
    }
}

void printLinksForGrp() {
    int id;
    listGroups(); // Assuming this function lists all profiles
    printf("Enter ID of the group for which you'd like to print links:\n");
    scanf("%d", &id);

    group *grp = NULL;

    // Search for the group with the specified ID
    for (int i = 0; i < limit; i++) {
        if (grp_list[i] != NULL && grp_list[i]->grps.id == id) {
            grp = grp_list[i];
            break;
        }
    }

    if (grp != NULL) {
        displaySeparatorWithType(typeIndividual);
        printf("Members of Group ID: %d, Name: %s\n", grp->grps.id, grp->grps.name);

        // Print links to individual members
        for (int i = 0; i < grp->indMemberCount; i++) {
            printf("- Individual ID: %d, Name: %s\n", grp->members[i]->ind.id, grp->members[i]->ind.name);
        }

        displaySeparatorWithType(typeBusiness);
        printf("Member businesses of Group ID: %d, Name: %s\n", grp->grps.id, grp->grps.name);

        // Print links to businesses
        for (int i = 0; i < grp->bizMemberCount; i++) {
            printf("- Business ID: %d, Name: %s\n", grp->bizMembers[i]->biz.id, grp->bizMembers[i]->biz.name);
        }
    } else {
        printf("Group not found.\n");
    }
}

void printLinksForOrg() {
    int id;
    listOrganisations(); // Assuming this function lists all profiles
    printf("Enter ID of the organization for which you'd like to print links:\n");
    scanf("%d", &id);

    organisation *org = NULL;

    // Search for the organization with the specified ID
    for (int i = 0; i < limit; i++) {
        if (org_list[i] != NULL && org_list[i]->org.id == id) {
            org = org_list[i];
            break;
        }
    }

    if (org != NULL) {
        displaySeparatorWithType(typeIndividual);
        printf("Members of Organization ID: %d, Name: %s\n", org->org.id, org->org.name);

        // Print links to individual members
        for (int i = 0; i < org->memberCount; i++) {
            printf("- Individual ID: %d, Name: %s\n", org->members[i]->ind.id, org->members[i]->ind.name);
        }
    } else {
        printf("Organization not found.\n");
    }
}

void printLinksForType(int type){
    switch (type) {
    case typeIndividual:
        printLinksForInd();
        break;
    case typeBusiness:
        printLinksForBiz();
        break;
    case typeGroup:
        printLinksForGrp();
        break;
    case typeOrganisation:
        // printLinksForOrg();
        break;
    default:
        printf("Invalid input");
        break;
}

}

void oneHopLinks(){
    printf("Enter the type of profile for which you'll like to print links.\n");
    displayOptions(2);
    int type;
    scanf("%d", &type);
    printLinksForType(type);
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
    int choice;
    while (true)
    {
        printf("What would you like to do?\n");
        displayOptions(1);
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            Create();
            break;
        }
        case 2:
        {
            deleteProfile();
            break;
        }
        case 3:
        {
            search();
            break;
        }
        case 4:
        {
            oneHopLinks();
            break;
        }
        case 5:
        {
            createContent();
            break;
        }
        case 6:
        {
            searchContent();
            break;
        }
        case 7:
        {
            searchForLinkedIndividuals();
            break;
        }
        default:
        {
            printf("Invalid input. Please provide an input from the given options.");
            continue;
        }
        }
    }

    // printf("test name : %s", individual_list[0]->ind.name);
}
