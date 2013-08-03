#include "TestColor.h"
#include "../../src/Color.h"

using namespace script;

namespace unittest
{

void TestColor::defaultConstructor()
{
  quint8 rExp = 0;
  quint8 gExp = 0;
  quint8 bExp = 0;

  Color color;

  QCOMPARE(color.r(), rExp);
  QCOMPARE(color.g(), gExp);
  QCOMPARE(color.b(), bExp);
}

void TestColor::r()
{
  quint8 rExp = 128;
  quint8 gExp = 0;
  quint8 bExp = 0;

  Color color;
  color.r(rExp);

  QCOMPARE(color.r(), rExp);
  QCOMPARE(color.g(), gExp);
  QCOMPARE(color.b(), bExp);
}

void TestColor::g()
{
  quint8 rExp = 0;
  quint8 gExp = 56;
  quint8 bExp = 0;

  Color color;
  color.g(gExp);

  QCOMPARE(color.r(), rExp);
  QCOMPARE(color.g(), gExp);
  QCOMPARE(color.b(), bExp);
}

void TestColor::b()
{
  quint8 rExp = 0;
  quint8 gExp = 0;
  quint8 bExp = 255;

  Color color;
  color.b(bExp);

  QCOMPARE(color.r(), rExp);
  QCOMPARE(color.g(), gExp);
  QCOMPARE(color.b(), bExp);
}

void TestColor::copyConstructor()
{
  quint8 rExp = 56;
  quint8 gExp = 123;
  quint8 bExp = 255;

  Color color;
  color.r(rExp);
  color.g(gExp);
  color.b(bExp);

  Color colorNew(color);

  QCOMPARE(colorNew.r(), rExp);
  QCOMPARE(colorNew.g(), gExp);
  QCOMPARE(colorNew.b(), bExp);
}

void TestColor::assignmentOperator()
{
  quint8 rExp = 56;
  quint8 gExp = 123;
  quint8 bExp = 255;

  Color color;
  color.r(rExp);
  color.g(gExp);
  color.b(bExp);

  Color colorNew;
  colorNew = color;

  QCOMPARE(colorNew.r(), rExp);
  QCOMPARE(colorNew.g(), gExp);
  QCOMPARE(colorNew.b(), bExp);
}

void TestColor::toScriptValue()
{
  quint8 rExp = 56;
  quint8 gExp = 123;
  quint8 bExp = 255;

  QScriptEngine *scriptEngine = new QScriptEngine();
  scriptEngine->setProcessEventsInterval(100);

  Color color;
  color.r(rExp);
  color.g(gExp);
  color.b(bExp);

  // convert color to script object
  QScriptValue scriptColor = color.toScriptValue(scriptEngine);

  // test red component of color
  QScriptValue rValue = scriptColor.property("r");

  // script object should have valid r property
  QVERIFY(rValue.isValid() == true);
  QVERIFY(rValue.isUndefined() == false);

  quint32 r = rValue.toUInt32();
  QCOMPARE(static_cast<quint8>(r), rExp);

  // test green component of color
  QScriptValue gValue = scriptColor.property("g");

  // script object schould have valid g property
  QVERIFY(gValue.isValid() == true);
  QVERIFY(gValue.isUndefined() == false);

  quint32 g = gValue.toUInt32();
  QCOMPARE(static_cast<quint8>(g), gExp);

  // test blue component of color
  QScriptValue bValue = scriptColor.property("b");

  // script object should have valid b property
  QVERIFY(bValue.isValid() == true);
  QVERIFY(bValue.isUndefined() == false);

  quint32 b = bValue.toUInt32();
  QCOMPARE(static_cast<quint8>(b), bExp);

  delete scriptEngine;
}

void TestColor::fromScriptValue()
{
  quint8 rExp = 1;
  quint8 gExp = 73;
  quint8 bExp = 254;

  QScriptEngine *scriptEngine = new QScriptEngine();
  scriptEngine->setProcessEventsInterval(100);

  QScriptValue colorObject = scriptEngine->newObject();

  colorObject.setProperty("r", rExp);
  colorObject.setProperty("g", gExp);
  colorObject.setProperty("b", bExp);

  // get color from script object
  Color color;
  color.fromScriptValue(colorObject);

  QCOMPARE(color.r(), rExp);
  QCOMPARE(color.g(), gExp);
  QCOMPARE(color.b(), bExp);
 
  delete scriptEngine;
}

void TestColor::colorConstructor()
{
  quint8 rExp = 0;
  quint8 gExp = 0;
  quint8 bExp = 0;

  QScriptEngine *scriptEngine = new QScriptEngine();
  scriptEngine->setProcessEventsInterval(100);

  QScriptContext *scriptContext = scriptEngine->currentContext();

  // add this-object and activation-object to fake a script function call
  QScriptValue thisObject;
  QScriptValue activationObject;

  scriptContext->setThisObject(thisObject);
  scriptContext->setActivationObject(activationObject);

  // ask for new script color object
  QScriptValue scriptColor = ::colorConstructor(scriptContext, scriptEngine);

  // test red component of color
  QScriptValue rValue = scriptColor.property("r");

  // script object should have valid r property
  QVERIFY(rValue.isValid() == true);
  QVERIFY(rValue.isUndefined() == false);

  quint32 r = rValue.toUInt32();
  QCOMPARE(static_cast<quint8>(r), rExp);

  // test green component of color
  QScriptValue gValue = scriptColor.property("g");

  // script object schould have valid g property
  QVERIFY(gValue.isValid() == true);
  QVERIFY(gValue.isUndefined() == false);

  quint32 g = gValue.toUInt32();
  QCOMPARE(static_cast<quint8>(g), gExp);

  // test blue component of color
  QScriptValue bValue = scriptColor.property("b");

  // script object should have valid b property
  QVERIFY(bValue.isValid() == true);
  QVERIFY(bValue.isUndefined() == false);

  quint32 b = bValue.toUInt32();
  QCOMPARE(static_cast<quint8>(b), bExp);

  delete scriptEngine;
}

void TestColor::colorToScriptValue()
{
  quint8 rExp = 56;
  quint8 gExp = 123;
  quint8 bExp = 255;

  QScriptEngine *scriptEngine = new QScriptEngine();
  scriptEngine->setProcessEventsInterval(100);

  Color color;
  color.r(rExp);
  color.g(gExp);
  color.b(bExp);

  // convert color to script object
  QScriptValue scriptColor = ::colorToScriptValue(scriptEngine, color);

  // test red component of color
  QScriptValue rValue = scriptColor.property("r");

  // script object should have valid r property
  QVERIFY(rValue.isValid() == true);
  QVERIFY(rValue.isUndefined() == false);

  quint32 r = rValue.toUInt32();
  QCOMPARE(static_cast<quint8>(r), rExp);

  // test green component of color
  QScriptValue gValue = scriptColor.property("g");

  // script object schould have valid g property
  QVERIFY(gValue.isValid() == true);
  QVERIFY(gValue.isUndefined() == false);

  quint32 g = gValue.toUInt32();
  QCOMPARE(static_cast<quint8>(g), gExp);

  // test blue component of color
  QScriptValue bValue = scriptColor.property("b");

  // script object should have valid b property
  QVERIFY(bValue.isValid() == true);
  QVERIFY(bValue.isUndefined() == false);

  quint32 b = bValue.toUInt32();
  QCOMPARE(static_cast<quint8>(b), bExp);

  delete scriptEngine;
}

void TestColor::colorFromScriptValue()
{
  quint8 rExp = 1;
  quint8 gExp = 73;
  quint8 bExp = 254;

  QScriptEngine *scriptEngine = new QScriptEngine();
  scriptEngine->setProcessEventsInterval(100);

  QScriptValue colorObject = scriptEngine->newObject();

  colorObject.setProperty("r", rExp);
  colorObject.setProperty("g", gExp);
  colorObject.setProperty("b", bExp);

  Color color;

  // get color from script object
  ::colorFromScriptValue(colorObject, color);

  QCOMPARE(color.r(), rExp);
  QCOMPARE(color.g(), gExp);
  QCOMPARE(color.b(), bExp);
 
  delete scriptEngine; 
}

} // unittest

QTEST_MAIN(unittest::TestColor)
