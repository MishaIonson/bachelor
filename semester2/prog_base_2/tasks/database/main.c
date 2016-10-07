#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "driver.h"
#define FILE_NAME "driver.db"

void print_driver_count(des_db_t * db);
void print_driver(driver_t * d);
void one_record_test(des_db_t * db);

int main(void)
{
    des_db_t * db = des_db_new(FILE_NAME);
    one_record_test(db);
    puts("Getting k drivers with criteria: way");
    size_t count = 0;
    driver * driver = des_db_get_filtered_designers(db, 5, 15000.0F, &count);
    printf("\nThere are %i \n", count);
    if(count > 0)
    {
        puts("Printing them ...");
        for(int i = 0; i < count; i++)
        {
            print_driver(driver + i);
        }
    }
    free(driver);
    des_db_delete(db);
    return EXIT_SUCCESS;
}
void one_record_test(des_db_t * db)
{
    puts("Getting the drivers count ...");
    print_driver_count(db);
    struct tm tm_time = {.tm_mday = 20, .tm_mon = 4 - 1, .tm_year = 2012 - 1900};
    time_t time = mktime(&tm_time);
    driver_t des1 = {.id = 3, .name = "Peter", .surname = "Bayleish", .averageVertices = 3.14, .experience = 10, .hireDate = time, .salary = 1005.00, .projectsCount = 100};
    puts("\nAdding a record ... ");
    des_db_add_designer(db, &des1);

    puts("\nGetting the designers count ...");
    print_driver_count(db);

    puts("\nGetting the record ... ");
    driver * des1_get = des_db_get_designer(db, 3);
    print_designer(des1_get);
    free(des1_get);

    puts("\nChanging the record's averageVertices to 3.15 ... ");
    des1.averageVertices = 3.15;
    des_db_update_designer(db, &des1);

    puts("\nGetting the record ... ");
    driver * des2 = des_db_get_designer(db, 3);
    print_designer(des2);
    free(des2);

    puts("\nDeleting the record ... ");
    des_db_delete_designer(db, 3);

    puts("\nGetting the designers count ...");
    print_driver_count(db);
}
void print_driver(driver_t * driver)
{
    puts("Driver");
    printf("\t %-18s: %-10i\n", "ID", driver->id);
    printf("\t %-18s: %-10s\n", "NAME", driver->name);
    printf("\t %-18s: %-10s\n", "SURNAME", driver->surname);
    printf("\t %-18s: %-10i\n", "WAY", driver->way);
    printf("\t %-18s: %-8.2f\n", "SALARY", driver->salary);
    struct tm * birthday = gmtime(&(driver->birthday));
    char time[10];
    sprintf(time, "%i-%i-%i", birthday->tm_year + 1900, birthday->tm_mon + 1, birthday->tm_mday);
    printf("\t %-18s: %-10s\n", "Birthday", time);
}
void print_driver_count(des_db_t * db)
{
    int count = des_db_rows_count(db);
    printf("Driver count : %i\n", count);
}
