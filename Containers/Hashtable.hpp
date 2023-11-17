#pragma once

#include <vector>
#include <list>
#include <memory>

// Hasher base class
template <typename K>
class Hasher
{
    public:
        virtual ~Hasher() {}
        virtual size_t hash(const K& key) const = 0;
};

// EqualityPredicate base class
template <typename K>
class EqualityPredicate
{
    public:
        virtual ~EqualityPredicate() {}
        virtual bool isEqual(const K& key1, const K& key2) const = 0;
};

// Hashtable class
template <typename K, typename V>
class Hashtable 
{
    private:
        struct Node
        {
            K key;
            V value;
            Node(K key, V value) : key(key), value(value) {}
        };

        std::vector<std::list<Node>> buckets;
        std::unique_ptr<Hasher<K>> hasher;
        std::unique_ptr<EqualityPredicate<K>> equalityPredicate;
        size_t bucketCount;

        size_t getBucketIndex(const K& key) const
        {
            return hasher->hash(key) % bucketCount;
        }

    public:
        Hashtable(size_t bucketCount, std::unique_ptr<Hasher<K>> hasher, std::unique_ptr<EqualityPredicate<K>> equalityPredicate):
        bucketCount(bucketCount), hasher(std::move(hasher)), equalityPredicate(std::move(equalityPredicate))
        {
            buckets.resize(bucketCount);
        }

        void insert(const K& key, const V& value)
        {
            size_t bucketIndex = getBucketIndex(key);
            for (auto& node : buckets[bucketIndex])
            {
                if (equalityPredicate->isEqual(node.key, key))
                {
                    node.value = value;
                    return;
                }
            }
            buckets[bucketIndex].emplace_back(key, value);
        }

        bool find(const K& key, V& value) const
        {
            size_t bucketIndex = getBucketIndex(key);
            for (const auto& node : buckets[bucketIndex])
            {
                if (equalityPredicate->isEqual(node.key, key))
                {
                    value = node.value;
                    return true;
                }
            }
            return false;
        }
};

// Concrete Hasher for int
class IntHasher : public Hasher<int>
{
    public:
        size_t hash(const int& key) const override 
        {
            return std::hash<int>{}(key);
        }
};

// Concrete EqualityPredicate for int
class IntEqualityPredicate : public EqualityPredicate<int> 
{
    public:
        bool isEqual(const int& key1, const int& key2) const override
        {
            return key1 == key2;
        }
};