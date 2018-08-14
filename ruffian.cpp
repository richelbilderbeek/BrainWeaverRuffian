#include "ruffian.h"

#include <QDebug>
#include <QKeyEvent>
#include <QWidget>
#include <QTimer>

#include "qtconceptmap.h"
#include "qtconceptmapconcepteditdialog.h"

Ruffian::Ruffian(int &argc, char **argv)
  : QApplication(argc, argv),
    m_ticks{0}
{
  //Ruffian::startTimer(100);

  {
    QTimer * const timer{new QTimer};
    connect(timer, SIGNAL(timeout()), this, SLOT(PressRandomButton()));
    //timer->start(100);
  }
}

void Ruffian::timerEvent(QTimerEvent *)
{
  PressRandomButton();
}

void Ruffian::PressRandomButton()
{
  ++m_ticks;
  qDebug() << m_ticks;
  this->processEvents();
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
    if (m_ticks % 2 == 1)
    {
      qDebug() << "Press F2";
      QKeyEvent e(QEvent::Type::KeyPress, Qt::Key_F2, Qt::NoModifier);
      qtconceptmap->keyPressEvent(&e);
    }
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
