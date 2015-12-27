#ifndef CONTAINER_STACK
#define CONTAINER_STACK

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

namespace containers{
//-----------------------------------------------------------------------------
//                     GENERIC STACK IMPLEMENTATION                          //
//-----------------------------------------------------------------------------

  template<typename element_type,
           typename container_type = std::vector<element_type> >
  class Stack{
    public:
     /// REQUIREMENTS
     //  operator[] has to be defined for the container_type
     //  that means std::list cannot be used as container_type

      void push(element_type const& t);
      element_type pop();
      
      element_type const& top() const;
      element_type&  top();

      bool empty() const;
      
      element_type const& operator[](size_t i) const
      { return elems[i]; }

      /*
       * not actually useful
      typename container_type::const_iterator begin() const 
      { return elems.begin(); }
      
      typename container_type::const_iterator end() const
      { return elems.end(); }
      */

      size_t size() const
      { return elems.size(); }
      
      template<typename element2_type, typename container2_type>
      Stack<element_type>& operator=(Stack<element2_type,
                                     container2_type> const& S);

    private:
      container_type elems;
      
  };
  
  /// puts the element at the tail of the stack
  template<typename element_type, typename container_type>
  void Stack<element_type, container_type>::push(element_type const& t)
  {
    elems.push_back(t);
  }

  /// @brief pops the last element inserted out of the stack
  /// returns a copy of the last element deleted
  /// throws std::out_of_range exception
  template<typename element_type, typename container_type>
  element_type Stack<element_type, container_type>::pop()
  {
    if(elems.empty())
      throw std::out_of_range("Stack<>::pop: empty stack");

    element_type t = elems.back();
    elems.pop_back();
    return t;
  }
  
  /// @brief returns a const reference of the last element of the stack
  /// throws std::out_of_range exception
  template<typename element_type, typename container_type>
  element_type const& Stack<element_type, container_type>::top() const
  {
    if(elems.empty())
      throw std::out_of_range("Stack<>::top: empty stack");
    
    return elems.back();//copy of the last element
  }

  /// @brief returns the reference of the last element of the stack
  /// throws std::out_of_range exception
  template<typename element_type, typename container_type>
  element_type & Stack<element_type, container_type>::top()
  {
    if(elems.empty())
      throw std::out_of_range("Stack<>::top: empty stack");
    
    return elems.back();//copy of the last element
  }

  template<typename element_type, typename container_type>
  bool Stack<element_type, container_type>::empty() const
  {
    return elems.empty();
  }

  template<typename element_type, typename container_type>
    template<typename element2_type, typename container2_type>
  Stack<element_type>& 
  Stack<element_type, container_type>::operator=(Stack<element2_type,
                                                 container2_type> const& S)
  {
    //self assignment
    if((void*)this == (void*)&S){
      return *this;
    }

    elems.clear();
    
    size_t i = 0;

    //not doing push_front kind of thing because every STL container will 
    //not support it, like vector
    //on the other hand, operator[] is also not supported by evey STL
    //container, but I prefer to support only those containers
    // which have this operator 

    //copy the elements
    while(i<S.size()){
      elems.push(S[i]);
      ++i;
    }

    return *this;
  }

  
  template<typename element_type, typename container_type>
  std::ostream& operator<<(std::ostream& os, Stack<element_type,
                           container_type> const& s)
  {
    
    for(size_t i = 0; i!= s.size(); ++i){
        os<<s[i];
        os<<"\n";
    }

    //std::copy(s.begin(),s.end(), std::ostream_iterator<element_type>(os, "\n"));
    return os;
  }
  
  
//-----------------------------------------------------------------------------
//                      STACK SPECIALIZATIONS                                //
//-----------------------------------------------------------------------------

  /// @brief useful when the size of stack is approximately known
  /// so that there is no overhead of resource management
  template<typename element_type, size_t container_size>
  class SmallStack{
    public:
      
      SmallStack();

      void push(element_type const& t);
      element_type pop();
      element_type const & top() const;
      element_type & top();
      bool empty() const;

/*    not really required
 *
      const element_type* begin() const 
      { return &elems[0]; }


      //even when the number of elements is zero there will be at least 
      //one default allocation to make sure this works      
      const element_type* end() const
      { return &elems[num_elems]; }
*/ 
      element_type const& operator[](size_t i) const
      { return elems[i]; }
     
      size_t size() const
      { return num_elems; }

    private:
      
      //one extra element for book keeping
      //so that begin() and end() work properly
      //also helpful when the stack has zero elements
      element_type elems[container_size+1];
      
      //to keep the count of elements available for use
      size_t num_elems;
  };



  template<typename element_type, size_t container_size>
  SmallStack<element_type, container_size>::SmallStack()
  :num_elems(0)
  {  }

  template<typename element_type, size_t container_size>
  void SmallStack<element_type, container_size>::push(element_type const& t)
  {
    if(num_elems == container_size)
      throw std::out_of_range("Stack<>::push: empty stack");

    elems[num_elems] = t;
    ++num_elems;
  }

  template<typename element_type, size_t container_size>
  element_type SmallStack<element_type, container_size>::pop()
  {
    if(num_elems <= 0)
      throw std::out_of_range("Stack<>::pop: empty stack");
    
    --num_elems;//decrement the counter
    //since the opt element rests at elems[num_elems-1],
    //after decrementing it points to the deleted element
    return elems[num_elems];
  }

  template<typename element_type, size_t container_size>
  element_type const& SmallStack<element_type, container_size>::top() const
  {
    if(num_elems <= 0)
      throw std::out_of_range("Stack<>::top: empty stack");

    return elems[num_elems -1];
  }

  template<typename element_type, size_t container_size>
  element_type& SmallStack<element_type, container_size>::top()
  {
    if(num_elems <= 0)
      throw std::out_of_range("Stack<>::top: empty stack");

    return elems[num_elems -1];
  }


  template<typename element_type, size_t container_size>
  bool SmallStack<element_type, container_size>::empty() const
  {
    return num_elems == 0;
  }


  template<typename element_type, size_t container_size>
  std::ostream& operator<<(std::ostream& os, SmallStack<element_type,
                           container_size> const& s)
  {
    for(size_t i = 0; i!= s.size(); ++i){
        os<<s[i];
        os<<"\n";
    }
    //std::copy(s.begin(),s.end(), std::ostream_iterator<element_type>(os, "\n"));
    return os;
  }
}

#endif // CONTAINER_STACK
