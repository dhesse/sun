#include <gtest/gtest.h>
#include <SUN.hpp>
#include <Vector.hpp>
#include <Helper.hpp>
#include <iostream>

using namespace sun;


TEST(Arithmetic, UnaryOp){
  Vec<3> A = rvec<3>(), B(A), C(A), D(A);
  B += A;
  C *= 2;
  D -= -A;
  ASSERT_TRUE(almost_equal(B, C));
  ASSERT_TRUE(almost_equal(B, D));
  C -= A;
  ASSERT_TRUE(almost_equal(A, C));
  B += -A;
  ASSERT_TRUE(almost_equal(A, B));
  D /= 2;
  ASSERT_TRUE(almost_equal(A, D));
}

TEST(Arithemtic, BinaryOp){
  Vec<3> A(rvec<3>()), B, C, D(A), E(A);
  // binary plus
  B = A + A;
  C = B + A;
  D *= 2;
  E *= 3;
  ASSERT_TRUE(almost_equal(D, B));
  ASSERT_TRUE(almost_equal(E, C));
  // binary minus
  B = C - B;
  C = D - A;
  ASSERT_TRUE(almost_equal(A, B));
  ASSERT_TRUE(almost_equal(A, C));
  // binary *
  B = 2 * A;
  C = A * 3;
  ASSERT_TRUE(almost_equal(D, B));
  ASSERT_TRUE(almost_equal(E, C));
  // binary /
  D = B / 2;
  ASSERT_TRUE(almost_equal(A, D));
}

TEST(Arithemtic, SU3xSU3UnaryKnownValues){
  typedef SU<3>::data_t cplx;
  SU<3> A;
  Vec<3> B,C,D, c, d;
  A(0,0) = cplx(0.4345449218950541,0.8286981174269157);
  A(0,1) = cplx(0.7800575088725352,0.5278863538419249);
  A(0,2) = cplx(0.4037919141879485,0.8766486860564826);
  A(1,0) = cplx(0.7613361914597401,0.5737853054338109);
  A(1,1) = cplx(0.0047498345374353,0.3057298640897348);
  A(1,2) = cplx(0.3084462431246160,0.2071130644912248);
  A(2,0) = cplx(0.3184610547651320,0.5497568360165798);
  A(2,1) = cplx(0.2745763885939049,0.9385030750385526);
  A(2,2) = cplx(0.3859744531241527,0.8097994874337767);
  B(0) = cplx(0.6666365067444182,0.4467844538933093);
  B(1) = cplx(0.1927885320987969,0.0472557423612687);
  B(2) = cplx(0.4407834268548740,0.9242650376333604);
  C(0) = cplx(-0.3286523585512720,1.4298511883400578);
  C(1) = cplx(-0.4757652400775161,1.4270495093303119);
  C(2) = cplx(-0.6511511681039593,1.5330077330396104);
  D(0) = cplx(-0.5873963936635341,1.6448439264573416);
  D(1) = cplx(0.1821749944298213,1.1582031596623095);
  D(2) = cplx(-0.6030777348862389,1.4163682520239456);
  c = detail::mul(B, A);
  d = detail::mul(A, B);
  ASSERT_TRUE(almost_equal(c, C));
  ASSERT_TRUE(almost_equal(d, D));
}
