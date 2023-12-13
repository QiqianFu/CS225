/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 * @modified by Dustin, 2018
 */
#include "lphashtable.h"

using hashes::hash;
using std::pair;

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    int n = 1;
    int k = 0;
    if (shouldResize())
        resizeTable();
    if(keyExists(key)==true){
 
        unsigned int idx = hash(key,size);
        int old_idx = findIndex(key);
        size_t start = idx;

        if((int)old_idx == (int)idx){
            pair<K,V> *temp = table[idx];
            delete temp; 
            table[idx] = new pair<K, V>(key, value);
            return ;            
        }


        while(table[idx]) {
            if (k == 0 ){
                idx = (start + n*n) % size;
                k = 1;
            }else{
                idx = (start - n*n) % size;
                k = 0;
                n += 1;
            }
            if((int)old_idx == (int)idx){
                pair<K,V> *temp = table[idx];
                delete temp; 
                table[idx] = new pair<K, V>(key, value);
                return ;            
            }
            // if(start == idx){
            //     return;
            // }
        }

        pair<K,V> *temp = table[idx];

        should_probe[old_idx] = false;   
        delete temp; 
        table[old_idx] = NULL;

        table[idx] = new pair<K, V>(key, value);
        should_probe[idx] = true;  
        return ;
    }
    size_t idx = hash(key, size);
    size_t start = idx;
    while(table[idx]) {
        if (k == 0 ){
            idx = (start  + n*n) % size;
            k = 1;
        }else{
            idx = (start - n*n) % size;
            k = 0;
            n += 1;
        }
        // if(start == idx){
        //     return;
        // }
    }
    should_probe[idx] = true;   
    table[idx] = new pair<K, V>(key, value);
    elems++;
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    int idx = findIndex(key);
    if (idx != -1) {
        delete table[idx];
        table[idx] = NULL;
        --elems;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    size_t idx = hash(key, size);
    size_t start = idx;
    int n = 1;
    int k = 0;
    while (should_probe[idx]) {
        if (table[idx] != NULL && table[idx]->first == key)
            return idx;
        if(k==0){
            idx = (start + n*n) % size;
            k = 1;
        }else{
            idx = (start - n*n) % size;
            k = 0;
            n += 1;
        }
        // if we've looped all the way around, the key has not been found
        // if (idx == start)
        //     break;
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
    size_t newSize = findPrime(size * 2);
    pair<K, V>** temp = new pair<K, V>*[newSize];
    delete[] should_probe;
    should_probe = new bool[newSize];
    for (size_t i = 0; i < newSize; i++) {
        temp[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t i = 0; i < size; i++) {
        if (table[i] != NULL) {
            size_t idx = hash(table[i]->first, newSize);
            while (temp[idx] != NULL)
                idx = (idx + 1) % newSize;
            temp[idx] = table[i];
            should_probe[idx] = true;
        }
    }

    delete[] table;
    // don't delete elements since we just moved their pointers around
    table = temp;
    size = newSize;
}