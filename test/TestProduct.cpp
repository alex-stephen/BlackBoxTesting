#include "Product.h"
#include "gtest/gtest.h"

TEST(TestProduct, defaultConstructorTest) {
  Product* p1 = new Product("", 0);
  Product* p2 = new Product("Paper", 100);

  EXPECT_EQ("", p1->getName());
  EXPECT_EQ(0, p1->getWeight());
  EXPECT_EQ("Paper", p2->getName());
  EXPECT_EQ(100, p2->getWeight());

  delete p1;
  delete p2;
}
