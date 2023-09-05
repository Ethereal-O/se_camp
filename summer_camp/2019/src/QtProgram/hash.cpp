#include "hash.h"
#include "qdebug.h"

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
    hashTable = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(INIT_CAPACITY);
}

template <typename K, typename V>
bool LinearHash_T<K, V>::ReHash()
{
    if (realNum <= hashTable->size() / 2)
        return true;

    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> newHashTable = std::make_unique<std::vector<std::optional<std::pair<K, V>>>>(hashTable->size() * 2);
    std::unique_ptr<std::vector<std::optional<std::pair<K, V>>>> oldHashTable = std::move(hashTable);
    hashTable = std::move(newHashTable);

    realNum = 0;
    for (auto &&v : *oldHashTable)
        if (v.has_value())
            Set(v.value().first, v.value().second);

    return true;
}

template <typename K, typename V>
std::optional<std::pair<K, V>> LinearHash_T<K, V>::Get(K key)
{
    int32_t realKey = caculateHash->hash(0, key, hashTable->size());
    if (realKey >= static_cast<int32_t>(hashTable->size()) || realKey < 0 || !hashTable->at(realKey).has_value())
        return std::nullopt;

    // now value is it
    if (hashTable->at(realKey).value().first == key)
        return hashTable->at(realKey).value();

    // not is it, go head until find a location
    int32_t nowRealKey = (realKey + 1) % hashTable->size();
    while (nowRealKey != realKey && hashTable->at(nowRealKey).has_value())
    {
        if (hashTable->at(nowRealKey).value().first == key)
            return hashTable->at(nowRealKey).value();
        else
            nowRealKey = (nowRealKey + 1) % hashTable->size();
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
    if (!hashTable->at(realKey).has_value())
    {
        hashTable->at(realKey) = std::make_pair(key, value);
        realNum++;
        return ReHash();
    }

    // have value, find a location
    int32_t nowRealKey = (realKey + 1) % hashTable->size();
    while (nowRealKey != realKey)
    {
        if (!hashTable->at(nowRealKey).has_value() || (hashTable->at(nowRealKey).has_value() && hashTable->at(nowRealKey).value().first == key))
        {
            hashTable->at(nowRealKey) = std::make_pair(key, value);
            realNum++;
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
        hashTable->at(realKey) = std::nullopt;
        realNum--;
        return true;
    }

    // not is it, go head until find a location
    int32_t nowRealKey = (realKey + 1) % hashTable->size();
    while (nowRealKey != realKey && hashTable->at(nowRealKey).has_value())
    {
        if (hashTable->at(nowRealKey).value().first == key)
        {
            hashTable->at(nowRealKey) = std::nullopt;
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
    std::vector<std::pair<int32_t, int32_t>> kickPath;
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
