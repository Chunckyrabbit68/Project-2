
#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

class CampusGraph {
private:
    // Stores building names in insertion order
    std::vector<std::string> buildings;

    // Adjacency list storing building connections
    std::vector<std::vector<int>> adjacencyList;

    // Total number of undirected connections
    int connectionCount;

    // Finds a building using case-insensitive matching
    int findBuilding(const std::string& name) const;

    // Removes surrounding whitespace
    std::string trim(const std::string& text) const;

    // Converts text to uppercase
    std::string toUpper(const std::string& text) const;

public:
    // Initializes an empty campus graph
    CampusGraph();

    // Adds a building if it does not already exist
    bool addBuilding(const std::string& name);

    // Adds an undirected connection between buildings
    bool addConnection(
        const std::string& buildingA,
        const std::string& buildingB
    );

    // Loads buildings and connections from files
    void loadBuildings(const std::string& filename);
    void loadConnections(const std::string& filename);

    // Displays buildings and their connections
    void displayGraph() const;

    // Displays building counts and degrees
    void displayStatistics() const;

    // Finds reachable buildings using BFS
    void bfs(const std::string& startBuilding) const;

    // finds the shortest path between buildings BFS
    void shortestPath(
        const std::string& startBuilding,
        const std::string& endBuilding
    ) const;

    void displayConnectivityReport() const;

    // Provides accepted building names for facility validation
    const std::vector<std::string>& getBuildings() const;
};

#endif
