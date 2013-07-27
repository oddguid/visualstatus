#ifndef VST_COLOR_H
#define VST_COLOR_H

#include <QObject>
#include <qscriptengine>

namespace script
{

/// Script class for RGB color.
class Color : public QObject
{
  Q_OBJECT

  Q_PROPERTY(quint8 r READ r WRITE r)
  Q_PROPERTY(quint8 g READ g WRITE g)
  Q_PROPERTY(quint8 b READ b WRITE b)

private:
  quint8 m_r;
  quint8 m_g;
  quint8 m_b;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of his object.
  explicit Color(QObject *parent = 0);
  
  /// Destructor.
  ~Color();

  /// Copy constructor.
  ///
  /// \param[in] that Object to copy.
  Color(const Color &that);

  /// Assignment operator.
  ///
  /// \param[in] that Object to copy.
  Color &operator=(const Color &that);

  /// Returns the red component of the color.
  ///
  /// \return Red component.
  quint8 r() const;

  /// Sets the red component of the color.
  ///
  /// \param[in] r Red component.
  void r(quint8 r);

  /// Returns the green component of the color.
  ///
  /// \return Green component.
  quint8 g() const;

  /// Sets the green component of the color.
  ///
  /// \param[in] g Green component.
  void g(quint8 g);

  /// Returns the blue component of the color.
  ///
  /// \return Blue component.
  quint8 b() const;

  /// Sets the blue component of the color.
  ///
  /// \param[in] b Blue component.
  void b(quint8 b);

  /// Converts the RGB color object to a QScriptValue object. The QScriptValue
  /// object will have the following properties:
  /// - r
  /// - g
  /// - b
  ///
  /// \param[in] engine Script engine that will create the QScriptValue object.
  /// \return QScriptValue object.
  QScriptValue toScriptValue(QScriptEngine *engine) const;

  /// Sets the RGB color from the given QScriptValue object. The QScriptValue
  /// object should have the following properties:
  /// - r
  /// - g
  /// - b
  ///
  /// If a property is not found, the value of the color component will be set
  /// to 0.
  ///
  /// \param[in] object QScriptValue object to set from.
  void fromScriptValue(const QScriptValue &object);
};

#ifdef WIN32
Q_DECLARE_METATYPE(Color);
#endif

} // script

#ifndef WIN32
Q_DECLARE_METATYPE(script::Color);
#endif

/// Custom constructor function for a Color object. This function makes it 
/// possible to create a Color object in a script:
///
/// var color = new Color;
///
/// \param[in] context Script context for the Color object. The first argument
/// of the script context is the parent of the new Color object.
/// \param[in] engine Script engine which will take ownership of the new Color
/// object.
/// \return The new Color object wrapped in a script object.
QScriptValue colorConstructor(QScriptContext *context,
                              QScriptEngine *engine);

/// Custom function to convert a Color object to a QScriptValue object. The 
/// actual conversion is performed by the function Color::toScriptValue().
///
/// \param[in] engine Script engine that will create the QScriptValue object.
/// \return QScriptValue object.
QScriptValue colorToScriptValue(QScriptEngine *engine, 
                                const script::Color &color);

/// Custom function to set a Color object from a QScriptValue object. The 
/// actual conversion is performed by the function Color::fromScriptValue().
///
/// \param[in] object QScriptValue object to set from.
/// \param[out] color Color object to set.
void colorFromScriptValue(const QScriptValue &object, 
                          script::Color &color);

#endif
