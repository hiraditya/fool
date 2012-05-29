#ifndef CONTAINER_QUEUE
#define CONTAINER_QUEUE

/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */


#include<vector>
#include<iostream>
#include<stdexcept>
#include<iterator>

#include<cassert>

namespace containers{
//-----------------------------------------------------------------------------
//                     GENERIC QUEUE IMPLEMENTATION                          //
//-----------------------------------------------------------------------------

  template<typename element_type, typename container_type = std::vector<element_type> >
  class Queue{
    public:
      
      //typedef typename container_type container_type;

      void push(element_type const& t);
      element_type pop();
      element_type front() const;
      bool empty() const;

      typename container_type::const_iterator begin() const 
      { return elems.begin(); }
      
      typename container_type::const_iterator end() const
      { return elems.end(); }

      size_t size() const
      { return elems.size(); }
      
    private:
      container_type elems;
      
  };
  
  /// puts the element at the tail of the queue
  template<typename element_type, typename container_type>
  void Queue<element_type, container_type>::push(element_type const& t)
  {
    elems.push_back(t);
  }

  /// @brief pops the last element inserted out of the queue
  /// returns a copy of the last element deleted
  /// throws std::out_of_range exception
  template<typename element_type, typename container_type>
  element_type Queue<element_type, container_type>::pop()
  {
    if(elems.empty())
      throw std::out_of_range("Queue<>::pop: empty queue");

    element_type t = *elems.begin();
    elems.erase(elems.begin());
    return t;
  }
  
  /// @brief returns a copy of the last element of the queue
  /// throws std::out_of_range exception
  template<typename element_type, typename container_type>
  element_type Queue<element_type, container_type>::front() const
  {
    if(elems.empty())
      throw std::out_of_range("Queue<>::front: empty queue");
    
    return *elems.begin();//copy of the first element
  }

  template<typename element_type, typename container_type>
  bool Queue<element_type, container_type>::empty() const
  {
    return elems.empty();
  }

  
  template<typename element_type, typename container_type>
  std::ostream& operator<<(std::ostream& os, Queue<element_type, container_type> const& s)
  {
    /*
    for(auto i = s.begin(); i!= s.end(); ++i){
        os<<*i;
        os<<"\n";
    }*/

    std::copy(s.begin(),s.end(), std::ostream_iterator<element_type>(os, "\n"));
    return os;
  }
  
  
//-----------------------------------------------------------------------------
//                      QUEUE SPECIALIZATIONS                                //
//-----------------------------------------------------------------------------

  /// @brief useful when the size of queue is approximately known
  /// so that there is no overhead of resource management
  template<typename element_type, size_t container_size>
  class SmallQueue{
    public:
      
      SmallQueue();

      void push(element_type const& t);
      element_type pop();
      element_type front() const;
      bool empty() const;

      //returns the number of elements in the queue
      size_t size() const
      { return num_elems; }

      //small queue cannot support begin and end because
      //it is implemented as a circular array.
      //hopefully I would provide iterators with operators 
      //in near future which would make things easier.

      //However, there is operator[] to access elements of the queue
      //the first element is accessed as q[0], the second q[1] etc.
      //this function has been added just to facilitate
      //access elements without modifying them
      element_type const& operator[](size_t i) const;
      
      //implemented but uncommented because this function 
      //does not reflect the semantics of a queue
      //element_type& operator[](size_t i);
     
    private:
      
      //one extra element for book keeping
      //so that i1 and i2 satisfy the requirements
      //also helpful when the queue has zero elements
      element_type elems[container_size+1];
      
      //to keep the count of elements available for use
      size_t num_elems;
      //index of the first element
      size_t i1;
      //index of the last element
      size_t i2;
  };



  template<typename element_type, size_t container_size>
  SmallQueue<element_type, container_size>::SmallQueue()
  :num_elems(0),i1(0),i2(0)
  {  }

  template<typename element_type, size_t container_size>
  void SmallQueue<element_type, container_size>::push(element_type const& t)
  {
    if(num_elems == container_size)
      throw std::out_of_range("Queue<>::push, queue full");

    if(i1)
      assert(i1 != i2);
    
    elems[i2] = t;

    i2 = (i2 + 1)%container_size;
    
    ++num_elems;
  }

  template<typename element_type, size_t container_size>
  element_type SmallQueue<element_type, container_size>::pop()
  {
    if(num_elems <= 0)
      throw std::out_of_range("Queue<>::pop: empty queue");
/*    
    if(i1)
      assert(i1 != i2);
*/    
    element_type e = elems[i1];

    i1 = (i1 + 1)%container_size;

    --num_elems;
    return e;
  }

  template<typename element_type, size_t container_size>
  element_type SmallQueue<element_type, container_size>::front() const
  {
    if(num_elems <= 0)
      throw std::out_of_range("Queue<>::top: empty queue");

    return elems[i1];
  }

  template<typename element_type, size_t container_size>
  bool SmallQueue<element_type, container_size>::empty() const
  {
    return num_elems == 0;
  }

/*
  template<typename element_type, size_t container_size>
  element_type& 
  SmallQueue<element_type, container_size>::operator[](size_t i)
  { 
    if(i > num_elems || i < 0)
      throw std::out_of_range("Queue<> index");

    return elems[(i1+i)%container_size]; 
  }
*/

  template<typename element_type, size_t container_size>
  element_type const& 
  SmallQueue<element_type, container_size>::operator[](size_t i) const
  { 
    if(i > num_elems || i < 0)
      throw std::out_of_range("Queue<> index");

    return elems[(i1+i)%container_size]; 
  }


  template<typename element_type, size_t container_size>
  std::ostream& operator<<(std::ostream& os, SmallQueue<element_type, container_size> const& s)
  {
    for(size_t i = 0; i != s.size(); ++i){
        os<<s[i];
        os<<"\n";
    }
    return os;
  }
}

#endif // CONTAINER_QUEUE
