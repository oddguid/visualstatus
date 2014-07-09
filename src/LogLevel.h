#ifndef VST_LOGLEVEL_H
#define VST_LOGLEVEL_H

#include <QString>

namespace LogLevel
{

/// Enumeration for log levels. The following levels are allowed:
/// - Error
/// - Warning
/// - Info
/// - Debug
enum Enum
{
  Error,
  Warning,
  Info,
  Debug
};

/// Converts the log level to a readable string. For illegal enum values the
/// readable string for log level Info is returned.
///
/// \param[in] level Log level to convert.
/// \return Log level as readable string.
QString toString(Enum level);

/// Converts the readable string to a log level. If the string cannot be
/// converted log level Info is returned.
///
/// \param[in] level Readable string to convert.
/// \return Log level.
Enum fromString(const QString &level);

} // LogLevel

#endif
