#include "qtbrainweaverruffianqtconceptmap_test.h"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QTest>
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

QPoint ribi::brar::QtConceptMapTest::GetRandomGlobalPos() noexcept
{
  return m_qtconceptmap->mapFromScene(GetRandomLocalPos());
}

Qt::Key ribi::brar::QtConceptMapTest::GetRandomKey() noexcept
{
  return m_keys[ std::rand() % m_keys.size() ];
}

Qt::KeyboardModifier ribi::brar::QtConceptMapTest
  ::GetRandomKeyboardModifier() noexcept
{
  return m_keyboard_modifiers[ std::rand() % m_keyboard_modifiers.size() ];
}

Qt::KeyboardModifiers ribi::brar::QtConceptMapTest::GetRandomKeyboardModifiers() noexcept
{
  return m_keyboard_modifierses[ std::rand() % m_keyboard_modifierses.size() ];
}


QPointF ribi::brar::QtConceptMapTest::GetRandomLocalPos() noexcept
{
  switch (0 + (std::rand() % 4))
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
  return m_mouse_buttons[ std::rand() % m_mouse_buttons.size() ];
}

QMouseEvent ribi::brar::QtConceptMapTest::GetRandomMouseEvent() noexcept
{
  const QEvent::Type type = GetRandomMouseEventType();
  const QPointF localPos(GetRandomLocalPos());
  const Qt::MouseButton button{
    type == QEvent::MouseMove ? Qt::NoButton : GetRandomMouseButton()
  };
  const Qt::MouseButtons buttons = Qt::NoButton;
  //const Qt::MouseButtons buttons = button;
  const Qt::KeyboardModifiers modifiers = GetRandomKeyboardModifiers();
  return QMouseEvent(type, localPos, button, buttons, modifiers);
}

QEvent::Type ribi::brar::QtConceptMapTest::GetRandomMouseEventType() noexcept
{
  return m_mouse_event_types[ std::rand() % m_mouse_event_types.size() ];
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

QKeyEvent ribi::brar::QtConceptMapTest::GetRandomKeyEvent() noexcept
{
  switch (std::rand() % 30)
  {
    //case  0: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_N, Qt::ControlModifier);
    case  1: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_E, Qt::ControlModifier);
    //case  2: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Delete, Qt::NoModifier);
    case  3: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Space, Qt::NoModifier);
    case  4: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Up, Qt::NoModifier);
    case  5: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Right, Qt::NoModifier);
    case  6: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Down, Qt::NoModifier);
    case  7: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Left, Qt::NoModifier);
    case  8: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Up, Qt::ControlModifier);
    case  9: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Right, Qt::ControlModifier);
    case 10: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Down, Qt::ControlModifier);
    case 11: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Left, Qt::ControlModifier);
    case 12: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Up, Qt::ShiftModifier);
    case 13: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Right, Qt::ShiftModifier);
    case 14: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Down, Qt::ShiftModifier);
    case 15: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Left, Qt::ShiftModifier);
    case 16: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Up, Qt::AltModifier);
    case 17: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Right, Qt::AltModifier);
    case 18: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Down, Qt::AltModifier);
    case 19: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Left, Qt::AltModifier);
    case 20: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Up, Qt::ControlModifier | Qt::ShiftModifier);
    case 21: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Right, Qt::ControlModifier | Qt::ShiftModifier);
    case 22: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Down, Qt::ControlModifier | Qt::ShiftModifier);
    case 23: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Left, Qt::ControlModifier | Qt::ShiftModifier);
    case 24: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Up, Qt::AltModifier | Qt::ShiftModifier);
    case 25: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Right, Qt::AltModifier | Qt::ShiftModifier);
    case 26: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Down, Qt::AltModifier | Qt::ShiftModifier);
    case 27: return QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Left, Qt::AltModifier | Qt::ShiftModifier);
    default: break;
  }
  //
  const Qt::Key key = GetRandomKey();
  Qt::KeyboardModifier modifier = GetRandomKeyboardModifier();
  return QKeyEvent(QEvent::Type::KeyPress, key, modifier);
}

void ribi::brar::QtConceptMapTest::PutCursorThere(const QMouseEvent& event) noexcept
{
  const QPoint mousePos = (m_qtconceptmap->pos()
    + m_qtconceptmap->mapFromScene(event.localPos()))
    + QPoint(0, m_qtconceptmap->isFullScreen() ? 0 : 27) //Window title, use if not full-screen
  ;
  m_qtconceptmap->cursor().setPos(mousePos);
}

void ribi::brar::QtConceptMapTest::timerEvent(QTimerEvent *)
{
  const bool use_keyboard{true};
  const bool use_mouse{true};

  ++m_ticks;

  if ((std::rand() >> 4) % 2 && use_keyboard)
  {
    QKeyEvent event = GetRandomKeyEvent();

    qDebug() << m_ticks << event.type() << QKeySequence(event.key()).toString() << event.modifiers();
    m_qtconceptmap->keyPressEvent(&event);
    return;
  }
  if (!use_mouse) return;
  const auto event_type = GetRandomMouseEventType();
  const auto mouse_button = GetRandomMouseButton();
  const auto keyboard_modifiers = GetRandomKeyboardModifiers();
  const QPoint global_pos = GetRandomGlobalPos();
  qDebug() << m_ticks << event_type << global_pos << mouse_button << keyboard_modifiers;
  if (event_type == QEvent::Type::MouseButtonDblClick
  ) {
    QTest::mouseMove(m_qtconceptmap, global_pos);
    QTest::mouseDClick(
      m_qtconceptmap->viewport(),
      mouse_button,
      keyboard_modifiers,
      global_pos
    );
  }
  if (event_type == QEvent::Type::MouseMove
  ) {
    QTest::mouseMove(m_qtconceptmap, global_pos);
  }
  else if (event_type == QEvent::Type::MouseButtonPress)
  {
    QTest::mouseMove(m_qtconceptmap, global_pos);
    QTest::mousePress(
      m_qtconceptmap->viewport(),
      mouse_button,
      keyboard_modifiers,
      global_pos
    );
  }
  else if (event_type == QEvent::Type::MouseButtonRelease)
  {
    QTest::mouseMove(m_qtconceptmap, global_pos);
    QTest::mouseRelease(
      m_qtconceptmap->viewport(),
      mouse_button,
      keyboard_modifiers,
      global_pos
    );
  }
}
