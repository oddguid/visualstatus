#include "TestColor.h"
#include "../../src/Color.h"

using namespace script;

namespace unittest
{

void TestColor::r()
{
  Color color;

  QCOMPARE(color.r(), static_cast<unsigned char>(0));
  QCOMPARE(color.g(), static_cast<unsigned char>(0));
  QCOMPARE(color.b(), static_cast<unsigned char>(0));
}

} // unittest

QTEST_MAIN(unittest::TestColor);
