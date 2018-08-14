#ifndef RIBI_BRAR_QTCONCEPTMAP_TEST_H
#define RIBI_BRAR_QTCONCEPTMAP_TEST_H

#include "qtconceptmap.h"
//#include <QtTest/QtTest>
#include <QDialog>

namespace ribi {
namespace brar {

class QtConceptMapTest : public QWidget
{
    Q_OBJECT //!OCLINT

public:

  QtConceptMapTest();
  ribi::cmap::QtConceptMap * const m_qtconceptmap;

private slots:

  ///Press a random button every certain amount of time.
  ///Mashing buttons must be done in a slot,
  ///as the pop-ups are 'exec'-ed, thus take all messages
  void timerEvent(QTimerEvent *event);

private:

  int m_ticks;

};

} //~namespace brar
} //~namespace ribi

#endif // RIBI_CMAP_QTCONCEPTMAP_TEST_H
