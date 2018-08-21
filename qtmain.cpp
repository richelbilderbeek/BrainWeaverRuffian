#include <QApplication>

#include <ctime>
#include <iostream>

#include <QDebug>
#include <QUndoView>

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
  seed = 1534858203; // after 71: QtQuadBezierArrowItem must have a parent
  qCritical() << "RNG seed: " << seed;
  std::srand(seed);



  ribi::brar::QtConceptMapTest t;
  t.m_qtconceptmap->show();
  t.m_qtconceptmap->setGeometry(32, 32, 1200, 600);
  QUndoView * const undo = new QUndoView(&t.m_qtconceptmap->GetUndo());
  undo->show();
  undo->setGeometry(32, 632, 1200, 200);
  return a.exec();
}
