#include<iostream>
template<typename T>
struct Node {
  T e; // Element
  Node *next;
  Node(T t, Node *n=nullptr)
  : e(t), next(n)
  {}
};

template<typename T>
struct singly_list {
  typedef Node<T> NodeT;
  typedef size_t size_type;
  typedef NodeT* iterator; // Forward iterator
  typedef const NodeT* const_iterator; // Forward iterator
  NodeT *head;
  NodeT *tail;
  size_type sz;
  singly_list() : head(nullptr), tail(head)
  {}
  singly_list(iterator b, iterator l, size_type s)
  : head(b), tail(l), sz(s)
  {}
  ~singly_list() {
    NodeT *h = head;
    while(h) {
      NodeT *temp = h->next;
      delete h;
      h = temp;
    }
    head = nullptr;
    tail = nullptr;
    sz = 0;
  }

  singly_list(const singly_list<T> &sl) {
    head = nullptr, tail = nullptr, sz = 0;
    const_iterator it = sl.begin();
    while (it != sl.end()) {
      push_back(it->e);
      ++it;
    }
    delete this;
  }

  singly_list<T>& operator=(const singly_list<T> &sl) {
    delete this;
    head = sl.head;
    tail = sl.tail;
    sz = sl.sz;
    sl.head = nullptr;
    sl.tail = nullptr;
    sl.sz = 0;
    return *this;
  }
  void push_back(T t) {
    //std::cout << "\nAdding: " << t;
    NodeT *n = new NodeT(t);
    if (!head) {
      //std::cout << "\nAdding head: " << t;
      head = n;
      head->next = nullptr;
      tail = head;
    } else {
      //std::cout << "\nAdding other: " << t;
      tail->next = n;
      tail = n;
    }
    ++sz;
  }

  void append(const singly_list<T> &sl) {
    iterator it = sl.begin();
    while (it != sl.end()) {
      push_back(it->e);
      ++it;
    }
  }

  // When head is already there this can be used.
  // This will avoid unnecessary check for nullness of head.
  void push_back_fast(T t) {
    NodeT *n = new NodeT(t);
    tail->next = n;
    tail = n;
    ++sz;
  }

  size_type size() const {
    return sz;
  }

  iterator begin() { return head; }
  iterator end() { return nullptr; }
  const_iterator begin() const { return head; }
  const_iterator end() const { return nullptr; }


  iterator advance(iterator it, size_type i) {
    while (i--) it = it->next;
    return it;
  }

  // Splits the list into two and returns the second half.
  singly_list<T> split(iterator it) {
    iterator b = begin();
    size_type s = 0;
    if (b == it) {
      singly_list<T> sl(*this);
      return sl;
    }
    while (b->next != it) {
      ++s;
      b = b->next;
    }
    iterator temp = b->next;
    b->next = nullptr;
    singly_list<T> sl(temp, tail, sz-s);
    tail = b;
    sz = s;
    return sl;
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const singly_list<T>& l) {
  typedef Node<T> Node;
  Node *h = l.head;

  //std::cout << "\nNodes: ";
  while(h) {
    os << " " << h->e;
    h = h->next;
  }
  return os;
}

