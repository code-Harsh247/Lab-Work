#include <stdlib.h>

#define limit 1000
#define typeIndividual 1
#define typeBusiness 2
#define typeGroup 3
#define typeOrganisation 4

struct individual_;
struct groups_;
struct business_;
struct organisation_;

//STRUCTURE DEFINATIONS
typedef struct Date{
    int day;
    int month;
    int year;
}date;

typedef struct basic_{
    int id;
    char *name;
    date creationDate;
    char *content[limit];
}basic;

typedef struct coordinate{
    float x;
    float y;
}coords;

typedef struct business_{
    basic biz;
    coords location;
    int ownerCount;
    int customerCount;
    struct individual_ *customers[limit];
    struct individual_ *owners[limit];
    struct group_ *memberOf[limit];
}business;

typedef struct groups_{
    basic grps;
    int indMemberCount;
    int bizMemberCount;
    struct individual_ *members[limit];
    struct business_ *bizMembers[limit];

}group;

typedef struct organisation_{
    basic org;
    coords location;
    int memberCount;
    struct individual_ *members[limit];
    
}organisation;

typedef struct individual_{
    basic ind;
    date birthday;
    group *linkedGrps[limit];
    business *ownerOf[limit];
    business *customerOf[limit];
    organisation *linkedOrg[limit];

}individual;

//STRUCTURE ARRAYS
individual *individual_list[limit];
business *biz_list[limit];
group *grp_list[limit];
organisation *org_list[limit];
