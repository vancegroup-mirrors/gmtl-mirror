/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecBase.h,v $
 * Date modified: $Date: 2002-03-15 03:26:57 $
 * Version:       $Revision: 1.6 $
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
#ifndef _GMTL_VECBASE_H_
#define _GMTL_VECBASE_H_

#include <iostream>
#include <gmtl/gmtlConfig.h>

namespace gmtl
{

template<class DATA_TYPE, unsigned SIZE>
class VecBase
{
public:
   typedef DATA_TYPE DataType;
   enum { Size = SIZE };

public:
   /** Default constructor.
   * Does nothing, leaves data alone.
   * This is for performance because this constructor is called by derived class constructors
   * Even when they just want to set the data directly
   */
   VecBase() {;}
   VecBase(const VecBase<DATA_TYPE, SIZE>& rVec);

   VecBase(const DATA_TYPE& val0);
   VecBase(const DATA_TYPE& val0,const DATA_TYPE& val1);
   VecBase(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2);
   VecBase(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2,const DATA_TYPE& val3);

      // Setting
   inline void set(const DATA_TYPE* dataPtr);
   inline void set(const DATA_TYPE& val0);
   inline void set(const DATA_TYPE& val0,const DATA_TYPE& val1);
   inline void set(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2);
   inline void set(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2,const DATA_TYPE& val3);

   // Member access
   inline DATA_TYPE& operator [](const unsigned i)
   {
      gmtlASSERT(i < SIZE);
      return mData[i];
   }
   inline const DATA_TYPE&  operator [](const unsigned i) const
   {
      gmtlASSERT(i < SIZE);
      return mData[i];
   }

   DATA_TYPE* getData()
   { return mData; }
   const DATA_TYPE* getData() const
   { return mData; }

public:
   DATA_TYPE mData[SIZE];
};

// --- Inline members --- //
template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE,SIZE>::VecBase(const VecBase<DATA_TYPE, SIZE>& rVec)
{
   for(unsigned i=0;i<SIZE;++i)
      mData[i] = rVec.mData[i];
}

template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE,SIZE>::VecBase(const DATA_TYPE& val0)
{
   gmtlASSERT( SIZE >= 1 && "out of bounds element access in VecBase" );
   mData[0] = val0;
}

template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE,SIZE>::VecBase(const DATA_TYPE& val0,const DATA_TYPE& val1)
{
   gmtlASSERT( SIZE >= 2 && "out of bounds element access in VecBase" );
   mData[0] = val0;
   mData[1] = val1;
}

template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE,SIZE>::VecBase(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2)
{
   gmtlASSERT( SIZE >= 3 && "out of bounds element access in VecBase" );
   mData[0] = val0;
   mData[1] = val1;
   mData[2] = val2;
}

template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE,SIZE>::VecBase(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2,const DATA_TYPE& val3)
{
   gmtlASSERT( SIZE >= 4 && "out of bounds element access in VecBase" );
   mData[0] = val0;
   mData[1] = val1;
   mData[2] = val2;
   mData[3] = val3;
}


// Setting
template<class DATA_TYPE, unsigned SIZE>
inline void VecBase<DATA_TYPE,SIZE>::set(const DATA_TYPE* dataPtr)
{
   for(unsigned i=0;i<SIZE;++i)
      mData[i] = dataPtr[i];
}
template<class DATA_TYPE, unsigned SIZE>
inline void VecBase<DATA_TYPE,SIZE>::set(const DATA_TYPE& val0)
{
   gmtlASSERT( SIZE >= 1 && "out of bounds element access in VecBase" );
   mData[0] = val0;
}
template<class DATA_TYPE, unsigned SIZE>
inline void VecBase<DATA_TYPE,SIZE>::set(const DATA_TYPE& val0,const DATA_TYPE& val1)
{
   gmtlASSERT( SIZE >= 2 && "out of bounds element access in VecBase" );
   mData[0] = val0;
   mData[1] = val1;
}
template<class DATA_TYPE, unsigned SIZE>
inline void VecBase<DATA_TYPE,SIZE>::set(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2)
{
   gmtlASSERT( SIZE >= 3 && "out of bounds element access in VecBase" );
   mData[0] = val0;
   mData[1] = val1;
   mData[2] = val2;
}
template<class DATA_TYPE, unsigned SIZE>
inline void VecBase<DATA_TYPE,SIZE>::set(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2,const DATA_TYPE& val3)
{
   gmtlASSERT( SIZE >= 4 && "out of bounds element access in VecBase" );
   mData[0] = val0;
   mData[1] = val1;
   mData[2] = val2;
   mData[3] = val3;
}

};

#endif
