#include <fstream>
#include <vector>
#include <cstdint>
#include <set>
#include <memory>
#include <ctime>
#include <iostream>
#include <cassert>
#include <string>
#include <numeric>

#include "AllPrototypes.h"

using namespace BinaryTrees;
using namespace Microsoft::VisualStudio::GraphModel;

void f() {
    std::vector<size_t> values(10);
    std::iota(values.begin(), values.end(), 1);
    auto tree = BinaryTrees::generate_random_tree(values, 42);

    Node<size_t> *root = &tree;
    append_node<size_t>(&root, 11);

    Graph^ graph = ToGraph(&tree);
    graph->Save(L"BinaryTree.dgml", gcnew GraphSerializationSettings());
}

int main() {
    f();
    return 0;
}
