#ifndef VST_COLOR_H
#define VST_COLOR_H

#include <QObject>
#include <QtScript/QScriptEngine>

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
  /// \param[in] parent Parent of this object.
  explicit Color(QObject *parent = nullptr);
  
  /// Constructor, takes RGB color.
  ///
  /// \param[in] r Red component of color, range 0 <= r <= 255.
  /// \param[in] g Green component of color, range 0 <= g <= 255.
  /// \param[in] b Blue component of color, range 0 <= b <= 255.
  /// \param[in] parent Parent of this object.
  Color(quint8 r, quint8 g, quint8 b, QObject *parent = nullptr);

  /// Destructor.
  virtual ~Color();

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
  /// \param[in] r Red component, range 0 <= r <= 255.
  void r(quint8 r);

  /// Returns the green component of the color.
  ///
  /// \return Green component.
  quint8 g() const;

  /// Sets the green component of the color.
  ///
  /// \param[in] g Green component, range 0 <= g <= 255.
  void g(quint8 g);

  /// Returns the blue component of the color.
  ///
  /// \return Blue component.
  quint8 b() const;

  /// Sets the blue component of the color.
  ///
  /// \param[in] b Blue component, range 0 <= b <= 255.
  void b(quint8 b);

  /// Sets the color with the given components.
  ///
  /// \param[in] r Red component of color, range 0 <= r <= 255.
  /// \param[in] g Green component of color, range 0 <= g <= 255.
  /// \param[in] b Blue component of color, range 0 <= b <= 255.
  Q_INVOKABLE void set(quint8 r, quint8 g, quint8 b);

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

Q_DECLARE_METATYPE(Color)

/// Custom constructor function for a Color object. This function makes it 
/// possible to create a Color object in a script:
///
/// var color = new Color;
/// var color2 = new Color(128, 0, 255);
///
/// \param[in] context Script context for the Color object. If color components
/// (red, green, blue) are supplied in the constructor, the fourth argument of
/// the script context is the parent of the new Color object. In other cases the
/// first argument of the script context is taken to be the parent of the new
/// Color object.
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
                                const Color &color);

/// Custom function to set a Color object from a QScriptValue object. The 
/// actual conversion is performed by the function Color::fromScriptValue().
///
/// \param[in] object QScriptValue object to set from.
/// \param[out] color Color object to set.
void colorFromScriptValue(const QScriptValue &object, 
                          Color &color);

#endif
