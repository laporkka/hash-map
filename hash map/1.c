#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "1.h"


HashTable *create_table()
{
    HashTable* table = malloc(sizeof(HashTable));

    table->main_area = calloc(TABLE_SIZE,sizeof(Record));

    table->ower_flow.capacity = 1000000;
    table->ower_flow.count = 0;
    table->ower_flow.records = malloc(table->ower_flow.capacity * sizeof(Record));

    return table;
};

void init_overflow(Over_Flow_Area* overflow)
{
    overflow->capacity = 1000000;
    overflow->count = 0;
    overflow->records = malloc(overflow->capacity * sizeof(Record));
}

void add_to_overflow(Over_Flow_Area* overflow, Record record)
{
    if (overflow->count >= overflow->capacity)
    {
        overflow->capacity *= 2;
        overflow->records = realloc(overflow->records,overflow->capacity * sizeof(Record));
    }
    overflow->records[overflow->count++] = record; 
}

unsigned int hash_division(const char *key, int size)
{
    unsigned int hash_value = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash_value += key[i];
    }
    return hash_value % size;
}

unsigned int hash_mid_square(const char* key, int size) {
    unsigned int hash = 0;
    for (int i = 0; i < 6 && key[i] != '\0'; i++) {
        hash = hash * 37 + key[i];
    }
    
    unsigned long long square = (unsigned long long)hash * hash;
    unsigned int middle = (square >> 16) & 0xFFFF;  
    
    return middle % size;
}

Record create_new_record(const char *key, const char *info, int val)
{
    Record new_record;
    strcpy(new_record.info, info);
    strcpy(new_record.key, key);
    new_record.val = val;

    return new_record;
}

int insert_record(Record* node, int size, int bucket_size, HashTable* table, unsigned int (*hash_method)(const char*, int))
{
    int bucket = hash_method(node->key, size);
    int start = bucket * bucket_size;
    int end = start + bucket_size;

    for (int i = start;i < end;i++)
    {
        if (table->main_area[i].key[0] == '\0')
        {
            table->main_area[i] = *node;
            return 1;
        }
    }

    add_to_overflow(&table->ower_flow, *node);  
    return 0;
}

int count_occupied(HashTable* table)
{
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table->main_area[i].key[0] != '\0')
        {
            count++;
        }
    }
    return count;
}

void free_table(HashTable* table) 
{
    free(table->main_area);
    free(table->ower_flow.records);
    free(table);
}

void generate_records_file(const char* filename, int count) 
{
    FILE* file = fopen(filename, "wb");
    for (int i = 0; i < count; i++) {
        Record record;
        char key[7];
        sprintf(key, "%c%05d", 'A' + (i / 100000), i % 100000);
        strcpy(record.key, key);
        strcpy(record.info, "User");
        record.val = i;
        fwrite(&record, sizeof(Record), 1, file);
    }
    fclose(file);
    printf("Generated %d records to %s\n", count, filename);
}


