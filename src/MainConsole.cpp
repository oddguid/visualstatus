#include "MainConsole.h"
#include <QFile>
#include "ScriptRunner.h"

MainConsole::MainConsole(QObject *parent)
  : QObject(parent)
  , m_scriptRunner(NULL)
  , m_log(stdout)
  , m_scriptFileName()
{
  createScriptRunner();
}

MainConsole::~MainConsole()
{
}

bool MainConsole::prepareScript(const QStringList &arguments)
{
  m_scriptFileName = "";

  // parse arguments
  for (int i = 0; i < arguments.size(); ++i)
  {
    // argument not starting with '-' is file name
    if (!arguments.at(i).startsWith('-'))
    {
      m_scriptFileName = arguments.at(i);
    }
  }

  if (m_scriptFileName.isEmpty())
  {
    // no file name given
    log(LogLevel::Warning, tr("No script file given"));

    return false;
  }

  return true;
}

void MainConsole::createScriptRunner()
{
  m_scriptRunner = new ScriptRunner(this);

  // only connect to appendLog signal, clearLog signal is not used when writing
  // to stdout
  connect(m_scriptRunner, SIGNAL(appendLog(LogLevel::Enum, QString)),
          this, SLOT(log(LogLevel::Enum, QString)));
}

void MainConsole::log(LogLevel::Enum logLevel, const QString &text)
{
  switch (logLevel)
  {
  case LogLevel::Error:
    m_log << tr("[ERROR] ");
    break;
  case LogLevel::Warning:
    m_log << tr("[WARNING] ");
    break;
  case LogLevel::Debug:
    m_log << tr("[DEBUG] ");
    break;
  case LogLevel::Info:
  default:
    break;
  }

  m_log << text << endl;
}

void MainConsole::runScript()
{
  if (m_scriptFileName.isEmpty())
  {
    // no file, nothing to do
    return;
  }

  // open file
  QFile scriptFile(m_scriptFileName);

  if (!scriptFile.open(QFile::ReadOnly | QFile::Text))
  {
    // error opening file
    log(LogLevel::Error, tr("Cannot read file %1: %2")
                         .arg(m_scriptFileName)
                         .arg(scriptFile.errorString()));

    return;
  }

  // run script
  QTextStream scriptStream(&scriptFile);

  m_scriptRunner->runScript(scriptStream.readAll(), m_scriptFileName);
}

