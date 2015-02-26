#include <string>
#include <functional>
#include <memory>
#include <numeric>

#include "BinaryTrees.h"

namespace BinaryTrees
{
    /*************************************************************************************/
    // Change a tree in such a way that each node's value is the sum of all nodes in its
    // sub-trees.
    void increment(Node<int>* node, int diff) {
        if (node->left) {
            node->left->value += diff;
            increment(node->left, diff);
        } else if (node->right) {
            node->right->value += diff;
            increment(node->right, diff);
        }
    }
    void make_subtree_sum(Node<int>* node) {
        if (!node || (!node->left && !node->right)) return;
        make_subtree_sum(node->left);
        make_subtree_sum(node->right);
        int left = node->left ? node->left->value : 0;
        int right = node->right ? node->right->value : 0;
        int diff = left + right - node->value;
        if (diff > 0) node->value += diff;
        if (diff < 0) increment(node, -diff);
    }
    /*************************************************************************************/
    // Test if a binary tree is a binary search tree.
    bool is_bst(Node<int>* node, int min, int max) {
        if (!node) return true;
        if (node->value < min || node->value > max) return false;
        return is_bst(node->left, min, node->value) &&
               is_bst(node->right, node->value, max);
    }
    // With in order traversal.
    bool is_bst_iot(Node<int>* root) {
        static Node<int> *prev = NULL;
        if (!root) return true;
        if (!is_bst(root->left)) return false;
        if (prev && root->value < prev->value) return false;
        prev = root;
        return is_bst(root->right);
    }
    // Do not use. This is wrong.
    bool is_bst_mit(Node<int>* curr, int min, int max) {
        if (curr->left) {
            if (curr->left->value < min || !is_bst_mit(curr->left, min, curr->value))
                return false;
        }
        if (curr->right) {
            if (curr->right->value > max || !is_bst_mit(curr->right, curr->value, max))
                return false;
        }
        return true;
    }
    bool is_bst(Node<int>* node) {
        return is_bst_mit(node,
                          std::numeric_limits<int>::min(), 
                          std::numeric_limits<int>::max());
    }
    /*************************************************************************************/
}
