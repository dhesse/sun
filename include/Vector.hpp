#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <Vector.hpp>
#include <SUN.hpp>

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
	  C(i) += A(i,k)*B(k);
      return C;
    }
    template <int N> Vec<N> mul( const Vec<N>& B, const SU<N>& A ){
      Vec<N> C;
      for (int i = 0; i< N; ++i)
	for (int k = 0; k < N; ++k)
	  C(i) += A(k,i)*B(k);
      return C;
    }
    template <int N> Vec<N>& add_assign( Vec<N>& A, const Vec<N>& B ){
      for (int i = 0; i < N; ++i) A(i) += B(i);
      return A;
    }
    template <int N> Vec<N>& sub_assign( Vec<N>& A, const Vec<N>& B ){
      for (int i = 0; i < N; ++i) A(i) -= B(i);
      return A;
    }
    template <int N, class C> Vec<N>& mul_assign(Vec<N>& A, const C& c) {
      for (int i = 0; i < N; ++i) A(i) *= c;
      return A;
    }
    template <int N, class C> Vec<N>& div_assign(Vec<N>& A, const C& c) {
      for (int i = 0; i < N; ++i) A(i) /= c;
      return A;
    }
  }
  ////////////////////////////////////////////////////////////
  //
  //  N-vector class template
  //
  //  \date      Wed Mar  6 11:18:48 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
  template <int N> class Vec : public detail::MatrixExpression<Vec<N> , N>{
  public:
    typedef Vec self_t;
    typedef typename detail::MatrixExpression<SU<N>, N>::data_t data_t;
    typedef typename detail::MatrixExpression<SU<N>, N>::rep_t rep_t;
    static const int rep_size = N;
    static const int size = N;
    ////////////////////////////////////////////////////////////
    //
    //  Element access. No range checking is done!
    //
    //  \date      Wed Mar  6 11:19:33 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    data_t& operator()(int i){ return rep[i]; }
    const data_t& operator()(int i) const { return rep[i]; }
    ////////////////////////////////////////////////////////////
    //
    //  Arithmetic. Implementation in detail.
    //
    //  \date      Wed Mar  6 11:20:55 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <class C> self_t& operator*=(const C& c){
      return detail::mul_assign(*this, c);
    }
    self_t& operator*=(const self_t& A){ // overload, no specialization
      self_t tmp = detail::mul(*this, A);
      std::swap(this->rep, tmp.rep);
      return *this;
    }
    template <class C> self_t& operator/=(const C& c){
      return detail::div_assign(*this, c);
    }
    self_t& operator-=(const self_t& c){
      return detail::sub_assign(*this, c);
    }
    self_t& operator+=(const self_t& c){
      return detail::add_assign(*this, c);
    }
    self_t operator-() const{
      self_t result;
      return detail::sub_assign(result, *this);
    }
  private:
    rep_t rep;
  };
  ////////////////////////////////////////////////////////////
  //
  //  Binary arithmetic.
  //
  //  \date      Wed Mar  6 11:36:33 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
  template <int N, class C> Vec<N> operator*(const Vec<N>& A, const C& c){
    Vec<N> result(A);
    return result *= c;
  }
  template <int N, class C> Vec<N> operator*( const C& c, const Vec<N>& A){
    Vec<N> result(A);
    return result *= c;
  }
  template <int N> Vec<N> operator*( const Vec<N>& A, const Vec<N>& B){
    Vec<N> result(A);
    return result *= B;
  }
  template <int N, class C> Vec<N> operator/(const Vec<N>& A, const C& c){
    Vec<N> result(A);
    return result /= c;
  }
  template <int N> Vec<N> operator+( const Vec<N>& A, const Vec<N>& B){
    Vec<N> result(A);
    return result += B;
  }
  template <int N> Vec<N> operator-( const Vec<N>& A, const Vec<N>& B){
    Vec<N> result(A);
    return result -= B;
  }
}

#endif /* _VECTOR_H_ */
