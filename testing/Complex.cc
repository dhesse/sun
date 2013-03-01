#include <gtest/gtest.h>
#include <cplx.hpp>
#include <Helper.hpp>

complex rnd(){ return complex(1.*rand()/RAND_MAX, 1.*rand()/RAND_MAX); }

TEST(Arithmetic, UnaryOp){
  complex a(rnd()), b(a), c(a);
  b += a;
  c *= 2;
  ASSERT_CPLX_EQ(c, b);
  c -= a;
  b /= 2;
  ASSERT_CPLX_EQ(c, b);
  b += a;
  b += -a;
  ASSERT_CPLX_EQ(c, b);
  b *= a;
  b /= a;
  ASSERT_CPLX_EQ(a, b);
}

TEST(Arithmetic, BinaryOp){
  complex a(rnd()), b(a), c(a);
  b = a + a;
  c = 2 * a;
  ASSERT_CPLX_EQ(c, b);
  c = c - a;
  b = b / 2;
  ASSERT_CPLX_EQ(c, b);
  b = a*a;
  b = b/a;
  ASSERT_CPLX_EQ(a, b);
}

TEST(Arithmetic, UnaryFuncs){
  complex a(rnd()), b, c;
  b = conj(a);
  c = complex(a.r, -a.i);
  ASSERT_CPLX_EQ(c, b);
  double n = a.abs();
  ASSERT_EQ(n, std::sqrt(a.r*a.r + a.i*a.i));
  ASSERT_DOUBLE_EQ(a.norm(), a.abs()*a.abs());
  ASSERT_EQ(abs(a),a.abs());
  ASSERT_EQ(norm(a),a.norm());
  ASSERT_CPLX_EQ(conj(a),a.conj());
  double e = std::exp(a.r);
  ASSERT_CPLX_EQ(exp(a), complex(e*std::cos(a.i), e*std::sin(a.i)));
}
