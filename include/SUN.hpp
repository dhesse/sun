#ifndef SUN_H
#define SUN_H
#include <cplx.hpp>
#include <tr1/array>
#include <complex>

#define SUN_NO_EXTEMP

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
    ////////////////////////////////////////////////////////////
    //
    //  Base class for Matrix expression templates using the curiously
    //  recurring template pattern.
    //
    //  \date      Fri Mar  1 14:30:16 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <class C, int N> class MatrixExpression {
    public:
      //  Choose wich complex type to use. We give the user the choice
      //  to use either std::complex<double> or our own naive
      //  implementation. The latter is faster (unless you compile using
      //  the -ffast-math option), the reason for which is that any
      //  naive implementation will NOT conform with the IEEE and ISO
      //  standards. Doing so will slow down the code.
      //typedef std::complex<double> data_t; // IEEE conformal
      typedef complex data_t; // Custom implementation
      typedef std::tr1::array<data_t, N*N> rep_t;
      data_t operator()(int i, int j) const {
	return (static_cast<const C&>(*this))(i, j);
      }
      data_t operator()(int i) const {
	return (static_cast<const C&>(*this))(i);
      }
      operator C&() { return static_cast<C&>(*this); }
      operator C const&() const { return static_cast<const C&>(*this); }
    };
    ////////////////////////////////////////////////////////////
    //
    //  Expression template for matrix product.
    //
    //  \date      Fri Mar  1 14:31:23 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <class C1, class C2, int N> class MatrixProduct :
      public MatrixExpression<MatrixProduct<C1, C2, N>, N>{
    public:
      typedef typename
      MatrixExpression<MatrixProduct<C1, C2, N>, N>::data_t data_t;
      MatrixProduct(const MatrixExpression<C1, N>& aa,
		    const MatrixExpression<C2, N>& bb) : a(aa), b(bb){ };
      data_t operator()(int i, int j) const {
	data_t tmp = 0;
	for (int k = 0; k < N; ++k)
	  tmp += a(i, k) * b(k, j);
	return tmp;
      }
      data_t operator()(int l) const {
	data_t tmp = 0;
	int i = l / N, j = l % N;
	for (int k = 0; k < N; ++k)
	  tmp += a(i, k) * b(k, j);
	return tmp;
      }
    private:
      const C1& a;
      const C2& b;
    };
    ////////////////////////////////////////////////////////////
    //
    //  Expression template for product with number.
    //
    //  \date      Fri Mar  1 15:00:20 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <class C1, class C2, int N> class ScaledMatrix :
      public MatrixExpression<ScaledMatrix<C1, C2, N>, N>
    {
    public:
      typedef typename
      MatrixExpression<ScaledMatrix<C1, C2, N>, N>::data_t data_t;
      ScaledMatrix(const C1& aa, const MatrixExpression<C2, N>& bb) :
	a(aa), b(bb){ };
      data_t operator()(int i, int j) const { return impl(i,j,a); }
      data_t operator()(int i) const { return impl(i,a); }
    private:
      // make sure this only gets called for int, double, and complex
      data_t impl(int i, int j, int) const { return a*b(i,j); }
      data_t impl(int i, int j, double) const { return a*b(i,j); }
      data_t impl(int i, int j, data_t) const { return a*b(i,j); }
      data_t impl(int i, int) const { return b(i)*(double)a; }
      data_t impl(int i, double) const { return a*b(i); }
      data_t impl(int i, data_t) const { return a*b(i); }
      const C1& a;
      const C2& b;
    };
    ////////////////////////////////////////////////////////////
    //
    //  Expression template for dagger.
    //
    //  \date      Fri Mar  1 16:26:01 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <class C, int N> class MatrixDagger :
      public MatrixExpression<MatrixDagger<C, N>, N>
    {
    public:
      typedef typename
      MatrixExpression<MatrixDagger<C, N>, N>::data_t data_t;
      MatrixDagger(const MatrixExpression<C, N>& a) : a_(a) { }
      data_t operator()(int i, int j) const { return conj(a_(j,i)); }
      data_t operator()(int i) const { return conj(a_((i % N)*N + i/N)); }
    private:
      const C& a_;
    };
  }
  template <int N> class SU : public detail::MatrixExpression<SU<N>, N> {
  public:
    typedef SU self_t;
    typedef typename detail::MatrixExpression<SU, N>::data_t data_t;
    typedef typename detail::MatrixExpression<SU, N>::rep_t rep_t;
    ////////////////////////////////////////////////////////////
    //
    //  Construct from MatrixExpression
    //
    //  \date      Fri Mar  1 11:01:15 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <class E>
    SU ( const detail::MatrixExpression<E, N>& A) : rep() {
      for (int i = 0; i < N*N; ++i) rep[i] = A(i);
    }
    ////////////////////////////////////////////////////////////
    //
    //  Default constructor.
    //
    //  \date      Fri Mar  1 11:04:26 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    SU () : rep() { }
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
#ifdef SUN_NO_EXTEMP
    self_t dag() const{
      self_t result;
      for (int i = 0; i < N; ++i)
    	for (int j = 0; j < N; ++j)
    	  result(i, j) = conj((*this)(j, i));
      return result;
    }
#else
    detail::MatrixDagger<SU, N> dag() const{
      return detail::MatrixDagger<SU, N>(*this);
    }
#endif
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
#ifdef SUN_NO_EXTEMP
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
#else
  template <class C, int N>
  detail::ScaledMatrix<int, C, N> operator*
  (const int& a, const detail::MatrixExpression<C, N>& A){
    return detail::ScaledMatrix<int, C, N>(a, A);
  }
  template <class C, int N>
  detail::ScaledMatrix<double, C, N> operator*
  (const double& a, const detail::MatrixExpression<C, N>& A){
    return detail::ScaledMatrix<double, C, N>(a, A);
  }
  template <class C, int N>
  detail::ScaledMatrix<typename SU<N>::data_t, C, N> operator*
  (const typename SU<N>::data_t& a, const detail::MatrixExpression<C, N>& A){
    return detail::ScaledMatrix<typename SU<N>::data_t, C, N>(a, A);
  }
  template <class C, int N>
  detail::ScaledMatrix<int, C, N> operator*
  (const detail::MatrixExpression<C, N>& A, const int& a){
    return detail::ScaledMatrix<int, C, N>(a, A);
  }
  template <class C, int N>
  detail::ScaledMatrix<double, C, N> operator*
  (const detail::MatrixExpression<C, N>& A, const double& a){
    return detail::ScaledMatrix<double, C, N>(a, A);
  }
  template <class C, int N>
  detail::ScaledMatrix<typename SU<N>::data_t, C, N> operator*
  (const detail::MatrixExpression<C, N>& A, const typename SU<N>::data_t& a){
    return detail::ScaledMatrix<typename SU<N>::data_t, C, N>(a, A);
  }
  template <class C1, class C2, int N>
  detail::MatrixProduct<C1, C2, N> operator*
  (const detail::MatrixExpression<C1, N>& A,
   const detail::MatrixExpression<C2, N>& B) {
    return detail::MatrixProduct<C1, C2, N>(A, B);
  }
#endif
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
