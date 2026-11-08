#include "../include/Facility.h"

// Constructor initializes facility information
Facility::Facility(const std::string& id,
                   const std::string& name,
                   const std::string& building,
                   const std::string& category)
    : id(id), name(name), building(building), category(category) {
}

// Returns facility ID
std::string Facility::getID() const {
    return id;
}

// Returns facility name
std::string Facility::getName() const {
    return name;
}

// Returns building location
std::string Facility::getBuilding() const {
    return building;
}

// Returns facility category
std::string Facility::getCategory() const {
    return category;
}
