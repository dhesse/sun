#ifndef _VECLIKE_H_
#define _VECLIKE_H_
namespace veclike {
  namespace detail {
    // Helper classes
    struct True {};
    struct False {};
    ////////////////////////////////////////////////////////////
    //
    //  This struct decideds if a scalar multiplication is desired or
    //  not.
    //
    //  \date      Tue Mar 12 21:33:44 2013
    //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
    template <typename T> struct ScalarMultiplyCheck { typedef False type; };
    template <> struct ScalarMultiplyCheck<int> { typedef True type; };
    template <> struct ScalarMultiplyCheck<double> { typedef True type; };
  }
  template <class Container> struct DefaultConstruct {
    static Container gen_default() { return Container(); }
  };
  template <class Container> struct GenWithSize {
    static Container gen_default() { return Container(); }
    GenWithSize(int i) : size(i) { }
    Container gen() const { return Container(size); }
    int size;
  };
  ////////////////////////////////////////////////////////////
  //
  //  Base class for vector-like objects. A vector-like object wraps
  //  around a container and provides some basic arithmetic for it,
  //  such as multiplication by a scalar (int, double, complex), as
  //  well as addition and subtraction operations.
  //
  //  \Date      Tue Mar 12 21:25:23 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
  template <class Container, template <class> class Creator> class Veclike {
  public:
    typedef Veclike self_t;
    typedef typename Container::value_type value_t;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    Veclike() : rep(Creator<Container>::gen_default()) { }
    explicit Veclike(const Creator<Container>& creator) : rep(creator.gen()) { }

    reference operator[](int i){ return rep[i]; }
    const_reference operator[](int i) const { return rep[i]; }

    iterator begin(){ return rep.begin(); }
    iterator end(){ return rep.end(); }
    const_iterator begin() const { return rep.begin(); }
    const_iterator end() const { return rep.end(); }

    template <typename T> self_t& operator*=(const T& other){
      return mul_assign_impl(other,
                             typename detail::ScalarMultiplyCheck<T>::type());
    }
     template <typename T> self_t& operator/=(const T& other){
       return div_assign_impl(other,
                              typename detail::ScalarMultiplyCheck<T>::type());
    }
    self_t& operator+=(const self_t& other){
      for (int i = 0; i < rep.size(); ++i) rep[i] += other[i];
      return *this;
    }
    self_t& operator-=(const self_t& other){
      for (int i = 0; i < rep.size(); ++i) rep[i] -= other[i];
      return *this;
    }
  private:
    Container rep;
    template <typename T> self_t& mul_assign_impl(const T& other, detail::True){
#ifdef __GXX_EXPERIMENTAL_CXX0X__
      for (auto &i : rep) i *= other;
#else
      for (int i = 0; i < rep.size(); ++i) rep[i] *= other;
#endif
      return *this;
    }
    template <typename T> self_t& div_assign_impl(const T& other, detail::True){
#ifdef __GXX_EXPERIMENTAL_CXX0X__
      for (auto &i : rep) i /= other;
#else
      for (int i = 0; i < rep.size(); ++i) rep[i] /= other;
#endif
      return *this;
    }
  };
}
#endif /* _VECLIKE_H_ */
