#ifndef RIBI_BRAR_QTCONCEPTMAP_TEST_H
#define RIBI_BRAR_QTCONCEPTMAP_TEST_H

#include "qtconceptmap.h"
#include <QDialog>
#include <QEvent>
#include "qtconceptmapmode.h"

namespace ribi {
namespace brar {

class QtConceptMapTest : public QWidget
{
    Q_OBJECT //!OCLINT

public:

  QtConceptMapTest(const ribi::cmap::Mode mode);
  ribi::cmap::QtConceptMap * const m_qtconceptmap;

  QPoint GetRandomGlobalPos() noexcept;
  Qt::Key GetRandomKey() noexcept;
  QPointF GetRandomLocalPos() noexcept;

  Qt::KeyboardModifiers GetRandomKeyboardModifiers() noexcept;
  Qt::MouseButton GetRandomMouseButton() noexcept;
  QEvent::Type GetRandomMouseEventType() noexcept;

private slots:

  ///Press a random button every certain amount of time.
  ///Mashing buttons must be done in a slot,
  ///as the pop-ups are 'exec'-ed, thus take all messages
  void timerEvent(QTimerEvent *event);

private:

  const std::vector<QEvent::Type> m_mouse_event_types{
    QEvent::Type::MouseButtonPress,
    QEvent::Type::MouseButtonRelease,
    QEvent::Type::MouseMove,
    QEvent::Type::MouseButtonDblClick
  };

  ///Allowed combinations of keyboard modifiers
  const std::vector<Qt::KeyboardModifiers> m_keyboard_modifiers{
    Qt::NoModifier,
    Qt::NoModifier,
    Qt::NoModifier,
    Qt::NoModifier,
    Qt::ShiftModifier,
    Qt::ControlModifier,
    Qt::ControlModifier,
    Qt::ControlModifier,
    Qt::AltModifier,
    Qt::ShiftModifier | Qt::ControlModifier,
    Qt::ControlModifier | Qt::AltModifier,
    Qt::AltModifier | Qt::ShiftModifier,
    Qt::ControlModifier | Qt::ShiftModifier | Qt::ControlModifier
  };

  const std::vector<Qt::Key> m_keys{
    Qt::Key_F1,
    Qt::Key_F2,
    Qt::Key_F3,
    Qt::Key_1,
    Qt::Key_2,
    Qt::Key_A,
    Qt::Key_Delete,
    Qt::Key_Down,
    Qt::Key_E,
    Qt::Key_E,
    Qt::Key_E,
    //Qt::Key_Equal, //Scale
    Qt::Key_H,
    Qt::Key_Left,
    //Qt::Key_Minus, //Scale
    Qt::Key_N,
    Qt::Key_Right,
    Qt::Key_Space,
    Qt::Key_T,
    Qt::Key_Up,
    Qt::Key_Z
  };

  const std::vector<Qt::MouseButton> m_mouse_buttons{
    Qt::LeftButton,
    Qt::RightButton
  };

  int m_ticks{0};

  const bool m_use_keyboard{true};
  const bool m_use_mouse{true};

  friend std::ostream& operator<<(std::ostream& os, const QtConceptMapTest& t) noexcept;
};

std::ostream& operator<<(std::ostream& os, const QtConceptMapTest& t) noexcept;
QDebug operator<<(QDebug d, const QtConceptMapTest& t) noexcept;

} //~namespace brar
} //~namespace ribi

#endif // RIBI_CMAP_QTCONCEPTMAP_TEST_H
