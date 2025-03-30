#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "AVL.h"
#include <algorithm>
#include <cstdlib>



using namespace std;

TEST_CASE("Insert randomly and print level count every 5 inserts", "[AVL]") {
    AVLTree tree;
    vector<string> insertedUFIDs;

    srand(time(0)); // Random seed

    for (int i = 1; i <= 1000; i++) {
        string name = "Person" + to_string(i);
        string ufid = to_string(10000000 + rand() % 90000000); // Random 8-digit UFID

        tree.insert(name, ufid);
        insertedUFIDs.push_back(ufid);

        if (i % 5 == 0) {
            INFO("Level Count after " << i << " inserts: " << tree.printLevelCount());
            cout << tree.printLevelCount() <<endl;
        }
    }

    // Verify all inserted UFIDs exist
    for (const auto& ufid : insertedUFIDs) {
        REQUIRE(tree.searchId(ufid) == true);
    }
}

TEST_CASE("Insert many nodes, print all traversals, and check level count", "[AVL]") {
    AVLTree tree;

    vector<pair<string, string>> testNodes = {
            {"Alice", "10000010"}, {"Bob", "10000020"}, {"Charlie", "10000030"},
            {"David", "10000040"}, {"Eve", "10000050"}, {"Frank", "10000060"},
            {"Grace", "10000070"}, {"Hannah", "10000080"}, {"Ian", "10000090"},
            {"Jack", "10000100"}, {"Kevin", "10000110"}, {"Liam", "10000120"},
            {"Mia", "10000130"}, {"Noah", "10000140"}, {"Olivia", "10000150"},
            {"Pam", "10000160"}, {"Quinn", "10000170"}, {"Rachel", "10000180"},
            {"Sam", "10000190"}, {"Tom", "10000200"}
    };

    for (auto &node : testNodes) {
        tree.insert(node.first, node.second);
    }

    // Print traversals
    INFO("Pre-order Traversal: ");
    vector<string> preOrder = tree.printPreorder();
    REQUIRE(preOrder.size() == testNodes.size());

    INFO("In-order Traversal: ");
    vector<string> inOrder = tree.printInorder();
    REQUIRE(inOrder.size() == testNodes.size());

    INFO("Post-order Traversal: ");
    vector<string> postOrder = tree.printPostorder();
    REQUIRE(postOrder.size() == testNodes.size());

    // Check level count
    INFO("Level Count: " << tree.printLevelCount());
    cout << tree.printLevelCount()<< endl;
}