#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <Common.hpp>

namespace sun{
  template <int N> class Vec;
  namespace detail {
    ////////////////////////////////////////////////////////////
    //
    //  N-vector arithmetic.
    //
    //  \date      Wed Mar  6 11:13:53 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <int N> Vec<N> mul( const SU<N>& A, const Vec<N>& B ){
      Vec<N> C;
      for (int i = 0; i< N; ++i)
	for (int k = 0; k < N; ++k)
	  C[i] += A(i,k)*B[k];
      return C;
    }
    template <int N> Vec<N> mul( const Vec<N>& B, const SU<N>& A ){
      Vec<N> C;
      for (int i = 0; i< N; ++i)
	for (int k = 0; k < N; ++k)
	  C[i] += A(k,i)*B[k];
      return C;
    }
  }
  ////////////////////////////////////////////////////////////
  //
  //  N-vector class template
  //
  //  \date      Wed Mar  6 11:18:48 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
  template <int N> class Vec : public Base<N, Vec<N> >::type {
  public:
    typedef Vec self_t;
    static const int rep_size = N;
    static const int size = N;
    typedef typename Base<N, Vec<N> >::type base_t;
    typedef typename base_t::value_t data_t;
    using typename base_t::iterator;
    using typename base_t::const_iterator;

    ////////////////////////////////////////////////////////////
    //
    //  Arithmetic. Implementation in detail.
    //
    //  \date      Wed Mar  6 11:20:55 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    using base_t::operator*=;
    self_t& operator*=(const self_t& A){ // overload, no specialization
      self_t tmp = detail::mul(*this, A);
      std::swap(this->rep, tmp.rep);
      return *this;
    }
  };
  ////////////////////////////////////////////////////////////
  //
  //  Binary arithmetic.
  //
  //  \date      Wed Mar  6 11:36:33 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
  template <int N, class C> Vec<N> operator*(const Vec<N>& A, const C& c){
    Vec<N> result(A);
    result *= c;
    return result;
  }
  template <int N, class C> Vec<N> operator*( const C& c, const Vec<N>& A){
    Vec<N> result(A);
    result *= c;
    return result;
  }
  template <int N> Vec<N> operator*( const Vec<N>& A, const Vec<N>& B){
    Vec<N> result(A);
    result *= B;
    return result;
  }
  template <int N, class C> Vec<N> operator/(const Vec<N>& A, const C& c){
    Vec<N> result(A);
    result /= c;
    return result;
  }
}

#endif /* _VECTOR_H_ */
