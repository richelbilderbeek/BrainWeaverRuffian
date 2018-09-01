#include "qtbrainweaverruffianqtconceptmap_test.h"

#include <iostream>
#include <sstream>

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QThread>
#include <QTimer>
#include <QTest>
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapclassifyexamplesdialogcloser.h"
#include "qtconceptmapeditconceptdialog.h"
#include "qtconceptmapeditconceptdialogcloser.h"
#include "qtconceptmaprateconceptdialogcloser.h"
#include "conceptmapfactory.h"
#include "conceptmaphelper.h"
#include "qtconceptmaptoolsitem.h"

ribi::brar::QtConceptMapTest::QtConceptMapTest(const ribi::cmap::Mode mode)
  : m_qtconceptmap{new ribi::cmap::QtConceptMap}
{
  m_qtconceptmap->SetConceptMap(
    ribi::cmap::ConceptMapFactory().GetRated()
  );
  m_qtconceptmap->SetMode(mode);
  m_qtconceptmap->show();
  startTimer(200);
}

QPoint ribi::brar::QtConceptMapTest::GetRandomGlobalPos() noexcept
{
  return m_qtconceptmap->mapFromScene(GetRandomLocalPos());
}

Qt::Key ribi::brar::QtConceptMapTest::GetRandomKey() noexcept
{
  return m_keys[ std::rand() % m_keys.size() ];
}

Qt::KeyboardModifiers ribi::brar::QtConceptMapTest::GetRandomKeyboardModifiers() noexcept
{
  return m_keyboard_modifiers[ std::rand() % m_keyboard_modifiers.size() ];
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

QEvent::Type ribi::brar::QtConceptMapTest::GetRandomMouseEventType() noexcept
{
  return m_mouse_event_types[ std::rand() % m_mouse_event_types.size() ];
}

void ribi::brar::QtConceptMapTest::timerEvent(QTimerEvent *)
{

  ++m_ticks;

  #define SWITCH_MODE
  #ifdef SWITCH_MODE
  if (m_ticks % 100 == 0)
  {
    m_qtconceptmap->SetMode(ribi::cmap::Mode::edit);
  }
  else if (m_ticks % 100 == 45)
  {
    m_qtconceptmap->SetMode(ribi::cmap::Mode::rate);
  }
  else if (m_ticks % 100 == 90)
  {
    m_qtconceptmap->SetMode(ribi::cmap::Mode::uninitialized);
  }
  #endif // SWITCH_MODE

  if (!ribi::cmap::OnTravis())
  {
    if (m_ticks == 100302)
    {
      qCritical() << *this << '\n';
      while (1)
      {
        qApp->processEvents();
      }
      qCritical() << "Clean exit";
      std::exit(0);
    }
  }
  const auto keyboard_modifiers = GetRandomKeyboardModifiers();

  if ((std::rand() >> 4) % 2 && m_use_keyboard)
  {
    const auto key = GetRandomKey();
    qCritical() << m_ticks << "KeyPress" << QKeySequence(keyboard_modifiers + key).toString();

    ribi::cmap::QtClassifyExamplesDialogCloser classify_examples_closer;
    ribi::cmap::QtEditConceptDialogCloser edit_concept_closer;
    ribi::cmap::QtRateConceptDialogCloser rate_concept_closer;
    if (m_qtconceptmap->GetMode() == ribi::cmap::Mode::edit
      && key == Qt::Key_F2
      && keyboard_modifiers == Qt::NoModifier
    )
    {
      qApp->processEvents();
      QTimer::singleShot(400, &edit_concept_closer, SLOT(Modify()));
      QTimer::singleShot(800, &edit_concept_closer, SLOT(PressOk()));
    }
    else if (m_qtconceptmap->GetMode() == ribi::cmap::Mode::rate
      && key == Qt::Key_F1
      && keyboard_modifiers == Qt::NoModifier
    )
    {
      qApp->processEvents();
      QTimer::singleShot(400, &rate_concept_closer, SLOT(Modify()));
      QTimer::singleShot(800, &rate_concept_closer, SLOT(PressOk()));
    }
    else if (m_qtconceptmap->GetMode() == ribi::cmap::Mode::rate
      && key == Qt::Key_F2
      && keyboard_modifiers == Qt::NoModifier
    )
    {
      qApp->processEvents();
      QTimer::singleShot(400, &classify_examples_closer, SLOT(Modify()));
      QTimer::singleShot(800, &classify_examples_closer, SLOT(PressOk()));
    }
    QTest::keyPress(m_qtconceptmap, key, keyboard_modifiers);
    return;
  }
  if (!m_use_mouse) return;
  const auto event_type = GetRandomMouseEventType();
  const auto mouse_button = GetRandomMouseButton();
  const QPoint global_pos = GetRandomGlobalPos();
  qCritical() << m_ticks << event_type << global_pos << mouse_button << keyboard_modifiers;
  if (event_type == QEvent::Type::MouseButtonDblClick)
  {
    QTest::mouseMove(m_qtconceptmap, global_pos);
    QTest::mouseDClick(
      m_qtconceptmap->viewport(),
      mouse_button,
      keyboard_modifiers,
      global_pos
    );
  }
  if (event_type == QEvent::Type::MouseMove)
  {
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

std::ostream& ribi::brar::operator<<(std::ostream& os, const QtConceptMapTest& t) noexcept
{
  os
    << "#ticks: " << t.m_ticks << '\n'
    << "QtConceptMap:\n" << *t.m_qtconceptmap;
  return os;
}

QDebug ribi::brar::operator<<(QDebug d, const QtConceptMapTest& t) noexcept
{
  std::stringstream s;
  s << t;
  d << s.str().c_str();
  return d;
}
