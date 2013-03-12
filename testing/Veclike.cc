#include <gtest/gtest.h>
#include <Veclike.hpp>
#include <Helper.hpp>
#include <iostream>
#include <vector>

using namespace veclike;


TEST(Arithmetic, UnaryOp){
  typedef std::vector<double> Container;
  typedef GenWithSize<Container> Generator;
  typedef Veclike<Container, GenWithSize> Vec;
  Generator a(10);
  Vec A(a);
  randomize(A);
  Vec B(A), C(A), D(A);
  B += A;
  C *= 2;
  //D -= -A;
  ASSERT_TRUE(near(B, C));
  //ASSERT_TRUE(near(B, D));
  C -= A;
  ASSERT_TRUE(near(A, C));
  //B += -A;
  //ASSERT_TRUE(near(A, B));
  //D /= 2;
  //ASSERT_TRUE(near(A, D));
}

struct foo : public Veclike<std::vector<double>, GenWithSize> {
  foo(const GenWithSize<std::vector<double> >& g) :
    Veclike<std::vector<double>, GenWithSize>(g) { }
};

TEST(Arithmetic, UnaryOpInherited){
  typedef std::vector<double> Container;
  typedef GenWithSize<Container> Generator;
  Generator a(10);
  foo A(a);
  randomize(A);
  foo B(A), C(A), D(A);
  B += A;
  C *= 2;
  //D -= -A;
  ASSERT_TRUE(near(B, C));
  //ASSERT_TRUE(near(B, D));
  C -= A;
  ASSERT_TRUE(near(A, C));
}
