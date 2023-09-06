#include "hash.h"

template <typename K>
int32_t CaculateHashNormal_T<K>::hash(int order, K key, int capacity)
{
    order, key, capacity;
    return -1;
}

template <>
int32_t CaculateHashNormal_T<int32_t>::hash(int order, int32_t key, int capacity)
{
    while (order-- > 0)
        key /= capacity;
    return key % capacity;
}

template <typename K, typename V>
LinearHash_T<K, V>::LinearHash_T(std::unique_ptr<CaculateHash<K>> &&caculateHash) : caculateHash(std::move(caculateHash)), realNum(0)
{
    this->type = HASHTYPE::LINEARHASH;
    hashTable = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(INIT_CAPACITY);
    deleteTable = std::make_unique<std::vector<int8_t>>(INIT_CAPACITY);
}

template <typename K, typename V>
bool LinearHash_T<K, V>::ReHash()
{
    if (realNum <= hashTable->size() / 2)
        return true;

    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> newHashTable = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(hashTable->size() * 2);
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> oldHashTable = std::move(hashTable);
    hashTable = std::move(newHashTable);

    std::unique_ptr<std::vector<int8_t>> newDeleteTable = std::make_unique<std::vector<int8_t>>(deleteTable->size() * 2);
    std::unique_ptr<std::vector<int8_t>> oldDeleteTable = std::move(deleteTable);
    deleteTable = std::move(newDeleteTable);

    realNum = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(oldHashTable->size()); i++)
        if (oldHashTable->at(i).has_value() && oldDeleteTable->at(i) == 0)
            Set(oldHashTable->at(i).value().first, oldHashTable->at(i).value().second);

    return true;
}

template <typename K, typename V>
size_t LinearHash_T<K, V>::Size()
{
    return realNum;
}

template <typename K, typename V>
size_t LinearHash_T<K, V>::Capacity()
{
    return hashTable->size();
}

template <typename K, typename V>
std::vector<std::vector<std::optional<std::pair<K, V>>>> LinearHash_T<K, V>::GetHashTable()
{
    std::vector<std::vector<std::optional<std::pair<K, V>>>> hashTables;
    std::vector<std::optional<std::pair<K, V>>> realHashTable;
    for (int32_t i = 0; i < static_cast<int32_t>(hashTable->size()); i++)
        if (hashTable->at(i).has_value() && deleteTable->at(i) == 0)
            realHashTable.push_back(hashTable->at(i));
        else
            realHashTable.push_back(std::nullopt);

    hashTables.push_back(*hashTable);
    return hashTables;
}

template <typename K, typename V>
std::optional<std::pair<K, V>> LinearHash_T<K, V>::Get(K key)
{
    int32_t realKey = caculateHash->hash(0, key, hashTable->size());
    if (realKey >= static_cast<int32_t>(hashTable->size()) || realKey < 0 || !hashTable->at(realKey).has_value())
        return std::nullopt;

    // now value is it
    if (hashTable->at(realKey).value().first == key)
    {
        if (deleteTable->at(realKey) == 0)
            return hashTable->at(realKey).value();
        else
            return std::nullopt;
    }

    // not is it, go head until find a location
    int32_t nowRealKey = (realKey + 1) % hashTable->size();
    while (nowRealKey != realKey && hashTable->at(nowRealKey).has_value())
    {
        if (hashTable->at(nowRealKey).value().first == key)
        {
            if (deleteTable->at(nowRealKey) == 0)
                return hashTable->at(nowRealKey).value();
            else
                return std::nullopt;
        }
        else
        {
            nowRealKey = (nowRealKey + 1) % hashTable->size();
        }
    }

    return std::nullopt;
}

template <typename K, typename V>
bool LinearHash_T<K, V>::Set(const K &key, const V &value)
{
    int32_t realKey = caculateHash->hash(0, key, hashTable->size());
    if (realKey >= static_cast<int32_t>(hashTable->size()) || realKey < 0)
        return false;

    // don't have value, directly set
    if ((!hashTable->at(realKey).has_value()) || (hashTable->at(realKey).has_value() && hashTable->at(realKey).value().first == key) || (hashTable->at(realKey).has_value() && deleteTable->at(realKey) != 0))
    {
        hashTable->at(realKey) = std::make_pair(key, value);
        realNum++;
        deleteTable->at(realKey) = 0;
        return ReHash();
    }

    // have value, find a location
    int32_t nowRealKey = (realKey + 1) % hashTable->size();
    while (nowRealKey != realKey)
    {
        if (!hashTable->at(nowRealKey).has_value() || (hashTable->at(nowRealKey).has_value() && hashTable->at(nowRealKey).value().first == key) || (hashTable->at(nowRealKey).has_value() && deleteTable->at(nowRealKey) != 0))
        {
            hashTable->at(nowRealKey) = std::make_pair(key, value);
            realNum++;
            deleteTable->at(nowRealKey) = 0;
            return ReHash();
        }
        else
        {
            nowRealKey = (nowRealKey + 1) % hashTable->size();
        }
    }
    return false;
}

template <typename K, typename V>
bool LinearHash_T<K, V>::Delete(const K &key)
{
    int32_t realKey = caculateHash->hash(0, key, hashTable->size());
    if (realKey >= static_cast<int32_t>(hashTable->size()) || realKey < 0 || !hashTable->at(realKey).has_value())
        return false;

    // now value is it
    if (hashTable->at(realKey).value().first == key)
    {
        deleteTable->at(realKey) = 1;
        realNum--;
        return true;
    }

    // not is it, go head until find a location
    int32_t nowRealKey = (realKey + 1) % hashTable->size();
    while (nowRealKey != realKey && hashTable->at(nowRealKey).has_value())
    {
        if (hashTable->at(nowRealKey).value().first == key)
        {
            deleteTable->at(nowRealKey) = 1;
            realNum--;
            return true;
        }
        else
        {
            nowRealKey = (nowRealKey + 1) % hashTable->size();
        }
    }
    return false;
}

template <typename K, typename V>
CuckooHash_T<K, V>::CuckooHash_T(std::unique_ptr<CaculateHash<K>> &&caculateHash) : caculateHash(std::move(caculateHash)), realNum_1(0), realNum_2(0)
{
    this->type = HASHTYPE::CUCKOOHASH;
    hashTable_1 = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(INIT_CAPACITY);
    hashTable_2 = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(INIT_CAPACITY);
}

template <typename K, typename V>
bool CuckooHash_T<K, V>::ReHash()
{
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> newHashTable_1 = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(hashTable_1->size() * 2);
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> newHashTable_2 = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(hashTable_2->size() * 2);
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> oldHashTable_1 = std::move(hashTable_1);
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> oldHashTable_2 = std::move(hashTable_2);
    hashTable_1 = std::move(newHashTable_1);
    hashTable_2 = std::move(newHashTable_2);

    realNum_1 = 0;
    realNum_2 = 0;
    for (auto &&v : *oldHashTable_1)
        if (v.has_value())
            Set(v.value().first, v.value().second);

    for (auto &&v : *oldHashTable_2)
        if (v.has_value())
            Set(v.value().first, v.value().second);

    return true;
}

template <typename K, typename V>
bool CuckooHash_T<K, V>::Kick(std::vector<std::pair<int32_t, int32_t>> &kickOldPath, int32_t kickTable, int32_t kickIndex)
{
    // check value
    if (kickTable != 0 && kickTable != 1)
        return false;
    if (kickTable == 0 && (kickIndex < 0 || kickIndex >= static_cast<int32_t>(hashTable_1->size())))
        return false;
    if (kickTable == 1 && (kickIndex < 0 || kickIndex >= static_cast<int32_t>(hashTable_2->size())))
        return false;
    // if it is empty, just return true
    if (kickTable == 0 && kickIndex >= 0 && kickIndex < static_cast<int32_t>(hashTable_1->size()) && !hashTable_1->at(kickIndex).has_value())
        return true;
    if (kickTable == 1 && kickIndex >= 0 && kickIndex < static_cast<int32_t>(hashTable_2->size()) && !hashTable_2->at(kickIndex).has_value())
        return true;

    // check if has kicked
    for (auto &&kicked : kickOldPath)
    {
        if (kicked.first == kickTable && kicked.second == kickIndex)
        {
            ReHash();
            return false;
        }
    }

    // real kick
    int32_t newKickTable = (kickTable + 1) % 2;
    int32_t newKickIndex = -1;
    if (kickTable == 0)
        newKickIndex = caculateHash->hash(1, hashTable_1->at(kickIndex).value().first, hashTable_1->size());
    if (kickTable == 1)
        newKickIndex = caculateHash->hash(1, hashTable_2->at(kickIndex).value().first, hashTable_2->size());
    kickOldPath.push_back({kickTable, kickIndex});
    if (!Kick(kickOldPath, newKickTable, newKickIndex))
        return false;

    if (kickTable == 0 && newKickTable == 1)
        hashTable_2->at(newKickIndex) = std::move(hashTable_1->at(kickIndex));
    if (kickTable == 1 && newKickTable == 0)
        hashTable_1->at(newKickIndex) = std::move(hashTable_2->at(kickIndex));

    return true;
}

template <typename K, typename V>
size_t CuckooHash_T<K, V>::Size()
{
    return realNum_1 + realNum_2;
}

template <typename K, typename V>
size_t CuckooHash_T<K, V>::Capacity()
{
    return hashTable_1->size() + hashTable_2->size();
}

template <typename K, typename V>
std::vector<std::vector<std::optional<std::pair<K, V>>>> CuckooHash_T<K, V>::GetHashTable()
{
    //    return std::make_tuple(*hashTable_1, *hashTable_2);
    std::vector<std::vector<std::optional<std::pair<K, V>>>> hashTables;
    hashTables.push_back(*hashTable_1);
    hashTables.push_back(*hashTable_2);
    return hashTables;
}

template <typename K, typename V>
std::vector<std::pair<int32_t, int32_t>> CuckooHash_T<K, V>::GetKickPath()
{
    return kickPath;
}

template <typename K, typename V>
std::optional<std::pair<K, V>> CuckooHash_T<K, V>::Get(K key)
{
    int32_t realKey_1 = caculateHash->hash(0, key, hashTable_1->size());
    int32_t realKey_2 = caculateHash->hash(1, key, hashTable_2->size());

    if (realKey_1 < static_cast<int32_t>(hashTable_1->size()) && realKey_1 >= 0 && hashTable_1->at(realKey_1).has_value() && hashTable_1->at(realKey_1).value().first == key)
        return hashTable_1->at(realKey_1);

    if (realKey_2 < static_cast<int32_t>(hashTable_2->size()) && realKey_2 >= 0 && hashTable_2->at(realKey_2).has_value() && hashTable_2->at(realKey_2).value().first == key)
        return hashTable_2->at(realKey_2);

    return std::nullopt;
}

template <typename K, typename V>
bool CuckooHash_T<K, V>::Set(const K &key, const V &value)
{
    int32_t realKey_1 = caculateHash->hash(0, key, hashTable_1->size());
    if (realKey_1 < static_cast<int32_t>(hashTable_1->size()) && realKey_1 >= 0 && (!hashTable_1->at(realKey_1).has_value() || (hashTable_1->at(realKey_1).has_value() && hashTable_1->at(realKey_1).value().first == key)))
    {
        hashTable_1->at(realKey_1) = std::make_pair(key, value);
        realNum_1++;
        return true;
    }

    // need kick
    kickPath.clear();
    while (!Kick(kickPath, 0, realKey_1))
    {
        kickPath.clear();
        realKey_1 = caculateHash->hash(0, key, hashTable_1->size());
        if (realKey_1 >= static_cast<int32_t>(hashTable_1->size()) || realKey_1 < 0)
            return false;
    }

    hashTable_1->at(realKey_1) = std::make_pair(key, value);
    realNum_1++;
    return true;
}

template <typename K, typename V>
bool CuckooHash_T<K, V>::Delete(const K &key)
{
    int32_t realKey_1 = caculateHash->hash(0, key, hashTable_1->size());
    int32_t realKey_2 = caculateHash->hash(1, key, hashTable_2->size());

    if (realKey_1 < static_cast<int32_t>(hashTable_1->size()) && realKey_1 >= 0 && hashTable_1->at(realKey_1).has_value() && hashTable_1->at(realKey_1).value().first == key)
    {
        hashTable_1->at(realKey_1) = std::nullopt;
        realNum_1--;
        return true;
    }

    if (realKey_2 < static_cast<int32_t>(hashTable_2->size()) && realKey_2 >= 0 && hashTable_2->at(realKey_2).has_value() && hashTable_2->at(realKey_2).value().first == key)
    {
        hashTable_2->at(realKey_2) = std::nullopt;
        realNum_2--;
        return true;
    }

    return false;
}
