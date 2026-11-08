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
