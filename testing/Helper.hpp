#ifndef HELPER_H
#define HLPER_H
#include <SUN.hpp>
#include <Vector.hpp>
#include <gtest/gtest.h>

using namespace sun;

#define ASSERT_CPLX_EQ(a ,b)			\
  ASSERT_DOUBLE_EQ((a).real(), (b).real());	\
  ASSERT_DOUBLE_EQ((a).imag(), (b).imag());

template <int N> SU<N> rsu(){
  SU<N> A;
  for (int n =0; n < N*N; ++n)
    A[n] = typename SU<N>::data_t(1. - 2.*rand()/RAND_MAX,
				  1. - .2* rand()/RAND_MAX);
  return A;
}

template <int N> Vec<N> rvec(){
  Vec<N> A;
  for (int n =0; n < N; ++n)
    A[n] = typename Vec<N>::data_t(1. - 2.*rand()/RAND_MAX,
				  1. - .2* rand()/RAND_MAX);
  return A;
}

template <class C>
bool almost_equal(const C& A, const C& B, int k = 5){
  bool result = true;
  typename C::const_iterator a, b;
  for (a = A.begin(), b = B.begin(); a != A.end(); ++a, ++b)
    if (abs( *a - *b) / abs(*a + *b) >
	(std::numeric_limits<double>::epsilon() * k)){
      std::cout << a->real() << ", " << a->imag() << std::endl;
      std::cout << abs( *a - *b ) << std::endl;
      std::cout << std::numeric_limits<double>::epsilon() * k << std::endl;
      return false;
    }
  return result;
}

template <int N> bool equal(const SU<N>& A, const SU<N>& B){
  bool result = true;
  for (int n =0; n < N*N && result; ++n)
    if (abs( A[n] - B[n] ) != 0.0) result = false;
  return result;
}

template <class C> bool near(const C& a, const C& b){
  typename C::const_iterator ait = a.begin(), bit = b.begin();
  for (; ait != a.end(); ++ait, ++bit)
    if (abs( *ait - *bit ) > std::numeric_limits<double>::epsilon() * 5)
      return false;
  return true;
}
template <class C> void randomize(C& a){
  typename C::iterator i;
  for (i = a.begin(); i != a.end(); ++i)
    *i = (1. - 2.*rand()/RAND_MAX);
}
#endif
