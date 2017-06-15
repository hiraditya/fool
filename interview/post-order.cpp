// Visit post order using recursion
void post_order(Node *n) {
  if(!n)
    return;
  post_order(n->L);
  post_order(n->R);
  visit(n);
}

void post_order(Node *n) {
  if (!n)
    return;
  stack s;
  Node *l = nullptr;
  while (!s.empty() || n != nullptr) {
    if (n != nullptr) {
      s.push(n);
      n = n->L;
    } else {
      Node *t = s.top();
      // If the last visited node was the right node
      // of if there is no right node then visit root (top)
      if (l = t->R || t->R == nullptr) {
        l = s.pop();
        visit(l);
      } else // Visit right node first
        n = t->R;
    }
  }
}
