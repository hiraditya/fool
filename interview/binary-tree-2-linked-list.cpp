#include<iostream>
struct Node {
  Node *L;
  Node *R;
};

Node *Prev = nullptr;
Node *Root = nullptr;

void binary_tree_linked_list(Node *r) {
  if (!r) {
    return;
  }

  binary_tree_linked_list(r->L);

  if (Prev) {
    r->L = Prev;
    Prev->R = r;
  }
  else
    Root = r;

  Prev = r;
  binary_tree_linked_list(r->R);
}
