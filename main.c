#include <stdio.h>

void find_peak_hours(float* prices, int hours)
{
    //Search maximum prices in array
    int max = 0; //store position of max by integer instead of value by float.
    printf("NordPool prices list in 24 hourse: \n");//print out prices list in 24h:
    for (int i = 0; i < hours; i++) {
        printf(" %.2f | ", *(prices+i)); ////print out prices list in 24h:
        if (*(prices + max) < *(prices + (i+1))) max = i+1; //compare with the next prices
    }
    //Print the number of maximum in array
    printf("\nThe highest prices:\n");
    for (int j = 0; j < hours; j++) {
        if (*(prices + max) == *(prices + j))
            printf("%d ", j + 1); //+1 cause 1-24h
    }
}
void main()
{
    //float nordpool_prices[24] = { 40.12, 41.11, 44.44, 42.13, 40.10, 42.14, 43.15, 41.12, 40.11, 40.10, 39.09, 38.08, 37.07, 36.06, 38.08, 39.09, 40.10, 41.11, 42.12, 43.13, 44.14, 45.15, 46.16, 47.17 };
    float nordpool_prices[24] = { 40.12, 41.11, 44.44, 42.13, 47.17, 42.14, 43.15, 41.12, 40.11, 40.11, 39.09, 38.08, 37.07, 47.17, 38.08, 39.09, 40.10, 41.11, 42.12, 43.13, 44.14, 45.15, 46.16, 47.17 };
    int num_hours = 24;

    find_peak_hours(nordpool_prices, num_hours);
}
