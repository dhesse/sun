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
    A(n) = typename SU<N>::data_t(1. - 2.*rand()/RAND_MAX,
				  1. - .2* rand()/RAND_MAX);
  return A;
}

template <int N> Vec<N> rvec(){
  Vec<N> A;
  for (int n =0; n < N; ++n)
    A(n) = typename Vec<N>::data_t(1. - 2.*rand()/RAND_MAX,
				  1. - .2* rand()/RAND_MAX);
  return A;
}

template <int N, class C1, class C2>
bool almost_equal(const detail::MatrixExpression<C1,N>& A, 
		  const detail::MatrixExpression<C2,N>& B, int k = 5){
  bool result = true;
  for (int n =0; n < C1::rep_size && result; ++n)
    if (abs( A(n) - B(n)) / abs(A(n) + B(n)) >
	(std::numeric_limits<double>::epsilon() * k)){
      std::cout << A(n).real() << ", " << A(n).imag() << std::endl;
      std::cout << abs( A(n) - B(n) ) << std::endl;
      std::cout << std::numeric_limits<double>::epsilon() * k << std::endl;
      result = false;
    }
  return result;
}

template <int N> bool equal(const SU<N>& A, const SU<N>& B){
  bool result = true;
  for (int n =0; n < N*N && result; ++n)
    if (abs( A(n) - B(n) ) != 0.0) result = false;
  return result;
}
#endif
