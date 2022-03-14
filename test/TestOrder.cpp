#include "Order.h"
#include "Product.h"
#include "PaperCompany.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include <string>
#include <map>
#include "gtest/gtest.h"

TEST(TestOrder, defaultConstructorTest) {
  PaperCompany* pc1 = new PaperCompany();
  Order* o = pc1->createOrder();
  Warehouse * w = o->getWH();
  Waitlist * wl = o->getWait();

  EXPECT_NO_THROW(Order(w, wl));

  delete pc1;
}
TEST(TestOrder, defaultConstructorNullWaitlistTest) {
  PaperCompany* pc1 = new PaperCompany();
  Order* o = pc1->createOrder();
  Warehouse * w = o->getWH();

  EXPECT_THROW(Order(w, nullptr), invalid_parameter_error);

  delete pc1;
}

TEST(TestOrder, defaultConstructorNullWarehouseTest) {
  PaperCompany* pc1 = new PaperCompany();
  Order* o = pc1->createOrder();
  Waitlist * wl = o->getWait();

  EXPECT_THROW(Order(nullptr, wl), invalid_parameter_error);

  delete pc1;
}

TEST(TestOrder, defaultConstructorNullTest) {
  PaperCompany* pc1 = new PaperCompany();
  Order* o = pc1->createOrder();

  EXPECT_THROW(Order(nullptr, nullptr), invalid_parameter_error);

  delete pc1;
}

TEST(TestOrder, testEditContents) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Product* p1 = new Product("Paper", 50);
  Order* o = new Order(w, wl);

  EXPECT_TRUE(o->editContents(p1, 10));

  delete p1;
  delete w;
  delete wl;
  delete o;
}

TEST(TestOrder, testIsEmpty) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Product* p1 = new Product("", 0);
  Order* o = new Order(w, wl);

  EXPECT_TRUE(o->isEmpty());

  delete p1;
  delete wl;
  delete w;
  delete o;
}
TEST(TestOrder, testInCartStatus) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Product* p1 = new Product("Paper", 50);
  Order* o = new Order(w, wl);

  o->editContents(p1, 20);
  OrderState* os = o->getStatus();

  EXPECT_EQ(o->getStatus(), os);

  delete p1;
  delete o;
  delete w;
  delete wl;
}
TEST(TestOrder, TestGetContents) {
  PaperCompany* pc1 = new PaperCompany();
  Product* p = new Product("Paper", 25);

  pc1->addProduct("Paper", 25);
  pc1->adjustInventory("Paper", 5);

  Order* o = pc1->createOrder();
  o->editContents(p, 30);

  map<Product* , int> z = o->getContents();
  EXPECT_EQ(z[p], 30);

  delete p;
  delete pc1;
}
TEST(TestOrder, testCancelPendingStatusSubmit) {
  PaperCompany* pc1 = new PaperCompany();
  Product* p = new Product("Paper", 25);

  pc1->addProduct("Paper", 25);

  Order* o = pc1->createOrder();
  pc1->addToOrders(o);

  o->editContents(p, 0);

  o->submit();
  o->cancel();
  Waitlist* wl = o->getWait();
  EXPECT_EQ(wl->size(), 0);

  delete p;
  delete pc1;
}
TEST(TestOrder, testCompleteStateSubmit) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);
  OrderState* os = o->getStatus();

  EXPECT_TRUE(os->submit(o));

  delete wl;
  delete w;
  delete o;
}
TEST(TestOrder, setShippingTruckTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);

  o->setShipping(0);
  ShippingMethod* method = o->getShipping();
  std::string name = method->name();

  EXPECT_EQ("Truck", name);

  o->setShipping(50);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Truck", name);

  o->setShipping(100);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Truck", name);

  o->setShipping(101);
  method = o->getShipping();
  name = method->name();

  EXPECT_NE("Truck", name);

  delete wl;
  delete w;
  delete o;
}

TEST(TestOrder, setShippingAirTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);

  o->setShipping(100);
  ShippingMethod* method = o->getShipping();
  std::string name = method->name();

  EXPECT_NE("Air", name);

  o->setShipping(500);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Air", name);

  o->setShipping(1000);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Air", name);

  o->setShipping(1001);
  method = o->getShipping();
  name = method->name();

  EXPECT_NE("Air", name);

  delete wl;
  delete w;
  delete o;
}

TEST(TestOrder, setShippingTrainTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);

  o->setShipping(1000);
  ShippingMethod* method = o->getShipping();
  std::string name = method->name();

  EXPECT_NE("Train", name);

  o->setShipping(5000);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Train", name);

  o->setShipping(10000);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Train", name);

  o->setShipping(10001);
  method = o->getShipping();
  name = method->name();

  EXPECT_NE("Train", name);

  delete wl;
  delete w;
  delete o;
}

TEST(TestOrder, setShippingShipTest) {
  Waitlist* wl = new Waitlist();
  Warehouse* w = new Warehouse(wl);
  Order* o = new Order(w, wl);

  o->setShipping(10000);
  ShippingMethod* method = o->getShipping();
  std::string name = method->name();

  EXPECT_NE("Ship", name);

  o->setShipping(20000);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Ship", name);

  o->setShipping(100000);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Ship", name);

  o->setShipping(10000000);
  method = o->getShipping();
  name = method->name();

  EXPECT_EQ("Ship", name);

  delete wl;
  delete w;
  delete o;
}
