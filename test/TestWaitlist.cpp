#include "Waitlist.h"
#include "Order.h"
#include "gtest/gtest.h"

TEST(TestWaitlist, addOrderTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);
  Order* o1 = nullptr;

  EXPECT_NO_THROW(wl->addOrder(o));
  EXPECT_THROW(wl->addOrder(o1), invalid_parameter_error);

  delete wl;
  delete w;
  delete o;
  delete o1;
}
TEST(TestWaitlist, removeOrderTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);
  Order* o1 = nullptr;

  wl->addOrder(o);
  EXPECT_EQ(wl->size(), 1);
  EXPECT_NO_THROW(wl->removeOrder(o));
  EXPECT_EQ(wl->size(), 0);
  EXPECT_THROW(wl->addOrder(o1), invalid_parameter_error);

  delete wl;
  delete w;
  delete o;
  delete o1;
}
TEST(TestOrder, testCheckAll) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);

  wl->addOrder(o);
  EXPECT_EQ(wl->size(), 1);
  wl->checkAll();
  EXPECT_EQ(wl->size(), 0);

  delete wl;
  delete w;
  delete o;
}
