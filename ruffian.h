#ifndef RUFFIAN_H
#define RUFFIAN_H

#include <QApplication>

class Ruffian : public QApplication
{
    Q_OBJECT //!OCLINT


public:
  Ruffian(int &argc, char **argv);

public slots:

  void PressRandomButton();

private slots:

  ///Press a random button every certain amount of time.
  ///Mashing buttons must be done in a slot,
  ///as the pop-ups are 'exec'-ed, thus take all messages
  void timerEvent(QTimerEvent *event);


private:
  int m_ticks;
};

#endif // RUFFIAN_H
