#include <QApplication>

#include <ctime>
#include <iostream>

#include <QDebug>
#include <QDesktopWidget>
#include <QUndoView>

#include "conceptmaphelper.h"
#include "qtbrainweaverruffianqtconceptmap_test.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  std::srand(0);

  int seed = 2;
  if (ribi::cmap::OnTravis())
  {
    seed = std::time(0);
  }
  qCritical() << "RNG seed: " << seed;
  std::srand(seed);

  ribi::brar::QtConceptMapTest t(ribi::cmap::Mode::edit);
  t.m_qtconceptmap->show();
  QDesktopWidget w;

  t.m_qtconceptmap->setGeometry(
    0,
    0,
    w.screen()->width(),
    8 * w.screen()->height() / 10
  );
  QUndoView * const undo = new QUndoView(&t.m_qtconceptmap->GetUndo());
  undo->show();
  undo->setGeometry(
    0,
    8 * w.screen()->height() / 10,
    w.screen()->width(),
    2 * w.screen()->height() / 10
  );
  return a.exec();
}
