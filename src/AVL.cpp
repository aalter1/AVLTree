#include "AVL.h"
#include <iostream>
#include <vector>
using namespace  std;

// Calls insert helper function
void AVLTree::insert(string name, string ufid) {
    this->root = insertHelper(this->root, name, ufid);
    cout << "successful"<<endl;
}

//insert algorithm
Node* AVLTree::insertHelper(Node* node, string name, string ufid) {

    // check where to place node recursively
    if (node == nullptr) {
        return new Node(name,ufid);
    }
    if (ufid < node->ufid) {
        node->left = insertHelper(node->left, name, ufid);
    }
    else if (ufid > node->ufid) {
        node->right = insertHelper(node->right, name, ufid);
    }
    //update height
    node->height = 1 + max(heightGetter(node->left), heightGetter(node->right));
    //check tree balance
    int balance = balanceGetter(node);
    //rotation cases
// Left Heavy
    if (balance > 1) {
        // Check if left subtree is left-heavy or right-heavy
        if (balanceGetter(node->left) >= 0) {
            // Left-Left case
            return rotateRight(node);
        } else {
            // Left-Right case
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
// Right Heavy
    if (balance < -1) {
        // Check if right subtree is right-heavy or left-heavy
        if (balanceGetter(node->right) <= 0) {
            // Right-Right case
            return rotateLeft(node);
        } else {
            // Right-Left case
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    //otherwise just return the node
    return node;
}

// Getter function to calculate height
int AVLTree::heightGetter(Node* N) {
    if (N == nullptr) {
        return 0;
    }
    return N->height;
}

//get balance of node N (should only ever be -1, 0 ,1)
int AVLTree::balanceGetter(Node* N) {
    if (N == nullptr) {
        return 0;
    }
    return heightGetter(N->left) - heightGetter(N->right);
}

//Rotate functions
Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;

    x->height = 1 + max(heightGetter(x->left), heightGetter(x->right));
    y->height = 1 + max(heightGetter(y->left), heightGetter(y->right));

    return y;
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max(heightGetter(y->left), heightGetter(y->right));
    x->height = 1 + max(heightGetter(x->left), heightGetter(x->right));
    return x;
}

//Printing functions
vector<string> AVLTree::printPreorder() {
    vector<string> namesPre;
    printPreorderHelper(this->root, namesPre);
    for (size_t i = 0; i < namesPre.size(); i++) {
        cout << namesPre[i];
        if (i < namesPre.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return namesPre;
}

void AVLTree::printPreorderHelper(Node* N, vector<string>& names) {
    if (N != nullptr) {
        names.push_back(N->name);
        printPreorderHelper(N->left, names);
        printPreorderHelper(N->right, names);
    }
}

vector<string>  AVLTree::printInorder() {
    vector<string> namesIn;
    printInorderHelper(this->root, namesIn);
    for (size_t i = 0; i < namesIn.size(); i++) {
        cout << namesIn[i];
        if (i < namesIn.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return namesIn;
}

void AVLTree::printInorderHelper(Node* N, vector<string>& names) {
    if (N != nullptr) {
        printInorderHelper(N->left, names);
        names.push_back(N->name);
        printInorderHelper(N->right, names);
    }
}

vector<string>  AVLTree::printPostorder() {
    vector<string> namesPost;
    printPostorderHelper(this->root, namesPost);
    for (size_t i = 0; i < namesPost.size(); i++) {
        cout << namesPost[i];
        if (i < namesPost.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return namesPost;
}

void AVLTree::printPostorderHelper(Node* N, vector<string>& names) {
    if (N != nullptr) {
        printPostorderHelper(N->left, names);
        printPostorderHelper(N->right, names);
        names.push_back(N->name);
    }
}

int AVLTree::printLevelCount() {
    if (this->root == nullptr) {
        return 0;
    }
    else {
        return  1 + max(heightGetter(root->left), heightGetter(root->right));
    }
}

// searching algorithms (IMPLEMENT)
bool AVLTree::searchName(string name) {
    bool found = false;
    searchNameHelper(this->root, name, found);
    if (!found) {
        cout << "unsuccessful" << endl;
    }
    return found;
}

void AVLTree::searchNameHelper(Node *N, string name, bool &found) {
    if (N != nullptr) {
        if(N->name == name) {
            cout << N->ufid << endl;
            found = true;
        }
        searchNameHelper(N->left, name, found);
        searchNameHelper(N->right, name, found);
    }
}

bool AVLTree::searchId(string ufid) {
    bool found = false;
    searchIdHelper(this->root, ufid, found);
    if (!found) {
        cout << "unsuccessful" << endl;
    }
    return found;
}

void AVLTree::searchIdHelper(Node *N, string ufid, bool &found) {
    if (N != nullptr) {
        if(N->ufid == ufid) {
            cout << N->name << endl;
            found = true;
            return;
        }else if (ufid < N->ufid) {
            searchIdHelper(N->left, ufid, found);
        } else {
            searchIdHelper(N->right, ufid, found);
        }
    }
}

Node* AVLTree::getInorderSuccesor(Node *N) {
    N = N->right;
    while ( N != nullptr && N->left != nullptr) {
        N = N->left;
    }
    return N;
}

bool AVLTree::removeID(string ufid){
    bool found = false;
    removeIDHelper(this->root, ufid, found);
    if (!found) {
        cout << "unsuccessful" << endl;
    }
    else {
        cout << "successful" <<endl;
    }
    return found;
}

Node* AVLTree::removeIDHelper(Node *N, string ufid, bool &found) {
    if (N == nullptr) return N;

    // Find the node
    if (ufid < N->ufid) {
        N->left = removeIDHelper(N->left, ufid, found);
    }
    else if (ufid > N->ufid) {
        N->right = removeIDHelper(N->right, ufid, found);
    }
    else {  // Node to delete found
        found = true;

        // Case 1: Node has only a right child or no child
        if (N->left == nullptr) {
            Node* temp = N->right;
            delete N;
            return temp;
        }
            // Case 2: Node has only a left child
        else if (N->right == nullptr) {
            Node* temp = N->left;
            delete N;
            return temp;
        }
        else {// Case 3: Node has two children
            Node *successor = getInorderSuccesor(N);
            N->ufid = successor->ufid;
            N->name = successor->name;
            N->right = removeIDHelper(N->right, successor->ufid, found);
        }
    }

    // Update height and balance for the current node
    if (N == nullptr) return N;  // Added safety check

    N->height = 1 + max(heightGetter(N->left), heightGetter(N->right));
    int balance = balanceGetter(N);

    // Left Left Case
    if (balance > 1 && balanceGetter(N->left) >= 0)
        return rotateRight(N);

    // Left Right Case
    if (balance > 1 && balanceGetter(N->left) < 0) {
        N->left = rotateLeft(N->left);
        return rotateRight(N);
    }

    // Right Right Case
    if (balance < -1 && balanceGetter(N->right) <= 0)
        return rotateLeft(N);

    // Right Left Case
    if (balance < -1 && balanceGetter(N->right) > 0) {
        N->right = rotateRight(N->right);
        return rotateLeft(N);
    }

    return N;
}

void AVLTree::inOrderNode(Node *N, vector<Node *> &nodes) {
    if (N == nullptr) {
        return;
    }
    inOrderNode(N->left, nodes);
    nodes.push_back(N);
    inOrderNode(N->right, nodes);
}

bool AVLTree::removeInorder(int num){
    bool found = false;
    removeInorderHelper(this->root, num, found);
    if (!found) {
        cout << "unsuccessful" << endl;
    }
    return found;
}

void AVLTree::removeInorderHelper(Node* N, int num, bool &found) {
    vector<Node*> nodes;
    inOrderNode(N, nodes);
    if (!nodes.empty() && num >= 0 && static_cast<size_t>(num) < nodes.size()) {
        found = true;
        removeID(nodes[num]->ufid);
    }
}

//input verification
vector<string> AVLTree::ufidList = {};

// function to verify numbers for insertion
bool AVLTree::verifyNumInsert(string num) {
    // make sure number is 8
    if (num.length() != 8){
        return false;
    }
    // make sure each char is  0-9
    for (char c : num) {
        if (!isdigit(c)) { //https://www.geeksforgeeks.org/isdigit-in-cpp/
            return false;
        }
    }
    // make sure all ufids are unique
    for (unsigned i = 0; i < AVLTree::ufidList.size(); i++) {
        if( num == AVLTree::ufidList.at(i)) {
            return false;
        }
    }
    //if all successful, add the ufid to the list of used options
    AVLTree::ufidList.push_back(num);
    return true;
}

// function to verify numbers not for insertion
bool AVLTree::verifyNum(string num) {
    // make sure number is 8
    if (num.length() != 8){
        return false;
    }
    // make sure each char is  0-9
    for (char c : num) {
        if (!isdigit(c)) { //https://www.geeksforgeeks.org/isdigit-in-cpp/
            return false;
        }
    }
    return true;
}

// function to verify names
bool AVLTree::verifyName(string word) {
    // make sure each char is  a-z, A-Z
    for (char c : word) {
        if (!isalpha(c) && !isspace(c)) { //https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/
            // https://www.geeksforgeeks.org/isspace-in-c/
            return false;
        }
    }
    return true;
}

vector<string> AVLTree::functionList = {"insert", "remove", "search", "printinorder", "printpostorder", "printlevelcount",
                                      "removeinorder", "printpreorder"};

// function to verify function names
bool AVLTree::verifyFunction(string function) {
    //check that the function is usable
    for (unsigned i = 0; i < AVLTree::functionList.size(); i++) {
        if (function == AVLTree::functionList.at(i)) {
            return true;
        }
    }
    return false;
}

//Destructor
AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::deleteTree(Node* N) {
    if (N == nullptr) return;
    deleteTree(N->left);
    deleteTree(N->right);

    delete N;
}
