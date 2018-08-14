#ifndef RIBI_BRAR_QTCONCEPTMAP_TEST_H
#define RIBI_BRAR_QTCONCEPTMAP_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace brar {

class QtConceptMapTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:

  void Construct() const;

};

} //~namespace brar
} //~namespace ribi

#endif // RIBI_CMAP_QTCONCEPTMAP_TEST_H
