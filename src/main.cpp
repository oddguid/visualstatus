#include <QCoreApplication>
#include <qtimer.h>
#include <iostream>
#include "MainConsole.h"

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  // create console app
  MainConsole *console = new MainConsole(&app);
  console->prepareScript(app.arguments());

  QObject::connect(console, SIGNAL(exit()), &app, SLOT(quit()));

  // use timer to start app
  QTimer timer;
  timer.singleShot(0, console, SLOT(runScript()));

  int result = app.exec();
  
  return result;
}

