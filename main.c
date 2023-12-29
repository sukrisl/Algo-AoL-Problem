#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int search_by_location(Data_t* dest) {
    char location[100];
    fflush(stdin);
    gets(location);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (!strcmp(list_data[i].location, location)) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_by_city(Data_t* dest) {
    char city[100];
    fflush(stdin);
    gets(city);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (!strcmp(list_data[i].city, city)) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_by_price(Data_t* dest) {
    int price;
    fflush(stdin);
    scanf("%d", &price);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (list_data[i].price == price) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_by_rooms(Data_t* dest) {
    int rooms;
    fflush(stdin);
    scanf("%d", &rooms);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (list_data[i].rooms == rooms) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_by_bathroom(Data_t* dest) {
    int bathroom;
    fflush(stdin);
    scanf("%d", &bathroom);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (list_data[i].bathroom == bathroom) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_by_park(Data_t* dest) {
    int park;
    fflush(stdin);
    scanf("%d", &park);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (list_data[i].park == park) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_by_type(Data_t* dest) {
    char type[100];
    fflush(stdin);
    gets(type);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (!strcmp(list_data[i].type, type)) {
            dest[found++] = list_data[i];
        }
    }
    return found;
}

static int search_by_furnish(Data_t* dest) {
    char furnish[100];
    fflush(stdin);
    gets(furnish);

    int i, found = 0;
    for (i = 0; list_data[i].price != -1 && i < data_count; i++) {
        if (!strcmp(list_data[i].furnish, furnish)) {
            dest[found++] = list_data[i];
        }
    }
    return found;
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
            found = search_by_location(export_list_data);
            break;
        case SEARCH_CITY:
            found = search_by_city(export_list_data);
            break;
        case SEARCH_PRICE:
            found = search_by_price(export_list_data);
            break;
        case SEARCH_ROOMS:
            found = search_by_rooms(export_list_data);
            break;
        case SEARCH_BATHROOM:
            found = search_by_bathroom(export_list_data);
            break;
        case SEARCH_PARK:
            found = search_by_park(export_list_data);
            break;
        case SEARCH_TYPE:
            found = search_by_type(export_list_data);
            break;
        case SEARCH_FURNISH:
            found = search_by_furnish(export_list_data);
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
        // case SEARCH_LOCATION:
        //     sort_by_location(export_list_data, order);
        //     break;
        // case SEARCH_CITY:
        //     sort_by_city(export_list_data, order);
        //     break;
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
        // case SEARCH_TYPE:
        //     sort_by_type(export_list_data, order);
        //     break;
        // case SEARCH_FURNISH:
        //     sort_by_furnish(export_list_data, order);
        //     break;
        default:
            printf("Failed to sort data!\n");
            return;
    }

    print_header();
    int i;
    for (i = 0; i < 100; i++) print_data(&export_list_data[i]);
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