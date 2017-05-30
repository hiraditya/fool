#include "singly_list.h"
#include<iostream>

// Reverse a singly linked list
// Node { Node *next; T Item }


//        [Head] -> [N1] -> [N2] -> [N3] -> null
// prev     curr
//                 temp

// null <- [Head] <- [N1] <- [N2] <- [N3]

template <typename T>
void reverse(singly_list<T>& l) {
  typedef Node<T> NodeT;
  NodeT *prev = nullptr;
  NodeT *curr = l.head;

  while (curr) {
    NodeT *temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  l.tail = l.head;
  l.head = prev;
}

int main() {
  singly_list<int> l;
  for (int i = 0; i < 11; i++)
    l.push_back(i);

  std::cout << "\nOriginal: " << l;
  reverse(l);
  std::cout << "\nReversed: " << l;
  return 0;
}
