#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

Data_t list_data[MAX_DATA_COUNT];
Data_t export_list_data[MAX_DATA_COUNT];
char header[8][100];
int data_count = 0;

static void print_data(Data_t* data) {
    printf("%-30s %-15s %-10d %-8d %-10d %-10d %-10s %-15s\n",
           data->location, data->city, data->price, data->rooms,
           data->bathroom, data->park, data->type, data->furnish);
}

static void print_header(void) {
    printf("%-30s %-15s %-10s %-8s %-10s %-10s %-10s %-15s\n",
           header[0], header[1], header[2], header[3],
           header[4], header[5], header[6], header[7]);
}

static void init_mem(Data_t* list, size_t size) {
    int i;
    for (i = 0; i < size; i++) list[i].price = -1;
}

static void swap(Data_t* a, Data_t* b) {
    Data_t buffer = *a;
    *a = *b;
    *b = buffer;
}

static int get_column_id(void) {
    char col[100];
    fflush(stdin);
    printf("Choose column: ");
    gets(col);

    int len = strlen(col);
    if (!strcmp(col, header[SEARCH_LOCATION])) {
        return SEARCH_LOCATION;
    } else if (!strcmp(col, header[SEARCH_CITY])) {
        return SEARCH_CITY;
    } else if (!strcmp(col, header[SEARCH_PRICE])) {
        return SEARCH_PRICE;
    } else if (!strcmp(col, header[SEARCH_ROOMS])) {
        return SEARCH_ROOMS;
    } else if (!strcmp(col, header[SEARCH_BATHROOM])) {
        return SEARCH_BATHROOM;
    } else if (!strcmp(col, header[SEARCH_PARK])) {
        return SEARCH_PARK;
    } else if (!strcmp(col, header[SEARCH_TYPE])) {
        return SEARCH_TYPE;
    } else if (!strcmp(col, header[SEARCH_FURNISH])) {
        return SEARCH_FURNISH;
    }

    printf("Please input valid column.\n");
    return -1;
}

static bool match_location(Data_t* data, const char* location) {
    return !strcmp(data->location, location);
}

static bool match_city(Data_t* data, const char* city) {
    return !strcmp(data->city, city);
}

static bool match_price(Data_t* data, const int price) {
    return (data->price == price);
}

static bool match_rooms(Data_t* data, const int rooms) {
    return (data->rooms == rooms);
}

static bool match_bathroom(Data_t* data, const int bathroom) {
    return (data->bathroom == bathroom);
}

static bool match_park(Data_t* data, const int park) {
    return (data->park == park);
}

static bool match_type(Data_t* data, const char* type) {
    return !strcmp(data->type, type);
}

static bool match_furnish(Data_t* data, const char* furnish) {
    return !strcmp(data->furnish, furnish);
}

static int search_string(Data_t* dest, MatchStrFunction match) {
    char str[100];
    fflush(stdin);
    gets(str);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (match(&list_data[i], str)) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_integer(Data_t* dest, MatchIntFunction match) {
    int num;
    fflush(stdin);
    scanf("%d", &num);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (match(&list_data[i], num)) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static bool compare_location(Data_t* a, Data_t* b) {
    return (strcmp(b->location, a->location) > 0);
}

static bool compare_city(Data_t* a, Data_t* b) {
    return (strcmp(b->city, a->city) > 0);
}

static bool compare_price(Data_t* a, Data_t* b) {
    return (a->price < b->price);
}

static bool compare_room(Data_t* a, Data_t* b) {
    return (a->rooms < b->rooms);
}

static bool compare_bathroom(Data_t* a, Data_t* b) {
    return (a->bathroom < b->bathroom);
}

static bool compare_park(Data_t* a, Data_t* b) {
    return (a->park < b->park);
}

static bool compare_type(Data_t* a, Data_t* b) {
    return (strcmp(b->type, a->type) > 0);
}

static bool compare_furnish(Data_t* a, Data_t* b) {
    return (strcmp(b->furnish, a->furnish) > 0);
}

static void bubble_sort(Data_t* data, size_t size, int order, CompareFunction comp) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (j = 0; j < size - i - 1; j++) {
            bool need_swap = order ? comp(&data[j], &data[j + 1]) : comp(&data[j + 1], &data[j]);
            if (need_swap) {
                swap(&data[j], &data[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

int display_data(void) {
    int target_row;
    printf("Number of rows: ");
    scanf("%d", &target_row);

    int i;
    print_header();
    for (i = 0; (i < target_row) && (list_data[i].price != -1); i++) print_data(&list_data[i]);
}

void search_data(void) {
    init_mem(export_list_data, data_count);
    int to_search = get_column_id();
    int found = 0;
    if (to_search != -1) printf("What data do you want to find? ");

    switch (to_search) {
        case SEARCH_LOCATION:
            found = search_string(export_list_data, match_location);
            break;
        case SEARCH_CITY:
            found = search_string(export_list_data, match_city);
            break;
        case SEARCH_PRICE:
            found = search_integer(export_list_data, match_price);
            break;
        case SEARCH_ROOMS:
            found = search_integer(export_list_data, match_rooms);
            break;
        case SEARCH_BATHROOM:
            found = search_integer(export_list_data, match_bathroom);
            break;
        case SEARCH_PARK:
            found = search_integer(export_list_data, match_park);
            break;
        case SEARCH_TYPE:
            found = search_string(export_list_data, match_type);
            break;
        case SEARCH_FURNISH:
            found = search_string(export_list_data, match_furnish);
            break;
    }

    if (found) {
        printf("Data found. Detail of data:\n");
        print_header();
        int i;
        for (i = 0; i < found; i++) print_data(&export_list_data[i]);
    } else {
        printf("Data not found!\n");
    }
}

void sort_data(void) {
    int n;
    for (n = 0; n < MAX_DATA_COUNT; n++) {
        export_list_data[n] = list_data[n];
    }

    int to_sort = get_column_id();
    if (to_sort == -1) return;

    printf("Sort ascending or descending? ");
    char order_str[10];
    scanf("%s", order_str);
    int order = (!strcmp(order_str, "asc")) ? SORT_ASCENDING : SORT_DESCENDING;

    switch (to_sort) {
        case SEARCH_LOCATION:
            bubble_sort(export_list_data, data_count, order, compare_location);
            break;
        case SEARCH_CITY:
            bubble_sort(export_list_data, data_count, order, compare_city);
            break;
        case SEARCH_PRICE:
            bubble_sort(export_list_data, data_count, order, compare_price);
            break;
        case SEARCH_ROOMS:
            bubble_sort(export_list_data, data_count, order, compare_room);
            break;
        case SEARCH_BATHROOM:
            bubble_sort(export_list_data, data_count, order, compare_bathroom);
            break;
        case SEARCH_PARK:
            bubble_sort(export_list_data, data_count, order, compare_park);
            break;
        case SEARCH_TYPE:
            bubble_sort(export_list_data, data_count, order, compare_type);
            break;
        case SEARCH_FURNISH:
            bubble_sort(export_list_data, data_count, order, compare_furnish);
            break;
        default:
            printf("Failed to sort data!\n");
            return;
    }

    print_header();
    int i;
    for (i = 0; i < 10; i++) print_data(&export_list_data[i]);
}

void export_data(void) {
    char buffer[100];
    fflush(stdin);
    printf("File name: ");
    gets(buffer);

    char fname[100];

#ifdef BUILT_USING_CMAKE
    sprintf(fname, "../%s.csv", buffer);
#else
    sprintf(fname, "%s.csv", buffer);
#endif  // BUILT_USING_CMAKE

    FILE* file = fopen(fname, "w");
    if (file == NULL) {
        printf("Failed to create %s file!\n", fname);
        return;
    }

    char header_line[1024];
    fprintf(file, "%s,%-15s,%-10s,%-8s,%-10s,%-10s,%-10s,%-15s\n",
            header[0], header[1], header[2], header[3],
            header[4], header[5], header[6], header[7]);
    fclose(file);
    file = fopen(fname, "a");

    int i;
    for (i = 0; i < data_count; i++) {
        if (export_list_data[i].price == -1) break;
        fprintf(file, "%s,%s,%d,%d,%d,%d,%s,%s\n",
                export_list_data[i].location, export_list_data[i].city, export_list_data[i].price,
                export_list_data[i].rooms, export_list_data[i].bathroom, export_list_data[i].park,
                export_list_data[i].type, export_list_data[i].furnish);
    }

    printf("Data successfully written to file %s!\n", fname);
    fclose(file);
}

void display_menu(void) {
    printf("What do you want to do?\n");
    printf("1. Display data\n");
    printf("2. Search Data\n");
    printf("3. Sort Data\n");
    printf("4. Export Data\n");
    printf("5. Exit\n");
    printf("Your choice: ");
}

void select_menu(int menu) {
    switch (menu) {
        case MENU_DISPLAY:
            display_data();
            break;
        case MENU_SEARCH:
            search_data();
            break;
        case MENU_SORT:
            sort_data();
            break;
        case MENU_EXPORT:
            export_data();
            break;
        case MENU_EXIT:
            printf("Exiting app.\n");
            break;
        default:
            printf("Please select valid menu.\n");
            break;
    }
}

bool load_file(const char* fname) {
    init_mem(list_data, MAX_DATA_COUNT);
    init_mem(export_list_data, MAX_DATA_COUNT);

    FILE* file = fopen(fname, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", fname);
        return false;
    }

    fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
           header[0], header[1], header[2], header[3],
           header[4], header[5], header[6], header[7]);

    sprintf(header[0], "Location");
    sprintf(header[1], "City");
    sprintf(header[4], "Bathroom");
    sprintf(header[5], "Carpark");

    int i = 0;
    while (fscanf(file, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%[^\n]\n",
                  list_data[i].location, list_data[i].city, &list_data[i].price,
                  &list_data[i].rooms, &list_data[i].bathroom, &list_data[i].park,
                  list_data[i].type, list_data[i].furnish) > 0) {
        data_count = ++i;
    }

    fclose(file);
    return true;
}

int main() {
#ifdef BUILT_USING_CMAKE
    if (!load_file("../file.csv")) return 1;
#else
    if (!load_file("file.csv")) return 1;
#endif  // BUILT_USING_CMAKE

    int input = 0;
    while (input != MENU_EXIT) {
        display_menu();
        scanf("%d", &input);
        fflush(stdin);
        select_menu(input);
    }

    return 0;
}