#ifndef GRAPH_BINARYTREE_HPP
#define GRAPH_BINARYTREE_HPP

/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */
#include "algorithm"

#include<algorithm>

namespace graph{
 
  template<typename TreeHead>
  bool TestBlalanced(TreeHead* h)
  {
    if(!h)
      return true;
    return general_utilities::abs(TreeHeight(h->left) - TreeHeight(h->right)) <=1;
  }


  template<typename TreeHead>
  size_t TreeHeight(const TreeHead * h) const
  {
    if(!h)
      return 0;
    return TreeDepth(h) -1;
  }


  template<typename TreeHead>
  size_t TreeDepth(const TreeHead * h) const
  {
    if(!h)
     return 0;
    return std::max(TreeDepth(h->left) +1, TreeDepth(h->right) +1);
  }


} //namespace graph
#endif //GRAPH_BINARYTREE_HPP
