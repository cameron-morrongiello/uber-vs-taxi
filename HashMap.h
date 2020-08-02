//
// Created by ivano on 7/31/2020.
//

#ifndef TAXIPROJECT_HASHMAP_H
#define TAXIPROJECT_HASHMAP_H

#include <vector>
#include <list>

template<typename K, typename D>
class HashMap {
    std::vector<std::list<std::pair<K,D>>> hashTable;
    int size;
    double loadFactor;
public:
    HashMap();
    void insert(K key, D data);
};

template<typename K, typename D>
HashMap<K, D>::HashMap() : size(0), loadFactor(0.0) {
    hashTable.reserve(11);
}

template<typename K, typename D>
void HashMap<K, D>::insert(K key, D data) {
    int hashCode = key % hashTable.size();
    hashTable[hashCode].insert(std::make_pair(key, data));
    size++;
    //todo change size of table based on load factor
}


#endif //TAXIPROJECT_HASHMAP_H
