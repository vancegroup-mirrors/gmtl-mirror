/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Vec.h,v $
 * Date modified: $Date: 2002-05-17 20:01:30 $
 * Version:       $Revision: 1.7 $
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
#ifndef _GMTL_VEC_H_
#define _GMTL_VEC_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/VecBase.h>

namespace gmtl
{

/**
 * A representation of a vector with SIZE components using DATA_TYPE as the data
 * type for each component.
 *
 * @param DATA_TYPE     the datatype to use for the components
 * @param SIZE          the number of components this VecBase has
 * @addtogroup Types
 */
template<class DATA_TYPE, unsigned SIZE>
class Vec : public VecBase<DATA_TYPE, SIZE>
{
public:
   /// The datatype used for the components of this Vec.
   typedef DATA_TYPE DataType;

   /// The number of components this Vec has.
   enum { Size = SIZE };

   /// The superclass type.
   typedef VecBase<DATA_TYPE, SIZE> BaseType;

public:
   /**
    * Default constructor. All components are initialized to zero.
    */
   Vec()
   {
      for (unsigned i = 0; i < SIZE; ++i)
         mData[i] = (DATA_TYPE)0;
   }

   /// @name Value constructors
   //@{
   /**
    * Make an exact copy of the given Vec object.
    *
    * @param rVec    the Vec object to copy
    */
   Vec(const Vec<DATA_TYPE, SIZE>& rVec)
      : BaseType(static_cast<BaseType>(rVec))
   {;}
   Vec(const VecBase<DATA_TYPE, SIZE>& rVec)
      : BaseType(rVec)
   {;}

   /**
    * Creates a new Vec initialized to the given values.
    */
   Vec(const DATA_TYPE& val0)
      : BaseType(val0)
   {;}

   Vec(const DATA_TYPE& val0,const DATA_TYPE& val1)
   : BaseType(val0, val1)
   {;}

   Vec(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2)
   : BaseType(val0, val1, val2)
   {;}

   Vec(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2,const DATA_TYPE& val3)
   : BaseType(val0, val1, val2, val3)
   {;}
   //@}
};

// --- helper types --- //
typedef Vec<float,2> Vec2f;
typedef Vec<double,2> Vec2d;
typedef Vec<float,3> Vec3f;
typedef Vec<double,3> Vec3d;
typedef Vec<float,4> Vec4f;
typedef Vec<double,4> Vec4d;

};

#endif
