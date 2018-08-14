#include <cassert>
#include <iostream>

#include "qtbrainweaverruffianqtconceptmap_test.h"
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  //{ ribi::braw::qtbrainweaveroverviewdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  assert(!"Do not forget to comment this out on Travis");


  { ribi::brar::qtconceptmap_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
