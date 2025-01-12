// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/def.hpp>
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/list.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/return_internal_reference.hpp>

#if defined(_AIX) && defined(__EDG_VERSION__) && __EDG_VERSION__ < 245
# include <iostream> // works around a KCC intermediate code generation bug
#endif

using namespace boost::python;

char const* const format = "int(%s); char(%s); string(%s); double(%s); ";

///////////////////////////////////////////////////////////////////////////////
//
//  Overloaded functions
//
///////////////////////////////////////////////////////////////////////////////
object
bar(int a, char b, std::string c, double d)
{
    return format % make_tuple(a, b, c, d);
}

object
bar(int a, char b, std::string c)
{
    return format % make_tuple(a, b, c, 0.0);
}

object
bar(int a, char b)
{
    return format % make_tuple(a, b, "default", 0.0);
}

object
bar(int a)
{
    return format % make_tuple(a, 'D', "default", 0.0);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(bar_stubs, bar, 1, 4)

///////////////////////////////////////////////////////////////////////////////
//
//  Functions with default arguments
//
///////////////////////////////////////////////////////////////////////////////
object
foo(int a, char b = 'D', std::string c = "default", double d = 0.0)
{
    return format % make_tuple(a, b, c, d);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(foo_stubs, foo, 1, 4)

///////////////////////////////////////////////////////////////////////////////
//
//  Overloaded member functions with default arguments
//
///////////////////////////////////////////////////////////////////////////////
struct Y {

    Y() {}

    object
    get_state() const
    {
        return format % make_tuple(a, b, c, d);
    }

    int a; char b; std::string c; double d;
};


struct X {

    X() {}

    X(int a, char b = 'D', std::string c = "constructor", double d = 0.0)
    : state(format % make_tuple(a, b, c, d))
    {}

    X(std::string s, bool b)
    : state("Got exactly two arguments from constructor: string(%s); bool(%s); " % make_tuple(s, b))
    {}

    object
    bar(int a, char b = 'D', std::string c = "default", double d = 0.0) const
    {
        return format % make_tuple(a, b, c, d);
    }

    Y const&
    bar2(int a = 0, char b = 'D', std::string c = "default", double d = 0.0)
    {
        // tests zero arg member function and return_internal_reference policy
        y.a = a;
        y.b = b;
        y.c = c;
        y.d = d;
        return y;
    }

    object
    foo(int a, bool b=false) const
    {
        return "int(%s); bool(%s); " % make_tuple(a, b);
    }

    object
    foo(std::string a, bool b=false) const
    {
        return "string(%s); bool(%s); " % make_tuple(a, b);
    }

    object
    foo(list a, list b, bool c=false) const
    {
        return "list(%s); list(%s); bool(%s); " % make_tuple(a, b, c);
    }

    object
    get_state() const
    {
        return state;
    }

    Y y;
    object state;
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(X_bar_stubs, bar, 1, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(X_bar_stubs2, bar2, 0, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(X_foo_2_stubs, foo, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(X_foo_3_stubs, foo, 2, 3)

///////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MODULE(defaults_ext)
{
    def("foo", foo, foo_stubs());
    def("bar", (object(*)(int, char, std::string, double))0, bar_stubs());

    class_<Y>("Y", init<>("doc of Y init")) // this should work
        .def("get_state", &Y::get_state)
        ;

    class_<X>("X")

        .def(init<int, optional<char, std::string, double> >("doc of init"))
        .def(init<std::string, bool>()[default_call_policies()]) // what's a good policy here?
        .def("get_state", &X::get_state)
        .def("bar", &X::bar, X_bar_stubs())
        .def("bar2", &X::bar2, X_bar_stubs2("doc of X::bar2")[return_internal_reference<>()])
        .def("foo", (object(X::*)(std::string, bool) const)0, X_foo_2_stubs())
        .def("foo", (object(X::*)(int, bool) const)0, X_foo_2_stubs())
        .def("foo", (object(X::*)(list, list, bool) const)0, X_foo_3_stubs())
        ;
}

#include "module_tail.cpp"

