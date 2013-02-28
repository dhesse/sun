#include <gtest/gtest.h>
#include <SUN.hpp>
#include <Helper.hpp>

using namespace sun;

TEST(Arithmetic, UnaryOp){
  SU<3> A = rsu<3>(), B(A), C(A), D(A);
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

TEST(Arithemtic, SU3xSU3UnariKnownValues){
  typedef SU<3>::data_t cplx;
  SU<3> A, B, C;
  A(0,0) = cplx(0.4960685627719248,0.9214494246201619);
  A(0,1) = cplx(0.6739050298879316,0.7863386650012856);
  A(0,2) = cplx(0.4700369768597230,0.3354264593278846);
  A(1,0) = cplx(0.1850169119206341,0.8853934478058721);
  A(1,1) = cplx(0.5834826461018613,0.3893594694931147);
  A(1,2) = cplx(0.8933915486039109,0.4682040508316970);
  A(2,0) = cplx(0.1561510981620575,0.6173956636089984);
  A(2,1) = cplx(0.1921556384507118,0.2527338523372648);
  A(2,2) = cplx(0.8770937485783085,0.3845908156005826);
  B(0,0) = cplx(0.8249759086597955,0.6410888229856085);
  B(0,1) = cplx(0.6320807808219280,0.2374914231626668);
  B(0,2) = cplx(0.5987286933157685,0.4733398321806416);
  B(1,0) = cplx(0.3282132678134630,0.5735965081585628);
  B(1,1) = cplx(0.0313121058494649,0.0696567794292429);
  B(1,2) = cplx(0.3195668937470143,0.5284098442743209);
  B(2,0) = cplx(0.1657894400159358,0.6026822962913432);
  B(2,1) = cplx(0.8846644362365872,0.7846783516964337);
  B(2,2) = cplx(0.4913306104240707,0.3632510056909927);
  C(0,0) = cplx(-0.5355712757237816,2.0617270716241936);
  C(0,1) = cplx(0.2136697518794662,1.4373741740747992);
  C(0,2) = cplx(-0.2302000319914724,1.7294397682885521);
  C(1,0) = cplx(-0.5808732423642086,1.9275716480327716);
  C(1,1) = cplx(0.3207829756846389,1.7716437788982669);
  C(1,2) = cplx(-0.0587216693641852,1.6049990670989640);
  C(2,0) = cplx(-0.4352569848349135,1.3949836495277306);
  C(2,1) = cplx(0.4146396640813071,1.4770973457034744);
  C(2,2) = cplx(0.0203537144416228,1.1334337631054769);
  A *= B;
  ASSERT_TRUE(almost_equal(A, C));
}

TEST(Arithemtic, BinaryOp){
}
