#include "hash.h"

template <typename K>
int32_t CaculateHash::hash_1(K key, int capacity)
{
    key;
    return -1;
}

int32_t CaculateHash::hash_1(int32_t key, int capacity)
{
    return key%capacity;
}

template <typename K>
int32_t CaculateHash::hash_2(K key, int capacity)
{
    key;
    return -1;
}

int32_t CaculateHash::hash_2(int32_t key, int capacity)
{
    return (key/capacity)%capacity;
}


template<typename K, typename V>
V LinearHash_T<K,V>::Get(K key)
{
    int32_t real_key=CaculateHash::hash_1(key, hashTable.size());

}
