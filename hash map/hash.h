#ifndef HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1200000


typedef struct 
{
    char key[7];
    char info[30];
    int val;
} Record;

typedef struct 
{
    Record* records;
    int capacity;
    int count;
} Over_Flow_Area;

typedef struct 
{
    Record* main_area;
    Over_Flow_Area ower_flow;
} HashTable;


HashTable *create_table();
void init_overflow(Over_Flow_Area* overflow);
void add_to_overflow(Over_Flow_Area* overflow, Record record);
void free_table(HashTable* table);

unsigned int hash_division(const char* key, int size);
unsigned int hash_shift(const char* key, int size);

Record create_new_record(const char *key, const char *info, int val);
int insert_record(Record* record, int size, int bucket_size, HashTable* table, unsigned int (*hash_method)(const char*, int));

int count_occupied(HashTable* table);
void generate_records_file(const char* filename, int count);
void run_func(int size, const char* input_file, unsigned int (*hash_method)(const char*, int), FILE* output);

#endif