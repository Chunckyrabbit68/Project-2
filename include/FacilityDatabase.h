#pragma once

#include <string>
#include <vector>
#include "Facility.h"
#include "HashTable.h"

class FacilityDatabase {
private:
    std::vector<Facility> facilities;
    HashTable hashTable;

    int acceptedCount;
    int rejectedCount;

    // Removes whitespace from the beginning and end
    std::string trim(const std::string& text) const;

    // Converts text to uppercase
    std::string toUpper(const std::string& text) const;

    // Checks whether an ID follows F followed by three digits
    bool isValidID(const std::string& id) const;

public:
    FacilityDatabase();

    // Loads and validates facilities from a file
    void loadFacilities(
        const std::string& filename,
        const std::vector<std::string>& buildings
    );

    // Displays all accepted facilities
    void displayFacilities() const;

    // Searches for a facility by ID
    void searchFacilityByID(const std::string& id) const;

    // Displays loading and hash table statistics
    void displayLoadSummary() const;
};
