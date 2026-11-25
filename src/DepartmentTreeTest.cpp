#include <iostream>
#include "../include/DepartmentTree.h"

using namespace std;

// Tests the Department Tree Final requirements
int main() {
    // Test 1: Sample department tree
    cout << "===== SAMPLE TREE =====\n";
    {
        DepartmentTree tree;
        tree.loadFromFile("data/departments.txt");

        cout << "\nPostorder Traversal:\n";
        tree.postorderTraversal();

        cout << "\nLevel-Order Traversal:\n";
        tree.levelOrderTraversal();

        cout << "\nDepartment Statistics:\n";
        tree.displayStatistics();
    }

    // Test 2: Empty department tree
    cout << "\n===== EMPTY TREE =====\n";
    {
        DepartmentTree tree;
        tree.postorderTraversal();
        tree.levelOrderTraversal();
        tree.displayStatistics();
    }

    // Test 3: Root-only department tree
    cout << "\n===== ROOT-ONLY TREE =====\n";
    {
        DepartmentTree tree;
        tree.addDepartment("University", "");

        cout << "\nPostorder Traversal:\n";
        tree.postorderTraversal();

        cout << "\nLevel-Order Traversal:\n";
        tree.levelOrderTraversal();

        cout << "\nDepartment Statistics:\n";
        tree.displayStatistics();
    }

    return 0;
}
