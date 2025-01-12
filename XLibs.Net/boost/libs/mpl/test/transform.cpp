//-----------------------------------------------------------------------------
// boost mpl/test/transform.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-03
// Aleksey Gurtovoy, Dave Abrahams
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/transform.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/type_traits/add_pointer.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    using namespace mpl::placeholders;
    
    {
        typedef mpl::list<char,short,int,long,float,double> types;
        typedef mpl::list<char*,short*,int*,long*,float*,double*> pointers;

        typedef mpl::transform1< types,boost::add_pointer<_1> >::type result1;
        BOOST_STATIC_ASSERT((mpl::equal<result1,pointers>::type::value));
        
        typedef mpl::transform< types,boost::add_pointer<_1> >::type result;
        BOOST_STATIC_ASSERT((mpl::equal<result,pointers>::type::value));
    }
    
    {
        typedef mpl::list_c<long,0,2,4,6,8,10> evens;
        typedef mpl::list_c<long,2,3,5,7,11,13> primes;
        typedef mpl::list_c<long,2,5,9,13,19,23> sums;

        typedef mpl::transform2< evens, primes, mpl::plus<> >::type result1;
        BOOST_STATIC_ASSERT((mpl::equal<result1::type,sums::type>::type::value));
        
        typedef mpl::transform< evens, primes, mpl::plus<> >::type result;
        BOOST_STATIC_ASSERT((mpl::equal<result::type,sums::type>::type::value));
    }
    
    return 0;
}
