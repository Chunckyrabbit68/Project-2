# PROJECT OVERVIEW

The Smart Campus Navigation and Facility Analytics System is a C++ program that manages campus facilities, building connections, and academic departments.

The program uses three main data structures:

Custom Hash Table: Stores campus facilities and allows searching by facility ID.

Campus Graph: Represents buildings and their connections using an undirected graph.

Department General Tree: Organizes university departments into a hierarchy.

The program reads campus information from text files and provides a menu for users to search, navigate, display information, and generate reports.

# PROJECT STRUCTURE

```text
Project-2/
    include/
        Facility.h
        FacilityDatabase.h
        HashTable.h
        CampusGraph.h
        DepartmentNode.h
        DepartmentTree.h

    src/
        main.cpp
        Facility.cpp
        FacilityDatabase.cpp
        HashTable.cpp
        CampusGraph.cpp
        departmentTree.cpp

    data/
        buildings.txt
        connections.txt
        facilities.txt
        departments.txt

    testdata/
        case1/
            buildings.txt
            connections.txt
            facilities.txt
            departments.txt

    README.txt
    CONTRIBUTIONS.txt
    design_document.txt
    test_results.txt
    .gitignore
```

# COMPILATION INSTRUCTIONS

The project uses C++17 and can be compiled using g++.

Open a terminal in the main Project-2 directory.

Compile the program using:

```
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o campus
```

If compilation is successful, an executable named campus will be created.

# RUNNING THE PROGRAM

To run the program using the default data files:

```
./campus
```

The program automatically loads the files located in the data/ directory.

To run the program with a different data directory:

```
./campus testdata/case1
```

The testdata/case1 directory contains additional records used to test input validation and edge cases.

The directory must contain input files using the required formats.

# INPUT FILES

The program uses four text files.

buildings.txt

Contains campus building names.

connections.txt

Contains connections between buildings.

facilities.txt

Contains facility IDs, names, building locations, and categories.

departments.txt

Contains department names and their parent departments.

The files are loaded in the following order:

1. buildings.txt
2. connections.txt
3. facilities.txt
4. departments.txt

Invalid records are rejected, and the program displays warnings and loading summaries.

# PROGRAM MENU

The final program provides the following options:

```text
1. View all facilities
2. Search facility by ID
3. Search facility by name
4. Search facility by category
5. View campus graph
6. Display graph counts and degrees
7. Find reachable buildings (BFS)
8. Find shortest path (BFS)
9. Add department
10. Search department
11. Display department hierarchy
12. Preorder traversal
13. Postorder traversal
14. Level-order traversal
15. Department statistics
16. Facility category report
17. Graph connectivity report
0. Exit
```

Users can select an option by entering its corresponding number.

Invalid menu choices are rejected. The menu continues displaying until the user exits.

# DATA STRUCTURES

## FACILITY DATABASE AND HASH TABLE

Facilities are stored in a vector to maintain their original file order.

A custom hash table is used to search for facilities by ID.

The hash table uses separate chaining to handle collisions.

Facility IDs are converted to uppercase before searching.

Duplicate facility IDs are rejected.

Facility name and category searches use linear search to find all matching facilities. Searches are case insensitive and use complete names or categories.

The facility category report displays the number and percentage of facilities belonging to each category, along with the total number of facilities.

## CAMPUS GRAPH

The campus graph uses an adjacency list.

Each building represents a vertex, and each connection represents an undirected edge.

The graph supports displaying connections, calculating building degrees, finding reachable buildings, and finding the shortest path between two buildings.

BFS uses a queue to visit buildings and calculate their distances from a starting location.

Shortest path searching uses BFS to determine the path with the fewest connections between two buildings.

The graph connectivity report displays:

- Total buildings
- Total connections
- Buildings with the highest degree
- Isolated buildings
- Number of connected components

## DEPARTMENT GENERAL TREE

The department hierarchy is represented using a general tree.

Each department can have multiple children and contains a pointer to its parent.

The tree supports adding departments, searching by name, displaying the hierarchy, and performing different tree traversals.

Preorder traversal visits the parent before visiting its children.

Postorder traversal visits the children before visiting their parent.

Level-order traversal uses a queue to visit departments one level at a time.

The department statistics report displays:

- Total number of departments
- Number of leaf departments
- Tree height

Dynamically allocated department nodes are released when the program exits.

# TESTING

The program was compiled and tested using GitHub Codespaces. The updated program was also compiled and tested using g++ with C++17 and compiler warnings enabled.

The following features have been successfully tested:

- Loading all four input files.
- Displaying all 10 facilities.
- Searching for an existing facility ID.
- Searching using a lowercase facility ID.
- Rejecting invalid facility IDs.
- Handling facility IDs that do not exist.
- Searching for facilities by name.
- Searching for facilities by category.
- Returning multiple matching facilities.
- Displaying all seven buildings and their connections.
- Displaying graph counts and degrees.
- Running BFS from Library.
- Running BFS from an isolated building.
- Handling an unknown starting building.
- Finding the shortest path between buildings.
- Handling buildings with no available path.
- Adding a department.
- Searching for a department.
- Displaying the department hierarchy.
- Performing preorder traversal.
- Performing postorder traversal.
- Performing level-order traversal.
- Displaying department statistics.
- Generating the facility category report.
- Generating the graph connectivity report.
- Handling invalid input records.
- Handling missing data files.

Additional testing information is included in test_results.txt.

The program must also be compiled and tested on UNT CSE CELL machines before submission.

# NOTES

All campus information is loaded from external files.

Campus records and report results are not hard-coded into the program.

The program supports an optional data directory for testing.

The GitHub repository contains the source code and project documentation.
