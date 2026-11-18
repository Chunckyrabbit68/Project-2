#include "../include/FacilityDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>

// Initializes facility database
FacilityDatabase::FacilityDatabase()
    : acceptedCount(0), rejectedCount(0) {
}

// Removes whitespace from beginning and end
std::string FacilityDatabase::trim(const std::string& text) const {
    size_t start = 0;
    size_t end = text.length();

    while (start < end &&
           std::isspace(static_cast<unsigned char>(text[start]))) {
        start++;
    }

    while (end > start &&
           std::isspace(static_cast<unsigned char>(text[end - 1]))) {
        end--;
    }

    return text.substr(start, end - start);
}

// Converts text to uppercase
std::string FacilityDatabase::toUpper(const std::string& text) const {
    std::string result = text;

    for (char& c : result) {
        c = static_cast<char>(
            std::toupper(static_cast<unsigned char>(c))
        );
    }

    return result;
}

// Validates facility ID format
bool FacilityDatabase::isValidID(const std::string& id) const {
    if (id.length() != 4 || id[0] != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }

    return true;
}

// Loads facilities from a text file
void FacilityDatabase::loadFacilities(
    const std::string& filename,
    const std::vector<std::string>& buildings
) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Cannot open " << filename << "\n";
        displayLoadSummary();
        return;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::vector<std::string> fields;
        size_t start = 0;

        while (true) {
            size_t pos = line.find('|', start);

            if (pos == std::string::npos) {
                fields.push_back(trim(line.substr(start)));
                break;
            }

            fields.push_back(trim(line.substr(start, pos - start)));
            start = pos + 1;
        }

        std::string reason;

        if (fields.size() != 4) {
            reason = "Incorrect number of fields";
        } else {
            std::string id = toUpper(fields[0]);
            std::string name = fields[1];
            std::string building = fields[2];
            std::string category = fields[3];

            if (id.empty() || name.empty() ||
                building.empty() || category.empty()) {
                reason = "Empty required field";
            } else if (!isValidID(id)) {
                reason = "Invalid facility ID (expected F plus three digits)";
            } else {
                bool buildingFound = false;

                for (const std::string& validBuilding : buildings) {
                    if (toUpper(trim(validBuilding)) == toUpper(building)) {
                        building = validBuilding;
                        buildingFound = true;
                        break;
                    }
                }

                if (!buildingFound) {
                    reason = "Unknown building: " + building;
                } else {
                    Facility facility(id, name, building, category);

                    if (!hashTable.insert(facility)) {
                        reason = "Duplicate facility ID: " + id;
                    } else {
                        facilities.push_back(facility);
                        acceptedCount++;
                    }
                }
            }
        }

        if (!reason.empty()) {
            rejectedCount++;

            std::cout << "Warning: " << filename
                      << " line " << lineNumber
                      << ": " << reason << "\n";
        }
    }

    file.close();
    displayLoadSummary();
}

// Displays all accepted facilities
void FacilityDatabase::displayFacilities() const {
    if (facilities.empty()) {
        std::cout << "No facilities available.\n";
        std::cout << "Total facilities: 0\n";
        return;
    }

    for (const Facility& facility : facilities) {
        std::cout << "\nID: " << facility.getID() << "\n";
        std::cout << "Name: " << facility.getName() << "\n";
        std::cout << "Building: " << facility.getBuilding() << "\n";
        std::cout << "Category: " << facility.getCategory() << "\n";
    }

    std::cout << "\nTotal facilities: "
              << facilities.size() << "\n";
}

// Searches for a facility by ID
void FacilityDatabase::searchFacilityByID(const std::string& input) const {
    std::string id = toUpper(trim(input));

    if (!isValidID(id)) {
        std::cout << "Invalid facility ID.\n";
        std::cout << "ID must be F followed by exactly three digits.\n";
        return;
    }

    const Facility* facility = hashTable.search(id);

    if (facility == nullptr) {
        std::cout << "Facility " << id << " not found.\n";
        return;
    }

    std::cout << "\nFacility Found!\n";
    std::cout << "ID: " << facility->getID() << "\n";
    std::cout << "Name: " << facility->getName() << "\n";
    std::cout << "Building: " << facility->getBuilding() << "\n";
    std::cout << "Category: " << facility->getCategory() << "\n";
}

// Displays loading and hash table statistics
void FacilityDatabase::displayLoadSummary() const {
    std::cout << "\nfacilities.txt: "
              << acceptedCount << " accepted, "
              << rejectedCount << " rejected\n";

    std::cout << "Hash capacity: "
              << hashTable.getCapacity() << "\n";

    std::cout << "Hash entries: "
              << hashTable.getEntryCount() << "\n";

    std::cout << "Hash collisions: "
              << hashTable.getCollisionCount() << "\n";
    
}
// Searches for facilities by complete name
void FacilityDatabase::searchFacilityByName(const std::string& input) const {
    std::string name = toUpper(trim(input));
    int matches = 0;

    if (name.empty()) {
        std::cout << "Error: Facility name cannot be blank.\n";
        return;
    }

    for (const Facility& facility : facilities) {
        if (toUpper(facility.getName()) == name) {
            std::cout << "\nID: " << facility.getID() << "\n";
            std::cout << "Name: " << facility.getName() << "\n";
            std::cout << "Building: " << facility.getBuilding() << "\n";
            std::cout << "Category: " << facility.getCategory() << "\n";
            matches++;
        }
    }

    if (matches == 0) {
        std::cout << "No facilities found with that name.\n";
    }

    std::cout << "Matches: " << matches << "\n";
}

// Searches for facilities by category
void FacilityDatabase::searchFacilityByCategory(const std::string& input) const {
    std::string category = toUpper(trim(input));
    int matches = 0;

    if (category.empty()) {
        std::cout << "Error: Category cannot be blank.\n";
        return;
    }

    for (const Facility& facility : facilities) {
        if (toUpper(facility.getCategory()) == category) {
            std::cout << "\nID: " << facility.getID() << "\n";
            std::cout << "Name: " << facility.getName() << "\n";
            std::cout << "Building: " << facility.getBuilding() << "\n";
            std::cout << "Category: " << facility.getCategory() << "\n";
            matches++;
        }
    }

    if (matches == 0) {
        std::cout << "No facilities found in that category.\n";
    }

    std::cout << "Matches: " << matches << "\n";
}

// Displays facility counts and percentages by category
void FacilityDatabase::displayCategoryReport() const {
    if (facilities.empty()) {
        std::cout << "No facilities available.\n";
        std::cout << "Total facilities: 0\n";
        return;
    }

    std::vector<std::string> categories;
    std::vector<int> counts;

    for (const Facility& facility : facilities) {
        std::string category = facility.getCategory();
        bool found = false;

        for (size_t i = 0; i < categories.size(); i++) {
            if (toUpper(categories[i]) == toUpper(category)) {
                counts[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
        categories.push_back(category);
        counts.push_back(1);
    
        }
  }

 std::cout << "\n===== FACILITY CATEGORY REPORT =====\n";

for (size_t i = 0; i < categories.size(); i++) {
    double percentage =
        (static_cast<double>(counts[i]) / facilities.size()) * 100.0;

    std::cout << categories[i]
              << " | Count: " << counts[i]
              << " | Percentage: "
              << std::fixed << std::setprecision(1)
              << percentage << "%\n";
}

std::cout << "\nTotal facilities: "
          << facilities.size() << "\n";
}
  
