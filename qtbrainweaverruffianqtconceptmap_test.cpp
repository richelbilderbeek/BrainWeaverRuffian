#include "qtbrainweaverruffianqtconceptmap_test.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDesktopWidget>

#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapconcepteditdialog.h"
#include "conceptmapfactory.h"
#include "qtconceptmaptoolsitem.h"

ribi::brar::QtConceptMapTest::QtConceptMapTest()
  : m_qtconceptmap{new ribi::cmap::QtConceptMap},
    m_ticks{0}
{
  m_qtconceptmap->SetConceptMap(
    ribi::cmap::ConceptMapFactory().GetRated()
  );
  m_qtconceptmap->SetMode(ribi::cmap::Mode::edit);
  m_qtconceptmap->show();

  startTimer(10);
}

Qt::Key ribi::brar::QtConceptMapTest::GetRandomKey() noexcept
{
  const std::vector<Qt::Key> key =
  {
    //Qt::Key_F1,
    //Qt::Key_F2,
    Qt::Key_Space,
    Qt::Key_Left,
    Qt::Key_Right,
    Qt::Key_Up,
    Qt::Key_Down,
    Qt::Key_Delete,
    Qt::Key_1,
    Qt::Key_2,
    //Qt::Key_A,
    //Qt::Key_B,
    //Qt::Key_C,
    //Qt::Key_D,
    Qt::Key_E,
    //Qt::Key_F,
    //Qt::Key_G,
    Qt::Key_H,
    //Qt::Key_I,
    //Qt::Key_J,
    //Qt::Key_K,
    //Qt::Key_L,
    //Qt::Key_M,
    Qt::Key_N,
    //Qt::Key_O,
    //Qt::Key_P,
    //Qt::Key_Q,
    //Qt::Key_R,
    //Qt::Key_S,
    Qt::Key_T
    //Qt::Key_U,
    //Qt::Key_V,
    //Qt::Key_W,
    //Qt::Key_X,
    //Qt::Key_Y,
    //Qt::Key_Z
  };
  return key[ std::rand() % key.size() ];
}

Qt::KeyboardModifier ribi::brar::QtConceptMapTest
  ::GetRandomKeyboardModifier() noexcept
{
  const std::vector<Qt::KeyboardModifier> modifiers =
  {
    Qt::NoModifier,
    Qt::ShiftModifier,
    Qt::ControlModifier,
    Qt::AltModifier
  };
  return modifiers[ std::rand() % modifiers.size() ];
}

Qt::KeyboardModifiers ribi::brar::QtConceptMapTest::GetRandomKeyboardModifiers() noexcept
{
  const std::vector<Qt::KeyboardModifiers> modifiers =
  {
    Qt::NoModifier,
    Qt::ShiftModifier,
    Qt::ControlModifier,
    Qt::AltModifier,
    Qt::ShiftModifier | Qt::ControlModifier,
    Qt::ControlModifier | Qt::AltModifier,
    Qt::AltModifier | Qt::ShiftModifier,
    Qt::ControlModifier | Qt::ShiftModifier | Qt::ControlModifier
  };
  return modifiers[ std::rand() % modifiers.size() ];
}

QPointF ribi::brar::QtConceptMapTest::GetRandomLocalPos() noexcept
{
  switch (0 + (std::rand() % 3))
  {
    case 0: //On item
    {
      const auto items = m_qtconceptmap->GetScene().items();
      const int n_items = items.size();
      if (n_items == 0) {
        return GetRandomLocalPos();
      }
      const auto item = items[ std::rand() % n_items ];
      if (qgraphicsitem_cast<ribi::cmap::QtNode*>(item)
        || qgraphicsitem_cast<ribi::cmap::QtEdge*>(item)
      )
      {
        return item->pos();
      }
      return GetRandomLocalPos();
    }
    case 1: //On selected item
    {
      const auto items = m_qtconceptmap->GetScene().selectedItems();
      const int n_items = items.size();
      if (n_items == 0) {
        return QPointF();
      }
      const auto item = items[ std::rand() % n_items ];
      if (qgraphicsitem_cast<ribi::cmap::QtNode*>(item)
        || qgraphicsitem_cast<ribi::cmap::QtEdge*>(item)
      )
      {
        return item->pos();
      }
      return GetRandomLocalPos();
    }
    case 2: //On ToolIcon
    {
      if (m_qtconceptmap->GetQtToolItem().isVisible())
      {
        return QPointF(
          m_qtconceptmap->GetQtToolItem().pos().x() + 12.0,
          m_qtconceptmap->GetQtToolItem().pos().y() + 12.0
        );
      }
      break;
    }
    case 3: //Random on window, close to cursor
    {
      const QPointF local_pos{
        m_qtconceptmap->mapToScene(
          m_qtconceptmap->cursor().pos().x()
            - m_qtconceptmap->geometry().left()
            + 2
            - 50 + (std::rand() % 101),
          m_qtconceptmap->cursor().pos().y()
            - m_qtconceptmap->geometry().top()
            + 27
            - 50 + (std::rand() % 101)
        )
      };
      return local_pos;
    }
    case 4: //Random on window
    {
      const int x = (m_qtconceptmap->width() / 4) + (std::rand() % (m_qtconceptmap->width() / 2));
      const int y = (m_qtconceptmap->height() / 4) + (std::rand() % (m_qtconceptmap->height() / 2));
      const QPointF local_pos{
        m_qtconceptmap->mapToScene(x, y)
      };
      return local_pos;
    }
    case 5: //Random on scene
    {
      const QPointF local_pos{
        m_qtconceptmap->sceneRect().topLeft()
        + QPointF(
          std::rand() % static_cast<int>(m_qtconceptmap->sceneRect().width()),
          std::rand() % static_cast<int>(m_qtconceptmap->sceneRect().height())
        )
      };
      return local_pos;
    }
  }
  return GetRandomLocalPos();
}

Qt::MouseButton ribi::brar::QtConceptMapTest::GetRandomMouseButton() noexcept
{
  const std::vector<Qt::MouseButton> buttons =
  {
    Qt::LeftButton,
    Qt::RightButton
  };
  return buttons[ std::rand() % buttons.size() ];
}

int ribi::brar::QtConceptMapTest::GetRandomX() noexcept
{
  return m_qtconceptmap->geometry().left()
    + (std::rand() % m_qtconceptmap->width());
}

int ribi::brar::QtConceptMapTest::GetRandomY() noexcept
{
  const int y{
    m_qtconceptmap->geometry().top()
    + 64 // Window title
    + (std::rand() % (m_qtconceptmap->geometry().height() - 64))
  };
  assert(y > 0);
  return y;
}

void ribi::brar::QtConceptMapTest::timerEvent(QTimerEvent *)
{
  ++m_ticks;
  //qDebug() << m_ticks;
  const int event_type{std::rand() % 5};
  if (event_type == 0)
  {
    const Qt::Key key = GetRandomKey();
    Qt::KeyboardModifier modifier = GetRandomKeyboardModifier();

    QKeyEvent e(QEvent::Type::KeyPress, key, modifier);
    m_qtconceptmap->keyPressEvent(&e);
    return;
  }
  const QPointF localPos(GetRandomLocalPos());
  const Qt::MouseButton button = GetRandomMouseButton();
  const Qt::MouseButtons buttons = Qt::NoButton;
  const QPoint mousePos = (m_qtconceptmap->pos()
    + m_qtconceptmap->mapFromScene(localPos)) + QPoint(0, 27)
  ;
  m_qtconceptmap->cursor().setPos(mousePos);
  const Qt::KeyboardModifiers modifiers = GetRandomKeyboardModifiers();
  if (event_type == 1)
  {
    return;
    QMouseEvent event(
      QEvent::Type::MouseButtonDblClick,
      localPos,
      button,
      buttons,
      modifiers
    );
    m_qtconceptmap->mouseDoubleClickEvent(&event);
  }
  if (event_type == 2)
  {
    QMouseEvent event(
      QEvent::Type::MouseMove,
      localPos,
      Qt::NoButton,
      buttons,
      modifiers
    );
    m_qtconceptmap->mouseMoveEvent(&event);
  }
  else if (event_type == 3)
  {
    QMouseEvent event(
      QEvent::Type::MouseButtonPress,
      localPos,
      button,
      buttons,
      modifiers
    );
    m_qtconceptmap->mousePressEvent(&event);
  }
  else if (event_type == 4)
  {
    QMouseEvent event(
      QEvent::Type::MouseButtonRelease,
      localPos,
      button,
      buttons,
      modifiers
    );
    m_qtconceptmap->mouseReleaseEvent(&event);
  }
}
