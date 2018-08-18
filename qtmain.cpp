#include <QApplication>

#include "qtbrainweaverruffianqtconceptmap_test.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::brar::QtConceptMapTest t;
  t.m_qtconceptmap->showFullScreen();
  return a.exec();
}
