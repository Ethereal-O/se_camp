#ifndef HASH_H
#define HASH_H

#include <bits/stdc++.h>

const int32_t INIT_CAPACITY = 8;

template <typename K>
class CaculateHash
{
public:
    virtual int32_t hash(int order, K key, int capacity) = 0;
};

template <typename K>
class CaculateHashNormal_T : public CaculateHash<K>
{
public:
    int32_t hash(int order, K key, int capacity);
};

template <typename K, typename V>
class Hash
{
private:
    virtual bool ReHash() = 0;

public:
    Hash(){};
    virtual ~Hash(){};
    virtual std::optional<std::pair<K, V>> Get(K key) = 0;
    virtual bool Set(const K &key, const V &value) = 0;
    virtual bool Delete(const K &key) = 0;
};

template <typename K, typename V>
class LinearHash_T : public Hash<K, V>
{
private:
    std::unique_ptr<CaculateHash<K>> caculateHash;
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> hashTable;
    size_t realNum;
    bool ReHash();

public:
    LinearHash_T(std::unique_ptr<CaculateHash<K>> &&caculateHash);
    ~LinearHash_T(){};
    std::optional<std::pair<K, V>> Get(K key);
    bool Set(const K &key, const V &value);
    bool Delete(const K &key);
};

template <typename K, typename V>
class CuckooHash_T : public Hash<K, V>
{
private:
    std::unique_ptr<CaculateHash<K>> caculateHash;
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> hashTable_1;
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> hashTable_2;
    size_t realNum_1;
    size_t realNum_2;
    bool ReHash();
    bool Kick(std::vector<std::pair<int32_t, int32_t>> &kickOldPath, int32_t kickTable, int32_t kickIndex);

public:
    CuckooHash_T(std::unique_ptr<CaculateHash<K>> &&caculateHash);
    ~CuckooHash_T(){};
    std::optional<std::pair<K, V>> Get(K key);
    bool Set(const K &key, const V &value);
    bool Delete(const K &key);
};

template class LinearHash_T<int32_t, int32_t>;
template class CuckooHash_T<int32_t, int32_t>;
template class CaculateHashNormal_T<int32_t>;

using LinearHash = LinearHash_T<int32_t, int32_t>;
using CuckooHash = CuckooHash_T<int32_t, int32_t>;
using CaculateHashNormal = CaculateHashNormal_T<int32_t>;

#endif // HASH_H
