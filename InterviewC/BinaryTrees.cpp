#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <stack>
#include <string>

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
    // http://www.geeksforgeeks.org/connect-nodes-at-same-level-with-o1-extra-space/
    Node<int>* find_sibling(Node<int> *n) {
        for (n = n->sibling; n; n = n->sibling) {
            if (n->left) return n->left;
            if (n->right) return n->right;
        }
        return NULL;
    }
    void link_levels(Node<int>* n) {
        while (n) {
            for (Node<int> *bn = n; bn; bn = bn->sibling) {
                if (bn->left) bn->left->sibling = bn->right ? bn->right : find_sibling(bn);
                if (bn->right) bn->right->sibling = find_sibling(bn);
            }
            n = n->left ? n->left : n->right ? n->right : find_sibling(n);
        }
    }
    /*************************************************************************************/
    // AVL Tree Implementation //
    // http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    // http://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    int get_height(Node<int> *n) {
        return n ? n->height : 0;
    }
    int get_balance(Node<int> *n) {
        return n ? get_height(n->left) - get_height(n->right) : 0;
    }
    Node<int>* avl_rotate_right(Node<int> *y) {
        Node<int> *x = y->left;
        Node<int> *t = x->right;

        x->right = y;
        y->left = t;

        y->height = std::max(get_height(y->left), get_height(y->right)) + 1;
        x->height = std::max(get_height(x->left), get_height(x->right)) + 1;

        return x;
    }
    Node<int>* avl_rotate_left(Node<int> *x) {
        Node<int> *y = x->right;
        Node<int> *t = y->left;

        y->left = x;
        x->right = t;

        x->height = std::max(get_height(x->left), get_height(x->right)) + 1;
        y->height = std::max(get_height(y->left), get_height(y->right)) + 1;

        return y;
    }
    Node<int>* avl_insert(Node<int>* node, int key) {
        if (!node) return new Node<int>(key);

        if (key < node->value)
            node->left = avl_insert(node->left, key);
        else
            node->right = avl_insert(node->right, key);

        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
        int balance = get_balance(node);

        if (balance > 1 && key < node->left->value)
            return avl_rotate_right(node);
        if (balance < -1 && key > node->right->value)
            return avl_rotate_left(node);

        if (balance > 1 && key > node->left->value) {
            node->left = avl_rotate_left(node->left);
            return avl_rotate_right(node);
        }
        if (balance < -1 && key < node->right->value) {
            node->right = avl_rotate_right(node->right);
            return avl_rotate_left(node);
        }
        return node;
    }
    Node<int>* get_min_node(Node<int> *node) {
        while (node->left) node = node->left;
        return node;
    }
    Node<int>* avl_delete(Node<int>* root, int key) {
        if (!root) return root;

        if (key < root->value)
            root->left = avl_delete(root->left, key);
        else if (key > root->value)
            root->right = avl_delete(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node<int> *temp = root->left ? root->left : root->right;

                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }
                else *root = *temp;

                delete temp;
            }
            else {
                Node<int>* temp = get_min_node(root->right);
                root->value = temp->value;
                root->right = avl_delete(root->right, temp->value);
            }
        }

        if (!root) return root;

        root->height = std::max(get_height(root->left), get_height(root->right)) + 1;
        int balance = get_balance(root);

        if (balance > 1 && get_balance(root->left) >= 0)
            return avl_rotate_right(root);
        if (balance > 1 && get_balance(root->left) < 0) {
            root->left = avl_rotate_left(root->left);
            return avl_rotate_right(root);
        }
        if (balance < -1 && get_balance(root->right) <= 0)
            return avl_rotate_left(root);
        if (balance < -1 && get_balance(root->right) > 0) {
            root->right = avl_rotate_right(root->right);
            return avl_rotate_left(root);
        }
        return root;
    }
    /*************************************************************************************/
    // Red-Black Tree Implementation
    // http://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
    // http://geeksquiz.com/c-program-red-black-tree-insertion/
    void rb_rotate_left(Node<int> **root, Node<int> *x) {
        Node<int> *y = x->right;
        x->right = y->left;
        if (x->right) x->right->parent = x;
        y->parent = x->parent;

        if (!x->parent) *root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }
    void rb_rotate_right(Node<int> **root, Node<int> *y) {
        Node<int> *x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;

        if (!x->parent) *root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;

        x->right = y;
        y->parent = x;
    }
    void rb_insert_fixup(Node<int> **root, Node<int> *z) {
        while (z != *root && z->parent->color == 'R') {
            Node<int> *y;
            y = z->parent == z->parent->parent->left ? 
                z->parent->parent->right : 
                z->parent->parent->left;

            if (y->color == 'R') {
                y->color = 'B';
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z->parent == z->parent->parent->left && z == z->parent->left) {
                    char ch = z->parent->color;
                    z->parent->color = z->parent->parent->color;
                    z->parent->parent->color = ch;
                    rb_rotate_right(root, z->parent->parent);
                }
                if (z->parent == z->parent->parent->left && z == z->parent->right) {
                    char ch = z->color;
                    z->color = z->parent->parent->color;
                    z->parent->parent->color = ch;
                    rb_rotate_left(root, z->parent);
                    rb_rotate_right(root, z->parent->parent);
                }
                if (z->parent == z->parent->parent->right && z == z->parent->right) {
                    char ch = z->parent->color;
                    z->parent->color = z->parent->parent->color;
                    z->parent->parent->color = ch;
                    rb_rotate_left(root, z->parent->parent);
                }
                if (z->parent == z->parent->parent->right && z == z->parent->left) {
                    char ch = z->color;
                    z->color = z->parent->parent->color;
                    z->parent->parent->color = ch;
                    rb_rotate_right(root, z->parent);
                    rb_rotate_left(root, z->parent->parent);
                }
            }
        }
        (*root)->color = 'B';
    }
    void rb_insert(Node<int> **root, int data) {
        Node<int> *z = (Node<int>*)malloc(sizeof(Node<int>));
        z->value = data;
        z->left = z->right = z->parent = NULL;

        if (*root == NULL) {
            z->color = 'B';
            *root = z;
        } else {
            Node<int> *y = NULL;
            Node<int> *x = *root;

            while (x != NULL) {
                y = x;
                x = z->value < x->value ? x->left : x->right;
            }
            z->parent = y;
            if (z->value > y->value) y->right = z;
            else y->left = z;
            z->color = 'R';
            rb_insert_fixup(root, z);
        }
    }
    /*************************************************************************************/
    // http://www.geeksforgeeks.org/connect-nodes-at-same-level/
    // Connect levels in complete binary tree.
    void link_levels_complete2(Node<int>* p) {
        if (!p) return;
        if (p->left) p->left->sibling = p->right;
        if (p->right) p->right->sibling = p->sibling ? p->sibling->left : NULL;

        link_levels_complete2(p->left);
        link_levels_complete2(p->right);
    }
    void link_levels_complete(Node<int>*p) {
        p->sibling = NULL;
        link_levels_complete2(p);
    }
    /*************************************************************************************/
    // http://www.geeksforgeeks.org/vertex-cover-problem-set-2-dynamic-programming-solution-tree/
    // Finds the size of the vertex cover of a binary tree. Every edge must be represented
    // by one of its nodes.
    size_t cover(Node<int> *root) {
        if (!root) return 0;
        if (!root->left && !root->right) return 0;
        if (root->cover) return root->cover;

        // 'root' is either included or excluded. If it is excluded, both children must 
        // be part of the set cover or there would be no edge to root.
        size_t incl = 1 + cover(root->left) + cover(root->right);
        size_t excl = 0;

        if (root->left) excl += 1 + cover(root->left->left) + cover(root->left->right);
        if (root->right) excl += 1 + cover(root->right->left) + cover(root->right->right);

        return root->cover = std::min(incl, excl);
    }
    /*************************************************************************************/
    // http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/
    void morris(Node<int> *root) {
        if (!root) return;

        Node<int> *cur = root, *pre;
        while (cur) {
            if (cur->left) {
                pre = cur->left;
                while (pre->right && pre->right != cur)
                    pre = pre->right;

                if (pre->right) {
                    printf(" %d ", cur->value);
                    pre->right = NULL;
                    cur = cur->right;
                } else {
                    pre->right = cur;
                    cur = cur->left;
                }
            } else {
                printf(" %d ", cur->value);
                cur = cur->right;
            }
        }
    }
    /*************************************************************************************/
    Node<int>* morris(Node<int>** cs, Node<int>** ps) {
        if (!*cs) return NULL;
        while (*cs) {
            if ((*cs)->left) {
                *ps = (*cs)->left;
                while ((*ps)->right && (*ps)->right != (*cs))
                    *ps = (*ps)->right;

                if ((*ps)->right) {
                    auto temp = *cs;
                    (*ps)->right = NULL;
                    *cs = (*cs)->right;
                    return temp;
                }
                else {
                    (*ps)->right = *cs;
                    *cs = (*cs)->left;
                }
            }
            else {
                auto temp = *cs;
                *cs = (*cs)->right;
                return temp;
            }
        }
        return NULL;
    }
    void merge(Node<int> *r1, Node<int> *r2) {
        Node<int> *cs1 = r1, *cs2 = r2, *ps1, *ps2, *n1, *n2;
        ps1 = ps2 = n1 = n2 = NULL;

        n1 = morris(&cs1, &ps1);
        n2 = morris(&cs2, &ps2);

        while (n1 || n2) {
            if ((n1 && !n2) || (n1 && n2 && n1->value <= n2->value)) {
                printf("%d\n", n1->value);
                n1 = morris(&cs1, &ps1);
            }
            if ((n2 && !n1) || (n1 && n2 && n2->value <= n1->value)) {
                printf("%d\n", n2->value);
                n2 = morris(&cs2, &ps2);
            }
        }
    }
    void test_merge() {
        // 4 2 5 1 3
        /* 
             7
            / \
           4   8
          / \
         2   5
        */
        Node<int> *root1 = new Node<int>(7);
        root1->left = new Node<int>(4);
        root1->right = new Node<int>(8);
        root1->left->left = new Node<int>(2);
        root1->left->right = new Node<int>(5);

        /*
            3
           / \
          1   9
             / \
            6  10
        */
        Node<int> *root2 = new Node<int>(3);
        root2->left = new Node<int>(1);
        root2->right = new Node<int>(9);
        root2->right->left = new Node<int>(6);
        root2->right->right = new Node<int>(10);

        merge(root1, root2);
    }
    /*************************************************************************************/
    void push_inorder(std::stack<Node<int>*> &s, Node<int> *n) {
        if (n->left) s.push(n->left);
        s.push(n);
    }
    void traverse_inorder(Node<int> *n) {
        std::stack<Node<int>*> s;
        push_inorder(s, n);
        while (!s.empty()) {
            n = s.top();
            s.pop();
            if (!s.empty() && s.top() == n->left) {
                Node<int>* t = s.top();
                s.pop();
                s.push(n);
                push_inorder(s, t);
            }
            else {
                std::cout << n->value << std::endl;
                if (n->right) push_inorder(s, n->right);
            }
        }
    }
    void test_traverse_inorder() {
        std::vector<int> v(10);
        std::iota(v.begin(), v.end(), 1);
        auto tree = generate_random_tree(v);
        auto settings = gcnew Microsoft::VisualStudio::GraphModel::GraphSerializationSettings();
        ToGraph(&tree)->Save("BinaryTree.dgml", settings);
        traverse_inorder(&tree);
    }
    /*************************************************************************************/
    template <typename T> struct LNode {
        LNode(T t) {
            this->value = t;
            this->next = NULL;
        }
        T value;
        LNode<T> *next;
    };
    LNode<int>** bst_to_dlist(LNode<int> **l, Node<int> *n) {
        if (!n) return l;
        l = bst_to_dlist(l, n->left);
        *l = new LNode<int>(n->value);
        l = &((*l)->next);
        return l = bst_to_dlist(l, n->right);
    }
    void test_bst_to_dlist() {
        std::vector<int> v(10);
        std::iota(v.begin(), v.end(), 1);
        auto tree = generate_random_tree(v);
        auto settings = gcnew Microsoft::VisualStudio::GraphModel::GraphSerializationSettings();
        ToGraph(&tree)->Save("BinaryTree.dgml", settings);
        LNode<int>* list;
        bst_to_dlist(&list, &tree);
    }
    /*************************************************************************************/
}
