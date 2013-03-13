#include <gtest/gtest.h>
#include <SUN.hpp>
#include <Helper.hpp>

using namespace sun;

TEST(Constructor, InitToZero){
  SU<3> A;
  for (int i = 0; i < 9; ++i){
    ASSERT_EQ(A[i].real(), 0.0);
    ASSERT_EQ(A[i].imag(), 0.0);
  }
}

TEST(Constructor, Copy){
  SU<2> A(rsu<2>()), B(A);
  ASSERT_TRUE(equal(A,B));
}

TEST(Constructor, Assign){
  SU<2> A(rsu<2>()), B = A;
  ASSERT_TRUE(equal(A,B));
}


TEST(SelfTest, rsu){
  SU<4> A(rsu<4>());
  ASSERT_NE(A(1,2).real(), 0.0);
}
