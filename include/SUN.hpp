////////////////////////////////////////////////////////////
//
//  File: SUN.hpp
//
//  Here, I implement a generic NxN complex matrix arithmetic. I named
//  the classes SU(N), because we will use it for SU(N) matrices, but
//  one may use them for any generic complex square matrix.
//
//  \date      Wed Mar  6 11:10:42 2013
//  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
#ifndef SUN_H
#define SUN_H
#include <cplx.hpp>
#include <tr1/array>
#include <complex>
#include <Veclike.hpp>
#include <Common.hpp>

namespace sun {

  template <int N> class SU;

  namespace detail {
    ////////////////////////////////////////////////////////////
    //
    //  Implementation of SU(N) arithmetic
    //
    //  \date      Wed Mar  6 11:10:17 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <int N> SU<N> mul( const SU<N>& A, const SU<N>& B ){
      SU<N> C;
      for (int i = 0; i< N; ++i)
	for (int j = 0; j < N; ++j)
	  for (int k = 0; k < N; ++k)
	    C(i,j) += A(i,k)*B(k,j);
      return C;
    }
  }
  ////////////////////////////////////////////////////////////
  //
  //  SU(N) class template
  //
  //  \date      Wed Mar  6 11:09:06 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
  template <int N> class SU : public Base<N*N, SU<N> >::type {
  public:
    typedef SU self_t;
    static const int rep_size = N*N;
    static const int size = N;
    typedef typename Base<N*N, SU<N> >::type base_t;
    typedef typename base_t::value_t data_t;
    using typename base_t::iterator;
    using typename base_t::const_iterator;

    SU(const base_t& other) : base_t(other) { }
    SU() { }
    ////////////////////////////////////////////////////////////
    //
    //  Element access. Note that tere is no range-checking.
    //
    //  \date      Thu Feb 28 15:53:19 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    data_t& operator()(int i, int j){ return base_t::operator[](i*N + j); }
    const data_t& operator()(int i, int j) const { 
      return base_t::operator[](i*N + j);
    }
    ////////////////////////////////////////////////////////////
    //
    //  Arihmetics. The implemtations are in detail.
    //
    //  \date      Thu Feb 28 15:53:41 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    using base_t::operator*=;
    self_t& operator*=(const self_t& A){ // overload, no specialization
      self_t tmp = detail::mul(*this, A);
      base_t::swap(tmp);
      return *this;
    }
    ////////////////////////////////////////////////////////////
    //
    //  'Special' functions like trace, dagger.
    //
    //  \date      Thu Feb 28 17:32:16 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    data_t tr() const{
      data_t tmp = 0;
      for (int i = 0; i < N; ++i) tmp += base_t::operator[](i*N +i);
      return tmp;
    }
    self_t reh() const{
      self_t result(*this);
      result -= this->dag();
      result *= .5;
      complex troN = result.tr() / N;
      for (int i = 0; i < N; ++i) result(i,i) -= troN;
      return result;
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
      for (int i = 0; i < N; ++i) tmp += abs(base_t::operator[](i));
      return tmp;
    }
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
  template <class R> SU<3> SU3rand(R& Rand){
    SU<3> result;
    typedef typename SU<3>::data_t cplx;
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

    result[0] = cplx(0,g[7]+g[6]);
    result[1] = cplx(g[1],g[0]);
    result[2] = cplx(g[3],g[2]);
    result[3] = cplx(-g[1],g[0]);
    result[4] = cplx(0,g[7]-g[6]);
    result[5] = cplx(g[5],g[4]);
    result[6] = cplx(-g[3],g[2]);
    result[7] = cplx(-g[5],g[4]);
    result[8] = cplx(0,-g[7]*2);
    return result;
  }
  template <class R> SU<2> SU2rand(R& Rand){
    SU<2> result;
    typedef typename SU<2>::data_t cplx;
    static double twopi = std::atan(1.0) * 8.0;
    double g[4], r, t;
    // get flat distribution
    Rand.ranlxd(g, g+4);
    // make gaussian
    for (int i = 0; i < 4; i+=2){
      t = twopi*g[i];
      r = std::sqrt( -std::log((1. - g[i+1])) );
      g[i]   = r*std::cos(t);
      g[i+1] = r*std::sin(t);
    }
    result(0,0) = cplx(0, g[2]);
    result(0,1) = cplx(g[1], g[0]);
    result(1,0) = cplx(-g[1], g[0]);
    result(1,1) = cplx(0, -g[2]);
    return result;
  }
}
#endif
