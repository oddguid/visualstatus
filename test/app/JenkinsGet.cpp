#include <stdio.h>
#include <QCoreApplication>
#include "../../src/JenkinsManager.h"
#include "../../src/HttpPort.h"

int main(int argc, char *argv[])
{
  // automatic cleanup of curl
  cURLpp::Cleanup curlCleanup;

  QCoreApplication app(argc, argv);

  if (argc < 2)
  {
    // no url parameter
    std::cout << "No URL given, please supply a URL" << std::endl;

    return 1;
  }

  HttpPort port;
  JenkinsManager manager;

  manager.setHttpPort(&port);

  // get status from Jenkins server
  if (!manager.getStatus(QString(argv[1])))
  {
    // error
    std::cout << "Error getting data:\n" << manager.error().toStdString()
              << std::endl;

    return 2;
  }

  // print data to console in format that is understood by MockJenkinsManager
  QStringList jobNames = manager.jobNames();

  for (int i = 0; i < jobNames.size(); ++i)
  {
    QString jobName = jobNames[i];

    std::cout << jobName.toStdString() << "|"
              << manager.jobUrl(jobName).toStdString() << "|"
              << manager.jobColor(jobName).toStdString() << std::endl;
  }

  return 0;
}
