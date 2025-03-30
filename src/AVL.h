#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
#include <iostream>
#include <vector>

using namespace std;

// Node class
struct Node {
    // Node att
    string name;
    string ufid;
    Node* left;
    Node* right;
    int height;

    Node(string name, string ufid) {
        this->name = name;
        this->ufid = ufid;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};


// AVLTree class
class AVLTree {
private:
    Node* root = nullptr;
    //Helpers
    Node* insertHelper(Node* node, string name, string ufid);
    int heightGetter(Node* N);
    int balanceGetter(Node* N);
    Node* rotateRight(Node* x);
    Node* rotateLeft(Node* x);
    void printInorderHelper(Node* N, vector<string>& names);
    void printPreorderHelper(Node* N, vector<string>& names);
    void printPostorderHelper(Node* N, vector<string>& names);
    void searchNameHelper(Node* N, string name, bool &found);
    void searchIdHelper(Node* N, string ufid, bool &found);
    Node* getInorderSuccesor(Node* N);
    Node* removeIDHelper(Node* N, string ufid, bool &found);
    void removeInorderHelper(Node* N, int num, bool &found);
    void inOrderNode(Node* N, vector<Node*>& nodes);
    void deleteTree(Node* N);
    // vector of usable functions
    static vector<string> functionList;



public:
    //main functions
    void insert(string name, string ufid);
    vector<string> printInorder();
    vector<string> printPreorder();
    vector<string> printPostorder();
    int printLevelCount();
    bool searchName(string name);
    bool searchId(string ufid);
    bool removeID(string ufid);
    bool removeInorder(int num);
    //verification functions
    static bool verifyNumInsert(string num);
    static bool verifyNum(string num);
    static bool verifyName(string word);
    static bool verifyFunction(string function);
    // Vector to hold all ufids for uniqueness
    static vector<string> ufidList;
    //Destructor
    ~AVLTree();
    void debugPrintTree(Node* node, int level = 0);
};

#endif //PROJECT1_AVL_H