// test file for octonion.hpp

//  (C) Copyright Hubert Holin 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.


#include <iomanip>
#include <iostream>
#include <sstream>
#include <functional>


#include <boost/bind.hpp>
#include <boost/function.hpp>


#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite_ex.hpp>


#include <boost/math/octonion.hpp>

#if defined(__GNUC__) && (__GNUC__ < 3)
    // gcc 2.x ignores function scope using declarations,
    // put them in the scope of the enclosing namespace instead:
using   ::std::sqrt;
using   ::std::atan;
using   ::std::log;
using   ::std::exp;
using   ::std::cos;
using   ::std::sin;
using   ::std::tan;
using   ::std::cosh;
using   ::std::sinh;
using   ::std::tanh;

using   ::std::numeric_limits;

using   ::boost::math::abs;
#endif  /* defined(__GNUC__) && (__GNUC__ < 3) */


#ifdef  BOOST_NO_STDC_NAMESPACE
using   ::sqrt;
using   ::atan;
using   ::log;
using   ::exp;
using   ::cos;
using   ::sin;
using   ::tan;
using   ::cosh;
using   ::sinh;
using   ::tanh;
#endif  /* BOOST_NO_STDC_NAMESPACE */

#ifdef  BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
using   ::boost::math::real;
using   ::boost::math::unreal;
using   ::boost::math::sup;
using   ::boost::math::l1;
using   ::boost::math::abs;
using   ::boost::math::norm;
using   ::boost::math::conj;
using   ::boost::math::exp;
using   ::boost::math::pow;
using   ::boost::math::cos;
using   ::boost::math::sin;
using   ::boost::math::tan;
using   ::boost::math::cosh;
using   ::boost::math::sinh;
using   ::boost::math::tanh;
using   ::boost::math::sinc_pi;
using   ::boost::math::sinhc_pi;
#endif  /* BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP */
  
// Provide standard floating point abs() overloads for MSVC
#ifdef    BOOST_MSVC
#if        (BOOST_MSVC < 1300) || (defined(_MSC_EXTENSIONS) && BOOST_MSVC < 1310)
inline float        abs(float v)
{
    return(fabs(v));
}

inline double        abs(double v)
{
    return(fabs(v));
}

inline long double    abs(long double v)
{
    return(fabs(v));
}
#endif    /* need abs */
#endif    /* BOOST_MSVC */


// explicit (if ludicrous) instanciation
#ifndef __GNUC__
template    class ::boost::math::octonion<int>;
#else
// gcc doesn't like the absolutely-qualified namespace
template class boost::math::octonion<int>;
#endif


namespace
{
    template<typename T>
    ::boost::math::octonion<T>    index_i_element(int idx)
    {
        return(
            ::boost::math::octonion<T>(
                        (idx == 0) ?
                            static_cast<T>(1) :
                            static_cast<T>(0),
                        (idx == 1) ?
                            static_cast<T>(1) :
                            static_cast<T>(0),
                        (idx == 2) ?
                            static_cast<T>(1) :
                            static_cast<T>(0),
                        (idx == 3) ?
                            static_cast<T>(1) :
                            static_cast<T>(0),
                        (idx == 4) ?
                            static_cast<T>(1) :
                            static_cast<T>(0),
                        (idx == 5) ?
                            static_cast<T>(1) :
                            static_cast<T>(0),
                        (idx == 6) ?
                            static_cast<T>(1) :
                            static_cast<T>(0),
                        (idx == 7) ?
                            static_cast<T>(1) :
                            static_cast<T>(0)
            ));
    }
}



void    octonion_manual_test()
{
    // tests for evaluation by humans
    
    
    // using default constructor
    ::boost::math::octonion<float>            o0;
    
    ::boost::math::octonion<float>            oa[2];
    
    // using constructor "O seen as R^8"
    ::boost::math::octonion<float>            o1(1,2,3,4,5,6,7,8);
    
    ::std::complex<double>                    c0(9,10);
    
    // using constructor "O seen as C^4"
    ::boost::math::octonion<double>            o2(c0);
    
    ::boost::math::quaternion<long double>    q0(11,12,13,14);
    
    // using constructor "O seen as H^2"
    ::boost::math::octonion<long double>      o3(q0);
    
    // using UNtemplated copy constructor
    ::boost::math::octonion<float>            o4(o1);
    
    // using templated copy constructor
    ::boost::math::octonion<long double>      o5(o2);
    
    // using UNtemplated assignment operator
    o5 = o3;
    oa[0] = o0;
    
    // using templated assignment operator
    o5 = o2;
    oa[1] = o5;
    
    float                                     f0(15);
    
    // using converting assignment operator
    o0 = f0;
    
    // using converting assignment operator
    o2 = c0;
    
    // using converting assignment operator
    o5 = q0;
    
    // using += (const T &)
    o4 += f0;
    
    // using += (const ::std::complex<T> &)
    o2 += c0;
    
    // using += (const ::boost::math::quaternion<T> &)
    o3 += q0;
    
    // using += (const quaternion<X> &)
    o5 += o4;
    
    // using -= (const T &)
    o1 -= f0;
    
    // using -= (const ::std::complex<T> &)
    o2 -= c0;
    
    // using -= (const ::boost::math::quaternion<T> &)
    o5 -= q0;
    
    // using -= (const octonion<X> &)
    o3 -= o4;
    
    double                                    d0(16);
    ::std::complex<double>                    c1(17,18);
    ::boost::math::quaternion<double>         q1(19,20,21,22);
    
    // using *= (const T &)
    o2 *= d0;
    
    // using *= (const ::std::complex<T> &)
    o2 *= c1;
    
    // using *= (const ::boost::math::quaternion<T> &)
    o2 *= q1;
    
    // using *= (const octonion<X> &)
    o2 *= o4;
    
    long double                               l0(23);
    ::std::complex<long double>               c2(24,25);
    
    // using /= (const T &)
    o5 /= l0;
    
    // using /= (const ::std::complex<T> &)
    o5 /= c2;
    
    // using /= (const quaternion<X> &)
    o5 /= q0;
    
    // using /= (const octonion<X> &)
    o5 /= o5;
    
    // using + (const T &, const octonion<T> &)
    ::boost::math::octonion<float>            o6 = f0+o0;
    
    // using + (const octonion<T> &, const T &)
    ::boost::math::octonion<float>            o7 = o0+f0;
    
    // using + (const ::std::complex<T> &, const quaternion<T> &)
    ::boost::math::octonion<double>           o8 = c0+o2;
    
    // using + (const octonion<T> &, const ::std::complex<T> &)
    ::boost::math::octonion<double>           o9 = o2+c0;
    
    // using + (const ::boost::math::quaternion<T>, const octonion<T> &)
    ::boost::math::octonion<long double>      o10 = q0+o3;
    
    // using + (const octonion<T> &, const ::boost::math::quaternion<T> &)
    ::boost::math::octonion<long double>      o11 = o3+q0;
    
    // using + (const quaternion<T> &,const quaternion<T> &)
    ::boost::math::octonion<float>            o12 = o0+o4;
    
    // using - (const T &, const octonion<T> &)
    o6 = f0-o0;
    
    // using - (const octonion<T> &, const T &)
    o7 = o0-f0;
    
    // using - (const ::std::complex<T> &, const octonion<T> &)
    o8 = c0-o2;
    
    // using - (const octonion<T> &, const ::std::complex<T> &)
    o9 = o2-c0;
    
    // using - (const quaternion<T> &,const octonion<T> &)
    o10 = q0-o3;
    
    // using - (const octonion<T> &,const quaternion<T> &)
    o11 = o3-q0;
    
    // using - (const octonion<T> &,const octonion<T> &)
    o12 = o0-o4;
    
    // using * (const T &, const octonion<T> &)
    o6 = f0*o0;
    
    // using * (const octonion<T> &, const T &)
    o7 = o0*f0;
    
    // using * (const ::std::complex<T> &, const octonion<T> &)
    o8 = c0*o2;
    
    // using * (const octonion<T> &, const ::std::complex<T> &)
    o9 = o2*c0;
    
    // using * (const quaternion<T> &,const octonion<T> &)
    o10 = q0*o3;
    
    // using * (const octonion<T> &,const quaternion<T> &)
    o11 = o3*q0;
    
    // using * (const octonion<T> &,const octonion<T> &)
    o12 = o0*o4;
    
    // using / (const T &, const octonion<T> &)
    o6 = f0/o0;
    
    // using / (const octonion<T> &, const T &)
    o7 = o0/f0;
    
    // using / (const ::std::complex<T> &, const octonion<T> &)
    o8 = c0/o2;
    
    // using / (const octonion<T> &, const ::std::complex<T> &)
    o9 = o2/c0;
    
    // using / (const ::boost::math::quaternion<T> &, const octonion<T> &)
    o10 = q0/o3;
    
    // using / (const octonion<T> &, const ::boost::math::quaternion<T> &)
    o11 = o3/q0;
    
    // using / (const octonion<T> &,const octonion<T> &)
    o12 = o0/o4;
    
    // using + (const octonion<T> &)
    o4 = +o0;
    
    // using - (const octonion<T> &)
    o0 = -o4;
    
    // using == (const T &, const octonion<T> &)
    f0 == o0;
    
    // using == (const octonion<T> &, const T &)
    o0 == f0;
    
    // using == (const ::std::complex<T> &, const octonion<T> &)
    c0 == o2;
    
    // using == (const octonion<T> &, const ::std::complex<T> &)
    o2 == c0;
    
    // using == (const ::boost::math::quaternion<T> &, const octonion<T> &)
    q0 == o3;
    
    // using == (const octonion<T> &, const ::boost::math::quaternion<T> &)
    o3 == q0;
    
    // using == (const octonion<T> &,const octonion<T> &)
    o0 == o4;
    
    // using != (const T &, const octonion<T> &)
    f0 != o0;
    
    // using != (const octonion<T> &, const T &)
    o0 != f0;
    
    // using != (const ::std::complex<T> &, const octonion<T> &)
    c0 != o2;
    
    // using != (const octonion<T> &, const ::std::complex<T> &)
    o2 != c0;
    
    // using != (const ::boost::math::quaternion<T> &, const octonion<T> &)
    q0 != o3;
    
    // using != (const octonion<T> &, const ::boost::math::quaternion<T> &)
    o3 != q0;
    
    // using != (const octonion<T> &,const octonion<T> &)
    o0 != o4;
    
    BOOST_MESSAGE("Please input an octonion...");
    
#ifdef BOOST_INTERACTIVE_TEST_INPUT_ITERATOR
    ::std::cin >> o0;
    
    if    (::std::cin.fail())
    {
        BOOST_MESSAGE("You have entered nonsense!");
    }
    else
    {
        BOOST_MESSAGE("You have entered the octonion " << o0 << " .");
    }
#else
    ::std::istringstream                bogus("(1,2,3,4,5,6,7,8)");
    
    bogus >> o0;
    
    BOOST_MESSAGE("You have entered the octonion " << o0 << " .");
#endif
    
    BOOST_MESSAGE("For this octonion:");
    
    BOOST_MESSAGE( "the value of the real part is "
                << real(o0));
    
    BOOST_MESSAGE( "the value of the unreal part is "
                << unreal(o0));
    
    BOOST_MESSAGE( "the value of the sup norm is "
                << sup(o0));
    
    BOOST_MESSAGE( "the value of the l1 norm is "
                << l1(o0));
    
    BOOST_MESSAGE( "the value of the magnitude (euclidian norm) is "
                << abs(o0));
    
    BOOST_MESSAGE( "the value of the (Cayley) norm is "
                << norm(o0));
    
    BOOST_MESSAGE( "the value of the conjugate is "
                << conj(o0));
    
    BOOST_MESSAGE( "the value of the exponential is "
                << exp(o0));
    
    BOOST_MESSAGE( "the value of the cube is "
                << pow(o0,3));
    
    BOOST_MESSAGE( "the value of the cosinus is "
                << cos(o0));
    
    BOOST_MESSAGE( "the value of the sinus is "
                << sin(o0));
    
    BOOST_MESSAGE( "the value of the tangent is "
                << tan(o0));
    
    BOOST_MESSAGE( "the value of the hyperbolic cosinus is "
                << cosh(o0));
    
    BOOST_MESSAGE( "the value of the hyperbolic sinus is "
                << sinh(o0));
    
    BOOST_MESSAGE( "the value of the hyperbolic tangent is "
                << tanh(o0));
    
#ifdef    BOOST_NO_TEMPLATE_TEMPLATES
    BOOST_MESSAGE( "no template templates, can't compute cardinal functions");
#else    /* BOOST_NO_TEMPLATE_TEMPLATES */
    BOOST_MESSAGE( "the value of the Sinus Cardinal (of index pi) is "
                << sinc_pi(o0));
    
    BOOST_MESSAGE( "the value of "
                << "the Hyperbolic Sinus Cardinal (of index pi) is "
                << sinhc_pi(o0));
#endif    /* BOOST_NO_TEMPLATE_TEMPLATES */
    
    BOOST_MESSAGE(" ");
    
    float                            rho = ::std::sqrt(4096.0f);
    float                            theta = ::std::atan(1.0f);
    float                            phi1 = ::std::atan(1.0f);
    float                            phi2 = ::std::atan(1.0f);
    float                            phi3 = ::std::atan(1.0f);
    float                            phi4 = ::std::atan(1.0f);
    float                            phi5 = ::std::atan(1.0f);
    float                            phi6 = ::std::atan(1.0f);
    
    BOOST_MESSAGE( "The value of the octonion represented "
                << "in spherical form by "
                << "rho = " << rho << " , theta = " << theta
                << " , phi1 = " << phi1 << " , phi2 = " << phi2
                << " , phi3 = " << phi3 << " , phi4 = " << phi4
                << " , phi5 = " << phi5 << " , phi6 = " << phi6
                << " is "
                << ::boost::math::spherical(rho, theta,
                        phi1, phi2, phi3, phi4, phi5, phi6));
    
    float                            rho1 = 1;
    float                            rho2 = 2;
    float                            rho3 = ::std::sqrt(2.0f);
    float                            rho4 = ::std::sqrt(8.0f);
    float                            theta1 = 0;
    float                            theta2 = ::std::atan(1.0f)*2;
    float                            theta3 = ::std::atan(1.0f);
    float                            theta4 = ::std::atan(::std::sqrt(3.0f));
    
    BOOST_MESSAGE( "The value of the octonion represented "
                << "in multipolar form by "
                << "rho1 = " << rho1 << " , theta1 = " << theta1
                << " , rho2 = " << rho2 << " , theta2 = " << theta2
                << "rho3 = " << rho3 << " , theta3 = " << theta3
                << " , rho4 = " << rho4 << " , theta4 = " << theta4
                << " is "
                << ::boost::math::multipolar(rho1, theta1, rho2, theta2,
                        rho3, theta3, rho4, theta4));
    
    float                            r = ::std::sqrt(2.0f);
    float                            angle = ::std::atan(1.0f);
    float                            h1 = 3;
    float                            h2 = 4;
    float                            h3 = 5;
    float                            h4 = 6;
    float                            h5 = 7;
    float                            h6 = 8;
    
    BOOST_MESSAGE( "The value of the octonion represented "
                << "in cylindrical form by "
                << "r = " << r << " , angle = " << angle
                << " , h1 = " << h1 << " , h2 = " << h2
                << " , h3 = " << h3 << " , h4 = " << h4
                << " , h5 = " << h5 << " , h6 = " << h6
                << " is " << ::boost::math::cylindrical(r, angle,
                        h1, h2, h3, h4, h5, h6));
    
    double                               real_1(1);
    ::std::complex<double>               complex_1(1);
    ::std::complex<double>               complex_i(0,1);
    ::boost::math::quaternion<double>    quaternion_1(1);
    ::boost::math::quaternion<double>    quaternion_i(0,1);
    ::boost::math::quaternion<double>    quaternion_j(0,0,1);
    ::boost::math::quaternion<double>    quaternion_k(0,0,0,1);
    ::boost::math::octonion<double>      octonion_1(1);
    ::boost::math::octonion<double>      octonion_i(0,1);
    ::boost::math::octonion<double>      octonion_j(0,0,1);
    ::boost::math::octonion<double>      octonion_k(0,0,0,1);
    ::boost::math::octonion<double>      octonion_e_prime(0,0,0,0,1);
    ::boost::math::octonion<double>      octonion_i_prime(0,0,0,0,0,1);
    ::boost::math::octonion<double>      octonion_j_prime(0,0,0,0,0,0,1);
    ::boost::math::octonion<double>      octonion_k_prime(0,0,0,0,0,0,0,1);
    
    
    BOOST_MESSAGE(" ");
    
    BOOST_MESSAGE( "Real 1: " << real_1
                << " ; Complex 1: " << complex_1
                << " ; Quaternion 1: " << quaternion_1
                << " ; Octonion 1: " << octonion_1 << " .");
                
    BOOST_MESSAGE( "Complex i: " << complex_i
                << " ; Quaternion i: " << quaternion_i
                << " ; Octonion i : " << octonion_i << " .");
                
    BOOST_MESSAGE( "Quaternion j: " << quaternion_j
                << " ; Octonion j: " << octonion_j << " .");
    
    BOOST_MESSAGE( "Quaternion k: " << quaternion_k
                << " ; Octonion k: " << octonion_k << " .");
    
    BOOST_MESSAGE( "Quaternion e\': " << octonion_e_prime << " .");
    
    BOOST_MESSAGE( "Quaternion i\': " << octonion_i_prime << " .");
    
    BOOST_MESSAGE( "Quaternion j\': " << octonion_j_prime << " .");
    
    BOOST_MESSAGE( "Quaternion k\': " << octonion_k_prime << " .");
    
    BOOST_MESSAGE(" ");
    
    BOOST_MESSAGE( octonion_1*octonion_1 << " ; "
                << octonion_1*octonion_i << " ; "
                << octonion_1*octonion_j << " ; "
                << octonion_1*octonion_k << " ; "
                << octonion_1*octonion_e_prime << " ; "
                << octonion_1*octonion_i_prime << " ; "
                << octonion_1*octonion_j_prime << " ; "
                << octonion_1*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE( octonion_i*octonion_1 << " ; "
                << octonion_i*octonion_i << " ; "
                << octonion_i*octonion_j << " ; "
                << octonion_i*octonion_k << " ; "
                << octonion_i*octonion_e_prime << " ; "
                << octonion_i*octonion_i_prime << " ; "
                << octonion_i*octonion_j_prime << " ; "
                << octonion_i*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE( octonion_j*octonion_1 << " ; "
                << octonion_j*octonion_i << " ; "
                << octonion_j*octonion_j << " ; "
                << octonion_j*octonion_k << " ; "
                << octonion_j*octonion_e_prime << " ; "
                << octonion_j*octonion_i_prime << " ; "
                << octonion_j*octonion_j_prime << " ; "
                << octonion_j*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE( octonion_k*octonion_1 << " ; "
                << octonion_k*octonion_i << " ; "
                << octonion_k*octonion_j << " ; "
                << octonion_k*octonion_k << " ; "
                << octonion_k*octonion_e_prime << " ; "
                << octonion_k*octonion_i_prime << " ; "
                << octonion_k*octonion_j_prime << " ; "
                << octonion_k*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE( octonion_e_prime*octonion_1 << " ; "
                << octonion_e_prime*octonion_i << " ; "
                << octonion_e_prime*octonion_j << " ; "
                << octonion_e_prime*octonion_k << " ; "
                << octonion_e_prime*octonion_e_prime << " ; "
                << octonion_e_prime*octonion_i_prime << " ; "
                << octonion_e_prime*octonion_j_prime << " ; "
                << octonion_e_prime*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE( octonion_i_prime*octonion_1 << " ; "
                << octonion_i_prime*octonion_i << " ; "
                << octonion_i_prime*octonion_j << " ; "
                << octonion_i_prime*octonion_k << " ; "
                << octonion_i_prime*octonion_e_prime << " ; "
                << octonion_i_prime*octonion_i_prime << " ; "
                << octonion_i_prime*octonion_j_prime << " ; "
                << octonion_i_prime*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE( octonion_j_prime*octonion_1 << " ; "
                << octonion_j_prime*octonion_i << " ; "
                << octonion_j_prime*octonion_j << " ; "
                << octonion_j_prime*octonion_k << " ; "
                << octonion_j_prime*octonion_e_prime << " ; "
                << octonion_j_prime*octonion_i_prime << " ; "
                << octonion_j_prime*octonion_j_prime << " ; "
                << octonion_j_prime*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE( octonion_k_prime*octonion_1 << " ; "
                << octonion_k_prime*octonion_i << " ; "
                << octonion_k_prime*octonion_j << " ; "
                << octonion_k_prime*octonion_k << " ; "
                << octonion_k_prime*octonion_e_prime << " ; "
                << octonion_k_prime*octonion_i_prime << " ; "
                << octonion_k_prime*octonion_j_prime << " ; "
                << octonion_k_prime*octonion_k_prime << " ; ");
    
    BOOST_MESSAGE(" ");
    
    BOOST_MESSAGE("i\'*(e\'*j) : "
    << octonion_i_prime*(octonion_e_prime*octonion_j) << " ;");
    
    BOOST_MESSAGE("(i\'*e\')*j : "
    << (octonion_i_prime*octonion_e_prime)*octonion_j << " ;");
    
    BOOST_MESSAGE(" ");
}


template<typename T>
void    multiplication_test(const char * more_blurb)
{
#if defined(__GNUC__) && (__GNUC__ < 3)
#else   /* defined(__GNUC__) && (__GNUC__ < 3) */
    using ::std::numeric_limits;
    
    using ::boost::math::abs;
#endif /* defined(__GNUC__) && (__GNUC__ < 3) */
    
    
    BOOST_MESSAGE("Testing multiplication for " << more_blurb << ".");
    
    BOOST_REQUIRE_PREDICATE(::std::less_equal<T>(), 2,
        (
            abs(::boost::math::octonion<T>(1,0,0,0,0,0,0,0)*
                ::boost::math::octonion<T>(1,0,0,0,0,0,0,0)-
                static_cast<T>(1)),
            numeric_limits<T>::epsilon()
        ));
    
    for    (int idx = 1; idx < 8; ++idx)
    {
        ::boost::math::octonion<T>    toto = index_i_element<T>(idx);
        
        BOOST_REQUIRE_PREDICATE(::std::less_equal<T>(), 2,
            (
                abs(toto*toto+static_cast<T>(1)),
                numeric_limits<T>::epsilon()
            ));
    }
}


template<typename T>
void    exp_test(const char * more_blurb)
{
#if defined(__GNUC__) && (__GNUC__ < 3)
#else   /* defined(__GNUC__) && (__GNUC__ < 3) */
    using ::std::numeric_limits;
    
    using ::std::atan;
    
    using ::boost::math::abs;
#endif  /* defined(__GNUC__) && (__GNUC__ < 3) */
    
    
    BOOST_MESSAGE("Testing exp for " << more_blurb << ".");
    
    for    (int idx = 1; idx < 8; ++idx)
    {
        ::boost::math::octonion<T>    toto =
            static_cast<T>(4)*atan(static_cast<T>(1))*index_i_element<T>(idx);
            
        BOOST_CHECK_PREDICATE(::std::less_equal<T>(), 2,
            (
                abs(exp(toto)+static_cast<T>(1)),
                2*numeric_limits<T>::epsilon()
            ));
    }
}


boost::unit_test_framework::test_suite *    init_unit_test_suite(int, char *[])
{
    //::boost::unit_test_framework::unit_test_log::instance().
    //    set_log_threshold_level_by_name("messages");
    
    boost::unit_test_framework::test_suite *    test =
        BOOST_TEST_SUITE("octonion_test");
    
#define    BOOST_OCTONION_COMMON_GENERATOR(fct,type)               \
    test->add(BOOST_TEST_CASE(::boost::bind(static_cast            \
        < void (*) (const char *) >(&fct##_test<type>), #type)));
    
    
#define    BOOST_OCTONION_TEST(type)                        \
    BOOST_OCTONION_COMMON_GENERATOR(multiplication,type)    \
    BOOST_OCTONION_COMMON_GENERATOR(exp,type)
    
    
    BOOST_OCTONION_TEST(float)
    BOOST_OCTONION_TEST(double)
    BOOST_OCTONION_TEST(long double)
    
    
#undef    BOOST_OCTONION_TEST
    
#undef    BOOST_OCTONION_COMMON_GENERATOR
    
    
#ifdef BOOST_OCTONION_TEST_VERBOSE
    
    octonion_manual_test();
    
#endif    /* BOOST_OCTONION_TEST_VERBOSE */
    
    return(test);
}
