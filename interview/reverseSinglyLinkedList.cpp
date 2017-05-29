#include "singly_list.h"
#include<iostream>

// Reverse a singly linked list
// Node { Node *next; T Item }
// [Head] -> [] -> [] -> [] ->null
template <typename T>
void reverse(singly_list<T>& l) {
  typedef Node<T> Node;
  Node *prev = nullptr;
  Node *head = l.head;
  while (head) {
    Node *temp = head->next;
    head->next = prev;
    prev = head;
    head = temp;
  }
  l.tail = l.head;
  l.head = prev;
}

template <typename T>
Node<T> *get_middle(singly_list<T>& l) {
  typedef Node<T> Node;
  Node *slow = l.head;
  Node *fast = l.head;
  while (fast) {
    fast = fast->next;
    if (fast) {
      slow = slow->next;
      fast = fast->next;
    }
  }
  return slow;
}

int main() {
  singly_list<int> l;
  for (int i = 0; i < 11; i++)
    l.push_back(i);

  std::cout << l;
  //std::cout << "\nMiddle: " << get_middle(l)->e;
  reverse(l);
  std::cout << l;
  //std::cout << "\nMiddle: " << get_middle(l)->e;
  auto sl = l.split(l.begin());
  std::cout << "\nAfter split: " << l << " and " << sl;
return 0;
}
