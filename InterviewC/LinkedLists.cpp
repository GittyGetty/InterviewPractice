#include <memory>
#include <iostream>

#include "LinkedLists.h"

/************************************************************************************/
struct node {
	node(int v) {
		this->v = v;
		this->next = NULL;
	}
	int v;
	node* next;
};
/************************************************************************************/
int find_node(int v, node* root, node** n, node** pn) {
	int i = 0;
	for (*n = root; *n != NULL && (*n)->v != v; ++i) {
		*pn = *n;
		*n = (*n)->next;
	}
	return i;
}
void swap_nodes(node **root, int v1, int v2) {
	if (v1 == v2) return;

	node *n1, *n2, *pn1, *pn2;

	int p1 = find_node(v1, *root, &n1, &pn1);
	int p2 = find_node(v2, *root, &n2, &pn2);

	if (p1 > p2) {
		std::swap(n1, n2);
		std::swap(pn1, pn2);
		std::swap(p1, p2);
	}

	if (p1 == 0) *root = n2;
	else pn1->next = n2;

	node* nn1 = n1->next;
	n1->next = n2->next;

	if (p2 - p1 > 1) {
		n2->next = nn1;
		pn2->next = n1;
	}
	else n2->next = n1;
}
/************************************************************************************/
void print_linked_list(node* root) {
	while (root != NULL) {
		std::cout << root->v << std::endl;
		root = root->next;
	}
}
/************************************************************************************/
void swap_pairwise_g4g1(struct node **head) {
	if (*head == NULL || (*head)->next == NULL)
		return;

	struct node *prev = *head;
	struct node *curr = (*head)->next;
	*head = curr;

	while (true) {
		struct node *next = curr->next;
		curr->next = prev;

		if (next == NULL || next->next == NULL)	{
			prev->next = next;
			break;
		}

		prev->next = next->next;
		prev = next;
		curr = prev->next;
	}
}
struct node *swap_pairwise_g4g2(struct node* head) {
	if (!head || !head->next) return head;

	struct node* remaing = head->next->next;
	struct node* newhead = head->next;
	head->next->next = head;
	head->next = swap_pairwise_g4g2(remaing);

	return newhead;
}
/************************************************************************************/
// http://www.geeksforgeeks.org/write-a-function-to-reverse-the-nodes-of-a-linked-list/
void reverse(struct node** root) {
    struct node* prev = NULL;
    struct node* current = *root;
    struct node* next;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *root = prev;
}
/************************************************************************************/
// http://www.geeksforgeeks.org/merge-a-linked-list-into-another-linked-list-at-alternate-positions/
// 5->7->17->13->11 : 12->10->2->4->6 => 5->12->7->10->17->2->13->4->11->6 
void merge(struct node *p, struct node **q) {
    struct node *p_curr = p, *q_curr = *q;
    struct node *p_next, *q_next;

    while (p_curr && q_curr) {
        p_next = p_curr->next;
        q_next = q_curr->next;

        q_curr->next = p_next;
        p_curr->next = q_curr;

        p_curr = p_next;
        q_curr = q_next;
    }
    *q = q_curr;
}
/************************************************************************************/
// http://www.mytechinterviews.com/loop-in-a-singly-linked-list
bool hasLoop(struct node *startNode) {
    struct node *slowNode, *fastNode;
    slowNode = fastNode = startNode;
    while (slowNode && fastNode && fastNode->next) {
        if (slowNode == fastNode->next || slowNode == fastNode->next->next) return true;
        slowNode = slowNode->next;
        fastNode = fastNode->next->next;
    }
    return false;
}
/************************************************************************************/
// Find first node on which two linked lists merge.
// http://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/
size_t get_length(struct node* head) {
    size_t count;
    for (count = 0; head; ++count) head = head->next;
    return count;
}
// Returns the value of the node at which lists merge.
int find_merge_node(int d, struct node* head1, struct node* head2) {
    struct node* n1 = head1;
    struct node* n2 = head2;

    for (int i = 0; i < d; ++i) {
        if (!n1) return -1;
        n1 = n1->next;
    }
    while (n1 && n2) {
        if (n1 == n2) return n1->v;
        n1 = n1->next;
        n2 = n2->next;
    }
    return -1;
}
int find_merge_node(struct node* head1, struct node* head2) {
    size_t l1 = get_length(head1);
    size_t l2 = get_length(head2);
    size_t d;

    if (l1 > l2) {
        d = l1 - l2;
        return find_merge_node(d, head1, head2);
    } else {
        d = l2 - l1;
        return find_merge_node(d, head2, head1);
    }
}
/************************************************************************************/
struct node2 {
    int data;
    node2 *next = nullptr;
    node2 *other = nullptr;
};
node2* copy_linked_list(node2* list) {
    if (list == nullptr) return list;
    // Pass 1: Insert copies into linked list.
    node2 *n = list;
    while (n != nullptr) {
        node2* copy = new node2();
        copy->data = n->data;
        copy->next = n->next;
        n->next = copy;
        n = n->next->next;
    }
    // Pass 2: Set other pointers.
    while (n != nullptr) {
        n->next->other = n->other->next;
        n = n->next->next;
    }
    // Pass 3: Separate interweaved lists.
    node2* copy_list = nullptr;
    while (n != nullptr) {
        node2 *tmp = n->next;

        if (copy_list == nullptr) copy_list = tmp;
        else copy_list->next = tmp;

        n->next = n->next->next;
        n = n->next;
    }
    return copy_list;
}
/************************************************************************************/