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
    return general_utilities::abs(TreeMaxDepth(h) - TreeMinDepth(h)) <=1;
  }


  template<typename TreeHead>
  size_t TreeHeight(const TreeHead * h) const
  {
    if(!h)
      return 0;
    return TreeMaxDepth(h) -1;
  }


  template<typename TreeHead>
  size_t TreeMaxDepth(const TreeHead * h) const
  {
    if(!h)
     return 0;
    return 1 + std::max(TreeDepth(h->left), TreeDepth(h->right));
  }

  template<typename TreeHead>
  size_t TreeMinDepth(const TreeHead * h) const
  {
    if(!h)
     return 0;
    return 1 + std::min(TreeDepth(h->left), TreeDepth(h->right));
  }


} //namespace graph
#endif //GRAPH_BINARYTREE_HPP
