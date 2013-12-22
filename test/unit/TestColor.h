#ifndef VST_TESTCOLOR_H
#define VST_TESTCOLOR_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for Color class.
class TestColor : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the constructor taking an RGB color.
  void rgbConstructor();

  /// Tests the getter and setter functions for the red component of the color.
  void r();

  /// Tests the getter and setter functions for the green component of the
  /// color.
  void g();

  /// Tests the getter and setter functions for the blue component of the 
  /// color.
  void b();

  /// Tests the copy constructor.
  void copyConstructor();

  /// Tests the assignment operator.
  void assignmentOperator();

  /// Tests the toScriptValue function.
  void toScriptValue();

  /// Tests the fromScriptValue function.
  void fromScriptValue();

  /// Tests the global function colorConstructor.
  void colorConstructor();

  /// Tests the global function colorToScriptValue.
  void colorToScriptValue();

  /// Tests the global function colorFromScriptValue.
  void colorFromScriptValue();
};

} // unittest

#endif

