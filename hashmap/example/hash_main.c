#include "hash.h"
#include "hashmap.h"
#include <stdio.h>
void test_hash()
{
    HashTable* hash;
    hash_init(&hash);
    int i = 0;
    for (; i < 200; i++)
    {
        char key[10] = {0};
        char value[10] = {0};
        sprintf(key, "hello%d", i);
        sprintf(value, "world%d", i);
        hash_insert(hash, key, value);
    }
    for (i = 0; i < 200; i++)
    {
        if (i % 2 == 0)
        {
            char key[10] = {0};
            sprintf(key, "hello%d", i);
            hash_remove(hash, key);
        }
    }

    for (i = 0; i < 200; i++)
    {
        char key[100] = {0};
        sprintf(key, "hello%d", i);
        Bucket* bucket;
        int result = hash_find(hash, key, &bucket);
        if (result)
        {
            printf("%s=>%s\n", bucket->key, bucket->value);
        }
    }
    hash_free(hash);
}

void test_hashmap()
{
    Hashmap hash;
    int i = 0;
    for (; i < 200; i++)
    {
        char key[10] = {0};
        char value[10] = {0};
        sprintf(key, "hello%d", i);
        sprintf(value, "world%d", i);
        hash.insert(key, value);
    }
    for (i = 0; i < 200; i++)
    {
        if (i % 2 == 0)
        {
            char key[10] = {0};
            sprintf(key, "hello%d", i);
            hash.remove(key);
        }
    }

    for (i = 0; i < 200; i++)
    {
        char key[100] = {0};
        sprintf(key, "hello%d", i);
        Bucket* bucket;
        int result = hash.find(key, &bucket);
        if (result)
        {
            printf("%s=>%s\n", bucket->key, bucket->value);
        }
    }
}
int main()
{
    test_hashmap();
    return 0;
}
