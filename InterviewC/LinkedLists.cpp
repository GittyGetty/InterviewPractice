#include <memory>
#include <iostream>

/************************************************************/

struct node {
	node(int v) {
		this->v = v;
		this->next = NULL;
	}
	int v;
	node* next;
};

/************************************************************/

int find_node(int v, node* root, node** n, node** pn) {
	int i = 0;
	for (*n = root; *n != NULL && (*n)->v != v; ++i) {
		*pn = *n;
		*n = (*n)->next;
	}
	return i;
}

/************************************************************/

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
	else {
		n2->next = n1;
	}
}

/************************************************************/

void print_linked_list(node* root) {
	while (root != NULL) {
		std::cout << root->v << std::endl;
		root = root->next;
	}
}

/************************************************************/

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

/************************************************************/

struct node *swap_pairwise_g4g2(struct node* head)
{
	if (head == NULL || head->next == NULL)
		return head;

	struct node* remaing = head->next->next;
	struct node* newhead = head->next;
	head->next->next = head;
	head->next = swap_pairwise_g4g2(remaing);

	return newhead;
}

/************************************************************/

node* swap(node* first) {
	if (first == NULL || first->next == NULL) return first;

	node* second = first->next;
	first->next = swap(second->next);
	second->next = first;

	return second;
}

/************************************************************/

node* swap_k(node* head, int k) {
	node *pn, *n = head,
		*pnx = nullptr, *nx = nullptr,
		*pny = nullptr, *ny = head;
	int p;

	for (p = 0; n != NULL; ++p) {
		pn = n;
		if (p == k) {
			pnx = pn;
			nx = n;
		}
		if (p > k) {
			pny = ny;
			ny = ny->next;
		}
		n = n->next;
	}

	if (p <= k) return NULL;
	if (nx == ny) return head;

	// Head and tail are to be swapped, so update head.
	if (p == 0) {
		ny->next = nx->next;
		pny->next = nx;
		nx->next = NULL;
		head = ny;
		// Adjacent nodes are to be swapped.
	} else if (p / 2 == k + 1) {
		pnx->next = ny;
		auto tmp = ny->next;
		ny->next = nx;
		nx->next = tmp;
		// Nodes are at least one apart.
	} else {
		pnx->next = ny;
		auto tmp = ny->next;
		ny->next = nx->next;
		pny->next = nx;
		nx->next = tmp;
	}
	return head;
}

/************************************************************/

node* swap_pairwise(node* root) {
	// Prepend a node to root to reduce special-casing.
	std::auto_ptr<node> aux(new node(0));
	aux->next = root;
	node* n1 = aux.get();

	while (n1->next != NULL && n1->next->next != NULL) {
		node *n2 = n1->next, *n3 = n2->next, *n4 = n3->next;

		n1->next = n3;
		n3->next = n2;
		n2->next = n4;

		n1 = n2;
	}
	return aux->next;
}

