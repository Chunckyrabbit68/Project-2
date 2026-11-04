#include <string>
#include <vector>
using namespace std;

#ifndef DEPARTMENTNODE_H
#define DEPARTMENTNODE_H

struct DepartmentNode{
    string name;
    DepartmentNode* parent;
    vector<DepartmentNode*> children;

    DepartmentNode(string departmentName, DepartmentNode* parentNode = nullptr){
        name = departmentName;
        parent = parentNode;
    }
};

#endif