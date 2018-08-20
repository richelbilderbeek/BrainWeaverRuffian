#include <QApplication>

#include <iostream>

#include "conceptmaphelper.h"
#include "qtbrainweaverruffianqtconceptmap_test.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  if (ribi::cmap::OnTravis())
  {
    //Randomize timer
    const int seed = std::time(0);
    std::cout << "RNG seed: " << seed;
    std::srand(seed);
  }
  ribi::brar::QtConceptMapTest t;
  t.m_qtconceptmap->showFullScreen();
  return a.exec();
}
