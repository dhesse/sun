namespace sun {
  namespace detail {
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
}
