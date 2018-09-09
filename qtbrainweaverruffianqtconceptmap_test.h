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

  const bool m_do_shift_mode{true};

  ///Allowed combinations of keyboard modifiers
  const std::vector<Qt::KeyboardModifiers> m_keyboard_modifiers{
    Qt::NoModifier,
    Qt::ShiftModifier,
    Qt::ControlModifier,
    Qt::AltModifier
  };

  const std::vector<Qt::Key> m_keys;

  const std::vector<Qt::MouseButton> m_mouse_buttons{
    Qt::LeftButton,
    Qt::RightButton
  };

  const std::vector<QEvent::Type> m_mouse_event_types{
    QEvent::Type::MouseButtonPress,
    QEvent::Type::MouseButtonRelease,
    QEvent::Type::MouseMove,
    QEvent::Type::MouseButtonDblClick
  };

public:
  ///The QWidget it is about
  ribi::cmap::QtConceptMap * const m_qtconceptmap;
private:

  int m_ticks{0};

  const bool m_use_keyboard{true};
  const bool m_use_mouse{true};

  friend std::ostream& operator<<(std::ostream& os, const QtConceptMapTest& t) noexcept;
};

///Create the keys the Ruffian is allowed to use
/// @param is_on_travis Must be true when running on Travis
///   CI. When running on Travis, less keys (F1 and F2) are
///   used as Travis cannot handle all types of pop-ups
std::vector<Qt::Key> CreateKeys(const bool is_on_travis = false) noexcept;

std::ostream& operator<<(std::ostream& os, const QtConceptMapTest& t) noexcept;
QDebug operator<<(QDebug d, const QtConceptMapTest& t) noexcept;

} //~namespace brar
} //~namespace ribi

#endif // RIBI_CMAP_QTCONCEPTMAP_TEST_H
