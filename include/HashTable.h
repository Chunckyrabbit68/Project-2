#pragma once

#include <string>
#include <vector>
#include "Facility.h"

class HashTable {
private:
    static const int TABLE_SIZE = 11;

    // Separate chaining handles hash collisions
    std::vector<std::vector<Facility>> table;

    int entryCount;
    int collisionCount;

    // Calculates a hash index from a facility ID
    int hashFunction(const std::string& key) const;

public:
    // Initializes the hash table
    HashTable();

    // Inserts a facility, rejecting duplicate IDs
    bool insert(const Facility& facility);

    // Searches for a facility using its ID
    const Facility* search(const std::string& id) const;

    // Returns hash table statistics
    int getCapacity() const;
    int getEntryCount() const;
    int getCollisionCount() const;
};
