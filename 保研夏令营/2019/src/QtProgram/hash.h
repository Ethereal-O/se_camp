#ifndef HASH_H
#define HASH_H

#include<array>

const int32_t INIT_CAPACITY = 8;

template<typename K, typename V>
class Hash
{
public:
    Hash(){};
    virtual ~Hash();
    virtual V Get(K key)=0;
    virtual bool Set(const K& key, const V& value)=0;
    virtual bool Delete(const K& key)=0;
};

template<typename K, typename V>
class LinearHash_T:public Hash<K, V>
{
private:
    std::array<V,INIT_CAPACITY> hashTable;
    bool ReHash();
public:
    LinearHash_T(){};
    ~LinearHash_T(){};
    V Get(K key) override;
    bool Set(const K& key, const V& value) override;
    bool Delete(const K& key) override;
};

template<typename K, typename V>
class CuckooHash_T:public Hash<K, V>
{
private:
    std::array<V,INIT_CAPACITY> hashTable_1;
    std::array<V,INIT_CAPACITY> hashTable_2;
    bool ReHash();
public:
    CuckooHash_T(){};
    ~CuckooHash_T(){};
    V Get(K key) override;
    bool Set(const K& key, const V& value) override;
    bool Delete(const K& key) override;
};

class CaculateHash
{
public:
    template <typename K>
    static int32_t hash_1(K key, int capacity);
    static int32_t hash_1(int32_t key, int capacity);
    template <typename K>
    static int32_t hash_2(K key, int capacity);
    static int32_t hash_2(int32_t key, int capacity);
};

using LinearHash = LinearHash_T<int32_t, int32_t>;
using CuckooHash = CuckooHash_T<int32_t, int32_t>;

#endif // HASH_H
