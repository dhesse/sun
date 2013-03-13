#ifndef CPLX_H
#define CPLX_H
#include <cmath>

////////////////////////////////////////////////////////////
//
//  Naive complex class. Note that this class is for testing purposes
//  only and does not conform to all ISO and IEEE standards. It is,
//  however faster than std::complex<double> if one does not use the
//  -ffast-math compiler option.
//
//  \date      Fri Mar  1 10:03:19 2013
//  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>
struct complex {
  double r, i;
  complex () : r(0), i(0) { }
  complex (const double& j, const double& k) : r(j), i(k)  { }
  complex (const int& a) : r(a), i(0) {}
  complex (const double& a) : r(a), i(0) {}
  bool operator==(const complex& other) const {
    return (r == other.r) && (i == other.i);
  }
  double& real() { return r; }
  const double& real() const { return r; }
  double& imag() { return i; }
  const double& imag() const { return i; }
  complex& operator+=(const double& other){
    r += other;
    return *this;
  }
  complex& operator-=(const double& other){
    r -= other;
    return *this;
  }
  complex& operator+=(const complex& other){
    r += other.r;
    i += other.i;
    return *this;
  }
  complex& operator-=(const complex& other){
    r -= other.r;
    i -= other.i;
    return *this;
  }
  template <class C> complex& operator*=(const C& other){
    r *= other;
    i *= other;
    return *this;
  }
  template <class C> complex& operator/=(const C& other){
    r /= other;
    i /= other;
    return *this;
  }
  complex& operator*=(const complex& other){
    double r, i;
    r = this->r * other.r - this->i * other.i;
    i = this->i * other.r + this->r * other.i;
    this->r = r;
    this->i = i;
    return *this;
  }
  complex& operator/=(const complex& other){
    double t = other.r*other.r + other.i*other.i;
    double r = (this->r * other.r + this->i*other.i)/t;
    double i = (this->i * other.r - this->r*other.i)/t;
    this->r = r;
    this->i = i;
    return *this;
  }
  complex operator-() const{ return complex(-r, -i); }
  complex conj() const { return complex(r, -i); }
  double norm() const { return r*r + i*i; }
  double abs() const { return std::sqrt(r*r + i*i); }
};

inline complex conj(const complex& c){ return c.conj(); }
inline double abs(const complex& c){ return c.abs(); }
inline double norm(const complex& c){ return c.norm(); }
inline complex exp(const complex& c){
  double tmp = std::exp(c.r);
  return complex(std::cos(c.i)*tmp, std::sin(c.i)*tmp);
}

////////////////////////////////////////////////////////////
//
//  Binary ops
//
//  \date      Thu Feb 28 20:34:10 2013
//  \author    Dirk Hesse <dirk.hesse@fis.unipr.it>

template <class C> inline complex operator+(const C& a, const complex& b){
  return complex(b) += a;
}
template <class C> inline complex operator+(const complex& b, const C& a){
  return complex(b) += a;
}
template <class C> inline complex operator-(const C& a, const complex& b){
  return complex(-b) += a;
}
template <class C> inline complex operator-(const complex& b, const C& a){
  return complex(b) -= a;
}
inline complex operator*(const int& a, const complex& b){
  return complex(b) *= a;
}
inline complex operator*(const complex& b, const int& a){
  return complex(b) *= a;
}
inline complex operator*(const double& a, const complex& b){
  return complex(b) *= a;
}
inline complex operator*(const complex& b, const double& a){
  return complex(b) *= a;
}
template <class C> inline complex operator/(const C& a, const complex& other){
  double t = other.r*other.r + other.i*other.i;
  return complex(a * other.r / t, a * other.i / t);
}
template <class C> inline complex operator/(const complex& b, const C& a){
  return complex(b) /= a;
}
inline complex operator/(const complex& a, const complex& b){
  return complex(a) /= b;
}
inline complex operator*(const complex& a, const complex& b){
  return complex(a) *= b;
}
inline complex operator+(const complex& a, const complex& b){
  return complex(a) += b;
}
inline complex operator-(const complex& a, const complex& b){
  return complex(a) -= b;
}

#endif
