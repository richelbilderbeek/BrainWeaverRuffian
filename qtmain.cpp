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
  ribi::brar::QtConceptMapTest t;
  t.m_qtconceptmap->showFullScreen();
  return a.exec();
}
