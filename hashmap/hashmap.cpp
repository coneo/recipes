/*
 * Author: HongXiaoqiang  - cool.hxq@gmail.com
 *
 * Description: 
 */

#include "hashmap.h"
#include <stdio.h>

#define HASH_SIZE 100
#define SAFE_DELETE(x)\
    if (x)\
        delete x;

#define SAFE_DELETE_ARR(x)\
    if (x)\
        delete [] x;

Bucket::Bucket()
{
    has_value = false;
    next = NULL;
}

Bucket::~Bucket()
{
}

HashmapIter& HashmapIter::operator++()
{
    if (*this == ht->end())
        return *this;

    Bucket* old = ptr;
    if (ptr->next && ptr->next->next)
        ptr = ptr->next;
    else
    {
        ptr = NULL;
        int bucindex = ht->get_hash_index(old->key);
        while (!ptr && ++bucindex < ht->max_bucket_count())
        {
            Bucket* tmp = ht->getBucket(bucindex);
            if (tmp->has_value)
                ptr = tmp;
        }
        if (NULL == ptr)
        {
            ptr = &*(ht->end());
        }
    }
    return *this;
}

Hashmap::Hashmap()
{
    m_max_bucket_count = HASH_SIZE;
    m_buckets = new Bucket[m_max_bucket_count+1];
    start.init(&m_buckets[m_max_bucket_count], this);
    finish.init(&m_buckets[m_max_bucket_count], this);
}

Hashmap::~Hashmap()
{
    int i = 0;
    Bucket* bucket;
    for (i = m_max_bucket_count - 1; i > -1; i--)
    {
        bucket = &m_buckets[i];
        if (!bucket) continue;
        int is_sub = 0;
        do
        {
            if (is_sub)
            {
                Bucket* tmp = bucket;
                bucket = bucket->next;
                SAFE_DELETE(tmp);
            }
            else
            {
                bucket = bucket->next;
            }
            is_sub++;
        }while (bucket);
    }
    SAFE_DELETE_ARR(m_buckets);
}

unsigned int Hashmap::get_hash_index(std::string str)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    char* tmp_str = const_cast<char*>(str.c_str());
    while (*tmp_str) {
        hash = (hash << 4) + (*tmp_str++);
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
    return (hash & 0x7FFFFFFF) % m_max_bucket_count;
}

int Hashmap::insert(std::string key, std::string value)
{
    m_mutex.lock();
    int index = get_hash_index(key);
    Bucket* bucket;
    bucket = &m_buckets[index];
    while (NULL != (bucket->next))
    {
        bucket = bucket->next;
    }
    bucket->key = key;
    bucket->value = value;
    bucket->has_value = true;
    bucket->next = new Bucket();
    if (!bucket->next)
    {
        return 1;   //new failed
    }
    bucket->next->next = NULL;
    if (size() == 1)    //first insert
    {
        start.init(getBucket(index), this);
    }
    else if (size() > 1)
    {
        printf("insert: key:%s,index:%d,size:%u\n", key.c_str(), index, size());
        int sIndex = get_hash_index(start->key);
        if (index < sIndex)
            start.init(getBucket(index), this);
    }
    m_mutex.unlock();
    return 0;
}

int Hashmap::find(std::string key, Bucket** result)
{
    int index = get_hash_index(key);
    Bucket* bucket = &m_buckets[index];
    while (bucket)
    {
        if (bucket->key == key)
        {
            (*result) = bucket;
            return 0;
        }
        bucket = bucket->next;
    }
    return 1;   //find failed
}

int Hashmap::remove(std::string key)
{
    m_mutex.lock();
    int index = get_hash_index(key);
    Bucket* bucket = &m_buckets[index];
    int is_sub = 0;
    Bucket* prev = NULL;
    while (bucket)
    {
        if (key != bucket->key)
            continue;
        if (is_sub)
        {
            prev->next = bucket->next;
            SAFE_DELETE(bucket);
            return 0;
        }
        else
        {
            if (bucket->next)
            {
                bucket->key = bucket->next->key;
                bucket->value = bucket->next->value;
                bucket->next = bucket->next->next;
            }
            return 0;
        }
        prev = bucket;
        bucket = bucket->next;
        is_sub++;
    }
    m_mutex.unlock();
    return 1;
}

int Hashmap::max_bucket_count() const
{
    return m_max_bucket_count;
}

int Hashmap::size()
{
    int size = 0;
    Bucket* bucket;
    for (int i = 0; i < m_max_bucket_count; i++)
    {
        bucket = &m_buckets[i];
        if (!bucket) continue;
        while (NULL != (bucket->next))
        {
            size++;
            bucket = bucket->next;
        }
    }
    return size;
}

Bucket* Hashmap::getBucket(int index)
{
    if (index < 0 || index >= max_bucket_count())
        return NULL;
    return &m_buckets[index];
}
