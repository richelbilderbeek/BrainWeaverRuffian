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

  //Center the QtConceptMap
  if (std::rand() < -1)
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    t.m_qtconceptmap->setGeometry(screen.adjusted(364, 64, -364, -64));
    t.m_qtconceptmap->move(screen.center() - t.m_qtconceptmap->rect().center());
    t.m_qtconceptmap->setGeometry(
      t.m_qtconceptmap->geometry().adjusted(0, 0, 0, -264)
    );
  }
  t.m_qtconceptmap->showFullScreen();
  return a.exec();
}
