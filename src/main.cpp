#include <QCoreApplication>
#include <qtimer.h>
#include <iostream>
#include <curl/curl.h>
#include "MainConsole.h"

int main(int argc, char *argv[])
{
  // initialize curl
  curl_global_init(CURL_GLOBAL_ALL);

  QCoreApplication app(argc, argv);

  // create console app
  MainConsole *console = new MainConsole(&app);
  console->prepareScript(app.arguments());

  QObject::connect(console, SIGNAL(exit()), &app, SLOT(quit()));

  // use timer to start app
  QTimer timer;
  timer.singleShot(0, console, SLOT(runScript()));

  int result = app.exec();
  
  // clean up curl
  curl_global_cleanup();

  return result;
}

