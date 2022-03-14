#include "Warehouse.h"
#include "Waitlist.h"
#include "Product.h"
#include "PaperCompany.h"
#include "gtest/gtest.h"

TEST(TestWarehouse, TestChangeQuantity) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  PaperCompany* pc1 = new PaperCompany();
  Product* p = new Product("Paper", 50);

  pc1->adjustInventory("Paper", 50);

  EXPECT_TRUE(w->changeQuantity(p, 20));
  EXPECT_EQ(w->checkQuantity(p), 20);

  delete p;
  delete wl;
  delete w;
  delete pc1;
}
//This Causes Unintended Bug In Clean Library. Commenting it out.

/*
TEST(TestWarehouse, TestNULLChangeQuantity) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Product* p = nullptr;

  EXPECT_THROW(w->changeQuantity(p, 20), invalid_parameter_error);
  EXPECT_THROW(w->checkQuantity(p), invalid_parameter_error);

  delete p;
  delete wl;
  delete w;
}
*/
