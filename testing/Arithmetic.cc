#include <gtest/gtest.h>
#include <SUN.hpp>
#include <Helper.hpp>
#include <iostream>

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

TEST(Arithemtic, SU3xSU3UnaryKnownValues){
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
  SU<3> A(rsu<3>()), B, C, D(A), E(A);
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

TEST(Arithemtic, SU3xSU3BinaryKnownValues){
  typedef SU<3>::data_t cplx;
  SU<3> A, B, C;
  A(0,0) = cplx(0.2606954494779902,0.7515623678671419);
  A(0,1) = cplx(0.4394557818162318,0.2152913572485954);
  A(0,2) = cplx(0.7718736615638118,0.0104681449718826);
  A(1,0) = cplx(0.6667602233432361,0.8389396254606404);
  A(1,1) = cplx(0.5674700136088885,0.7895213788884105);
  A(1,2) = cplx(0.6463149160374417,0.5808529952655967);
  A(2,0) = cplx(0.8644954214034205,0.1009180558707581);
  A(2,1) = cplx(0.7034635360937371,0.3243516125912830);
  A(2,2) = cplx(0.1563310227759446,0.8233208900519653);
  B(0,0) = cplx(0.7712229315723130,0.4360523258371555);
  B(0,1) = cplx(0.3728509506021059,0.2793251899939322);
  B(0,2) = cplx(0.1722697982524467,0.4825089779571052);
  B(1,0) = cplx(0.9119442787765776,0.3921295006942548);
  B(1,1) = cplx(0.6154265218205699,0.0182918297023662);
  B(1,2) = cplx(0.4266606560166215,0.1113236300121733);
  B(2,0) = cplx(0.6863825916791068,0.7827141246910936);
  B(2,1) = cplx(0.6515611806857390,0.7662612574477288);
  B(2,2) = cplx(0.0035775367111948,0.5583433884724550);
  C(0,0) = cplx(0.7112779631989550,1.6732978573585715);
  C(0,1) = cplx(0.6486864957520949,1.0918515301424008);
  C(0,2) = cplx(-0.1572775739168158,0.8270455627954265);
  C(1,0) = cplx(0.3452830707275890,2.7848402591249650);
  C(1,1) = cplx(0.3250880821694159,1.8690221675491019);
  C(1,2) = cplx(-0.4577117239264309,1.2292159683805650);
  C(2,0) = cplx(0.5999228541938902,1.7139105866069411);
  C(2,1) = cplx(0.1921164425995772,1.1478192981805977);
  C(2,2) = cplx(-0.0948716968594163,0.7414439752715860);
  ASSERT_TRUE(almost_equal(C, A*B, 10));
}

TEST(Arithmetic, Associativity){
  SU<4> A(rsu<4>()), B(rsu<4>()), C(rsu<4>());
  ASSERT_TRUE(almost_equal(A * (B * C), (A * B) * C, 9));
  ASSERT_TRUE(almost_equal(A + (B + C), (A + B) + C, 9));
}

TEST(Arithmetic, dagger){
  SU<4> A(rsu<4>()), B(A.dag()), C;
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      C(i, j) = conj(A(j, i));
  ASSERT_TRUE(equal(C,B));
}

TEST(Arithmetic, trace){
  SU<4> A(rsu<4>());
  SU<4>::data_t known = A(0,0) + A(1,1) + A(2,2) + A(3,3);
  ASSERT_CPLX_EQ(known, A.tr());
}

TEST(ExpressionTemplates, Product){
  SU<3> A(rsu<3>()), B(rsu<3>()), C = A*B;
  SU<3> D(detail::MatrixProduct<SU<3>, SU<3>, 3>(A,B));
  ASSERT_TRUE(almost_equal(D,C));
}

TEST(ExpressionTemplates, TripleProduct){
  typedef detail::MatrixProduct<SU<3>, SU<3>, 3> mp;
  typedef detail::MatrixProduct<mp, SU<3>, 3> mpp;
  SU<3> A(rsu<3>()), B(rsu<3>()), C(rsu<3>()), D = A*B*C;
  SU<3> E = mpp(mp(A, B), C);
  ASSERT_TRUE(almost_equal(D, E));
}

TEST(ExpressionTemplates, Scale){
  typedef detail::ScaledMatrix<double, SU<3>, 3> scm;
  SU<3> A(rsu<3>()), B(scm(1.5, A));
  ASSERT_TRUE(almost_equal(B, A*1.5));
}
