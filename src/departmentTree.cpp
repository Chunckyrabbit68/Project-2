#include "../include/DepartmentTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>

using namespace std;

// Removes whitespace from the beginning and end
static string trim(const string& text) {
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

// Converts text to uppercase for case-insensitive comparisons
static string toUpper(const string& text) {
    string result = text;

    for (char& c : result) {
        c = static_cast<char>(
            toupper(static_cast<unsigned char>(c))
        );
    }

    return result;
}

// Initializes an empty department tree
DepartmentTree::DepartmentTree() {
    root = nullptr;
}

// Releases dynamically allocated department nodes
DepartmentTree::~DepartmentTree() {
    deleteTree(root);
}

// Recursively deletes the tree
void DepartmentTree::deleteTree(DepartmentNode* current) {
    if (current == nullptr) {
        return;
    }

    for (DepartmentNode* child : current->children) {
        deleteTree(child);
    }

    delete current;
}

// Searches recursively for a department
DepartmentNode* DepartmentTree::findNode(
    DepartmentNode* current,
    const string& name
) const {
    if (current == nullptr) {
        return nullptr;
    }

    if (toUpper(current->name) == toUpper(trim(name))) {
        return current;
    }

    for (DepartmentNode* child : current->children) {
        DepartmentNode* found = findNode(child, name);

        if (found != nullptr) {
            return found;
        }
    }

    return nullptr;
}

// Adds a department under an existing parent
bool DepartmentTree::addDepartment(
    const string& name,
    const string& parentName
) {
    string departmentName = trim(name);
    string parent = trim(parentName);

    if (departmentName.empty()) {
        cout << "Error: Department name cannot be empty.\n";
        return false;
    }

    // Reject duplicate department names
    if (findNode(root, departmentName) != nullptr) {
        cout << "Error: Department already exists: "
             << departmentName << "\n";
        return false;
    }

    // First department becomes the root
    if (root == nullptr) {
        root = new DepartmentNode(departmentName);

        cout << "Root department added: "
             << departmentName << "\n";

        return true;
    }

    // Locate the parent department
    DepartmentNode* parentNode = findNode(root, parent);

    if (parentNode == nullptr) {
        cout << "Error: Unknown parent department: "
             << parent << "\n";
        return false;
    }

    // Create and attach the department
    DepartmentNode* newNode =
        new DepartmentNode(departmentName, parentNode);

    parentNode->children.push_back(newNode);

    cout << "Department added: "
         << departmentName << "\n";

    return true;
}

// Searches for a department and displays its information
void DepartmentTree::searchDepartment(const string& name) const {
    string departmentName = trim(name);

    if (departmentName.empty()) {
        cout << "Error: Department name cannot be empty.\n";
        return;
    }

    DepartmentNode* department = findNode(root, departmentName);

    if (department == nullptr) {
        cout << "Department not found: "
             << departmentName << "\n";
        return;
    }

    int depth = 0;
    DepartmentNode* current = department;

    // Calculate depth by following parent pointers
    while (current->parent != nullptr) {
        depth++;
        current = current->parent;
    }

    cout << "\nDepartment Found!\n";
    cout << "Name: " << department->name << "\n";

    if (department->parent == nullptr) {
        cout << "Parent: None\n";
    } else {
        cout << "Parent: "
             << department->parent->name << "\n";
    }

    cout << "Direct children: "
         << department->children.size() << "\n";

    cout << "Depth: " << depth << "\n";
}

// Recursively displays the hierarchy
void DepartmentTree::displayHierarchyHelper(
    DepartmentNode* current,
    int depth
) const {
    if (current == nullptr) {
        return;
    }

    // Four spaces per depth level
    cout << string(depth * 4, ' ')
         << current->name << "\n";

    for (DepartmentNode* child : current->children) {
        displayHierarchyHelper(child, depth + 1);
    }
}

// Displays the complete department hierarchy
void DepartmentTree::displayHierarchy() const {
    if (root == nullptr) {
        cout << "No departments are loaded.\n";
        return;
    }

    displayHierarchyHelper(root, 0);
}

// Recursive preorder traversal
void DepartmentTree::preorderHelper(
    DepartmentNode* current
) const {
    if (current == nullptr) {
        return;
    }

    // Visit the current department first
    cout << current->name << "\n";

    // Then visit each child in insertion order
    for (DepartmentNode* child : current->children) {
        preorderHelper(child);
    }
}

// Displays departments in preorder
void DepartmentTree::preorderTraversal() const {
    if (root == nullptr) {
        cout << "No departments are loaded.\n";
        return;
    }

    preorderHelper(root);
}

// Loads department records from a text file
void DepartmentTree::loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open " << filename << "\n";
        cout << "departments.txt: 0 accepted, 0 rejected\n";
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (getline(file, line)) {
        lineNumber++;

        line = trim(line);

        // Ignore blank lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        vector<string> fields;
        size_t start = 0;

        // Split fields using |
        while (true) {
            size_t pos = line.find('|', start);

            if (pos == string::npos) {
                fields.push_back(trim(line.substr(start)));
                break;
            }

            fields.push_back(trim(line.substr(start, pos - start)));
            start = pos + 1;
        }

        string reason;

        if (fields.size() != 2) {
            reason = "Incorrect number of fields";
        } else {
            string name = fields[0];
            string parent = fields[1];

            if (name.empty() || parent.empty()) {
                reason = "Empty required field";
            } else if (findNode(root, name) != nullptr) {
                reason = "Duplicate department: " + name;
            } else if (root == nullptr) {
                // First accepted record must have NONE as parent
                if (toUpper(parent) != "NONE") {
                    reason = "Root department must have NONE as parent";
                } else {
                    root = new DepartmentNode(name);
                    accepted++;
                }
            } else {
                // Later departments require an existing parent
                DepartmentNode* parentNode = findNode(root, parent);

                if (parentNode == nullptr) {
                    reason = "Unknown parent department: " + parent;
                } else {
                    DepartmentNode* newNode =
                        new DepartmentNode(name, parentNode);

                    parentNode->children.push_back(newNode);
                    accepted++;
                }
            }
        }

        // Report invalid records
        if (!reason.empty()) {
            rejected++;

            cout << "Warning: " << filename
                 << " line " << lineNumber
                 << ": " << reason << "\n";
        }
    }

    file.close();

    cout << "departments.txt: "
         << accepted << " accepted, "
         << rejected << " rejected\n";
}
