#include <cassert>
#include <iostream>

#include "qtbrainweaverruffianqtconceptmap_test.h"
#include "conceptmapfactory.h"
#include <qtconceptmap.h>
#include <QDesktopWidget>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  std::srand(0);
  ribi::brar::QtConceptMapTest t;
  t.m_qtconceptmap->showFullScreen();
  return a.exec();
}
