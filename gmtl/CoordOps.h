/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: CoordOps.h,v $
 * Date modified: $Date: 2002-06-11 21:20:21 $
 * Version:       $Revision: 1.4 $
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
#ifndef _GMTL_COORD_OPS_H_
#define _GMTL_COORD_OPS_H_

#include <gmtl/Coord.h>

namespace gmtl
{
/** @ingroup Compare Coord 
 * @name Coord Comparitors
 * @{
 */

   /** Compare two quaternions for equality.
    * @see isEqual( Coord, Coord )
    */
   template <typename POS_TYPE, typename ROT_TYPE>
   inline bool operator==( const Coord<POS_TYPE, ROT_TYPE>& q1, 
                           const Coord<POS_TYPE, ROT_TYPE>& q2 )
   {
      return bool( q1.getPos() == q2.getPos() &&
                   q1.getRot() == q2.getRot() );
   }

   /** Compare two quaternions for not-equality.
    * @see isEqual( Coord, Coord )
    */
   template <typename POS_TYPE, typename ROT_TYPE>
   inline bool operator!=( const Coord<POS_TYPE, ROT_TYPE>& q1, 
                           const Coord<POS_TYPE, ROT_TYPE>& q2 )
   {
      return !operator==( q1, q2 );
   }

   /** Compare two quaternions for equality with tolerance.
    */
   template <typename POS_TYPE, typename ROT_TYPE>
   bool isEqual( const Coord<POS_TYPE, ROT_TYPE>& q1, 
                 const Coord<POS_TYPE, ROT_TYPE>& q2, 
                 typename Coord<POS_TYPE, ROT_TYPE>::DataType tol = 
                     (typename Coord<POS_TYPE, ROT_TYPE>::DataType)0.0 )
   {
      return bool( isEqual( q1.getPos(), q2.getPos(), tol ) &&
                   isEqual( q1.getRot(), q2.getRot(), tol )     );
   }
/** @} */

}

#endif
