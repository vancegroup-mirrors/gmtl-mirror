/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: EulerAngle.h,v $
 * Date modified: $Date: 2002-06-10 18:28:15 $
 * Version:       $Revision: 1.2 $
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
template <typename DATA_TYPE>
class EulerAngle : public VecBase<DATA_TYPE, 3>
{
public:
   /** default constructor. initializes to identity rotation (no rotation). */
   EulerAngle() : 
      VecBase<DATA_TYPE, 3>( (DATA_TYPE)0.0, (DATA_TYPE)0.0, (DATA_TYPE)0.0 ),
      mOrder( gmtl::XYZ )
   {
   }
   
   /** copy constructor. */
   EulerAngle( const EulerAngle& e ) : VecBase<DATA_TYPE, 3>( e ),
         mOrder( e.getOrder() )
   {
   }
   
   /** data constructor.   angles are in radians. */
   EulerAngle( DATA_TYPE p0, DATA_TYPE p1, DATA_TYPE p2, 
               RotationOrder order ) :
            VecBase<DATA_TYPE, 3>( p0, p1, p2 ), 
            mOrder( order )
   {
   }
   
   /** set data.   angles are in radians. */
   void set( const DATA_TYPE& p0, const DATA_TYPE& p1, 
             const DATA_TYPE& p2, const RotationOrder& order )
   {
      VecBase<DATA_TYPE, 3>::set( p0, p1, p2 );
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

const EulerAngle<float> EULERANGLE_IDENTITYF( 0.0f, 0.0f, 0.0f, gmtl::XYZ );
const EulerAngle<double> EULERANGLE_IDENTITYD( 0.0, 0.0, 0.0, gmtl::XYZ );

typedef EulerAngle<float> EulerAnglef;
typedef EulerAngle<double> EulerAngled;

} // end of namespace gmtl

#endif
