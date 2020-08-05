//
// Created by ivano on 7/31/2020.
//

#ifndef TAXIPROJECT_HASHMAP_H
#define TAXIPROJECT_HASHMAP_H

#include <vector>
#include <list>

template<typename K, typename D>
class HashMap {
    std::vector<std::list<std::pair<K, D>>> hashTable;
    int count{};
    double loadFactor{};

    void resize();

public:
    HashMap();

    explicit HashMap(int capacity);

    explicit HashMap(int capacity, double _loadFactor);

    D &operator[](K Key);

    void insert(K key, D data);

    bool find(K Key);
    std::vector<std::list<std::pair<K, D>>>& getHashTable();
};

template<typename K, typename D>
HashMap<K, D>::HashMap() : count(0), loadFactor(0.75) {
    hashTable.resize(16);
}

template<typename K, typename D>
HashMap<K, D>::HashMap(int capacity) : count(0), loadFactor(0.75) {
    hashTable.resize(capacity);
}

template<typename K, typename D>
HashMap<K, D>::HashMap(int capacity, double _loadFactor) : count(0) {
    hashTable.resize(capacity);
    loadFactor = _loadFactor;
}

template<typename K, typename D>
void HashMap<K, D>::insert(K key, D data) {
    int hashCode = key % hashTable.size();
    if (hashTable[hashCode].empty()) {
        count++;
    }
    hashTable[hashCode].push_front(std::make_pair(key, data));
    if (((double) count) / hashTable.size() > loadFactor)
        resize(); // size is doubled if load factor is met
}

template<typename K, typename D>
void HashMap<K, D>::resize() {
    std::vector<std::list<std::pair<K, D>>> newTable;
    newTable.resize(hashTable.size() * 2);
    count = 0;
    for (auto &list : hashTable) {
        for (auto &e : list) {
            int hashcode = e.first % newTable.size();
            if (newTable[hashcode].empty()) {
                count++;
            }
            newTable[hashcode].push_front(std::make_pair(e.first, e.second));
        }
    }
    hashTable = newTable;
}

template<typename K, typename D>
D &HashMap<K, D>::operator[](K Key) {
    int hashcode = Key % hashTable.size();
    auto &list = hashTable[hashcode];
    for (auto &e : list) {
        if (e.first == Key) {
            return e.second;
        }
    }
    insert(Key, D());
    operator[](Key);
}

template<typename K, typename D>
bool HashMap<K, D>::find(K Key) {
    int hashcode = Key % hashTable.size();
    auto &list = hashTable[hashcode];
    for (auto &e : list) {
        if (e.first == Key) {
            return true;
        }
    }
    return false;
}

template<typename K, typename D>
std::vector<std::list<std::pair<K, D>>> &HashMap<K, D>::getHashTable() {
    return hashTable;
}


#endif //TAXIPROJECT_HASHMAP_H
