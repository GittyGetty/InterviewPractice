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

#include "Arithmetic.h"
#include "BinaryTrees.h"
#include "Permutations.h"
#include "Sorting.h"
#include "String.h"

int main() {
    /***************************************************************************/
    size_t pos;
    pos = rabin_karp_search(L"abc", L"123456789abc123456789");
    /***************************************************************************/
    {
        using namespace BinaryTrees;
        auto settings = gcnew Microsoft::VisualStudio::GraphModel::GraphSerializationSettings();
        Node<int> *root = NULL;

        rb_insert(&root, 5);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        rb_insert(&root, 3);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        rb_insert(&root, 7);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        rb_insert(&root, 2);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        rb_insert(&root, 4);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        rb_insert(&root, 6);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        rb_insert(&root, 8);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        rb_insert(&root, 11);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
    }
    /***************************************************************************/
    {
        using namespace BinaryTrees;
        auto settings = gcnew Microsoft::VisualStudio::GraphModel::GraphSerializationSettings();
        Node<int> *root = NULL;

        root = avl_insert(root, 10);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        root = avl_insert(root, 20);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        root = avl_insert(root, 30);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        root = avl_insert(root, 40);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        root = avl_insert(root, 50);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        root = avl_insert(root, 25);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
        root = avl_delete(root, 20);
        ToGraph(root)->Save("BinaryTree.dgml", settings);
    }
    /***************************************************************************/
    {
        using namespace BinaryTrees;
        auto settings = gcnew Microsoft::VisualStudio::GraphModel::GraphSerializationSettings();
        SplayTree<int> st1;
        Node<int>* n;

        st1.insert(5);
        st1.insert(9);
        st1.insert(13);
        st1.insert(11);
        st1.insert(1);
        st1.insert(2);
        st1.insert(3);
        st1.insert(4);

        n = st1.get(11);
        ToGraph(st1.root)->Save("BinaryTree.dgml", settings);
        st1.remove(11);
        ToGraph(st1.root)->Save("BinaryTree.dgml", settings);
        n = st1.get(11);
        ToGraph(st1.root)->Save("BinaryTree.dgml", settings);
        n = st1.get(13);
        ToGraph(st1.root)->Save("BinaryTree.dgml", settings);
        n = st1.get(1);
        ToGraph(st1.root)->Save("BinaryTree.dgml", settings);
        n = st1.get(5);
        ToGraph(st1.root)->Save("BinaryTree.dgml", settings);
        n = st1.get(9);
        ToGraph(st1.root)->Save("BinaryTree.dgml", settings);
    }
    /***************************************************************************/
    {
        std::vector<int> v(10);
        std::iota(v.begin(), v.end(), 1);
        auto tree = BinaryTrees::generate_random_tree(v);
        BinaryTrees::link_levels(&tree);

        auto settings = gcnew Microsoft::VisualStudio::GraphModel::GraphSerializationSettings();
        BinaryTrees::ToGraph(&tree)->Save("BinaryTree.dgml", settings);
    }
    /***************************************************************************/
}