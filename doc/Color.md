Color
=====

The _Color_ object holds an RGB-color and is mainly used to pass a color from a script to a connected device.

The color components are red, green, and blue. Their values are between 0 and 255 (inclusive) and the default color for a _Color_ object is black (r = 0, g = 0, b = 0).

Functions
---------

### Color()

Constructs a new _Color_ object with the default color black.

```javascript
var color = new Color;
```

### Color(r, g, b)

Constructs a new _Color_ object with the supplied color components.

```javascript
// set color to chocolate (r = 210, g = 105, b = 30)
var color = new Color(210, 105, 30);
```

### b

The blue color component is a property of the _Color_ object.

```javascript
var color = new Color(210, 105, 30);

// get blue color component
var blue = color.b;

// set blue color component
color.b = 127;
```

### g

The green color component is a property of the _Color_ object.

```javascript
var color = new Color(210, 105, 30);

// get green color component
var green = color.g;

// set green color component
color.g = 64;
```

### r

The red color component is a property of the _Color_ object.

```javascript
var color = new Color(210, 105, 30);

// get red color component
var red = color.r;

// set red color component
color.r = 255;
```

### void set(r, g, b)

Sets the color components of the _Color_ object.

```javascript
var color = new Color;

color.set(210, 105, 30);
```
