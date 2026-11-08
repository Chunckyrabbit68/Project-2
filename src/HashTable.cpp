#include "../include/HashTable.h"
#include <cctype>

// Initializes the hash table
HashTable::HashTable()
    : table(TABLE_SIZE), entryCount(0), collisionCount(0) {
}

// Calculates a hash index using the facility ID
int HashTable::hashFunction(const std::string& key) const {
    unsigned long hash = 0;

    for (char c : key) {
        hash = (hash * 31 + static_cast<unsigned char>(c))
               % table.size();
    }

    return static_cast<int>(hash);
}

// Inserts a facility using separate chaining
bool HashTable::insert(const Facility& facility) {
    std::string id = facility.getID();

    // Convert ID to uppercase
    for (char& c : id) {
        c = static_cast<char>(
            std::toupper(static_cast<unsigned char>(c))
        );
    }

    int index = hashFunction(id);

    // Check for duplicate IDs
    for (const Facility& existing : table[index]) {
        if (existing.getID() == id) {
            return false;
        }
    }

    // Count collisions only for accepted insertions
    if (!table[index].empty()) {
        collisionCount++;
    }

    table[index].push_back(facility);
    entryCount++;

    return true;
}

// Searches for a facility by ID
const Facility* HashTable::search(const std::string& id) const {
    std::string key = id;

    // Normalize ID to uppercase
    for (char& c : key) {
        c = static_cast<char>(
            std::toupper(static_cast<unsigned char>(c))
        );
    }

    int index = hashFunction(key);

    for (const Facility& facility : table[index]) {
        if (facility.getID() == key) {
            return &facility;
        }
    }

    return nullptr;
}

// Returns the hash table capacity
int HashTable::getCapacity() const {
    return static_cast<int>(table.size());
}

// Returns the number of stored facilities
int HashTable::getEntryCount() const {
    return entryCount;
}

// Returns the number of collisions
int HashTable::getCollisionCount() const {
    return collisionCount;
}
