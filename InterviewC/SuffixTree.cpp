#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

namespace trie {
    class SuffixNode;
    typedef std::unique_ptr<SuffixNode> Node;

    unsigned long node_id = 0;
    class SuffixNode {
    private:
        std::map<wchar_t, Node> children_;

    public:
        SuffixNode* suffix;
        unsigned long id;

        SuffixNode(SuffixNode *node = NULL) {
            suffix = node == NULL ? this : node;
            id = node_id++;
        }
        ~SuffixNode() {
            std::cout << this->id << std::endl;
        }
        SuffixNode* operator[](wchar_t c) {
            return children_.find(c) == children_.end() ? nullptr : children_[c].get();
        }
        void add_link(wchar_t c, SuffixNode* node) {
            children_[c] = Node(node);
        }
        bool contains(const std::wstring &pattern) {
            auto current = this;
            for (auto c : pattern) {
                if ((*current)[c] == NULL) return false;
                current = (*current)[c];
            }
            return true;
        }
    };
    Node build_trie(const std::wstring &s) {
        if (s.size() == 0) return Node(new SuffixNode());

        auto root = new SuffixNode();
        auto longest = new SuffixNode(root);
        root->add_link(s[0], longest);

        for (auto c : s.substr(1)) {
            SuffixNode *current = longest, *previous = NULL;
            bool added_to_root = false;

            while ((*current)[c] == NULL) {
                auto new_node = new SuffixNode();
                if (previous != NULL) previous->suffix = new_node;

                current->add_link(c, new_node);
                previous = new_node;

                if (current == root) added_to_root = true;
                current = current->suffix;
            }

            previous->suffix = added_to_root ? root : (*current)[c];

            longest = (*longest)[c];
        }
        return Node(root);
    }
}

//int main() {
//	auto trie = trie::build_trie(L"abaabcdeaaabb");
//
//	auto r1 = trie->contains(L"abc");
//	auto r2 = trie->contains(L"abcd");
//	auto r3 = trie->contains(L"abcde");
//	auto r4 = trie->contains(L"abcdx");
//
//	return 0;
//}

/*****************************************************************/
#define MAX_CHAR 256
struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];
    struct SuffixTreeNode *suffixLink;
    int suffixIndex;
    int start;
    int *end;
};
typedef struct SuffixTreeNode Node;

char text[100];
Node *root = NULL;
Node *lastNewNode = NULL;
Node *activeNode = NULL;
int activeEdge = -1;
int activeLength = 0;
int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = NULL;
int *splitEnd = NULL;
int size = -1;

Node* newNode(int start, int *end) {
    Node *node = (Node*)malloc(sizeof(Node));

    for (int i = 0; i < MAX_CHAR; i++)
        node->children[i] = NULL;

    node->suffixLink = root;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;

    return node;
}

int edgeLength(Node *n) {
    return n != root ? *n->end - n->start + 1 : 0;
}

int walkDown(Node *currNode) {
    if (activeLength < edgeLength(currNode)) return 0;

    activeEdge += edgeLength(currNode);
    activeLength -= edgeLength(currNode);
    activeNode = currNode;

    return 1;
}

void extendSuffixTree(int pos) {
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = NULL;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0) activeEdge = pos;

        if (activeNode->children[text[activeEdge]] == NULL) {
            activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

            if (lastNewNode != NULL) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        }
        else {
            Node *next = activeNode->children[text[activeEdge]];
            if (walkDown(next)) continue;

            if (text[next->start + activeLength] == text[pos]) {
                if (lastNewNode != NULL && activeNode != root) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }

                activeLength++;
                break;
            }

            splitEnd = (int*)malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;

            Node *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;

            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;

            if (lastNewNode != NULL) lastNewNode->suffixLink = split;
            lastNewNode = split;
        }

        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root) activeNode = activeNode->suffixLink;
    }
}

void setSuffixIndexByDFS(Node *n, int suffix) {
    if (n == NULL)
        return;

    bool leaf = true;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (n->children[i] != NULL) {
            leaf = false;
            setSuffixIndexByDFS(n->children[i], suffix + edgeLength(n->children[i]));
        }
    }

    if (leaf) {
        auto sub_string = std::string(text).substr(n->start, *n->end - n->start + 1);
        n->suffixIndex = size - suffix;
        auto suffix = std::string(text).substr(strlen(text) - 1 - n->suffixIndex, n->suffixIndex);
    }
}

void freeSuffixTreeByPostOrder(Node *n) {
    if (n == NULL)
        return;

    for (int i = 0; i < MAX_CHAR; i++)
        if (n->children[i] != NULL)
            freeSuffixTreeByPostOrder(n->children[i]);

    if (n->suffixIndex == -1)
        free(n->end);
    free(n);
}

void buildSuffixTree() {
    size = strlen(text);
    rootEnd = (int*)malloc(sizeof(int));
    *rootEnd = -1;
    root = newNode(-1, rootEnd);
    activeNode = root;

    for (int i = 0; i < size; i++)
        extendSuffixTree(i);

    setSuffixIndexByDFS(root, 0);
}

// -1: Mismatch
//  0: Have remainder
//  1: Match
int traverseEdge(char *str, int idx, int start, int end) {
    for (int k = start; k <= end && str[idx] != '\0'; k++, idx++)
        if (text[k] != str[idx])
            return -1;

    return str[idx] == '\0';
}

int doTraversalToCountLeaf(Node *n) {
    if (n == NULL) return 0;
    if (n->suffixIndex > -1) {
        printf("%s: pattern @ %d.\n", text, n->suffixIndex);
        return 1;
    }

    int count = 0;
    for (int i = 0; i < MAX_CHAR; i++)
        if (n->children[i] != NULL)
            count += doTraversalToCountLeaf(n->children[i]);

    return count;
}

int countLeaf(Node *n) {
    if (n == NULL)
        return 0;
    return doTraversalToCountLeaf(n);
}

int doTraversal(Node *n, char* str, int idx) {
    if (n == NULL)
        return 0;

    if (n->start != -1) {
        int res = traverseEdge(str, idx, n->start, *n->end);
        if (res == -1) return 0;
        if (res == 1) {
            if (n->suffixIndex > -1) {
                printf("%s: pattern @ %d.\n", text, n->suffixIndex);
                return 1;
            }
            return countLeaf(n);
        }
        idx += edgeLength(n);
    }

    if (n->children[str[idx]] == NULL)
        return 0;

    return doTraversal(n->children[str[idx]], str, idx);
}

int checkForSubString(char* str) {
    return doTraversal(root, str, 0);
}

//int main(int argc, char *argv[]) {
//    int r;
//
//    strcpy_s(text, "GEEKSFORGEEKS$");
//    buildSuffixTree();
//    r = checkForSubString("GEEKS");
//    r = checkForSubString("GEEK1");
//    r = checkForSubString("FOR");
//    freeSuffixTreeByPostOrder(root);
//
//    strcpy_s(text, "AABAACAADAABAAABAA$");
//    buildSuffixTree();
//    r = checkForSubString("AABA");
//    r = checkForSubString("AA");
//    r = checkForSubString("AAE");
//    freeSuffixTreeByPostOrder(root);
//
//    strcpy_s(text, "AAAAAAAAA$");
//    buildSuffixTree();
//    r = checkForSubString("AAAA");
//    r = checkForSubString("AA");
//    r = checkForSubString("A");
//    r = checkForSubString("AB");
//    freeSuffixTreeByPostOrder(root);
//
//    return 0;
//}

/*****************************************************************/