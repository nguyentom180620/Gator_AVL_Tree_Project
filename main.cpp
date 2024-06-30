#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

// GatorAVLTree Class
class GatorAVLTree {
private:
    struct Student {
        string _name;
        string _id;
        int _height;
        int _bal_factor;
        Student* left;
        Student* right;

        Student(string name, string id, int height);
        ~Student();
    };

    Student* root = nullptr;
    bool checkUniqueID(Student* helperRoot, string id);
    GatorAVLTree::Student* InsertHelper(Student* helperRoot, string name, string id,
                                        int height = 0);
    void InsertRotations(string id);
    void updateHeights(Student* helperRoot, int helperHeight = 0);
    void updateBalFactor(Student* helperRoot);
    int deepestHeight(Student* helperRoot);

    bool silentSearch(Student* helperRoot, string id);
    GatorAVLTree::Student* findInorderSuccessor(Student* helperRoot);
    GatorAVLTree::Student* RemoveHelper(Student* helperRoot, string id, Student* parent);

    GatorAVLTree::Student* SearchHelperID(Student* helperRoot, string id);

    void SearchHelperName(Student* helperRoot, string name, int& count);

    void PrintInorderHelper(Student* helperRoot, string& names);

    void PrintPreorderHelper(Student* helperRoot, string& names);

    void PrintPostorderHelper(Student* helperRoot, string& names);

    void RemoveInorderHelper(Student* helperRoot, vector<Student*>& students);

    void forTestingOnlyInorder(Student* helperRoot, vector<string>& students);
public:
    void insert(string name, string id);
    void remove(string id);
    void searchID(string id);
    void searchName(string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(string N);

    vector<string> inorder();
};

// Student Function Implementations
GatorAVLTree::Student::Student(string name, string id, int height) {
    _name = name;
    _id = id;
    _height = height;
    _bal_factor = 0;
    left = nullptr;
    right = nullptr;
}

GatorAVLTree::Student::~Student() {
    left = nullptr;
    right = nullptr;
}

// GatorAVLTree Function Implementations
int GatorAVLTree::deepestHeight(GatorAVLTree::Student *helperRoot) {
    // get deepest heights recursively to help in calculating bal_factors for each
    int self = 0;
    if (helperRoot == nullptr) {
        return self;
    }
    else {
        self = helperRoot->_height;
    }
    int left = deepestHeight(helperRoot->left);
    int right = deepestHeight(helperRoot->right);
    if (self >= left && self >= right) {
        return self;
    }
    else if (left >= self && left >= right) {
        return left;
    }
    else {
        return right;
    }
}

void GatorAVLTree::updateBalFactor(GatorAVLTree::Student *helperRoot) {
    if (helperRoot == nullptr) {
        return;
    }
    updateBalFactor(helperRoot->left);
    updateBalFactor(helperRoot->right);

    int self = helperRoot->_height;
    int left = 0;
    int right = 0;

    if (helperRoot->left == nullptr) {
        left = self;
    }
    else {
        left = deepestHeight(helperRoot->left);
    }
    if (helperRoot->right == nullptr) {
        right = self;
    }
    else {
        right = deepestHeight(helperRoot->right);
    }
    helperRoot->_bal_factor = left - right;
}

bool GatorAVLTree::checkUniqueID(GatorAVLTree::Student *helperRoot, std::string id) {
    bool unique = true;
    bool checkRight = true;
    bool checkLeft = true;
    if (helperRoot == nullptr) {
        return true;
    }
    else if (id == helperRoot->_id) {
        return false;
    }
    else if (stoi(id) > stoi(helperRoot->_id)) {
        checkRight = checkUniqueID(helperRoot->right, id);
    }
    else {
        checkLeft = checkUniqueID(helperRoot->left, id);
    }
    return unique && checkRight && checkLeft;
}

GatorAVLTree::Student* GatorAVLTree::InsertHelper(GatorAVLTree::Student* helperRoot, string name, string id,
                                                  int height) {
    // Initial Insert
    if (helperRoot == nullptr) {
        return new Student(name, id, height);
    }
    else if (stoi(id) > stoi(helperRoot->_id)) {
        helperRoot->right = InsertHelper(helperRoot->right, name, id, height + 1);
    }
    else {
        helperRoot->left = InsertHelper(helperRoot->left, name, id, height + 1);
    }
    // Update Bal_factors of all nodes
    updateBalFactor(helperRoot);
    return helperRoot;
}

void GatorAVLTree::updateHeights(Student* helperRoot, int helperHeight) {
    queue<Student*> q;
    q.push(helperRoot);
    int height = helperHeight;
    int num_in_height = 1;
    int num_in_next = 0;

    while (!q.empty()) {
        for (int i = 0; i < num_in_height; i++) {
            q.front()->_height = height;
            if (q.front()->left != nullptr) {
                q.push(q.front()->left);
                num_in_next++;
            }
            if (q.front()->right != nullptr) {
                q.push(q.front()->right);
                num_in_next++;
            }
            q.pop();
        }
        height++;
        num_in_height = num_in_next;
        num_in_next = 0;
    }
}

void GatorAVLTree::InsertRotations(string id) {
    // Implement rotations
    // First travel to necessary location
    Student* travelNode = this->root;
    bool findingSpot = true;
    while (findingSpot) {
        if (travelNode == nullptr) {
            break;
        }
        int bal = travelNode->_bal_factor;
        int left_bal;
        int right_bal;
        if (travelNode->left != nullptr) {
            left_bal = travelNode->left->_bal_factor;
        }
        else {
            left_bal = 0;
        }
        if (travelNode->right != nullptr) {
            right_bal = travelNode->right->_bal_factor;
        }
        else {
            right_bal = 0;
        }
        // Check if we really are at right spot, or need to travel further down
        if (bal == 2 || bal == -2) {
            if (left_bal == 1 || left_bal == -1 || right_bal == 1 || right_bal == -1) {
                findingSpot = false;
                break;
            }
        }
        // If not, travel towards newly added node as it caused the imbalance
        if (stoi(id) > stoi(travelNode->_id)) {
            travelNode = travelNode->right;
        }
        else {
            travelNode = travelNode->left;
        }
    }
    // If findingSpot is true after break, problem was never found so tree is balance and no rotations
    // If it returns false, then it is found and travelNode has made it to where it needs to be
    // Send a second travel node to mark the node before where rotation needs to occur
    // This allows for information to not be in upper levels of tree during rotation
    Student* securingNode = this->root;
    bool findingTravelNode = true;
    bool securedLeft = false;
    bool securedRight = false;
    if (!findingSpot) {
        while (findingTravelNode) {
            if (securingNode == travelNode) {
                // This means travelNode is the root and will be important later for reassigning root
                findingTravelNode = false;
            }
            else if (securingNode->left == travelNode) {
                findingTravelNode = false;
                securedLeft = true;
            }
            else if (securingNode->right == travelNode) {
                findingTravelNode = false;
                securedRight = true;
            }
            else {
                if (stoi(id) > stoi(travelNode->_id)) {
                    securingNode = securingNode->right;
                }
                else {
                    securingNode = securingNode->left;
                }
            }
        }
    }
    // Rotations
    if (!findingSpot) {
        int bal = travelNode->_bal_factor;
        int left_bal;
        int right_bal;
        if (travelNode->left != nullptr) {
            left_bal = travelNode->left->_bal_factor;
        }
        else {
            left_bal = 0;
        }
        if (travelNode->right != nullptr) {
            right_bal = travelNode->right->_bal_factor;
        }
        else {
            right_bal = 0;
        }
        // If tree is left heavy
        if (bal == 2) {
            // If left subtree is left heavy
            if (left_bal == 1) {
                // Perform Right Rotation
                Student* grandchild = travelNode->left->right;
                Student* newParent = travelNode->left;
                newParent->right = travelNode;
                travelNode->left = grandchild;
                if (securingNode == travelNode) {
                    this->root = newParent;
                }
                else if (securedLeft) {
                    securingNode->left = newParent;
                }
                else if (securedRight) {
                    securingNode->right = newParent;
                }
            }
            else {
                // First work with left side
                Student* newChild = travelNode->left;
                Student* newParent = travelNode->left->right;
                Student* leftGrandchild = newParent->left;
                newParent->left = newChild;
                newChild->right = leftGrandchild;
                travelNode->left = newParent;

                // Now work with right side
                Student* rightGrandchild = newParent->right;
                newParent->right = travelNode;
                travelNode->left = rightGrandchild;
                if (securingNode == travelNode) {
                    this->root = newParent;
                }
                else if (securedLeft) {
                    securingNode->left = newParent;
                }
                else if (securedRight) {
                    securingNode->right = newParent;
                }
            }
        }
            // If tree is right heavy
        else if (bal == -2) {
            // If right subtree is right heavy
            if (right_bal == -1) {
                // Perform Left Rotation
                Student* grandchild = travelNode->right->left;
                Student* newParent = travelNode->right;
                newParent->left = travelNode;
                travelNode->right = grandchild;
                if (securingNode == travelNode) {
                    this->root = newParent;
                }
                else if (securedLeft) {
                    securingNode->left = newParent;
                }
                else if (securedRight) {
                    securingNode->right = newParent;
                }
            }
            else {
                // First work with right side
                Student* newChild = travelNode->right;
                Student* newParent = travelNode->right->left;
                Student* rightGrandchild = newParent->right;
                newParent->right = newChild;
                newChild->left = rightGrandchild;
                travelNode->right = newParent;

                // Now work with left side
                Student* leftGrandchild = newParent->left;
                newParent->left = travelNode;
                travelNode->right = leftGrandchild;
                if (securingNode == travelNode) {
                    this->root = newParent;
                }
                else if (securedLeft) {
                    securingNode->left = newParent;
                }
                else if (securedRight) {
                    securingNode->right = newParent;
                }
            }
        }
    }
    // Update heights after rotation for related nodes
    if (securingNode == travelNode) {
        updateHeights(this->root, 0);
    }
    else {
        if (securedLeft) {
            updateHeights(securingNode->left, securingNode->_height + 1);
        }
        if (securedRight) {
            updateHeights(securingNode->right, securingNode->_height + 1);
        }
    }
}

bool GatorAVLTree::silentSearch(GatorAVLTree::Student *helperRoot, std::string id) {
    bool exist = false;
    bool checkRight = false;
    bool checkLeft = false;
    if (helperRoot == nullptr) {
        return false;
    }
    else if (id == helperRoot->_id) {
        exist = true;
    }
    else if (stoi(id) > stoi(helperRoot->_id)) {
        checkRight = silentSearch(helperRoot->right, id);
    }
    else {
        checkLeft = silentSearch(helperRoot->left, id);
    }
    return exist || checkRight || checkLeft;
}

GatorAVLTree::Student* GatorAVLTree::findInorderSuccessor(GatorAVLTree::Student* helperRoot) {
    while (helperRoot->left != nullptr) {
        helperRoot = helperRoot->left;
    }
    return helperRoot;
}

GatorAVLTree::Student* GatorAVLTree::RemoveHelper(GatorAVLTree::Student *helperRoot, std::string id, Student* parent) {
    if (helperRoot == nullptr) {
        return nullptr;
    }
    if (id == helperRoot->_id) {
        // If no children
        if (helperRoot->left == nullptr && helperRoot->right == nullptr) {
            if (parent != nullptr) {
                if (parent->left == helperRoot) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }
            else {
                this->root = nullptr;
            }
            delete helperRoot;
            return nullptr;
        }
        // If two children
        else if (helperRoot->left != nullptr && helperRoot->right != nullptr) {
            Student* successor = findInorderSuccessor(helperRoot->right);
            helperRoot->_name = successor->_name;
            helperRoot->_id = successor->_id;
            helperRoot->right = RemoveHelper(helperRoot->right, successor->_id, helperRoot);
        }
        // If one child
        else {
            Student* child = (helperRoot->left != nullptr) ? helperRoot->left : helperRoot->right;
            if (parent != nullptr) {
                if (parent->left == helperRoot) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
            }
            else {
                this->root = child;
            }
            delete helperRoot;
            return child;
        }
    }
    else if (stoi(id) > stoi(helperRoot->_id)) {
        helperRoot->right = RemoveHelper(helperRoot->right, id, helperRoot);
    }
    else if (stoi(id) < stoi(helperRoot->_id)) {
        helperRoot->left = RemoveHelper(helperRoot->left, id, helperRoot);
    }
    return helperRoot;
}

GatorAVLTree::Student* GatorAVLTree::SearchHelperID(GatorAVLTree::Student *helperRoot, std::string id) {
    if (id == helperRoot->_id) {
        return helperRoot;
    }
    else if (stoi(id) > stoi(helperRoot->_id)) {
        return SearchHelperID(helperRoot->right, id);
    }
    else if (stoi(id) < stoi(helperRoot->_id)) {
        return SearchHelperID(helperRoot->left, id);
    }
}

void GatorAVLTree::SearchHelperName(GatorAVLTree::Student *helperRoot, std::string name, int& count) {
    if (helperRoot == nullptr) {
        return;
    }
    if (name == helperRoot->_name) {
        count++;
        cout << helperRoot->_id << endl;
    }
    SearchHelperName(helperRoot->left, name, count);
    SearchHelperName(helperRoot->right, name, count);
}

void GatorAVLTree::PrintInorderHelper(GatorAVLTree::Student *helperRoot, string& names) {
    if (helperRoot == nullptr) {
        return;
    }
    PrintInorderHelper(helperRoot->left, names);
    names += helperRoot->_name;
    names += ", ";
    PrintInorderHelper(helperRoot->right, names);
}

void GatorAVLTree::PrintPreorderHelper(GatorAVLTree::Student *helperRoot, std::string &names) {
    if (helperRoot == nullptr) {
        return;
    }
    names += helperRoot->_name;
    names += ", ";
    PrintPreorderHelper(helperRoot->left, names);
    PrintPreorderHelper(helperRoot->right, names);
}

void GatorAVLTree::PrintPostorderHelper(GatorAVLTree::Student *helperRoot, std::string &names) {
    if (helperRoot == nullptr) {
        return;
    }
    PrintPostorderHelper(helperRoot->left, names);
    PrintPostorderHelper(helperRoot->right, names);
    names += helperRoot->_name;
    names += ", ";
}

void GatorAVLTree::RemoveInorderHelper(GatorAVLTree::Student *helperRoot, vector<GatorAVLTree::Student*>& students) {
    if (helperRoot == nullptr) {
        return;
    }
    RemoveInorderHelper(helperRoot->left, students);
    students.push_back(helperRoot);
    RemoveInorderHelper(helperRoot->right, students);
}

void GatorAVLTree::insert(string name, string id) {
    // Check if ID is unique
    bool uniqueID = checkUniqueID(this->root, id);
    // Check if Name and ID follow constraints
    regex idTest = regex("[0-9]{8}");
    bool idCheck = regex_match(id,idTest);
    regex nameTest = regex("[a-zA-Z\\s]*");
    bool nameCheck = regex_match(name,nameTest);
    if (uniqueID && idCheck && nameCheck) {
        // First add new node and update bal_factors
        this->root = InsertHelper(this->root, name, id);
        // Then do non-recursive rotation function
        InsertRotations(id);
        // Finally update bal_factors
        updateBalFactor(this->root);
        cout << "successful";
    }
    else {
        cout << "unsuccessful";
    }
}

void GatorAVLTree::remove(std::string id) {
    // Check if ID exist
    bool exist = silentSearch(this->root, id);
    // Then call helper
    if (exist) {
        this->root = RemoveHelper(this->root, id, this->root);
        if (this->root != nullptr) {
            // Then do non-recursive rotation function
            InsertRotations(id);
            // Finally update bal_factors
            updateBalFactor(this->root);
        }
        cout << "successful";
    }
    else {
        cout << "unsuccessful";
    }
}

void GatorAVLTree::searchID(std::string id) {
    bool exist = silentSearch(this->root, id);
    if (exist) {
        Student* temp = SearchHelperID(this->root, id);
        cout << temp->_name;
    }
    else {
        cout << "unsuccessful";
    }
}

void GatorAVLTree::searchName(std::string name) {
    int count = 0;
    SearchHelperName(this->root, name, count);
    if (count == 0) {
        cout << "unsuccessful";
    }
}

void GatorAVLTree::printInorder() {
    string names = "";
    PrintInorderHelper(this->root, names);
    if (names != "") {
        names.pop_back();
        names.pop_back();
    }
    cout << names;
}

void GatorAVLTree::printPreorder() {
    string names = "";
    PrintPreorderHelper(this->root, names);
    if (names != "") {
        names.pop_back();
        names.pop_back();
    }
    cout << names;
}

void GatorAVLTree::printPostorder() {
    string names = "";
    PrintPostorderHelper(this->root, names);
    if (names != "") {
        names.pop_back();
        names.pop_back();
    }
    cout << names;
}

void GatorAVLTree::printLevelCount() {
    if (this->root == nullptr) {
        cout << 0;
    }
    else {
        int num_levels = deepestHeight(this->root) + 1;
        cout << num_levels;
    }
}

void GatorAVLTree::removeInorder(std::string N) {
    vector<Student*> students;
    RemoveInorderHelper(this->root, students);

    if (stoi(N) < 0 || stoi(N) >= students.size()) {
        cout << "unsuccessful";
    }
    else {
        string id = students[stoi(N)]->_id;
        this->remove(id);
    }
}

void GatorAVLTree::forTestingOnlyInorder(GatorAVLTree::Student *helperRoot, vector<std::string>& students) {
    if (helperRoot == nullptr) {
        return;
    }
    forTestingOnlyInorder(helperRoot->left, students);
    students.push_back(helperRoot->_name);
    forTestingOnlyInorder(helperRoot->right, students);
}

vector<string> GatorAVLTree::inorder() {
    vector<string> students;
    forTestingOnlyInorder(this->root, students);
    return students;
}

int main() {
    GatorAVLTree tree;
    string num_of_commands;
    int num_of_coms;
    cin >> num_of_commands;
    num_of_coms = stoi(num_of_commands);
    cin.ignore();

    for (int i = 0; i < num_of_coms; i++) {
        // Collect input
        string line;
        getline(cin, line);

        istringstream in(line);

        string command;
        in >> command;

        string name;
        string id;
        string N;

        if (command == "insert") {
            getline(in, name, '"');
            getline(in, name, '"');

            in >> id;
        }
        else if (command == "search" && line[7] == '"') {
            getline(in, name, '"');
            getline(in, name, '"');
        }
        else if (command == "remove" || command == "search") {
            in >> id;
        }
        else if (command == "removeInorder") {
            in >> N;
        }
        // else command is print command

        // Execute based on command
        if (command == "insert") {
            tree.insert(name,id);
        }
        else if (command == "search" && line[7] == '"') {
            tree.searchName(name);
        }
        else if (command == "remove" || command == "search") {
            if (command == "remove") {
                tree.remove(id);
            }
            else {
                tree.searchID(id);
            }
        }
        else if (command == "removeInorder") {
            tree.removeInorder(N);
        }
        else {
            if (command == "printInorder") {
                tree.printInorder();
            }
            else if (command == "printPreorder") {
                tree.printPreorder();
            }
            else if (command == "printPostorder") {
                tree.printPostorder();
            }
            else if (command == "printLevelCount") {
                tree.printLevelCount();
            }
            else {
                cout << "unsuccessful";
            }
        }
        cout << endl;
    }

    return 0;
}