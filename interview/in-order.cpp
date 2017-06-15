// Recursive Left->Root->Right
void in_order(Node *n) {
  if (!n)
    return;
  in_order(n->L);
  visit(n);
  in_order(n->R);
}

void in_order(Node *n) {
  stack s;
  while (!s.empty() || n != nullptr) {
    if (n != nullptr) {
      s.push(n);
      n = n->L;
    } else {
      n = s.pop();
      visit(n);
      n = n->R;
    }
  }
}
