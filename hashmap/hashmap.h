/*
 * Author: HongXiaoqiang  - cool.hxq@gmail.com
 *
 * Description: 
 */

#ifndef _HXQ_HASHMAP_H
#define _HXQ_HASHMAP_H

#include <string>
#include <mutex>

class Hashmap;

class Bucket
{
public:
    Bucket();
    ~Bucket();

    std::string key;
    std::string value;
    bool has_value;
    Bucket* next;
};

class HashmapIter
{
public:
    Bucket* ptr;
    Hashmap* ht;

    HashmapIter(Bucket* p, Hashmap* tab) : ptr(p), ht(tab){}
    HashmapIter() {}
    void init(Bucket* p, Hashmap* tab){ ptr = p; ht = tab;}

    Bucket& operator* () const { return *ptr; }
    Bucket* operator->() const { return ptr; }

    HashmapIter& operator++();

    bool operator==(const HashmapIter& i) const
    {
        return ptr == i.ptr;
    }

    bool operator!=(const HashmapIter& i) const
    {
        return ptr != i.ptr;
    }
};

class Hashmap
{
public:
    typedef HashmapIter iterator;

    Hashmap();
    ~Hashmap();

    unsigned int get_hash_index(std::string str);
    int insert(std::string key, std::string value);
    int find(std::string key, Bucket** bucket);
    int remove(std::string key);
    int max_bucket_count() const;
    int size();
    Bucket* getBucket(int index);

    iterator begin() const { return start; }
    iterator end() const { return finish; }

private:
    int m_max_bucket_count;
    iterator start;
    iterator finish;
    std::mutex m_mutex;
    Bucket* m_buckets;
};

#endif
