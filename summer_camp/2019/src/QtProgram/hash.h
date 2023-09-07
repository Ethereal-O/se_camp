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

enum class HASHTYPE
{
    LINEARHASH,
    CUCKOOHASH,
    OTHER
};

template <typename K, typename V>
class Hash_T
{
protected:
    HASHTYPE type = HASHTYPE::OTHER;
    virtual bool ReHash() = 0;

public:
    Hash_T(){};
    virtual ~Hash_T(){};
    HASHTYPE GetType() { return type; }
    virtual size_t Size() = 0;
    virtual size_t Capacity() = 0;
    virtual std::vector<std::vector<std::optional<std::pair<K, V>>>> GetHashTable() = 0;
    virtual std::optional<std::pair<K, V>> Get(K key) = 0;
    virtual bool Set(const K &key, const V &value) = 0;
    virtual bool Delete(const K &key) = 0;
};

template <typename K, typename V>
class LinearHash_T : public Hash_T<K, V>
{
private:
    std::unique_ptr<CaculateHash<K>> caculateHash;
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> hashTable;
    std::unique_ptr<std::vector<int8_t>> deleteTable;
    size_t realNum;
    bool ReHash();

public:
    LinearHash_T(std::unique_ptr<CaculateHash<K>> &&caculateHash);
    ~LinearHash_T(){};
    size_t Size();
    size_t Capacity();
    std::vector<std::vector<std::optional<std::pair<K, V>>>> GetHashTable();
    std::optional<std::pair<K, V>> Get(K key);
    bool Set(const K &key, const V &value);
    bool Delete(const K &key);
};

template <typename K, typename V>
class CuckooHash_T : public Hash_T<K, V>
{
private:
    std::unique_ptr<CaculateHash<K>> caculateHash;
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> hashTable_1;
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> hashTable_2;
    std::vector<std::pair<int32_t, int32_t>> kickPath;
    size_t realNum_1;
    size_t realNum_2;
    bool ReHash();
    bool Kick(std::vector<std::pair<int32_t, int32_t>> &kickOldPath, int32_t kickTable, int32_t kickIndex);

public:
    CuckooHash_T(std::unique_ptr<CaculateHash<K>> &&caculateHash);
    ~CuckooHash_T(){};
    size_t Size();
    size_t Capacity();
    std::vector<std::vector<std::optional<std::pair<K, V>>>> GetHashTable();
    std::vector<std::pair<int32_t, int32_t>> GetKickPath();
    std::optional<std::pair<K, V>> Get(K key);
    bool Set(const K &key, const V &value);
    bool Delete(const K &key);
};

template class Hash_T<int32_t, int32_t>;
template class LinearHash_T<int32_t, int32_t>;
template class CuckooHash_T<int32_t, int32_t>;
template class CaculateHashNormal_T<int32_t>;

#endif // HASH_H
