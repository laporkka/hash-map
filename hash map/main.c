#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

int main()
{
    generate_records_file("input.txt",1000000);

    int size_values[] = {
    20,40,60,80,100,120,140,160,180,200,
    400,600,800,1000,1200,1400,1600,1800,2000,
    4000,6000,8000,10000,12000,14000,16000,18000,20000,
    40000,60000,80000,100000,120000,140000,160000,180000,200000
    };

    int num = sizeof(size_values) / sizeof(size_values[0]);

    printf("\n=== Method 1: hash_division ===\n");
    FILE* out1 = fopen("result_division.txt", "w");
    fprintf(out1, "Size\tDensity(%%)\tOverflow(%%)\n");
   
    for(size_t i = 0;i < (size_t)num;i++)
    {
        run_func(size_values[i],"input.txt",hash_division,out1);
    }
    fclose(out1);

    printf("\n=== Method 2: hash_shift ===\n");
    FILE* out2 = fopen("result_shift.txt", "w");
    fprintf(out2, "Size\tDensity(%%)\tOverflow(%%)\n");

    for (size_t i = 0; i < (size_t)num; i++) {
        run_func(size_values[i], "input.txt", hash_shift, out2);
    }
    fclose(out2);
    
    printf("\nSuccess");
    return 0;
}