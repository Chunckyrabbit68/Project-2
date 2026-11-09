
#include <iostream>
#include <string>
#include <sstream>

#include "../include/FacilityDatabase.h"
#include "../include/CampusGraph.h"
#include "../include/DepartmentTree.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Use data/ by default or a custom directory for testing
    string dataDirectory = "data/";

    if (argc > 1) {
        dataDirectory = argv[1];

        if (!dataDirectory.empty() && dataDirectory.back() != '/') {
            dataDirectory += "/";
        }
    }

    // Initialize the three main systems
    FacilityDatabase database;
    CampusGraph graph;
    DepartmentTree tree;

    // Load files in the required order
    graph.loadBuildings(dataDirectory + "buildings.txt");
    graph.loadConnections(dataDirectory + "connections.txt");

    database.loadFacilities(
        dataDirectory + "facilities.txt",
        graph.getBuildings()
    );

    tree.loadFromFile(dataDirectory + "departments.txt");

    string input;
    int choice = -1;

    while (choice != 0) {

        cout << "\n===== SMART CAMPUS NAVIGATION =====\n";
        cout << "1. View all facilities\n";
        cout << "2. Search facility by ID\n";
        cout << "3. View campus graph\n";
        cout << "4. Display graph counts and degrees\n";
        cout << "5. Find reachable buildings (BFS)\n";
        cout << "6. Add department\n";
        cout << "7. Search department\n";
        cout << "8. Display department hierarchy\n";
        cout << "9. Run preorder traversal\n";
        cout << "10. Find shortest path (BFS)\n";
        cout << "11. Graph connectivity report\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!getline(cin, input)) {
            break;
        }

        stringstream ss(input);
        string extra;

        if (!(ss >> choice) || (ss >> extra) ||
            choice < 0 || choice > 11) {
            cout << "Invalid menu choice.\n";
            choice = -1;
            continue;
        }

        switch (choice) {

            case 1:
                database.displayFacilities();
                break;

            case 2: {
                string id;

                cout << "Enter facility ID: ";
                getline(cin, id);

                database.searchFacilityByID(id);
                break;
            }

            case 3:
                graph.displayGraph();
                break;

            case 4:
                graph.displayStatistics();
                break;

            case 5: {
                string building;

                cout << "Enter starting building: ";
                getline(cin, building);

                if (building.find_first_not_of(" \t\r") == string::npos) {
                    cout << "Error: Building name cannot be empty.\n";
                    break;
                }

                graph.bfs(building);
                break;
            }

            case 6: {
                string name;
                string parent;

                cout << "Enter new department name: ";
                getline(cin, name);

                if (name.find_first_not_of(" \t\r") == string::npos) {
                    cout << "Error: Department name cannot be empty.\n";
                    break;
                }

                cout << "Enter parent department";
                cout << " (leave blank if creating the root): ";
                getline(cin, parent);

                tree.addDepartment(name, parent);
                break;
            }

            case 7: {
                string name;

                cout << "Enter department name: ";
                getline(cin, name);

                if (name.find_first_not_of(" \t\r") == string::npos) {
                    cout << "Error: Department name cannot be empty.\n";
                    break;
                }

                tree.searchDepartment(name);
                break;
            }

            case 8:
                tree.displayHierarchy();
                break;

            case 9:
                tree.preorderTraversal();
                break;

            case 10: {
                string start;
                string destination;

                cout << "Enter starting building: ";
                getline(cin, start);

                cout << "Enter destination building: ";
                getline(cin, destination);

                if (start.find_first_not_of(" \t\r") == string::npos ||
                    destination.find_first_not_of(" \t\r") == string::npos) {
                    cout << "Error: Building cannot be empty\n";
                    break;
                }

                graph.shortestPath(start, destination);
                break;
            }

            case 11:
                graph.displayConnectivityReport();
                break;

            case 0:
                cout << "Exiting program.\n";
                break;
        }
    }

    return 0;
}
