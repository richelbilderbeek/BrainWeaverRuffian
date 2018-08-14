#include "qtbrainweaverruffianqtconceptmap_test.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QDesktopWidget>

#include "qtconceptmapconcepteditdialog.h"
#include "conceptmapfactory.h"

ribi::brar::QtConceptMapTest::QtConceptMapTest()
  : m_qtconceptmap{new ribi::cmap::QtConceptMap}
{
  m_qtconceptmap->SetMode(ribi::cmap::Mode::edit);
  m_qtconceptmap->SetConceptMap(
    ribi::cmap::ConceptMapFactory().GetRated()
  );
  m_qtconceptmap->show();

  startTimer(100);
}

void ribi::brar::QtConceptMapTest::timerEvent(QTimerEvent *)
{
  ++m_ticks;
  qDebug() << m_ticks;
  ribi::cmap::QtConceptMap * const qtconceptmap = qobject_cast<
    ribi::cmap::QtConceptMap*
  >(
    QApplication::activeWindow()
  );
  if (qtconceptmap)
  {
    qDebug() << "QtConceptMap active";
    if (m_ticks % 2 == 0)
    {
      qDebug() << "Press space";
      QKeyEvent e(QEvent::Type::KeyPress, Qt::Key_Space, Qt::NoModifier);
      qtconceptmap->keyPressEvent(&e);
    }
    /*
    if (m_ticks % 2 == 1)
    {
      qDebug() << "Press F2";
      QKeyEvent e(QEvent::Type::KeyPress, Qt::Key_F2, Qt::NoModifier);
      qtconceptmap->keyPressEvent(&e);
    }
    */
    return;
  }
  ribi::cmap::QtConceptMapConceptEditDialog * const edit_concept = qobject_cast<
      ribi::cmap::QtConceptMapConceptEditDialog*
    >(
      QApplication::activeWindow()
    );
  if (edit_concept)
  {
    qDebug() << "QtConceptMapConceptEditDialog active";
    qDebug() << "Close active window with ALT+O";
    QKeyEvent e(QEvent::Type::KeyPress, Qt::Key_O, Qt::AltModifier);
    edit_concept->keyPressEvent(&e);
  }
}
