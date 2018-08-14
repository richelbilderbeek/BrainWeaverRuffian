#include "qtbrainweaverruffianqtconceptmap_test.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDesktopWidget>

#include "qtconceptmapconcepteditdialog.h"
#include "conceptmapfactory.h"

ribi::brar::QtConceptMapTest::QtConceptMapTest()
  : m_qtconceptmap{new ribi::cmap::QtConceptMap},
    m_ticks{0}
{
  m_qtconceptmap->SetConceptMap(
    ribi::cmap::ConceptMapFactory().GetRated()
  );
  m_qtconceptmap->SetMode(ribi::cmap::Mode::edit);
  m_qtconceptmap->show();

  startTimer(100);
}

void ribi::brar::QtConceptMapTest::timerEvent(QTimerEvent *)
{
  ++m_ticks;
  qDebug() << m_ticks;
  const int event_type{std::rand() % 5};
  if (event_type == 0)
  {
    Qt::Key key = Qt::Key_Space;
    switch (std::rand() % 6)
    {
      case 0: key = Qt::Key_Space; break;
      case 1: key = Qt::Key_Left; break;
      case 2: key = Qt::Key_Right; break;
      case 3: key = Qt::Key_Up; break;
      case 4: key = Qt::Key_Down; break;
      case 5: key = Qt::Key_F2; break;
    }
    Qt::KeyboardModifier modifier = Qt::NoModifier;
    switch (std::rand() % 4)
    {
      case 0: modifier = Qt::NoModifier; break;
      case 1: modifier = Qt::ShiftModifier; break;
      case 2: modifier = Qt::ControlModifier; break;
      case 3: modifier = Qt::AltModifier; break;
    }

    QKeyEvent e(QEvent::Type::KeyPress, key, modifier);
    m_qtconceptmap->keyPressEvent(&e);
  }
  else if (event_type == 1)
  {
    const QPointF localPos(std::rand() % width(), std::rand() % height());
    Qt::MouseButton button;
    switch (std::rand() % 2)
    {
      case 0: button = Qt::LeftButton; break;
      case 1: button = Qt::RightButton; break;
    }
    Qt::MouseButtons buttons;
    Qt::KeyboardModifiers modifiers;
    QMouseEvent event(QEvent::Type::MouseButtonDblClick, localPos, button, buttons, modifiers);
    m_qtconceptmap->mouseDoubleClickEvent(&event);
  }
  else if (event_type == 2)
  {
    //Qt::MouseButton button = Qt::NoButton;
    //m_qtconceptmap->mouseMoveEvent();
  }
  else if (event_type == 3)
  {
    //m_qtconceptmap->mousePressEvent()
  }
  else if (event_type == 4)
  {
    //m_qtconceptmap->mouseReleaseEvent()
  }
}
