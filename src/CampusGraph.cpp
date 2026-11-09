#include "../include/CampusGraph.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cctype>

using namespace std;

// Initializes the campus graph
CampusGraph::CampusGraph() : connectionCount(0) {
}

// Removes whitespace from the beginning and end
string CampusGraph::trim(const string& text) const {
    size_t start = 0;
    size_t end = text.length();

    while (start < end &&
           isspace(static_cast<unsigned char>(text[start]))) {
        start++;
    }

    while (end > start &&
           isspace(static_cast<unsigned char>(text[end - 1]))) {
        end--;
    }

    return text.substr(start, end - start);
}

// Converts text to uppercase
string CampusGraph::toUpper(const string& text) const {
    string result = text;

    for (char& c : result) {
        c = static_cast<char>(
            toupper(static_cast<unsigned char>(c))
        );
    }

    return result;
}

// Finds a building by name, ignoring capitalization
int CampusGraph::findBuilding(const string& name) const {
    string target = toUpper(trim(name));

    for (size_t i = 0; i < buildings.size(); i++) {
        if (toUpper(buildings[i]) == target) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// Adds a building if it is valid and unique
bool CampusGraph::addBuilding(const string& name) {
    string buildingName = trim(name);

    if (buildingName.empty()) {
        return false;
    }

    if (findBuilding(buildingName) != -1) {
        return false;
    }

    buildings.push_back(buildingName);
    adjacencyList.push_back(vector<int>());

    return true;
}

// Adds an undirected connection
bool CampusGraph::addConnection(
    const string& buildingA,
    const string& buildingB
) {
    int indexA = findBuilding(buildingA);
    int indexB = findBuilding(buildingB);

    // Reject unknown buildings
    if (indexA == -1 || indexB == -1) {
        return false;
    }

    // Reject self-connections
    if (indexA == indexB) {
        return false;
    }

    // Reject duplicate and reversed connections
    for (int neighbor : adjacencyList[indexA]) {
        if (neighbor == indexB) {
            return false;
        }
    }

    // Add both directions
    adjacencyList[indexA].push_back(indexB);
    adjacencyList[indexB].push_back(indexA);

    // Count the undirected connection once
    connectionCount++;

    return true;
}

// Loads buildings from buildings.txt
void CampusGraph::loadBuildings(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open " << filename << "\n";
        cout << "buildings.txt: 0 accepted, 0 rejected\n";
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (getline(file, line)) {
        lineNumber++;

        line = trim(line);

        // Skip blank lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (line.find('|') != string::npos) {
            rejected++;

            cout << "Warning: " << filename
                 << " line " << lineNumber
                 << ": Incorrect number of fields\n";

            continue;
        }

        if (!addBuilding(line)) {
            rejected++;

            cout << "Warning: " << filename
                 << " line " << lineNumber
                 << ": Duplicate or invalid building: "
                 << line << "\n";

            continue;
        }

        accepted++;
    }

    cout << "buildings.txt: "
         << accepted << " accepted, "
         << rejected << " rejected\n";
}

// Loads building connections from connections.txt
void CampusGraph::loadConnections(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open " << filename << "\n";
        cout << "connections.txt: 0 accepted, 0 rejected\n";
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (getline(file, line)) {
        lineNumber++;

        line = trim(line);

        // Skip blank lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        string reason;
        size_t separator = line.find('|');

        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {
            reason = "Incorrect number of fields";
        } else {
            string buildingA = trim(line.substr(0, separator));
            string buildingB = trim(line.substr(separator + 1));

            if (buildingA.empty() || buildingB.empty()) {
                reason = "Empty required field";
            } else {
                int indexA = findBuilding(buildingA);
                int indexB = findBuilding(buildingB);

                if (indexA == -1) {
                    reason = "Unknown building: " + buildingA;
                } else if (indexB == -1) {
                    reason = "Unknown building: " + buildingB;
                } else if (indexA == indexB) {
                    reason = "Self-connection is not allowed";
                } else if (!addConnection(buildingA, buildingB)) {
                    reason = "Duplicate connection";
                } else {
                    accepted++;
                }
            }
        }

        if (!reason.empty()) {
            rejected++;

            cout << "Warning: " << filename
                 << " line " << lineNumber
                 << ": " << reason << "\n";
        }
    }

    cout << "connections.txt: "
         << accepted << " accepted, "
         << rejected << " rejected\n";
}

// Displays the campus graph
void CampusGraph::displayGraph() const {
    if (buildings.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }

    for (size_t i = 0; i < buildings.size(); i++) {
        cout << buildings[i] << ": ";

        if (adjacencyList[i].empty()) {
            cout << "(no connections)";
        } else {
            for (size_t j = 0; j < adjacencyList[i].size(); j++) {
                if (j > 0) {
                    cout << ", ";
                }

                cout << buildings[adjacencyList[i][j]];
            }
        }

        cout << "\n";
    }
}

// Displays building counts and degrees
void CampusGraph::displayStatistics() const {
    cout << "\nTotal buildings: "
         << buildings.size() << "\n";

    cout << "Total connections: "
         << connectionCount << "\n";

    if (buildings.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }

    for (size_t i = 0; i < buildings.size(); i++) {
        cout << buildings[i]
             << " - Degree: "
             << adjacencyList[i].size()
             << "\n";
    }
}

// Finds reachable buildings using breadth-first search
void CampusGraph::bfs(const string& startBuilding) const {
    int start = findBuilding(startBuilding);

    if (start == -1) {
        cout << "Error: Unknown building: "
             << trim(startBuilding) << "\n";
        return;
    }

    vector<bool> visited(buildings.size(), false);
    vector<int> distance(buildings.size(), -1);
    queue<int> q;

    // Mark the starting building visited when enqueued
    visited[start] = true;
    distance[start] = 0;
    q.push(start);

    int reachableCount = 0;

    cout << "\nReachable buildings:\n";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << buildings[current]
             << " (distance "
             << distance[current] << ")\n";

        reachableCount++;

        // Visit neighboring buildings in insertion order
        for (int neighbor : adjacencyList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }

    cout << "Reachable: "
         << reachableCount << " of "
         << buildings.size()
         << " buildings\n";
}

// Returns accepted building names for facility validation
const vector<string>& CampusGraph::getBuildings() const {
    return buildings;
}

// Find shortest path between two buildings BFS
void CampusGraph::shortestPath(
    const string& startBuilding,
    const string& endBuilding
) const {
    int start = findBuilding(startBuilding);
    int destination = findBuilding(endBuilding);

    // Identify every unknown building
    if (start == -1) {
        cout << "Error: Unknown building: "
             << trim(startBuilding) << "\n";
    }

    if (destination == -1) {
        cout << "Error: Unknown building: "
             << trim(endBuilding) << "\n";
    }

    if (start == -1 || destination == -1) {
        return;
    }

    vector<bool> visited(buildings.size(), false);

    // Stores building each was reached from
    vector<int> previous(buildings.size(), -1);
    queue<int> q;

    // starting building visited when enqueued
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Visit neighboring buildings
        for (int neighbor : adjacencyList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                previous[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    if (!visited[destination]) {
        cout << "No path exists between "
             << buildings[start] << " and "
             << buildings[destination] << "\n";
        return;
    }

    // Rebuild the path from destination to start
    vector<int> path;
    int building = destination;

    while (building != -1) {
        path.push_back(building);
        building = previous[building];
    }

    cout << "\nShortest path:\n";

    // Print the path begins at the start building
    for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--) {
        cout << buildings[path[i]] << "\n";
    }

    cout << "Number of connections: "
         << path.size() - 1 << "\n";
}

// display totals, highest degree, isolated buildings, and components
void CampusGraph::displayConnectivityReport() const {
    if (buildings.empty()) {
        cout << "No buildings are loaded.\n";
        cout << "Total buildings: 0\n";
        cout << "Total connections: 0\n";
        cout << "Connected components: 0\n";
        return;
    }

    cout << "\nTotal buildings: "
         << buildings.size() << "\n";

    cout << "Total connections: "
         << connectionCount << "\n";

    // Finds highest degree list every building tied 
    size_t highestDegree = 0;

    for (size_t i = 0; i < buildings.size(); i++) {
        if (adjacencyList[i].size() > highestDegree) {
            highestDegree = adjacencyList[i].size();
        }
    }

    cout << "Highest degree (" << highestDegree << "): ";

    bool first = true;

    for (size_t i = 0; i < buildings.size(); i++) {
        if (adjacencyList[i].size() == highestDegree) {
            if (!first) {
                cout << ", ";
            }

            cout << buildings[i];
            first = false;
        }
    }

    cout << "\n";

    // Isolated buildings no connections
    cout << "Isolated buildings: ";

    bool foundIsolated = false;

    for (size_t i = 0; i < buildings.size(); i++) {
        if (adjacencyList[i].empty()) {
            if (foundIsolated) {
                cout << ", ";
            }

            cout << buildings[i];
            foundIsolated = true;
        }
    }

    if (!foundIsolated) {
        cout << "None";
    }

    cout << "\n";

    // BFS from an unvisited building finds one new component
    vector<bool> visited(buildings.size(), false);
    int componentCount = 0;

    for (size_t i = 0; i < buildings.size(); i++) {
        if (visited[i]) {
            continue;
        }

        componentCount++;

        queue<int> q;

        visited[i] = true;
        q.push(static_cast<int>(i));

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    cout << "Connected components: "
         << componentCount << "\n";
}
