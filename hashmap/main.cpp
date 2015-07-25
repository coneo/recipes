#include "hashmap.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <thread>

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
    printf("size ======> %d\n", hash.size());
    for (i = 0; i < 200; i++)
    {
        if (i % 2 == 0)
        {
            char key[10] = {0};
            sprintf(key, "hello%d", i);
            hash.remove(key);
        }
    }
    printf("size ======> %d\n", hash.size());

    for (i = 0; i < 200; i++)
    {
        char key[100] = {0};
        sprintf(key, "hello%d", i);
        Bucket* bucket;
        int result = hash.find(key, &bucket);
        if (result == 0)
        {
            printf("%s=>%s\n", bucket->key.c_str(), bucket->value.c_str());
        }
    }
}

void test_iterator()
{
    Hashmap hash;
    for (int i = 0; i < 500; i++)
    {
        char key[10] = {0};
        char value[10] = {0};
        sprintf(key, "hello%d", i);
        sprintf(value, "world%d", i);
        hash.insert(key, value);
    }
    printf("size ======> %d\n", hash.size());

    Hashmap::iterator it = hash.begin();
    for (; it != hash.end(); ++it)
    {
        printf("it:%x, key:%s, value:%s\n", it, it->key.c_str(), it->value.c_str());
    }
}

void thread_insert(Hashmap& hash, int type)
{
    for (int i = 0; i < 500; i++)
    {
        char key[10] = {0};
        char value[10] = {0};
        sprintf(key, "thread%dkey%d", type, i);
        sprintf(value, "thread%dvalue%d", type, i);
        hash.insert(key, value);
    }
}
void test_thread()
{
    Hashmap hash;
    std::thread th1(thread_insert, std::ref(hash), 1);
    th1.join();
}


int main()
{
    //test_hashmap();
    test_iterator();
    //test_thread();
    return 0;
}
