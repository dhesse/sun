#include <gtest/gtest.h>
#include <SUN.hpp>

using namespace sun;

template <int N> SU<N> rsu(){
  SU<N> A;
  for (int n =0; n < N*N; ++n)
    A(n) = std::complex<double>(rand(), rand());
  return A;
}

template <int N> bool almost_equal(const SU<N>& A, const SU<N>& B){
  bool result = true;
  for (int n =0; n < N*N && result; ++n)
    if (abs( A(n) - B(n) ) > std::numeric_limits<double>::epsilon()*5)
      result = false;
  return result;
}

TEST(Arithmetic, SU3assign){
  SU<3> A = rsu<3>(), B(A), C(A);
  B += A;
  C *= 2;
  ASSERT_TRUE(almost_equal(B, C));
  C -= A;
  ASSERT_TRUE(almost_equal(A, C));
  B += -A;
  ASSERT_TRUE(almost_equal(A, B));
}

TEST(ARithmetic, SU3binaryop){
}
