#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include "DepartmentNode.h"
using namespace std;

class DepartmentTree{
private:
    DepartmentNode* root;

    DepartmentNode* findNode(DepartmentNode* current, const string& name) const;
    void displayHierarchyHelper(DepartmentNode* current, int depth) const;
    void preorderHelper(DepartmentNode* current) const;
    void deleteTree(DepartmentNode* current);

public:
    DepartmentTree();
    ~DepartmentTree();

    //adds a new department under an existing parent
    bool addDepartment(const string& name, const string& parentName); 

    //searches for a department and displays its info
    void searchDepartment(const string& name) const;

    //displays the department hierarchy with indentation
    void displayHierarchy() const;

    //displays the departments using preorder trasversal
    void preorderTraversal() const;

    //Loads department records from a text file
    void loadFromFile(const string& filename);
};

#endif