#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "1.h"

int main()
{
    generate_records_file("input.txt",1000000);
    HashTable* table = create_table();
    init_overflow(&table->ower_flow);

    FILE* input_file = fopen("input.txt","rb");
    FILE* output_file  = fopen("output.file","w");
    
    int step_values[] = {
    20,40,60,80,100,120,140,160,180,200,
    400,600,800,1000,1200,1400,1600,1800,2000,
    4000,6000,8000,10000,12000,14000,16000,18000,20000,
    40000,60000,80000,100000,120000,140000,160000,180000,200000
    };

    for(size_t i = 0;i < 40;i++)
    {
        int step = step_values[i];
        int bucket_size = TABLE_SIZE / step;
        
        
    }

}