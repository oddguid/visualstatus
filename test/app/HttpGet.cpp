#include <stdio.h>
#include <iostream>
#include <curl/curl.h>
#include <QCoreApplication>
#include "../../src/HttpPort.h"

int main(int argc, char *argv[])
{
  // initialize curl
  curl_global_init(CURL_GLOBAL_ALL);

  QCoreApplication app(argc, argv);

  if (argc < 2)
  {
    // no url parameter
    std::cout << "No URL given, please supply a URL" << std::endl;

    return 1;
  }

  HttpPort port;

  // get data
  if (!port.get(QString(argv[1])))
  {
    // error
    std::cout << "Error getting data:\n" << port.error().toStdString()
              << std::endl;

    return 2;
  }

  // print data to console
  std::cout << port.data().toStdString() << std::endl;

  // clean up curl
  curl_global_cleanup();

  return 0;
}
