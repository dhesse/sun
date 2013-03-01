#ifndef SUN_H
#define SUN_H
#include <cplx.hpp>
#include <tr1/array>

namespace sun {

  template <int N> class SU;

  namespace detail {
    template <int N> SU<N> mul( const SU<N>& A, const SU<N>& B ){
      SU<N> C;
      for (int i = 0; i< N; ++i)
	for (int j = 0; j < N; ++j)
	  for (int k = 0; k < N; ++k)
	    C(i,j) += A(i,k)*B(k,j);
      return C;
    }
    template <int N> SU<N>& add_assign( SU<N>& A, const SU<N>& B ){
      for (int i = 0; i < N*N; ++i)
	A(i) += B(i);
      return A;
    }
    template <int N> SU<N>& sub_assign( SU<N>& A, const SU<N>& B ){
      for (int i = 0; i < N*N; ++i) A(i) -= B(i);
      return A;
    }
    template <int N, class C> SU<N>& mul_assign(SU<N>& A, const C& c) {
      for (int i = 0; i < N*N; ++i) A(i) *= c;
      return A;
    }
    template <int N, class C> SU<N>& div_assign(SU<N>& A, const C& c) {
      for (int i = 0; i < N*N; ++i) A(i) /= c;
      return A;
    }
  }

  template <int N> class SU {
  public:
    typedef SU self_t;
    ////////////////////////////////////////////////////////////
    //
    //  Choose wich complex type to use. We give the user the choice
    //  to use either std::complex<double> or our own naive
    //  implementation. The latter is faster (unless you compile using
    //  the -ffast-math option), the reason for which is that any
    //  naive implementation will NOT conform with the IEEE and ISO
    //  standards. Doing so will slow down the code.
    //
    //  \date      Fri Mar  1 09:58:24 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    //typedef std::complex<double> data_t; // IEEE conformal
    typedef complex data_t; // Custom implementation
    typedef std::tr1::array<data_t, N*N> rep_t;
    ////////////////////////////////////////////////////////////
    //
    //  Element access. Note that tere is no range-checking.
    //
    //  \date      Thu Feb 28 15:53:19 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    data_t& operator()(int i, int j){ return rep[i*N + j]; }
    const data_t& operator()(int i, int j) const { return rep[i*N + j]; }
    data_t& operator()(int i){ return rep[i]; }
    const data_t& operator()(int i) const { return rep[i]; }
    ////////////////////////////////////////////////////////////
    //
    //  Arihmetics. The implemtations are in detail.
    //
    //  \date      Thu Feb 28 15:53:41 2013
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
    ////////////////////////////////////////////////////////////
    //
    //  'Special' functions like trace, dagger.
    //
    //  \date      Thu Feb 28 17:32:16 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    data_t tr() const{
      data_t tmp = 0;
      for (int i = 0; i < N; ++i) tmp += rep[i*N +i];
      return tmp;
    }
    self_t dag() const{
      self_t result;
      for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j)
	  result(i, j) = conj((*this)(j, i));
      return result;
    }
    double norm() const{
      double tmp = 0;
      for (int i = 0; i < N; ++i) tmp += abs(rep[i]);
      return tmp;
    }
  private:
    rep_t rep;
  };
  ////////////////////////////////////////////////////////////
  //
  //  Binary arithmetic.
  //
  //  \date      Thu Feb 28 16:50:49 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>

  template <int N, class C> SU<N> operator*(const SU<N>& A, const C& c){
    SU<N> result(A);
    return result *= c;
  }
  template <int N, class C> SU<N> operator*( const C& c, const SU<N>& A){
    SU<N> result(A);
    return result *= c;
  }
  template <int N> SU<N> operator*( const SU<N>& A, const SU<N>& B){
    SU<N> result(A);
    return result *= B;
  }
  template <int N, class C> SU<N> operator/(const SU<N>& A, const C& c){
    SU<N> result(A);
    return result /= c;
  }
  template <int N> SU<N> operator+( const SU<N>& A, const SU<N>& B){
    SU<N> result(A);
    return result += B;
  }
  template <int N> SU<N> operator-( const SU<N>& A, const SU<N>& B){
    SU<N> result(A);
    return result -= B;
  }
  template <class R> SU<3> SU3rand(R& Rand){
    SU<3> result;
    typedef SU<3>::data_t cplx;
    static double twopi = std::atan(1.0) * 8.0;
    static double soneo3 = std::sqrt( 1./ 3);
    double g[8], r, t;
    // get flat distribution
    Rand.ranlxd(g, g+8);
    // make gaussian
    for (int i = 0; i < 8; i+=2){
      t = twopi*g[i];
      r = std::sqrt( -std::log((1. - g[i+1])) );
      g[i]   = r*std::cos(t);
      g[i+1] = r*std::sin(t);
    }
    g[7] *= soneo3;

    result(0) = cplx(0,g[7]+g[6]);
    result(1) = cplx(g[1],g[0]);
    result(2) = cplx(g[3],g[2]);
    result(3) = cplx(-g[1],g[0]);
    result(4) = cplx(0,g[7]-g[6]);
    result(5) = cplx(g[5],g[4]);
    result(6) = cplx(-g[3],g[2]);
    result(7) = cplx(g[4],-g[5]);
    result(8) = cplx(0,-g[7]*2);
    return result;
  }
}
#endif
