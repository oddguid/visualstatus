#include "Logger.h"

namespace script
{

Logger::Logger(QObject *parent)
  : QObject(parent)
  , m_logLevel(LogLevel::Info)
{
}

Logger::~Logger()
{
}

void Logger::level(const QString &logLevel)
{
  m_logLevel = LogLevel::fromString(logLevel);
}

void Logger::clear()
{
  emit clearLog();
}

void Logger::log(const QString &text)
{
  if (m_logLevel >= LogLevel::Info)
  {
    emit appendLog(LogLevel::Info, text);
  }
}

void Logger::logError(const QString &text)
{
  if (m_logLevel >= LogLevel::Error)
  {
    emit appendLog(LogLevel::Error, text);
  }
}

void Logger::logWarning(const QString &text)
{
  if (m_logLevel >= LogLevel::Warning)
  {
    emit appendLog(LogLevel::Warning, text);
  }
}

void Logger::logInfo(const QString &text)
{
  if (m_logLevel >= LogLevel::Info)
  {
    emit appendLog(LogLevel::Info, text);
  }
}

void Logger::logDebug(const QString &text)
{
  if (m_logLevel >= LogLevel::Debug)
  {
    emit appendLog(LogLevel::Debug, text);
  }
}

} // script
