#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */
//#include "general_algorithm.hpp"

#include<algorithm>
#include<queue>
#include<stack>
#include<algorithm>

namespace graph{

  //Vertex is the starting node of the tree
  //Visitor is the function that takes node pointer
  //In breadth first search first the root node is visited
  //then all the adjacent nodes are visited. This continues
  //recursively until all the nodes are visited
  //
  //The Visitor takes pointer to the vertex to be visited
  //Each Tree vertex has adj_list of pointer to neighboring vertices.
  template<typename Vertex, typename Visitor>
  inline void BreadthFirstSearch(Vertex* h, Visitor visit)
  {
    std::queue<Vertex*> to_be_visited;
    if(!h)
      return;
    to_be_visited.push(h);
    
    while(to_be_visited.size()){
      
      auto adj_nodes = to_be_visited.front()->GetAdjList();
      
      std::for_each(adj_nodes.begin(), adj_nodes.end(),
          [&to_be_visited](Vertex* v){
            to_be_visited.push(v);
          });

      visit(to_be_visited.front());
      
      to_be_visited.pop();
    }
  }
 
  //Vertex is the starting node of the tree
  //Visitor is the function that takes node pointer
  //In depth first search first the root node is visited
  //then the subtree of each adjacent node is visited. 
  //This continues recursively until all the nodes are visited
  //
  //The Visitor takes pointer to the vertex to be visited
  //Each Tree vertex has adj_list of pointer to neighboring vertices.
  template<typename Vertex, typename Visitor>
  inline void DepthFirstSearch(Vertex* h, Visitor visit)
  {
    std::stack<Vertex*> to_be_visited;
    if(!h)
      return;
    to_be_visited.push(h);
    
    while(to_be_visited.size()){

      //make a copy of the node pointer to be visited
      auto top = to_be_visited.top();

      visit(top);
      
      to_be_visited.pop();
      
      //the order of visiting is opposite to the order 
      //in which nodes are iterated
      auto adj_nodes = top->GetAdjList();

      std::for_each(adj_nodes.begin(), adj_nodes.end(),
          [&to_be_visited](Vertex* v){
            to_be_visited.push(v);
          });
    }
  }
 

} //namespace graph


#endif //GRAPH_ALGORITHMS_HPP

