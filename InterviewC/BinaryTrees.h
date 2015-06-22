#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <stack>
#include <vector>
#include <chrono>

namespace BinaryTrees
{
    /*************************************************************************************/
    template<typename T>
    struct Node {
        Node(T value) { this->value = value; }
        ~Node() {
            if (left != NULL) delete left;
            if (right != NULL) delete right;
            //std::wcout << L"Destructor called for " << this->value << std::endl;
        }
        Node<T> *left = NULL, *right = NULL, *sibling = NULL, *parent = NULL;
        size_t height = 1;
        size_t cover = 0; // Vertex cover.
        char color = '\0';
        std::vector<Node<T>*> children;
        T value;
    };
    /*************************************************************************************/
    template<typename T>
    Node<T> generate_random_tree(const std::vector<T> &values) {
        return generate_random_tree(values, (unsigned)clock());
    }
    /*************************************************************************************/
    template<typename T>
    Node<T> generate_random_tree(const std::vector<T> &values, unsigned seed) {
        std::vector<T> valuesCopy = values;

        std::default_random_engine generator(seed);
        std::uniform_int_distribution<size_t> distribution(0, SIZE_MAX);
        auto randomizer = std::bind(distribution, generator);

        Node<T> *root;
        std::vector<Node<T>**> leaves = { &root };

        while (!valuesCopy.empty()) {
            size_t valueIndex = randomizer() % valuesCopy.size();
            T value = valuesCopy[valueIndex];
            valuesCopy.erase(valuesCopy.begin() + valueIndex);

            size_t leafIndex = randomizer() % leaves.size();
            Node<T> **leaf = leaves[leafIndex];
            leaves.erase(leaves.begin() + leafIndex);

            *leaf = new Node<T>(value);
            leaves.push_back(&(*leaf)->left);
            leaves.push_back(&(*leaf)->right);
        }
        return *root;
    }
    /*************************************************************************************/
    template<typename T>
    Node<T> generate_random_nary_tree(const std::vector<T> &values, size_t degree) {
        return generate_random_nary_tree(values, degree, (unsigned)clock());
    }
    template<typename T>
    Node<T> generate_random_nary_tree(const std::vector<T> &values, size_t degree, unsigned seed) {
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<size_t> distribution(0, SIZE_MAX);
        auto randomizer = std::bind(distribution, generator);

        std::vector<T> valuesCopy = values;
        size_t valueIndex = randomizer() % valuesCopy.size();
        T value = valuesCopy[valueIndex];
        valuesCopy.erase(valuesCopy.begin() + valueIndex);

        Node<T> *root = new Node<T>(value);
        std::vector<Node<T>*> leaves = { root };

        while (!valuesCopy.empty()) {
            size_t valueIndex = randomizer() % valuesCopy.size();
            T value = valuesCopy[valueIndex];
            valuesCopy.erase(valuesCopy.begin() + valueIndex);

            size_t leafIndex = randomizer() % leaves.size();
            Node<T> *leaf = leaves[leafIndex];

            auto newNode = new Node<T>(value);
            leaf->children.push_back(newNode);
            leaves.push_back(newNode);

            if (leaf->children.size() == degree)
                leaves.erase(leaves.begin() + leafIndex);
        }
        return *root;
    }
    /*************************************************************************************/
    using namespace Microsoft::VisualStudio::GraphModel;
    using namespace System;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Media;

    template <typename T> Graph^ ToGraph(Node<T> *root)
    {
        auto graph = gcnew Graph();
        auto nodeToId = gcnew Dictionary<IntPtr, GraphNodeId^>();

        std::vector<Node<T>*> leaves;
        leaves.push_back(root);
        GraphNode^ rootNode = graph->Nodes->CreateNew(root->value.ToString());
        String^ rootColor = root->color ? " " + gcnew String(new wchar_t[] { (wchar_t)root->color, L'\0' }) : L"";
        rootNode->Label = root->value.ToString() + rootColor;
        nodeToId->Add((IntPtr)root, rootNode->Id);

        while (leaves.size() > 0)
        {
            auto node = *leaves.crbegin();
            leaves.pop_back();

            GraphNodeId^ id = nodeToId[(IntPtr)node];
            GraphNode^ parent = graph->Nodes->Get(id);

            String^ leftColor = node->left && node->left->color ? " " + gcnew String(new wchar_t[] { (wchar_t)node->left->color, L'\0' }) : "";
            String^ labelLeft = node->left == NULL ? "None" : node->left->value.ToString() + leftColor;
            GraphNode^ left = graph->Nodes->CreateNew(labelLeft);
            left->Label = labelLeft;
            GraphLink^ leftLink = graph->Links->GetOrCreate(parent, left);
            leftLink->Label = L"Left";

            String^ rightColor = node->right && node->right->color ? " " + gcnew String(new wchar_t[] { (wchar_t)node->right->color, L'\0' }) : "";
            String^ labelRight = node->right == NULL ? L"None" : node->right->value.ToString() + rightColor;
            GraphNode^ right = graph->Nodes->CreateNew(labelRight);
            right->Label = labelRight;
            GraphLink^ rightLink = graph->Links->GetOrCreate(parent, right);
            rightLink->Label = L"Right";

            if (node->left != NULL)
            {
                nodeToId->Add((IntPtr)node->left, left->Id);
                leaves.push_back(node->left);
            }
            if (node->right != NULL)
            {
                nodeToId->Add((IntPtr)node->right, right->Id);
                leaves.push_back(node->right);
            }
        }
        return graph;
    }
    /*************************************************************************************/
    template <typename T> Graph^ ToNaryGraph(Node<T> *root) {
        auto graph = gcnew Graph();
        auto nodeToId = gcnew Dictionary<IntPtr, GraphNodeId^>();

        std::vector<Node<T>*> leaves;
        leaves.push_back(root);
        GraphNode^ rootNode = graph->Nodes->CreateNew(root->value.ToString());
        rootNode->Label = root->value.ToString();
        nodeToId->Add((IntPtr)root, rootNode->Id);

        while (leaves.size() > 0) {
            auto node = *leaves.begin();
            leaves.erase(leaves.begin());

            GraphNodeId^ id = nodeToId[(IntPtr)node];
            GraphNode^ parent = graph->Nodes->Get(id);

            for (Node<T>* n : node->children) {
                String^ label = n->value.ToString();
                GraphNode^ child = graph->Nodes->CreateNew(label);
                child->Label = label;
                GraphLink^ link = graph->Links->GetOrCreate(parent, child);
                nodeToId->Add((IntPtr)n, child->Id);
                leaves.push_back(n);
            }
        }
        return graph;
    }
    /*************************************************************************************/
    template <typename T>
    void append_node(Node<T> **root, T value) {
        while (*root != NULL) root = value > (*root)->value ? &((*root)->right) : &((*root)->left);
        *root = new Node<T>(value);
    }
    /*************************************************************************************/
    // Find the distance between two nodes, i.e. the number of nodes on the shortest path
    // between the two.
    template <typename T>
    ptrdiff_t node_distance(const Node<T> *root, T node1, T node2) {
        ptrdiff_t level1 = -1, level2 = -1, lcaLevel = -1;

        node_distance(root, 1, node1, node2, level1, level2, lcaLevel);

        if (lcaLevel == -1) return -1;

        ptrdiff_t distance = (level1 - lcaLevel) + (level2 - lcaLevel) + 1;
        return distance;
    }
    template <typename T>
    void node_distance(const Node<T> *n, ptrdiff_t level,
        T node1, T node2,
        ptrdiff_t &level1, ptrdiff_t &level2,
        ptrdiff_t &lcaLevel) {
        if (n == NULL) return;

        int prevLevel1 = level1, prevLevel2 = level2;
        if (n->value == node1) level1 = level;
        if (n->value == node2) level2 = level;

        if (level1 == -1 || level2 == -1) {
            node_distance(n->left, level + 1, node1, node2, level1, level2, lcaLevel);
            node_distance(n->right, level + 1, node1, node2, level1, level2, lcaLevel);
        }
        if (prevLevel1 != level1 && prevLevel2 != level2 && lcaLevel == -1) lcaLevel = level;
    }
    /*************************************************************************************/
    // Same as below, but with just two arguments.
    template<typename T>
    Node<T> *find_lca_two(Node<T> *root, T v1, T v2) {
        if (!root) return nullptr;
        if (root->value == v1 || root->value == v2) return root;
        Node<T> *l = find_lca_two(root->left, v1, v2);
        Node<T> *r = find_lca_two(root->right, v1, v2);
        if (l && r) return root;
        return l ? l : r;
    }
    /*************************************************************************************/
    template<typename T>
    Node<T> *find_lca(Node<T> *root, const std::vector<T> &v) {
        if (!root) return nullptr;
        for (T t : v) if (t == root->value) return root;
        Node<T> *l = find_lca(root->left, v);
        Node<T> *r = find_lca(root->right, v);
        if (l && r) return root;
        return l ? l : r;
    }
    /*************************************************************************************/
    // For arbitrary number of children, with arbitrary number of values.
    // NOTE: If a node brings together more than one node in its subtrees, 
    // that node is "an LCA" and can be returned.
    template<typename T>
    Node<T>* find_lca_general(Node<T>* root, std::vector<T> &values) {
        if (!root) return nullptr;
        for (T t : values) if (t == root->value) return root;

        Node<T> *lca = nullptr;
        for (Node<T>* child : root->children)
            if (auto tmp = find_lca_general(child, values)) {
            if (lca) return root;
            lca = tmp;
            }
        return lca;
    }
    /*************************************************************************************/
    template <typename T>
    Node<T>* find_lca(Node<T> &root, std::vector<T> values) {
        return find_lca(&root, values, std::vector<bool>(values.size(), false));
    }
    template <typename T>
    Node<T>* find_lca(Node<T> *n, std::vector<T> &values, std::vector<bool> &found) {
        if (n == NULL) return NULL;

        typedef std::vector<bool>::size_type vsize;
        std::vector<bool> found_previous = found;
        for (vsize i = 0; i < values.size(); ++i)
            if (n->value == values[i]) found[i] = true;

        Node<T> *left = NULL, *right = NULL;
        if (std::find(found.begin(), found.end(), false) != found.end()) {
            left = find_lca(n->left, values, found);
            right = find_lca(n->right, values, found);
        }

        if (left != NULL) return left;
        if (right != NULL) return right;

        for (vsize i = 0; i < values.size(); ++i)
            if (found[i] == found_previous[i]) return NULL;

        return n;
    }
    /*************************************************************************************/
    template<typename T>
    Node<T>* closest_leaf(Node<T>* n) {
        size_t level;
        return closest_leaf(n, level);
    }
    template<typename T>
    Node<T>* closest_leaf(Node<T>* n, size_t &level) {
        if (!n->left && !n->right) {
            level = 0;
            return n;
        }
        size_t ll = SIZE_MAX, lr = SIZE_MAX;
        Node<T> *nl = nullptr, *nr = nullptr;
        if (n->left) nl = closest_leaf(n->left, ll);
        if (n->right) nr = closest_leaf(n->right, lr);

        if (ll < lr) {
            level = ll;
            return nl;
        }
        else {
            level = lr;
            return nr;
        }
    }
    /*************************************************************************************/
    template<typename T>
    Node<T>* find_node(Node<T>* n, T v) {
        if (!n) return nullptr;
        if (n->value == v) return n;
        Node<T>* l = find_node(n->left, v);
        if (l) return l;
        Node<T>* r = find_node(n->right, v);
        if (r) return r;
        return nullptr;
    }
    /*************************************************************************************/
    template <typename T>
    long long sum_left_leaves(Node<T>* n, bool isLeft = false) {
        if (!n) return 0;
        if (isLeft && !n->left && !n->right) return n->value;
        return sum_left_leaves(n->left, true) + sum_left_leaves(n->right, false);
    }
    /*************************************************************************************/
    template <typename T>
    void print_spiral(Node<T>* root) {
        std::stack<Node<T>*> current_level, next_level;
        bool ltr = true;
        current_level.push(root);
        while (!current_level.empty()) {
            while (!current_level.empty()) {
                Node<T>* n = current_level.top();
                current_level.pop();
                if (!n) continue;
                std::cout << n->value << " ";
                if (ltr) {
                    next_level.push(n->left);
                    next_level.push(n->right);
                }
                else {
                    next_level.push(n->right);
                    next_level.push(n->left);
                }
            }
            std::cout << std::endl;
            std::swap(current_level, next_level);
            ltr = !ltr;
        }
    }
    /*************************************************************************************/
    template <typename T>
    void print_by_level(Node<T>* root) {
        if (root == NULL) return;
        std::deque<Node<T>*> d;
        d.push_front(root);

        while (!d.empty()) {
            size_t s = d.size();
            for (size_t i = 0; i < s; i++) {
                Node<T>* n = d.front();
                d.pop_front();
                if (!n) continue;
                std::wcout << n->value << " ";
                d.push_back(n->left);
                d.push_back(n->right);
            }
            std::wcout << std::endl;
        }
    }
    /*************************************************************************************/
    template <typename T>
    void print_tree_by_spiral(Node<T>* tree) {
        std::vector<Node<T>*> l1 = { tree }, l2;
        bool ltr = true;
        while (!l1.empty()) {
            while (!l1.empty()) {
                Node<T>* node = l1.back();
                l1.pop_back();
                if (node == NULL) continue;
                std::cout << node->value << " ";
                if (ltr) {
                    l2.push_back(node->left);
                    l2.push_back(node->right);
                }
                else {
                    l2.push_back(node->right);
                    l2.push_back(node->left);
                }
            }
            std::cout << std::endl;
            ltr = !ltr;
            std::swap(l1, l2);
        }
    }
    /*************************************************************************************/
    template <typename Key>
    struct SplayTree {
        Node<Key> *root = NULL;

        Node<Key>* get(Key key) {
            root = splay(root, key);
            return key == root->value ? root : NULL;
        }
        void insert(Key k) {
            if (!root) {
                root = new Node<Key>(k);
                return;
            }

            root = splay(root, k);
            if (root->value == k) return;
            Node<Key> *n = new Node<Key>(k);

            if (root->value > k) {
                n->right = root;
                n->left = root->left;
                root->left = NULL;
            } else {
                n->left = root;
                n->right = root->right;
                root->right = NULL;
            }
            root = n;
        }
        void remove(Key key) {
            remove(root, key);
        }
        Node<Key>* get_min_node(Node<Key> *node) {
            while (node->left) node = node->left;
            return node;
        }
        Node<Key>* remove(Node<Key>* root, Key key) {
            if (!root) return NULL;

            if (key < root->value)
                root->left = remove(root->left, key);
            else if (key > root->value)
                root->right = remove(root->right, key);
            else {
                if (!root->left) {
                    Node<Key> *temp = root->right;
                    delete root;
                    return temp;
                }
                else if (!root->right) {
                    Node<Key> *temp = root->left;
                    delete root;
                    return temp;
                }
                Node<Key>* min = get_min_node(root->right);
                root->value = min->value;
                root->right = remove(root->right, min->value);
            }
            return root;
        }
        Node<Key>* splay(Node<Key> *root, Key key) {
            if (!root || root->value == key) return root;

            if (root->value > key) {
                if (!root->left) return root;

                if (root->left->value > key) {
                    root->left->left = splay(root->left->left, key);
                    root = rotate_right(root);
                } else if (root->left->value < key) {
                    root->left->right = splay(root->left->right, key);
                    if (root->left->right)
                        root->left = rotate_left(root->left);
                }

                return root->left ? rotate_right(root) : root;
            } else {
                if (!root->right) return root;

                if (root->right->value > key) {
                    root->right->left = splay(root->right->left, key);
                    if (root->right->left)
                        root->right = rotate_right(root->right);
                } else if (root->right->value < key) {
                    root->right->right = splay(root->right->right, key);
                    root = rotate_left(root);
                }

                return root->right ? rotate_left(root) : root;
            }
        }
        size_t height() {
            return height(root);
        }
        size_t height(Node<Key>* x) {
            return x ? 1 + std::max(height(x->left), height(x->right)) : -1;
        }
        size_t size() {
            return size(root);
        }
        size_t size(Node<Key>* x) {
            return x ? 1 + size(x->left) + size(x->right) : 0;
        }
        Node<Key>* rotate_right(Node<Key>* n) {
            Node<Key>* x = n->left;
            n->left = x->right;
            x->right = n;
            return x;
        }
        Node<Key>* rotate_left(Node<Key>* n) {
            Node<Key>* x = n->right;
            n->right = x->left;
            x->left = n;
            return x;
        }
    };
    /*************************************************************************************/
    bool is_bst(Node<int>* node);
    void link_levels(Node<int>* n);
    Node<int>* avl_insert(Node<int>* node, int key);
    Node<int>* avl_delete(Node<int>* root, int key);
    void rb_insert(Node<int> **root, int data);
    size_t cover(Node<int> *root);
    void test_merge();
    void traverse_inorder(Node<int> *n);
    void test_traverse_inorder();
    void test_bst_to_dlist();
    /*************************************************************************************/
}
