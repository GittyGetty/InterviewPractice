template <typename T>
struct Node {
    Node(T v) {
        this->v = v;
    }
    T v = T();
    Node<T>* next = NULL;
};