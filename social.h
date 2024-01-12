#include <stdlib.h>

#define limit 1000

//GLOBAL VARIABLES
int individual_count=0;
int biz_count=0;
int grp_count=0;
int org_count=0;


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
    char *content;
    int links_id[4][limit];
}basic;

typedef struct coordinate{
    float x;
    float y;
}coords;

typedef struct individual_{
    basic ind;
    date birthday;
    
}individual;

typedef struct groups_{
    basic grps;

}group;

typedef struct business_{
    basic biz;
    coords location;
    
}business;

typedef struct organisation_{
    basic org;
    coords location;
    
}organisation;

//STRUCTURE ARRAYS
individual *individual_list[limit];
business *biz_list[limit];
group *grp_list[limit];
organisation *org_list[limit];
