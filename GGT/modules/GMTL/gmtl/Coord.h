#ifndef COORD_GMTL
#define COORD_GMTL

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
   
   Coord( const Vec<DATA_TYPE, POSSIZE>& pos, const Vec<DATA_TYPE, ROTSIZE>& rot ) : mPos( pos ), mRot( rot )
   {
   }
   
   const Vec<DATA_TYPE, POSSIZE>& getPos() const { return mPos; }
   const Vec<DATA_TYPE, ROTSIZE>& getRot() const { return mRot; }
   
   
   /// @todo what about having a pos, and a const_pos naming convention?
   /// @todo what about having a rot, and a const_rot naming convention?
   
   /** accessor to the position element */
   Vec<DATA_TYPE, POSSIZE>& pos() { return mPos; }

   /** accessor to the rotation element */
   Vec<DATA_TYPE, ROTSIZE>& rot() { return mRot; }
   
   /** const accessor to the position element */
   const Vec<DATA_TYPE, POSSIZE>& pos() const { return mPos; }

   /** const accessor to the rotation element */
   const Vec<DATA_TYPE, ROTSIZE>& rot() const  { return mRot; }

public:
   Vec<DATA_TYPE, POSSIZE> mPos;
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
