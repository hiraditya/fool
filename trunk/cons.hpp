/// \brief provide the cons function for a sequence
/// the sequence must have a begin and an end
/// and the value type
#ifndef FOOL_CAR
#define FOOL_CAR
#include<iterator>
#include<algorithm>
namespace fool {
  template<typename sequence>
  typename sequence::value_type& car(sequence& s)
  {
    return *begin(s);
  }

  template<typename sequence_of_sequences>
  typename sequence_of_sequences::value_type::value_type& caar(sequence_of_sequences& sos)
  {
    return *begin(*begin(sos));
  }
  //returning by value
  //relying on the move-semantics of c++11
  //will not work for arrays for now
  //FIXME: find out how it will work for arrays 
  //i.e. how to find if there is no size() member function
  template<typename sequence>
  sequence cdr(sequence& s)
  {
    sequence s_copy(s.size()-1);
    std::copy(++begin(s),end(s),begin(s_copy));
    return s_copy;
  }
  
  //returns the reference to the second element of the sequence
  template<typename sequence>
  typename sequence::iterator cdr_no_copy(sequence& s)
  {
    return ++std::begin(s);
  }
  
  template<typename sequence>
  typename sequence::value_type& cadr(sequence& s)
  {
    return begin(cdr_no_copy(s));
  }

  //returning by value, relying on the move semantics of c++11
  template<typename sequence>
  sequence cons(typename sequence::value_type v, sequence& s)
  {
    sequence s_cons(s.size()+1);
    *(std::begin(s_cons)) = v;
    std::copy(begin(s),end(s),++begin(s_cons));
    return s_cons;
  }
}
#endif // FOOL_CAR

