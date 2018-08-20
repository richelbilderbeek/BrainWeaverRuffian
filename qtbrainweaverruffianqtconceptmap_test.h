#ifndef RIBI_BRAR_QTCONCEPTMAP_TEST_H
#define RIBI_BRAR_QTCONCEPTMAP_TEST_H

#include "qtconceptmap.h"
#include <QDialog>
#include <QEvent>

namespace ribi {
namespace brar {

class QtConceptMapTest : public QWidget
{
    Q_OBJECT //!OCLINT

public:

  QtConceptMapTest();
  ribi::cmap::QtConceptMap * const m_qtconceptmap;

  QPoint GetRandomGlobalPos() noexcept;
  Qt::Key GetRandomKey() noexcept;
  QKeyEvent GetRandomKeyEvent() noexcept;
  QPointF GetRandomLocalPos() noexcept;
  int GetRandomX() noexcept;
  int GetRandomY() noexcept;
  Qt::KeyboardModifier GetRandomKeyboardModifier() noexcept;
  Qt::KeyboardModifiers GetRandomKeyboardModifiers() noexcept;
  Qt::MouseButton GetRandomMouseButton() noexcept;
  QMouseEvent GetRandomMouseEvent() noexcept;
  QEvent::Type GetRandomMouseEventType() noexcept;

  void PutCursorThere(const QMouseEvent& event) noexcept;

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

  ///Allowed modifiers
  const std::vector<Qt::KeyboardModifier> m_keyboard_modifiers
  {
    Qt::NoModifier,
    Qt::ShiftModifier,
    Qt::ControlModifier,
    Qt::AltModifier
  };

  ///Allowed modifierses (Gollumese plural)
  const std::vector<Qt::KeyboardModifiers> m_keyboard_modifierses{
    Qt::NoModifier,
    Qt::ShiftModifier,
    Qt::ControlModifier,
    Qt::AltModifier,
    Qt::ShiftModifier | Qt::ControlModifier,
    Qt::ControlModifier | Qt::AltModifier,
    Qt::AltModifier | Qt::ShiftModifier,
    Qt::ControlModifier | Qt::ShiftModifier | Qt::ControlModifier
  };

  const std::vector<Qt::Key> m_keys{
    //Qt::Key_F1,
    //Qt::Key_F2,
    //Qt::Key_F4,
    //Qt::Key_F7,
    //Qt::Key_F8,
    Qt::Key_1,
    Qt::Key_2,
    //Qt::Key_A,
    //Qt::Key_B,
    //Qt::Key_C,
    //Qt::Key_D,
    Qt::Key_Delete,
    Qt::Key_Down,
    Qt::Key_E,
    Qt::Key_Equal,
    //Qt::Key_F,
    //Qt::Key_G,
    Qt::Key_H,
    //Qt::Key_I,
    //Qt::Key_J,
    //Qt::Key_K,
    //Qt::Key_L,
    Qt::Key_Left,
    //Qt::Key_M,
    Qt::Key_Minus,
    Qt::Key_N,
    //Qt::Key_O,
    //Qt::Key_P,
    //Qt::Key_Q,
    //Qt::Key_R,
    Qt::Key_Right,
    //Qt::Key_S,
    Qt::Key_Space,
    Qt::Key_T,
    //Qt::Key_U,
    //Qt::Key_V,
    Qt::Key_Up,
    //Qt::Key_W,
    //Qt::Key_X,
    //Qt::Key_Y,
    Qt::Key_Z
  };

  const std::vector<Qt::MouseButton> m_mouse_buttons{
    Qt::LeftButton,
    Qt::RightButton
  };

  int m_ticks;

};

} //~namespace brar
} //~namespace ribi

#endif // RIBI_CMAP_QTCONCEPTMAP_TEST_H
