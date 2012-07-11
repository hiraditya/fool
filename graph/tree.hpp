#ifndef GRAPH_TREE_HPP
#define GRAPH_TREE_HPP

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

  template<typename Vertex, typename Edge>
  class Tree{
    public:
      
      typedef edge_container std::list;
      typedef vertex_container std::list;

      Tree()
      { }

      Tree(const Tree& t)
      { 
        vertices = t.GetVertices();
        edges = t.GetEdges();
      }

      Tree(const vertex_container& v, const edge_container& e)
      {
        vertices = v;
        edges = e;
      }

      ~Tree()
      {}

      Tree& operator=(const Tree& t)
      {
        //stolen from Bjarne Stroustrup's exceptions safety paper
        Tree temp(t);
        std::swap(*this, temp);
        return *this;
      }

      void clear()
      {
        vertices.clear();
        edges.clear();
      }

      edge_iterator begin()
      {
        return edges.begin();
      }

      edge_iterator end()
      {
        return edges.end();
      }

      vertex_iterator begin()
      {
        return vertices.begin();
      }

      vertex_iterator end()
      {
        return vertices.end();
      }

/**
 *  create edge_list/vertex_list only when explicitly asked in the program
 *  set the bool flag (edge_list create) if created is true
 *
 */
      friend class edge_iterator;
      friend class vertex_iterator;

    private:
      vertex_container<Vertex> vertices;
      
      edge_container<Edge> edges;
  };




}
#endif // GRAPH_TREE_HPP
