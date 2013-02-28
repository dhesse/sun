#ifndef HELPER_H
#define HLPER_H
#include <SUN.hpp>

using namespace sun;

template <int N> SU<N> rsu(){
  SU<N> A;
  for (int n =0; n < N*N; ++n)
    A(n) = typename SU<N>::data_t(rand(), rand());
  return A;
}

template <int N> bool almost_equal(const SU<N>& A, const SU<N>& B){
  bool result = true;
  for (int n =0; n < N*N && result; ++n)
    if (abs( A(n) - B(n) ) > std::numeric_limits<double>::epsilon()*5)
      result = false;
  return result;
}

template <int N> bool equal(const SU<N>& A, const SU<N>& B){
  bool result = true;
  for (int n =0; n < N*N && result; ++n)
    if (abs( A(n) - B(n) ) != 0.0) result = false;
  return result;
}
#endif

