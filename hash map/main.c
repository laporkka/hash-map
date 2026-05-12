#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1.h"

int main()
{

    struct HashTable *Table = create_table();

    insert(Table, "cat", 100);
    insert(Table, "act", 400);
    insert(Table, "tac", 800);
    insert(Table, "pore", 300);
    insert(Table, "frost", 200);
    insert(Table, "gost", 200);

    print_table(Table);

    char** klic = keys(Table);
    for (int i = 0;klic[i] != NULL;i++)
    {
        printf("%s",klic[i]);
        printf(" ");
    }
    free_keys(klic);

    free_table(Table);

    return 0;
}