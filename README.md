# ColorSpaces

A C++ library for color space conversion and calculating color difference. This library supports a variety of color models and offers functions for converting between them as well as calculating color distances.

### Dependencies

- **Make**
- **C++17** or higher

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/ColorSpaces.git
   cd ColorSpaces
	```

3. Build the library:
	```bash
	make
	```

4. To run tests:
	```bash
	make run
	```

5. Integrate the library into your project by including the necessary files:
	* colorDefinitions.h
	* util.h
	* Relevant src files for your use case

### Usage

Once integrated, you can use the library functions to convert between color spaces and calculate color differences. Example usage:

```cpp
#include "colorDefinitions.h"

// Convert between color spaces (sRGB to LinearRGB shown)
ColorSpace::Srgb color(255, 100, 50);
ColorSpace::LinearRgb linearColor = color.toLinearRgb();

// Get channel values. Most color spaces will return a 3-element float array
std::array<float, 3> = linearColor().getValues();

// Calculate Euclidean distance between two colors
float distance = ColorSpace::distEuclideanSquared(colorA, colorB);
```

### Supported Color Spaces
* sRGB
* RGB
* Lab
* XYZ
* xyY
* Luv
* LCH(ab)
* LCH(uv)

### Supported Conversions
![conversion-diagram](/documentationMedia/colorDiagram.png)

### Supported Distance Metrics
* Euclidean Distance

### References
* [Bruce Lindbloom's Color Science](<http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html>)
* [yy_color_converter (GitHub)](<https://github.com/ibireme/yy_color_convertor>)
* [ColorSpace Project (GitHub)](<https://github.com/berendeanicolae/ColorSpace?tab=readme-ov-file>)
