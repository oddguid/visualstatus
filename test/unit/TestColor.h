#ifndef VST_TESTCOLOR_H
#define VST_TESTCOLOR_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for Color class
class TestColor : public QObject
{
  Q_OBJECT

private slots:
  void r();
};

} // unittest

#endif

