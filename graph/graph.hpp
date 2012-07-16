#ifndef GRAPH_HPP
#define GRAPH_HPP

/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */
#include<algorithm>

namespace graph{

  //@class Vertex
  //member of the Tree data structure
  template<typename VertexDataType, typename VertexContainerType>
  class Vertex{
    public:
    
      Vertex(VertexDataType vertex)
        :v(vertex)
      {}
      
      //@warning does not check whether the element is already there or not
      //so if inserted more than once, it more than one connections will be there
      void Connect(VertexDataType vertex)
      { adj_list.push(vertex); }

      //@warning does not check whether the element is there or not.
      //so make sure the element is there before you delete it
      void Disconnect(VertexDataType vertex)
      { adj_list.erase(std::find(adj_list.begin(), adj_list.end(), vertex)); }

      VertexContainerType& GetAdjList()
      { return adj_list; }

//      const VertexContainerType& GetAdjList()
//      { return adj_list; }
    
    private:
      VertexDataType v;
      VertexContainerType adj_list;
  
  };

  //@class Edge
  //member of the Tree data structure
  template<typename EdgeDataType, typename EdgeContainerType>
  class Edge{
    public:
     
      Edge(EdgeDataType edge)
        :e(edge)
      {}

      EdgeContainerType& GetEdges()
      { return edge_list; }

//      const EdgeContainerType& GetEdges()
//      { return edge_list; }
    
    private:
      EdgeDataType e;
      EdgeContainerType edge_list;
  };




  //@brief The tree data structure
  template<typename VertexType, typename EdgeType, 
    typename VertexContainerType, typename EdgeContainerType>
  class Tree
  {
    public:

      typedef typename VertexContainerType::iterator VIterator;
      typedef typename EdgeContainerType::iterator EIterator;

      //default constructor
      Tree()
      {}
      
      //copy constructor
      Tree(const Tree& t)
      { 
        e_list = t.GetEdges(); 
        v_list = t.GetVertices();
      }
      
      //destructor
      ~Tree();
      
      Tree& operator=(const Tree& t)
      {
        //self assignment
        if(*this == t)
          return *this;
        clear();
        e_list = t.GetEdges();
        v_list = t.GetVertices();
        return *this;
      }
      
      void clear()
      {
        e_list.clear();
        v_list.clear();
      }

      VIterator vbegin()
      { return v_list.begin(); }

      VIterator vend()
      { return v_list.end(); }  

      EIterator ebegin()
      { return e_list.begin(); }

      EIterator eend()
      { return e_list.end(); }
      
      VertexContainerType& GetVertices()
      { return v_list; }

      EdgeContainerType& GetEdges()
      { return e_list; }

      friend class Vertex<VertexType, VertexContainerType>;
      friend class Edge<EdgeType, EdgeContainerType>;
    
    private:
      VertexContainerType v_list;
      EdgeContainerType e_list;


  };

}

#endif //GRAPH_HPP
