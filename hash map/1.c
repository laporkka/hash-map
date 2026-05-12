#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1.h"

#define TABLE_SIZE 10

struct Node
{
    char *key;
    int val;
    struct Node *next;
};

struct HashTable
{
    struct Node *Nods[TABLE_SIZE];
};

struct HashTable *create_table()
{
    struct HashTable *table = malloc(sizeof(struct HashTable));
    // struct HashTable* table = calloc(1,sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table->Nods[i] = NULL;
    }
    return table;
};

unsigned int Hash_func(const char *key)
{
    unsigned int hash_value = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash_value += key[i];
    }
    return hash_value % TABLE_SIZE;
}

struct Node *creat_new_node(const char *key, int val)
{
    struct Node *New_node = malloc(sizeof(struct Node));
    New_node->key = malloc(strlen(key) + 1);
    strcpy(New_node->key, key);

    New_node->val = val;
    New_node->next = NULL;

    return New_node;
}

void insert(struct HashTable *table, const char *key, const int val)
{
    unsigned int index = Hash_func(key);
    struct Node *new_node = creat_new_node(key, val);

    if (table->Nods[index] == NULL)
    {
        table->Nods[index] = new_node;
    }
    else
    {
        new_node->next = table->Nods[index];
        table->Nods[index] = new_node;
    }
}

int search_val(struct HashTable *table, const char *key)
{
    unsigned int index = Hash_func(key);
    struct Node *curr = table->Nods[index];

    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
        {
            return curr->val;
        }
        curr = curr->next;
    }

    printf("not found\n");
    return -1;
}

struct Node *search_node(struct HashTable *table, const char *key)
{
    unsigned int index = Hash_func(key);
    struct Node *curr = table->Nods[index];

    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
        {
            return curr;
        }
        curr = curr->next;
    }

    printf("not found\n");
}

void delete_node(struct HashTable *table, const char *key)
{
    unsigned int index = Hash_func(key);
    struct Node *curr = table->Nods[index];
    struct Node *pervios = NULL;

    while (curr != NULL && strcmp(curr->key, key) != 0)
    {
        pervios = curr;
        curr = curr->next;
    }

    if (curr != NULL)
    {
        if (pervios == NULL)
        {
            table->Nods[index] = curr->next;
        }
        else
        {
            pervios->next = curr->next;
        }

        free(curr->next);
        free(curr);
    }
}

int table_size(struct HashTable *table)
{
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Node *curr = table->Nods[i];
        while (curr != NULL)
        {
            curr = curr->next;
            count++;
        }
    }

    return count;
}

char** keys(struct HashTable *table)
{
    int size = table_size(table);
    char** keys = malloc((size + 1) * sizeof(char*));
    int index = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Node *curr = table->Nods[i];
        while (curr != NULL)
        {
            keys[index] = malloc(strlen(curr->key)+1);
            strcpy(keys[index],curr->key);
            index++;
            curr = curr->next;       
        }
    }
    keys[index] = NULL;

    return keys;    
}

void free_keys(char** keys) {
    for (int i = 0; keys[i] != NULL; i++) {
        free(keys[i]);
    }
    free(keys);
}

void print_table(struct HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table->Nods[i] != NULL)
        {
            struct Node *curr = table->Nods[i];

            while (curr != NULL)
            {
                printf("index %d -> key '%s' -> val %d\n", i, curr->key, curr->val);
                curr = curr->next;
            }
        }
    }
}

void free_table(struct HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Node *curr = table->Nods[i];
        while (curr != NULL)
        {
            struct Node *pervios = curr;
            curr = curr->next;
            free(pervios->key);
            free(pervios);
        }
    }

    free(table->Nods);
    free(table);
}

