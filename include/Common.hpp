#ifndef _COMMON_H_
#define _COMMON_H_

namespace sun {
  ////////////////////////////////////////////////////////////
  //
  //  Base class for fixed-length Vector and Matrix types.
  //
  //  \date      Wed Mar 13 13:49:03 2013
  //  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
  template <int N, class C> struct Base {
    typedef typename veclike::Veclike< std::tr1::array<complex, N>,
                                       veclike::DefaultConstruct, C > type;
  };
}

#endif /* _COMMON_H_ */
