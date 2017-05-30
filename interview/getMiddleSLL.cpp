#include "singly_list.h"
#include<iostream>

// [Head] -> [] -> [] -> [] ->null
// Find the middle of singly linked list
template <typename T>
Node<T> *get_middle(singly_list<T>& l) {
  typedef Node<T> NodeT;
  NodeT *slow = l.head;
  NodeT *fast = l.head;
  while (fast) {
    fast = fast->next;
    if (fast) {
      fast = fast->next;
      if (fast)
        slow = slow->next;
    }
  }
  return slow;
}

int main() {
  singly_list<int> l;
  for (int i = 0; i < 11; i++)
    l.push_back(i);

  std::cout << "\nOriginal: " << l;
  std::cout << "\nMiddle Node: " << get_middle(l)->e;
  std::cout << "\n";
  return 0;
}
