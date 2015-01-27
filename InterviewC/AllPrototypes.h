#include <functional>
#include <iostream>
#include <random>
#include <vector>
#include <map>

namespace BinaryTrees
{
    template<typename T>
    struct Node {
        Node(T value) { this->value = value; }
        ~Node() {
            if (left != NULL) delete left;
            if (right != NULL) delete right;
            std::wcout << L"Destructor called for " << this->value << std::endl;
        }
        Node<T> *left = NULL, *right = NULL;
        T value;
    };

    template<typename T>
    Node<T> generate_random_tree(const std::vector<T> &values) {
        return generate_random_tree(values, (unsigned)clock());
    }

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
        rootNode->Label = root->value.ToString();
        nodeToId->Add((IntPtr)root, rootNode->Id);

        while (leaves.size() > 0)
        {
            auto node = *leaves.crbegin();
            leaves.pop_back();

            GraphNodeId^ id = nodeToId[(IntPtr)node];
            GraphNode^ parent = graph->Nodes->Get(id);

            String^ labelLeft = node->left == NULL ? L"None" : node->left->value.ToString();
            GraphNode^ left = graph->Nodes->CreateNew(labelLeft);
            left->Label = labelLeft;
            GraphLink^ leftLink = graph->Links->GetOrCreate(parent, left);
            leftLink->Label = L"Left";

            String^ labelRight = node->right == NULL ? L"None" : node->right->value.ToString();
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

    template <typename T>
    void append_node(Node<T> **root, T value) {
        while (*root != NULL) root = value > (*root)->value ? &((*root)->right) : &((*root)->left);
        *root = new Node<T>(value);
    }
}