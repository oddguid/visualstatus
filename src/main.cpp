#include <QCoreApplication>
#include <qtimer.h>
#include <iostream>
//#include "ScriptRunner.h"

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

//  script::ScriptRunner runner;

//  QTimer timer;
//  timer.singleShot(0, &runner, SLOT(testSlot()));

  int result = app.exec();
  
  return result;
}

