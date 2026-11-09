# Project-2 PROJECT OVERVIEW

The Smart Campus Navigation and Facility Analytics System is a C++ program that manages campus facilities, building connections, and academic departments.

The program uses three main data structures:

Custom Hash Table: Stores campus facilities and allows searching by facility ID.

Campus Graph: Represents buildings and their connections using an undirected graph.

Department General Tree: Organizes university departments into a hierarchy.

The program reads campus information from text files and provides a menu for users to access each feature.

PROJECT STRUCTURE

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

Additional test files

Documentation:

README.txt

CONTRIBUTIONS.txt

design_document.txt

test_results.txt

.gitignore

COMPILATION INSTRUCTIONS

The project uses C++17 and can be compiled using g++.

Open a terminal in the main Project-2 directory.

Compile the program using:

g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o campus

If compilation is successful, an executable named campus will be created.

RUNNING THE PROGRAM

To run the program using the default data files:

./campus

The program automatically loads the files located in the data/ directory.

To run the program with a different data directory:

./campus testdata/case1

testdata/case1 also contains graph edge cases.

The directory must contain input files using the required formats.

INPUT FILES

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

buildings.txt

connections.txt

facilities.txt

departments.txt

Invalid records are rejected, and the program displays warnings and loading summaries.

PROGRAM MENU

The Milestone 1 program provides the following options:

View all facilities

Search facility by ID

View campus graph

Display graph counts and degrees

Find reachable buildings (BFS)

Add department

Search department

Display department hierarchy

Run preorder traversal

Find shortest path (BFS)

Graph connectivity report

Exit

Users can select an option by entering its corresponding number.

The menu continues displaying until the user exits.

DATA STRUCTURES

FACILITY DATABASE AND HASH TABLE

Facilities are stored in a vector to maintain their original file order.

A custom hash table is used to search for facilities by ID.

The hash table uses separate chaining to handle collisions.

Facility IDs are converted to uppercase before searching.

Duplicate facility IDs are rejected.

CAMPUS GRAPH

The campus graph uses an adjacency list.

Each building represents a vertex, and each connection represents an undirected edge.

The graph supports displaying connections, calculating building degrees, finding reachable buildings, finding the shortest path between two buildings, connectivity report.

BFS uses a queue to visit buildings and calculate their distances from a starting location.

DEPARTMENT GENERAL TREE

The department hierarchy is represented using a general tree.

Each department can have multiple children.

The tree supports adding departments, searching by name, displaying the hierarchy, and preorder traversal.

TESTING

The program was compiled and tested using GitHub Codespaces.

The following features were successfully tested using the provided sample data:

Loading all four input files.

Displaying all 10 facilities.

Searching for an existing facility.

Searching using a lowercase facility ID.

Rejecting an invalid facility ID.

Handling a facility ID that does not exist.

Displaying all seven buildings and their connections.

Displaying graph counts and degrees.

Running BFS from Library.

Running BFS from an isolated building.

Handling an unknown starting building.

Adding a department.

Searching for a department.

Displaying the department hierarchy.

Performing preorder traversal.

Additional edge-case testing is required before final submission.

The program must also be compiled and tested on UNT CSE CELL machines before submission.

NOTES

All campus information is loaded from external files.

Campus records and report results are not hard-coded into the program.

The program supports an optional data directory for testing.

The GitHub repository contains the source code and project documentation.
