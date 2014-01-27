#ifndef VST_SCRIPTENGINE_H
#define VST_SCRIPTENGINE_H

#include <QObject>
#include <QScriptEngine>

/// Script engine, extends QScriptEngine.
///
/// This class adds global functions to QScriptEngine which can be called from
/// within a script. Available script functions:
/// - exit(), to indicate that the script has finished running. This emits the
/// signal exitScript().
class ScriptEngine : public QScriptEngine
{
  Q_OBJECT

public:
  /// Constructor.
  ScriptEngine();

  /// Constructor.
  ///
  /// \parent[in] parent Parent of this object.
  explicit ScriptEngine(QObject *parent = 0);

  /// Destructor.
  ~ScriptEngine();

protected:
  /// Custom function for handling the script function exit(). Emits the
  /// signal exitScript().
  ///
  /// \param[in] context Script context.
  /// \param[in] engine Script engine which emits the signal.
  /// \return Undefined value.
  static QScriptValue exitScriptFunction(QScriptContext *context,
                                         QScriptEngine *engine);

  /// Adds the custom functions to the script engine.
  void addFunctions();

signals:
  /// Signal to indicate that the function exit() was called in the script.
  void exitScript();
};

#endif
