#ifndef COORD_GMTL
#define COORD_GMTL

#include <gmtl/Point.h>
#include <gmtl/Vec.h>

namespace gmtl
{
   
/** coord is a position/rotation pair. 
 *  coord consists of a position element and a rotation element.
 *
 * <h3> "How to define an Point/Euler pair (32 bit float precision):" </h3>
 * \code
 *    Coord<float, 3, 3> myEulerCoord;
 * \endcode
 *
 * <h3> "Or use the built in typedefs:" </h3>
 * \code
 *    CoordVec3dEuler myEulerCoord;
 *    CoordVec4fEuler myOtherEulerCoord;
 * \endcode
 */
template <typename DATA_TYPE, unsigned POSSIZE, unsigned ROTSIZE>
class Coord
{
public:
   Coord() : mPos(), mRot()
   {
   }
   
   typedef DATA_TYPE DataType;
   enum
   {
       PosSize = POSSIZE,
       RotSize = ROTSIZE
   };
    
   Coord( const Coord<DATA_TYPE, POSSIZE, ROTSIZE>& coord ) : mPos( coord.mPos ), mRot( coord.mRot )
   {
   }
   
   Coord( const Point<DATA_TYPE, POSSIZE>& pos, const Vec<DATA_TYPE, ROTSIZE>& rot ) : mPos( pos ), mRot( rot )
   {
   }
   
   const Point<DATA_TYPE, POSSIZE>& getPos() const { return mPos; }
   const Vec<DATA_TYPE, ROTSIZE>& getRot() const { return mRot; }
   
   /** accessor to the position element */
   Point<DATA_TYPE, POSSIZE>& pos() { return mPos; }

   /** accessor to the rotation element */
   Vec<DATA_TYPE, ROTSIZE>& rot() { return mRot; }

public:
   Point<DATA_TYPE, POSSIZE> mPos;
   Vec<DATA_TYPE, ROTSIZE> mRot;
};

typedef Coord<double, 3, 3> CoordVec3dEuler;
typedef Coord<float, 3, 3> CoordVec3fEuler;
typedef Coord<double, 4, 3> CoordVec4dEuler;
typedef Coord<float, 4, 3> CoordVec4fEuler;
typedef Coord<double, 3, 4> CoordVec3dAxisAngle;
typedef Coord<float, 3, 4> CoordVec3fAxisAngle;
typedef Coord<double, 4, 4> CoordVec4dAxisAngle;
typedef Coord<float, 4, 4> CoordVec4fAxisAngle;

}

#endif
