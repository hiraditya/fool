/*
 *  @author Aditya Kumar
 *
 *  This file is distributed under the MIT License. See
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php
 *  for terms and conditions.
 */



#ifndef FOOL_CONS_HPP
#define FOOL_CONS_HPP

#include "find_size.hpp"
#include <origin/sequence/concepts.hpp>
#include<iterator>
#include<algorithm>
namespace fool {
  namespace standard
  {
    /// \brief car stands for "Contents of the Address part of Register number"
    /// essentially it returns first element of the list
    /// returns reference to the first element of the sequence
    template<typename sequence>
    typename sequence::value_type&
    car(sequence& s)
    {
      static_assert(origin::is_STL_forward_container<sequence>(), "");
      return *begin(s);
    }
  /*
    /// returns a copy of the first element of the sequence
    template<typename sequence>
    typename sequence::value_type car(sequence& s) const
    {
      return *begin(s);
    }
  */

    /// TODO: check if the argument is actually a sequence of sequence or not.
    /// \brief caar stands for car(car s)
    /// \returns A reference to the first element of the
    ///          first element of the sequence_of_sequences.
    template<typename sequence_of_sequences>
    typename sequence_of_sequences::value_type::value_type&
    caar(sequence_of_sequences& sos)
    {
      static_assert(origin::is_STL_forward_container<sequence_of_sequences>(),
                    "");
      static_assert(origin::is_STL_forward_container<
                    typename sequence_of_sequences::value_type>(), "");
      return *begin(*begin(sos));
    }
  /*
    /// \returns a copy of the first element of the
    /// first element of the sequence_of_sequences
    template<typename sequence_of_sequences>
    typename sequence_of_sequences::value_type::value_type
    caar(sequence_of_sequences& sos) const
    {
      return *begin(*begin(sos));
    }
  */
    //returning by value
    //relying on the move-semantics of c++11
    //will not work for arrays for now
    //FIXME: find out how it will work for arrays
    //i.e. how to find if there is no size() member function

    /// \brief cdr stands for
    ///        "Contents of the Decrement part of Register number"
    /// \returns The elements of the sequence except for the first one.
    template<typename sequence>
    sequence cdr(sequence& s)
    {
      static_assert(origin::is_STL_forward_container<sequence>(), "");
      sequence s_copy(find_size(s)-1);
      std::copy(++begin(s),end(s),begin(s_copy));
      return s_copy;
    }

    //returns the reference to the second element of the sequence
    /// \brief cdr stands for
    ///        "Contents of the Decrement part of Register number"
    /// \returns The elements of the list except for the first one.
    template<typename sequence>
    typename sequence::iterator
    cdr_no_copy(sequence& s)
    {
      static_assert(origin::is_STL_forward_container<sequence>(), "");
      return ++begin(s);
    }

    /// \brief cadr stands for car(cdr s)
    /// \returns the second element of the sequence.
    template<typename sequence>
    typename sequence::value_type&
    cadr(sequence& s)
    {
      return *begin(cdr(s));
    }

    /// \brief cadr stands for car(cdr s)
    /// \returns the second element of the sequence but
    ///          call the no_copy version of \fn cdr.
    template<typename sequence>
    typename sequence::value_type&
    cadr_no_copy(sequence& s)
    {
      return *begin(cdr_no_copy(s));
    }

    /// \brief provide the cons function for a sequence
    ///        the sequence must have a begin and an end and the value type.
    /// \note returning by value, relying on the move semantics of C++11
/*    template<typename sequence>
    sequence
    cons(typename sequence::value_type v, sequence& s)
    {
      sequence s_cons(find_size(s)+1);
      *(begin(s_cons)) = v;
      std::copy(begin(s),end(s),++begin(s_cons));
      return s_cons;
    }*/

    template<typename value_type, typename sequence>
    constexpr sequence
    cons(value_type v, sequence& s)
    {
      static_assert(origin::is_STL_forward_container<sequence>(), "");
      static_assert(origin::Convertible<value_type,
                    typename sequence::value_type>(), "");
      sequence s_cons(find_size(s)+1);
      *(begin(s_cons)) = v;
      std::copy(begin(s),end(s),++begin(s_cons));
      return s_cons;
    }

    /// \brief accessors
    ///
    template<typename forward_iterator>
    inline forward_iterator succ(forward_iterator x, typename
           std::iterator_traits<forward_iterator>::difference_type n = 1)
    {
      static_assert(origin::has_forward_iterator_property<forward_iterator>(),
                    "");
      return next(x, n);
    }

    template<typename bidirectional_iterator>
    inline bidirectional_iterator pred(bidirectional_iterator x, typename
           std::iterator_traits<bidirectional_iterator>::difference_type n = 1)
    {
      static_assert(origin::has_bidirectional_iterator_property<
                            bidirectional_iterator>(), "");
      return prev(x, n);
    }

  } // namespace standard
} // namespace fool
#endif // FOOL_CONS_HPP

