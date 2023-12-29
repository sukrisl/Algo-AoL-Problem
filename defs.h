#pragma once

#define MAX_DATA_COUNT 10000

#define MENU_DISPLAY 1
#define MENU_SEARCH 2
#define MENU_SORT 3
#define MENU_EXPORT 4
#define MENU_EXIT 5

#define SEARCH_LOCATION 0
#define SEARCH_CITY 1
#define SEARCH_PRICE 2
#define SEARCH_ROOMS 3
#define SEARCH_BATHROOM 4
#define SEARCH_PARK 5
#define SEARCH_TYPE 6
#define SEARCH_FURNISH 7

#define SORT_ASCENDING 0
#define SORT_DESCENDING 1

typedef struct {
    char location[100];
    char city[100];
    int price, rooms, bathroom, park;
    char type[100];
    char furnish[100];
} Data_t;

typedef bool (*CompareFunction)(Data_t* a, Data_t* b);
typedef bool (*MatchStrFunction)(Data_t* data, const char* str);
typedef bool (*MatchIntFunction)(Data_t* data, const int number);