#include <array>
#include <string>
#include <utility>
#include <algorithm>
#include <numeric>
#include <utility>
#include <ctime>
#include <tuple>
#include <iostream>
#include <queue>
#include <cassert>
#include <limits>
#include <memory>
#include <future>
#include <type_traits>
#include <stdexcept>

/********************************************************/

std::tuple<size_t, size_t>* find_sub_with_sum
(unsigned int a[], size_t l, unsigned int s) {
	size_t i = 0;
	unsigned int cs = 0;

	for (size_t j = 0; j < l; j++) {
		cs += a[j];
		while (cs > s) cs -= a[i++];
		if (cs == s)
			return new std::tuple<size_t, size_t>(i, j);
	}
	return nullptr;
}

void find_sub_with_sum_driver()
{
	unsigned int a[] = { 0, 10, 5, 15, 20 };
	auto t = find_sub_with_sum(a, sizeof(a) / sizeof(unsigned int), 20);
}

/***********************************************************/

int max_sum(int* a, int n) {
	int max = 0, sum = 0;

	for (int i = 0; i < n; i++) {
		sum += a[i];
		sum = sum > 0 ? sum : 0;
		max = sum > max ? sum : max;
	}

	return max;
}

/***********************************************************/

int max_product(int a[], size_t n) {
	int mini = a[0], maxi = a[0], max = a[0];
	for (size_t i = 1; i < n; i++) {
		int maxp = a[i] * maxi;
		int minp = a[i] * mini;
		maxi = std::max(a[i], std::max(maxp, minp));
		mini = std::min(a[i], std::min(maxp, minp));
		max = std::max(maxi, max);
	}
	return max;
}

/******************************************************/

void counting_sort(int* a, size_t n, int k) {
	int* count = new int[k];
	memset(count, 0, sizeof(int) * k);

	for (int i = 0; i < n; i++) count[a[i] - 1]++;

	int sum = 0;
	for (int i = 0; i < k; i++) {
		int tmp = count[i];
		count[i] = sum;
		sum += tmp;
	}

	int* result = new int[n];
	for (int i = 0; i < n; i++) {
		result[count[a[i] - 1]] = a[i];
		count[a[i]]++;
	}

	for (int i = 0; i < n; i++) {
		printf("%d\n", result[i]);
	}
}

/******************************************************/

class Base1 {};
class Base2 : public Base1 {};
class Derived : public Base2 {
private:
	int a;

public:
	Derived() { a = 100; }

	void foo() {
		std::cout << a << std::endl;
	}
};

/******************************************************/

int median(const int a[], size_t n) {
	return (a[n / 2] + a[(n - 1) / 2]) / 2;
}

int median(const int a1[], const int a2[], size_t n) {
	if (n <= 0) return -1;
	if (n == 1) return (a1[0] + a2[0]) / 2;
	if (n == 2) return (std::max(a1[0], a2[0])
		+ std::min(a1[1], a2[1])) / 2;

	int m1 = median(a1, n);
	int m2 = median(a2, n);

	if (m1 > m2) std::swap(a1, a2);
	return median(a1 + (n - 1) / 2, a2, (n + 2) / 2);
}

/******************************************************/

bool can_win(int* a, size_t n, int cur, int sum) {
	if (cur >= sum) return false;

	for (int i = 0; i < n; i++) {
		if (!can_win(a, n, cur + a[i], sum)) {
			//printf("%d\n", a[i]);
			return true;
		}
	}
	return false;
}

/******************************************************/

template <typename T> class PriorityQueue {
public:
	PriorityQueue(size_t size) {
		size_ = size;
		start_ = 0;
		elements_ = 0;
		queue_ = new T[size];
	}

	~PriorityQueue() {
		delete queue_;
	}

	void enqueue(T item) {
		assert(elements_ < size_);

		size_t idx = (start_ + elements_) % size_;
		queue_[idx] = item;
		++elements_;
	}

	T dequeue() {
		assert(elements_ > 0);

		auto item = queue_[start_];
		start_ = (start_ + 1) % size_;
		--elements_;

		return item;
	}

private:
	size_t size_, start_, elements_;
	T* queue_;
};

struct node {
	node(int v) {
		this->v = v;
		this->next = NULL;
	}
	int v;
	node* next;
};

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
	else {
		n2->next = n1;
	}
}

void print_linked_list(node* root) {
	while (root != NULL) {
		std::cout << root->v << std::endl;
		root = root->next;
	}
}

/*************************************************************/

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

/*************************************************************/

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

node* swap(node* first) {
	if (first == NULL || first->next == NULL) return first;

	node* second = first->next;
	first->next = swap(second->next);
	second->next = first;

	return second;
}

class C {
public:
	C(const char* s) {
		name_ = s;
		std::cout << name_ << " constructed.\n";
	}

	~C() {
		std::cout << name_ << " destructed.\n";
	}

	void introduce_yourself() {
		std::cout << "Hi! My name is " << name_ << ".\n";
	}

	void stuff() {
		std::cout << "Hi! I have been allocated at address " << this << ".\n";
	}

private:
	const char* name_;
};

void test_auto() {
	std::auto_ptr<C> p(new C("C1"));
	p->introduce_yourself();
}

void test_auto2() {
	C* c = new C("C2");
	c->introduce_yourself();
}

/**************************************************************************/

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
	}
	else if (p / 2 == k + 1) {
		pnx->next = ny;
		auto tmp = ny->next;
		ny->next = nx;
		nx->next = tmp;
		// Nodes are at least one apart.
	}
	else {
		pnx->next = ny;
		auto tmp = ny->next;
		ny->next = nx->next;
		pny->next = nx;
		nx->next = tmp;
	}
	return head;
}

void string_matcher(const char *s, size_t ss, const char *p, size_t ps) {
	unsigned long long lp['z' - 'a' + 1] = { 0 };

	for (size_t i = 0; i < ps; i++) lp[p[i] - 'a'] |= 1ULL << i;

	unsigned long long col = s[0] == p[0];

	for (size_t i = 1; i < ss; i++) {
		if (col & 1ULL << (ps - 1))
			printf("Match @ %zu\n", i + 1 - ps);
		col = (col << 1 | 1) & lp[s[i] - 'a'];
	}

	if (col & 1ULL << (ps - 1))
		printf("Match @ %zu\n", ss - ps + 1);
}

void build_t(const char *w, size_t n) {
	int *t = new int[n] { -1, 0 };
	int p = 2, c = 0;

	while (p < n) {
		if (w[p - 1] == w[c]) {
			t[p++] = ++c;
			printf("%d", t[p - 1]);
		}
		else if (c > 0)
			c = t[c];
		else {
			t[p++] = 0;
			printf("%d", t[p - 1]);
		}
	}
	printf("\n");
}


/******************************************************************************/

struct Point {
	int x, y;
	double distance(const Point &p) {
		int dx = this->x - p.x, dy = this->y - p.y;
		return std::sqrt(dx * dx + dy * dy);
	}
};

typedef std::vector<Point> Points;

double closest_base(
	Points &points,
	double min = std::numeric_limits<double>::max()) {
	double cmin = min;

	for (auto i = points.begin(); i != points.end(); ++i)
		for (auto j = i + 1; j != points.end() && i->distance(*j) < min; ++j)
			cmin = std::min(cmin, i->distance(*j));

	return cmin;
}

double closest_sorted(Points &px, Points &py) {
	// Base case.
	if (px.size() <= 3) return closest_base(px);

	// Horizontally divide points into equal halves.
	Points::size_type mid = px.size() / 2;
	Points pxl = Points(px.begin(), px.begin() + mid);
	Points pxr = Points(px.begin() + mid + 1, px.end());
	Points pyl, pyr;
	for (Point p : py) {
		if (p.x <= py[mid].x) pyl.push_back(p);
		else pyr.push_back(p);
	}

	// Recurse to get left and right closest distance.
	double dl = closest_sorted(pxl, pyl);
	double dr = closest_sorted(pxr, pyr);
	double dlr = std::min(dl, dr);

	// Find smallest distance across halves.
	Points strip;
	for (Point p : py) {
		double dist = std::abs(p.x - px[mid].x);
		if (dist < dlr) strip.push_back(p);
	}
	double d = closest_base(strip, dlr);

	// Return overall minimum.
	d = std::min(d, dlr);
	return d;
}

double closest(const Points &points) {
	// Sort points by x and y coordinates.
	Points px = points, py = points;

	std::sort(px.begin(), px.end(), [](Point p1, Point p2) { return p1.x < p2.x; });
	std::sort(px.begin(), px.end(), [](Point p1, Point p2) { return p1.y < p2.y; });

	return closest_sorted(px, py);
}

/************************************************************/

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

		if (copy_list == nullptr)
			copy_list = tmp;
		else
			copy_list->next = tmp;

		n->next = n->next->next;
		n = n->next;
	}

	return copy_list;
}

/********************************************************/

void reverse_memory(char* mem, size_t len) {
	std::reverse(mem, mem + len);
}

/******************************************************************/

float locker_room_chances(int n, int x) {
	float p = 100;
	float nf = (float)n;
	
	for (int i = 1; i <= x; ++i)
		p *= 1 - 2 / (nf - i);

	return 100 - p;
}

/*******************************************************/
void print_reverse_test();

void main() {
	print_reverse_test();
}