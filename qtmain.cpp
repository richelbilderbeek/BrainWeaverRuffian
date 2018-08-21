#include <QApplication>

#include <ctime>
#include <iostream>

#include <QDebug>

#include "conceptmaphelper.h"
#include "qtbrainweaverruffianqtconceptmap_test.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  int seed = 2;
  if (ribi::cmap::OnTravis())
  {
    seed = std::time(0);
  }
  qCritical() << "RNG seed: " << seed;
  std::srand(seed);



  ribi::brar::QtConceptMapTest t;
  t.m_qtconceptmap->show();
  t.m_qtconceptmap->setGeometry(32, 32, 1200, 600);
  return a.exec();
}
