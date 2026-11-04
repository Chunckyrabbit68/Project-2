#include <iostream>
#include "DepartmentTree.h"
using namespace std;

//Test main code
int main() {
    DepartmentTree tree;

    //loads department data
    tree.loadFromFile("data/departments.txt");

    cout << "\nDepartment Hierarchy:\n";
    tree.displayHierarchy();

    cout << "\nPreorder Traversal:\n";
    tree.preorderTraversal();

    return 0;
}
