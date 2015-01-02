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

void permute(char* s, size_t l) {
	int* p = new int[l];
	std::iota(p, p + l, 0);
	for (size_t i = 0; i < l; /*printf("%s\n", s)*/) {
		std::swap(s[i], s[i % 2 * --p[i]]);
		for (i = 1; p[i] == 0; i++) p[i] = (int)i;
	}
}

void backtrack(char *str, int p) {
	size_t len = strlen(str);

	if (p == len) {
		//printf("%s\n", str);
		return;
	}

	for (size_t i = p; i < len; i++) {
		std::swap(str[p], str[i]);
		permute(str, p + 1);
		std::swap(str[p], str[i]);
	}
}

void heap_permute(char* s, size_t n) {
	if (n == 1)	{
		printf("%s\n", s);
		return;
	}

	for (int i = 0; i < n; i++)	{
		heap_permute(s, n - 1);
		std::swap(s[n % 2 ? 0 : i], s[n - 1]);
	}
}

void permute_driver()
{
	//char s[] = "abcdefghijkl";
	//char s[] = "abc";
	char s[] = "abcdefghijk";

	clock_t begin = clock();

	heap_permute(s, strlen(s));
	//permute(s, strlen(s));
	//permute(s, 0);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", elapsed_secs);
}

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
void quick_perm(char *s, int l)
{
	int* p = new int[l];
	for (int i = 0; i < l; i++) p[i] = i;
	for (int i = 0; i < l; printf("%s\n", s)) {
		std::swap(s[i], s[i % 2 * --p[i]]);
		for (i = 1; p[i] == 0; i++) p[i] = i;
	}
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

int max_product1(int* a, int n) {
	int p1 = 1, p2 = 1, max = 0;
	bool b = false;

	for (int i = 0; i < n; i++) {
		p1 *= a[i];
		p2 *= b ? 1 : a[i];

		max = std::max(max, std::max(p1, p2));

		if (a[i] == 0) {
			p1 = p2 = 1;
			b = false;
		}
		if (a[i] < 0) b = true;
	}

	return max;
}

int max_product2(int A[], int n) {
	if (n == 0) return 0;

	int maxi = 1, mini = 1;
	int out = INT_MIN;

	for (int i = 0; i < n; i++) {
		int oldmaxi = std::max(maxi, 1);
		if (A[i] > 0) {
			maxi = oldmaxi*A[i];
			mini *= A[i];
		}
		else {
			maxi = mini*A[i];
			mini = oldmaxi*A[i];
		}
		out = std::max(out, maxi);
	}

	return out;
}

int max_product3(int a[], size_t n) {
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

int median2(int ar1[], int ar2[], int left, int right, int n)
{
	if (left > right) return median2(ar2, ar1, 0, n - 1, n);

	int i = (left + right) / 2;
	int j = n - i - 1;

	if (ar1[i] > ar2[j] && (j == n - 1 || ar1[i] <= ar2[j + 1]))
		if (i == 0 || ar2[j] > ar1[i - 1]) return (ar1[i] + ar2[j]) / 2;
		else                               return (ar1[i] + ar1[i - 1]) / 2;
	else if (ar1[i] > ar2[j] && j != n - 1 && ar1[i] > ar2[j + 1])
		return median2(ar1, ar2, left, i - 1, n);
	else
		return median2(ar1, ar2, i + 1, right, n);
}

/******************************************************/

void print_primes(int n) {
	bool *is_prime = new bool[n + 1];
	for (int i = 2; i <= n; i++) is_prime[i] = true;

	for (int p = 2; p <= n; p++) {
		if (!is_prime[p]) continue;
		printf("%d\n", p);
		for (int i = p * p; i <= n; i += p)
			is_prime[i] = false;
	}
	delete is_prime;
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

void permute22(char* s, size_t n) {
	std::auto_ptr<int> ap(new int[n]);
	int* p = ap.get();

	for (size_t i = 0; i < n; ++i) p[n] = (int)i;
	for (size_t i = 0; i < n; printf("%s\n", s)) {
		std::swap(s[i], s[--p[i]]);
		for (i = 1; p[i] == 0; ++i) p[i] = (int)i;
	}
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

std::auto_ptr<ptrdiff_t> calculate_backtrack(const wchar_t* w, size_t wl) {
	ptrdiff_t *t = new ptrdiff_t[std::max(wl, (size_t)2)] {-1, 0};
	auto tp = std::auto_ptr<ptrdiff_t>(t);
	size_t p = 0, c = 2;
	while (c < wl) {
		if (w[c - 1] == w[p]) t[c++] = ++p;
		else if (p > 0) p = t[p];
		else t[c++] = 0;
	}
	return tp;
}

size_t kmp(const wchar_t* s, size_t sl, const wchar_t* w, size_t wl) {
	std::auto_ptr<ptrdiff_t> tp = calculate_backtrack(w, wl);
	ptrdiff_t *t = tp.get();

	size_t m = 0, i = 0;
	while (m + i < sl) {
		if (s[m + i] == w[i]) {
			if (i == wl - 1) return m;
			++i;
		}
		else {
			m += i - t[i];
			i = std::max((ptrdiff_t)0, t[i]);
		}
	}
	return wl;
}

void print_primes2(int N) {
	bool *isPrime = new bool[N + 1];
	for (int i = 0; i < N + 1; ++i) isPrime[i] = true;
	for (int i = 2; i < N + 1; ++i) {
		if (!isPrime[i]) continue;
		printf("%d is prime.\n", i);
		for (int m = i * i; m < N + 1; m += i) isPrime[m] = false;
	}
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

/*****************************************************************/

// s: xxxxabcabcabdyyyyyy 
// w: abcabd
/*
std::cout << kmp2(L"xxxxabcabcabdyyyyyy", L"abcabd") << std::endl;
std::cout << kmp2(L"日本日本日本語日本語日本人日本日本日本日本日本", L"日本語日本人") << std::endl;
*/

typedef std::unique_ptr<ptrdiff_t[]> offset_table;

offset_table get_backtrack_table(const std::wstring &w) {
	size_t ws = std::max((size_t)2, w.size());
	auto t = offset_table(new ptrdiff_t[ws] { -1, 0 });
	size_t c = 2, p = 0;

	while (c < w.size()) {
		if (w[c - 1] == w[p]) t[c++] = ++p;
		else if (p > 0) p = t[p];
		else t[c++] = 0;
	}

	return t;
}

size_t kmp2(const std::wstring s, const std::wstring w) {
	offset_table t = get_backtrack_table(w);
	size_t m = 0, i = 0;

	while (m + i < s.size()) {
		while (s[m + i] == w[i]) i++;
		if (i == w.size()) return m;
		m += i - t[i];
		i = std::max((ptrdiff_t)0, t[i]);
	}

	return s.size();
}

/************************************************************/

size_t kmp3(const std::wstring text, const std::wstring pattern) {
	std::vector<size_t> offset(pattern.size(), 0);
	size_t p = 0, t;

	for (t = 1; t < pattern.size(); t++) {
		offset[t] = p;
		p = pattern[t] == pattern[p] ? p + 1 : offset[p];
	}

	for (t = 0; t < text.size(); ) {
		while (text[t] == pattern[p]) { t++; p++; }
		if (p == pattern.size()) return t - p;
		p = offset[p];
		if (text[t] != pattern[p]) t++;
	}

	return text.size();
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

namespace {
	class A {};
	class B : public A {};

	template<class T, class B> struct Derived_from {
		static void constraints(T* p) { B* pb = p; }
		Derived_from() { void(*p)(T*) = constraints; }
	};

	template<class T> class Container : Derived_from < T, A > {
		// ...
	};
}

/********************************************************/

void print_primes3(int n) {
	auto is_prime = std::unique_ptr<bool[]>(new bool[n + 1]);
	for (int i = 2; i <= n; ++i) is_prime[i] = true;
	for (int i = 2; i <= n; ++i) {
		if (!is_prime[i]) continue;
		printf("%d is a prime number.\n", i);
		for (int m = i * i; m <= n; m += i) is_prime[m] = false;
	}
}

/********************************************************/

void print_primes4(const int n) {
	std::vector<bool> is_prime(n + 1, true);
	for (int i = 2; i <= n; ++i) {
		if (!is_prime[i]) continue;
		printf("%d is a prime number.\n", i);
		for (int m = i * i; m <= n; m += i) is_prime[m] = false;
	}
}

/********************************************************/

template <typename T> using IsArithmetic =
typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

template<typename T, typename = IsArithmetic<T>>
T get_median(T a[], std::size_t n) {
	return (a[(n - 1) / 2] + a[(n + 1) / 2]) / 2;
}

template<typename T, typename = IsArithmetic<T>>
T get_median_slow(T a1[], T a2[], std::size_t n) {
	std::vector<T> m;
	m.insert(m.end(), a1, a1 + n);
	m.insert(m.end(), a2, a2 + n);
	std::sort(m.begin(), m.end());
	return get_median(&m[0], m.size());
}

template<typename T, typename = IsArithmetic<T>>
T get_median(T a1[], T a2[], std::size_t n) {
	if (n <= 2) return get_median_slow(a1, a2, n);

	auto thread = [n](T a[]) { return get_median(a, n); };
	T m1 = std::async(std::launch::async, thread, a1).get();
	T m2 = std::async(std::launch::async, thread, a2).get();

	if (m1 > m2) std::swap(a1, a2);

	return get_median(a1 + (n - 1) / 2, a2, (n + 2) / 2);
}

/***************************************************/

template <int N>
struct Factorial {
	static const int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial < 0 > {
	static const int value = 1;
};

/*************************************************************/

template <typename T> T max(T t1, T t2) {
	return std::max(t1, t2);
}

template <typename T> T max(T* t1, T* t2) {
	return std::max(*t1, *t2);
}

/*************************************************************/

template <bool> struct bar {};
template <> struct bar < true > { typedef void t; };

template <int T, typename = bar<T == 10>::t> struct foo { static const int result = 1; };

/*************************************************************/

template<typename T, void(T::*)(std::string) = &T::quack> struct IsDuck {};
template<typename T, typename = IsDuck<T>> void quack_duck(T t) { t.quack("Quack!"); }
template<typename T> void f2(T t) { t.quack("f2"); }

template<> void f2<int>(int) { };

//constexpr int f3() { return 1; }

class Duck {
public:
	void quack(std::string s) {
		std::cout << "This duck says: " << s << std::endl;
	}
};

class Mime {
public:
	void quack(std::string s) {
		std::cout << "I'm not really a duck!" << std::endl;
	}
};

/******************************************************************/

void perm(std::string s) {
	auto p = std::unique_ptr<size_t[]>(new size_t[s.size()]);
	for (int i = 0; i < s.size(); ++i) p[i] = i;
	for (int i = 0; i < s.size(); printf("%s\n", s)) {
		std::swap(s[i], s[(i % 2) * --p[i]]);
		for (int i = 1; p[i] == 0; ++i) p[i] = i;
	}
}

void perm2(std::string &s) {
	std::vector<size_t> p(s.size());
	for (int i = 0; i < p.size(); ++i) p[i] = i;
	for (int i = 0; i < p.size(); printf("%s\n", s)) {
		std::swap(s[i], s[(i % 2) * --p[i]]);
		for (int i = 1; p[i] == 0; ++i) p[i] = i;
	}
}

/******************************************************************/

float sqrt2(const float x) {
	union {
		float x;
		int i;
	} u;
	u.x = x;
	u.i = 0x5f3759df - (u.i >> 1);  // gives initial guess y0
	return x*u.x*(1.5f - 0.5f*x*u.x*u.x); // Newton step, repeating increases accuracy 
}


template <typename T> struct IEEE {
	static const long long bias = std::numeric_limits<T>::max_exponent - 1;
	static const auto mantissa_bits = std::numeric_limits<T>::digits - 1;
	static const auto sqrt_mask = bias << (mantissa_bits - 1);
};

double my_sqrt(double d) {
	auto i = (unsigned long long*)&d;
	*i = (*i >> 1) + (1023ll << 51);
	return d;
}

float my_sqrt(float f) {
	auto i = (unsigned long*)&f;
	*i = (*i >> 1) + (127ll << 22);
	return f;
}


double sqrt1(const float x, const double precision) {
	union {
		unsigned long long i;
		double d;
		float f;
	} u;

	// u.i = (u.i >> 1) + (127 << 22)
	u.f = x;
	u.i = (u.i >> 1) + IEEE<float>::sqrt_mask;
	float sqrt_float = u.f;

	u.d = (double)x;
	u.i = (u.i >> 1) + IEEE<double>::sqrt_mask;
	double sqrt_double = u.d;

	while ((u.d * u.d) - x > precision) {
		u.d = (u.d + x / u.d) / 2;
	}

	return u.d;
}

#include <Windows.h>

void reverse_memory(char* mem, size_t len) {
	std::reverse(mem, mem + len);
}

float locker_room_chances(int n, int x) {
	float p = 100;
	float nf = (float)n;
	
	for (int i = 1; i <= x; ++i)
		p *= 1 - 2 / (nf - i);

	return 100 - p;
}

void main() {
	auto r1 = kmp3(L"ABCABCABDABCAB", L"ABCABD");
	auto r2 = kmp3(L"ABABABCABABABCABABABC", L"ABABAC");
	auto r3 = kmp3(L"bacbababaabcbab", L"abababca");
}