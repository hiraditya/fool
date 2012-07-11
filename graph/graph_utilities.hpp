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
#include "general_algorithm.hpp"

#include<algorithm>

namespace graph{
//enable_if the tree is binary
  template<typename TreeHead>
  inline bool TestBlalanced(TreeHead* h)
  {
    if(!h)
      return true;
    return general_utilities::abs(TreeMaxDepth(h) - TreeMinDepth(h)) <=1;
  }


  template<typename TreeHead>
  inline size_t TreeHeight(const TreeHead * h) 
  {
    if(!h)
      return 0;
    return TreeMaxDepth(h) -1;
  }


  template<typename TreeHead>
  inline size_t TreeMaxDepth(const TreeHead * h) 
  {
    if(!h)
     return 0;
    return 1 + std::max(TreeDepth(h->left), TreeDepth(h->right));
  }

  template<typename TreeHead>
  inline size_t TreeMinDepth(const TreeHead * h) 
  {
    if(!h)
     return 0;
    return 1 + std::min(TreeDepth(h->left), TreeDepth(h->right));
  }


} //namespace graph
#endif //GRAPH_BINARYTREE_HPP
