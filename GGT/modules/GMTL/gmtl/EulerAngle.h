/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: EulerAngle.h,v $
 * Date modified: $Date: 2002-06-06 19:30:25 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001,2002 Allen Bierbaum
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
 ************************************************************ ggt-cpr end */
#ifndef _GMTL_EULERANGLE_H_
#define _GMTL_EULERANGLE_H_

#include <gmtl/Math.h>     // for rotation order
#include <gmtl/VecBase.h>  // base class of EulerAngle
 
namespace gmtl
{

/** EulerAngle: Represents a group of euler angles.
 *  Euler angle can be used to represent rotations in 3-space.
 *
 *  To some people this rotation format can be more intuitive to specify than
 *  Matrix, Quat, or EulerParam formatted rotation.
 *
 *  For efficiency and to minimize problems from gimbal-lock, you should use
 *  one of the other rotation formats instead (Quat or Matrix are preferred).
 *
 * @pre all angles are in radians.
 *
 * @see EulerAngle3f, EulerAngle3d
 * @see Matrix, Quat, EulerParam
 * @ingroup Types
 */
template <typename DATA_TYPE, unsigned SIZE>
class EulerAngle : public VecBase<DATA_TYPE, SIZE>
{
public:
   /** default constructor. initializes to identity rotation (no rotation). */
   EulerAngle() : mOrder( gmtl::XYZ )
   {
      // @todo metaprogramming
      for (unsigned int x = 0; x < SIZE; ++x)
      {
         // init to identity.
         this->operator[]( x ) = (DATA_TYPE)0;
      }
   }
   
   /** copy constructor. */
   EulerAngle( const EulerAngle& e ) : VecBase<DATA_TYPE, SIZE>( e ),
         mOrder( e.getOrder() )
   {
   }
   
   /** data constructor.   angles are in radians. */
   EulerAngle( DATA_TYPE p0, DATA_TYPE p1, DATA_TYPE p2, RotationOrder order )
   {
      gmtlASSERT( SIZE == 3 && "this EulerAngle constructor can't be used when SIZE != 3" );
      this->operator[]( 0 ) = p0;
      this->operator[]( 1 ) = p1;
      this->operator[]( 2 ) = p2;
      mOrder = order;
   }
   
   /** set data.   angles are in radians. */
   void set( const DATA_TYPE& p0, const DATA_TYPE& p1, const DATA_TYPE& p2, const RotationOrder& order )
   {
      gmtlASSERT( SIZE == 3 && "set(x,y,z,o) can't be used when SIZE != 3" );
      VecBase<DATA_TYPE, SIZE>::set( p0, p1, p2 );
      mOrder = order;
   }

   /** get the rotation order.
    *  this is the order that you would perform rotations to get to the 
    *  final rotation
    * @see RotationOrder
    */
   const RotationOrder& getOrder() const { return mOrder; }
   
   /** set the rotation order.
    *  this is the order that you would perform rotations to get to the 
    *  final rotation
    * @see RotationOrder
    */
   void setOrder( const RotationOrder& o ) { mOrder = o; }
   
private:
   RotationOrder mOrder;
};

const EulerAngle<float, 3> EULERANGLE_IDENTITY3F( 0.0f, 0.0f, 0.0f, gmtl::XYZ );
const EulerAngle<double, 3> EULERANGLE_IDENTITY3D( 0.0, 0.0, 0.0, gmtl::XYZ );

typedef EulerAngle<float, 3> EulerAngle3f;
typedef EulerAngle<double, 3> EulerAngle3d;

} // end of namespace gmtl

#endif
