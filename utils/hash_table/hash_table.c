#include <stdio.h>
#include <unistd.h>
#include <time.h> 

#include "hash_table_dynamic_generic.h"

int main(void)
{

    HashTable* hash_table = hash_table_create();

    int i, values[30];
    for(i=0; i<5; i++)
    {
        values[i] = i;
        char buffer[32];
        sprintf(buffer, "name_%d_%d", i, rand()%10000);
        hash_table_insert(hash_table, buffer, &values[i]);
    }
    hash_info(hash_table);
    hash_table_free(hash_table);
    return 0;
}