#include "LogLevel.h"

namespace LogLevel
{

QString toString(Enum level)
{
  QString levelString;

  switch (level)
  {
  case Error:
    levelString = "error";
    break;
  case Warning:
    levelString = "warning";
    break;
  case Info:
    levelString = "info";
    break;
  case Debug:
    levelString = "debug";
    break;
  default:
    levelString = "info";
    break;
  }

  return levelString;
}

Enum fromString(const QString &level)
{
  QString lowerLevel = level.trimmed().toLower();
  Enum logLevel = Info;

  if (lowerLevel.compare("error") == 0)
  {
    logLevel = Error;
  }
  else if (lowerLevel.compare("warning") == 0)
  {
    logLevel = Warning;
  }
  else if (lowerLevel.compare("debug") == 0)
  {
    logLevel = Debug;
  }

  return logLevel;
}

} // LogLevel

