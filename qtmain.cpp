#include <cassert>
#include <iostream>

#include "qtbrainweaverruffianqtconceptmap_test.h"
#include "conceptmapfactory.h"
#include <qtconceptmap.h>
#include "ruffian.h"
#include <QDesktopWidget>
#include <QtTest/QtTest>

class Thread : public QThread
{

public:
  Thread(Ruffian& r)
    : m_r{r}
  {

  }
  void run()
  {
    while(1)
    {
      qDebug() << "THREAD";
      m_r.PressRandomButton();
      m_r.processEvents();
      wait(100);
    }
  }
private:
  Ruffian& m_r;
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //Ruffian a(argc, argv);
  //{ ribi::braw::qtbrainweaveroverviewdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //assert(!"Do not forget to comment this out on Travis");

  /*
  QTimer * const timer{new QTimer};
  timer->setTimerType(Qt::PreciseTimer);
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(PressRandomButton()));
  timer->start(100);
  */

  //{ ribi::brar::QtConceptMapTest t; error |= QTest::qExec(&t, argc, argv); }
  /*
  ribi::cmap::QtConceptMap t;
  t.SetConceptMap(ribi::cmap::ConceptMapFactory().GetRated());
  t.SetMode(ribi::cmap::Mode::edit);
  t.show();
  */
  ribi::brar::QtConceptMapTest t;
  //Center the dialog
  {

    const QRect screen = QApplication::desktop()->screenGeometry();
    t.m_qtconceptmap->setGeometry(screen.adjusted(64, 64, -64, -64));
    t.m_qtconceptmap->move(screen.center() - t.m_qtconceptmap->rect().center());
    t.m_qtconceptmap->setGeometry(
      t.m_qtconceptmap->geometry().adjusted(0, 0, 0, -264)
    );
  }
  //t.show();
  //Thread thread(a);
  //thread.run();
  //assert(1 == 2);
  return a.exec();
}
