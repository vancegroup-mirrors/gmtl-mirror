// this file for documentation purposes only (for doxygen generation)

/** @defgroup Defines Global Flags: Xelt, XYZ, etc...
 *  Constant Static Global Flags
 */
 
/** @defgroup Math C Math Abstraction: sin, cos, tan, Min, Max, PI
 *  We've abstracted C math to be cross platform and typesafe.
 */

/** @defgroup Types Abstract Data Types: Matrix, Vec, Quat, Coord, Sphere, Plane
 *  GMTL comes with many math data types: Vec, Point, Matrix, Quat, Coord, Sphere.
 */



/** @defgroup Ops Mathematical Operations: add(...), sub(...), mul(...), div(...), invert(...), dot(...), cross(...)
 *  Implements fundamental mathematical operations such as +, -, *, invert, dot product.
 */

/** @defgroup Transforms Spacial Transformers: xform( ... ), operator*( ... ).
 *  Transform points and vectors by Matrices and Quaternions.  Note that xform
 *  is defined differently for Point and Vec.  By Point is a full xform, by Vec 
 *  is only a rotation.
 */

/** @defgroup Compare Comparison: isEqual(...), isEquiv(...), ==, !=
 *  Tests for equality between GMTL data types.
 */

/** @defgroup Generate Generators: make( ... ), get( ... ), set( ... ), and convert( ... ).
 *  Make get and set functions for all math types in gmtl.
 */

/** @defgroup Convert Conversion: convert(...)
 *  Conversion between gmtl data types...
 */

/** @defgroup Interp Interpolation: lerp(...), slerp(...)
 *  Functions to interpolate between two values.
 */
 

/** @defgroup Output Output Stream Methods: operator<<( ... ). 
 *  Output GMTL data types to an ostream.  std::ostream& operator<< methods...
 */


/** @defgroup Meta Template Metaprogramming Utilities */
/** @defgroup HelperMeta Template Metaprogramming Utilities (Helpers) */
