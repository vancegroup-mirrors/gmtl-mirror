#ifndef COORD_GMTL
#define COORD_GMTL

#include <gmtl/Vec.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/EulerAngle.h>

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
 * @see Vec, AxisAngle, EulerAngle 
 * @ingroup Types
 */
template <typename POS_TYPE, typename ROT_TYPE>
class Coord
{
public:
   Coord() : mPos(), mRot()
   {
   }
   
   typedef typename POS_TYPE::DataType DataType;
   typedef POS_TYPE PosDataType;
   typedef ROT_TYPE RotDataType;
   enum
   {
       PosSize = POS_TYPE::Size,
       RotSize = ROT_TYPE::Size
   };
    
   Coord( const Coord<POS_TYPE, ROT_TYPE>& coord ) : mPos( coord.mPos ), mRot( coord.mRot )
   {
   }
   
   Coord( const POS_TYPE& pos, const ROT_TYPE& rot ) : mPos( pos ), mRot( rot )
   {
   }
   
   const POS_TYPE& getPos() const { return mPos; }
   const ROT_TYPE& getRot() const { return mRot; }
   
   /// @todo what about having a pos, and a const_pos naming convention?
   /// @todo what about having a rot, and a const_rot naming convention?
   
   /** accessor to the position element */
   POS_TYPE& pos() { return mPos; }

   /** accessor to the rotation element */
   ROT_TYPE& rot() { return mRot; }
   
   /** const accessor to the position element */
   //const POS_TYPE& pos() const { return mPos; }

   /** const accessor to the rotation element */
   //const ROT_TYPE& rot() const  { return mRot; }

public:
   POS_TYPE mPos;
   ROT_TYPE mRot;
};

typedef Coord<Vec3d, EulerAngleXYZd> CoordVec3EulerAngleXYZd;
typedef Coord<Vec3f, EulerAngleXYZf> CoordVec3EulerAngleXYZf;
typedef Coord<Vec4d, EulerAngleXYZd> CoordVec4EulerAngleXYZd;
typedef Coord<Vec4f, EulerAngleXYZf> CoordVec4EulerAngleXYZf;

typedef Coord<Vec3d, EulerAngleZYXd> CoordVec3EulerAngleZYXd;
typedef Coord<Vec3f, EulerAngleZYXf> CoordVec3EulerAngleZYXf;
typedef Coord<Vec4d, EulerAngleZYXd> CoordVec4EulerAngleZYXd;
typedef Coord<Vec4f, EulerAngleZYXf> CoordVec4EulerAngleZYXf;

typedef Coord<Vec3d, EulerAngleZXYd> CoordVec3EulerAngleZXYd;
typedef Coord<Vec3f, EulerAngleZXYf> CoordVec3EulerAngleZXYf;
typedef Coord<Vec4d, EulerAngleZXYd> CoordVec4EulerAngleZXYd;
typedef Coord<Vec4f, EulerAngleZXYf> CoordVec4EulerAngleZXYf;

typedef Coord<Vec3d, AxisAngled> CoordVec3AxisAngled;
typedef Coord<Vec3f, AxisAnglef> CoordVec3AxisAnglef;
typedef Coord<Vec4d, AxisAngled> CoordVec4AxisAngled;
typedef Coord<Vec4f, AxisAnglef> CoordVec4AxisAnglef;

}

#endif
