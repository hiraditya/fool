// Visit post order using recursion
// https://leetcode.com/problems/binary-tree-postorder-traversal/discuss/45648/three-ways-of-iterative-postorder-traversing-easy-explanation
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
  Node *l = nullptr; // last visited node.
  while (!s.empty() || n != nullptr) {
    if (n != nullptr) {
      s.push(n);
      n = n->L;
    } else {
      Node *t = s.top();
      // If the last visited node was the right node
      // or if there is no right node then visit root (top)
      if (l == t->R || t->R == nullptr) {
        l = s.pop();
        n = nullptr;
        visit(l);
      } else // Visit right node first
        n = t->R;
    }
  }
}
