#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include "AVL.h"
#include <algorithm>
using namespace std;

int main() {
    AVLTree tree;
    string numCommands;
    getline(cin, numCommands);
    bool verifyStart = true;
    for (char num : numCommands) {
        if (!isdigit(num)) { //https://www.geeksforgeeks.org/isdigit-in-cpp/
            verifyStart = false;
        }
    }
    if (!verifyStart) {
        cout << "unsuccessful";
        return 0;
    }
    for (int i = 0; i < stoi(numCommands); i++) {
        string line;
        getline(cin, line);
        istringstream inStream(line);
        string function;
        bool verifiedFunction;
        getline(inStream, function, ' ');
        transform(function.begin(), function.end(), function.begin(), ::tolower);
        verifiedFunction = AVLTree::verifyFunction(function);
        if (!verifiedFunction) {
            cout << "unsuccessful" << endl;
            continue;
        }
        if (function == "insert") {
            string next;
            getline(inStream, next, '"');
            string name;
            bool verifiedName;
            getline(inStream, name, '"');
            verifiedName = AVLTree::verifyName(name);
            if (!verifiedName) {
                cout << "unsuccessful" << endl;
                continue;
            }
            string next2;
            getline(inStream, next2, ' ');
            string number;
            bool verifiedNumber;
            getline(inStream, number);
            verifiedNumber = AVLTree::verifyNumInsert(number);
            if (!verifiedNumber) {
                cout << "unsuccessful" << endl;
                continue;
            }
            tree.insert(name, number);
            continue;
        }
        if (function == "remove") {
            inStream >> ws;
            string number;
            bool verifiedNumber;
            getline(inStream, number);
            verifiedNumber = AVLTree::verifyNum(number);
            if (!verifiedNumber) {
                cout << "unsuccessful" << endl;
                continue;
            }
            for (unsigned j = 0; j < AVLTree::ufidList.size(); j++) {
                if (number == AVLTree::ufidList.at(j)) {
                    AVLTree::ufidList.erase(find(AVLTree::ufidList.begin(), AVLTree::ufidList.end(), number));
                }
            }
            tree.removeID(number);
        }
        if (function == "search") {
            inStream >> ws;
            string number;
            bool verifiedNumber;
            getline(inStream, number);
            verifiedNumber = AVLTree::verifyNum(number);
            if (!verifiedNumber) {
                string name = number;
                if (!name.empty() && name[0] == '"' && name[name.size() - 1] == '"') {
                    name = name.substr(1, name.size() - 2);
                    bool verifiedName = AVLTree::verifyName(name);
                    if (!verifiedName) {
                        cout << "unsuccessful" << endl;
                        continue;
                    } else {
                        tree.searchName(name);
                    }
                } else {
                    cout << "unsuccessful" << endl;
                    continue;
                }
            } else {
                tree.searchId(number);
            }
        }
        if (function == "printinorder") {
            tree.printInorder();
        }
        if (function == "printpreorder") {
            tree.printPreorder();
        }
        if (function == "printpostorder") {
            tree.printPostorder();
        }
        if (function == "printlevelcount") {
            cout << tree.printLevelCount() << endl;
        }
        if (function == "removeinorder") {
            inStream >> ws;
            string number;
            bool verify = true;
            getline(inStream, number);
            for (char num : number) {
                if (!isdigit(num)) { //https://www.geeksforgeeks.org/isdigit-in-cpp/
                    verify = false;
                }
            }
            if (!verify) {
                cout << "unsuccessful" << endl;
                continue;
            } else {
                int newNumber = stoi(number);
                tree.removeInorder(newNumber);
            }
        }
    }
    return 0;
}
