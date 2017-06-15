// Recursive Root -> Left -> Right
void pre_order(Node *n) {
  if (!n)
    return;
  visit(n);
  pre_order(n->L);
  pre_order(n->R);
}

void pre_order(Node *n) {
  stack s;
  s.push(n);
  while (!s.empty()) {
    n = s.pop();
    visit(n);
    if (n->R)
      s.push(n->R);
    if (n->L)
      s.push(n->L);
  }
}
