#pragma once

#include <string>

class Facility {
private:
    std::string id;
    std::string name;
    std::string building;
    std::string category;

public:
    Facility(const std::string& id,
             const std::string& name,
             const std::string& building,
             const std::string& category);

    std::string getID() const;
    std::string getName() const;
    std::string getBuilding() const;
    std::string getCategory() const;
};
