. Serialize a binary tree to string, and deserialize the string back to the tree

class TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v):
  val(v){}
};
      2
  1       3
4   #   5   #


TreeNode* GetTreeNode(int val) {
  TreeNode *t = new TreeNode(val);
    return t;
}

string Serialize(const TreeNode* root) {
  std::queue<TreeNode*> q;
    q.push(root);
    std::string tree;
    while (!q.empty()) {
    auto n = q.front();
        q.deque();
        if (n) {
          tree += std::to_string(n);
            tree += ','
        }
        else
          tree += "#,";
        q.push(n->left);
        q.push(n->right);
    }
    return tree;
}
TreeNode Deserialize(const string& data) {
  std::vector<TreeNode*> nodes;
    auto dummy_node = nullptr; // GetTreeNode(-1);
    auto bit = data.begin();
    auto it = data.find(',');
    while (it != data.end()) {
      std::string_view nstr(bit, it);
        if (nstr != '#') {
          int num = atoi(nstr);
            auto node = GetTreeNode(num);
            nodes.push_back(node);
        } else {
          nodes.push_back(dummy_node);
        }
        bit = ++it;
        it = data.find(',', bit);
    }
    // Assing the pointers.
    for (int i = 0; i != nodes.size(); ++i) {
      auto N = nodes[i];
        if (N != dummy_node) {
          if (nodes[2*i+1] != dummy_node)
            N->left = nodes[2*i+1];
            else
              N->left = nullptr;

          if (nodes[2*i+2] != dummy_node)
            N->right = nodes[2*i+1];
            else
              N->right = nullptr;
        }
    }
    return *&nodes.begin();
}
