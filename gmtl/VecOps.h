 /************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecOps.h,v $
 * Date modified: $Date: 2002-03-11 20:18:33 $
 * Version:       $Revision: 1.9 $
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
#ifndef _GMTL_VEC_OPS_H_
#define _GMTL_VEC_OPS_H_

#include <gmtl/gmtlConfig.h>

// Core types
#include <gmtl/Vec.h>

namespace gmtl
{


// --- Basic VEC types operations -- //

/** Add a vector to another vector */
template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE, SIZE>& operator +=(VecBase<DATA_TYPE, SIZE>& v1, const VecBase<DATA_TYPE, SIZE>& v2)
{
   for(unsigned i=0;i<SIZE;++i)
   {
      v1[i] += v2[i];
   }
   
   return v1;
}

template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE, SIZE> operator +(const VecBase<DATA_TYPE, SIZE>& v1, const VecBase<DATA_TYPE, SIZE>& v2)
{
   VecBase<DATA_TYPE, SIZE> ret_val(v1);
   ret_val += v2;
   return ret_val;
}


template<class DATA_TYPE, unsigned SIZE>
VecBase<DATA_TYPE, SIZE>& operator -=(VecBase<DATA_TYPE, SIZE>& v1, const VecBase<DATA_TYPE, SIZE>& v2)
{
   for(unsigned i=0;i<SIZE;++i)
   {
      v1[i] -= v2[i];
   }
   
   return v1;
}


template < class DATA_TYPE, unsigned SIZE>
Vec<DATA_TYPE, SIZE> operator -(const VecBase<DATA_TYPE, SIZE>& v1, const VecBase<DATA_TYPE, SIZE>& v2)
{
   Vec<DATA_TYPE, SIZE> ret_val(v1);
   ret_val -= v2;
   return ret_val;
}

template<class DATA_TYPE, unsigned SIZE, class SCALAR_TYPE>
VecBase<DATA_TYPE, SIZE>& operator *=(VecBase<DATA_TYPE, SIZE>& v1, const SCALAR_TYPE& scalar)
{
   for(unsigned i=0;i<SIZE;++i)
   {
      v1[i] *= scalar;
   }
   
   return v1;
}

template<class DATA_TYPE, unsigned SIZE, class SCALAR_TYPE>
VecBase<DATA_TYPE, SIZE> operator *(const VecBase<DATA_TYPE, SIZE>& v1, const SCALAR_TYPE& scalar)
{
   VecBase<DATA_TYPE, SIZE> ret_val(v1);
   ret_val *= scalar;
   return ret_val;

   //return VecBase<DATA_TYPE, SIZE>(v1) *= scalar;
}


template<class DATA_TYPE, unsigned SIZE, class SCALAR_TYPE>
VecBase<DATA_TYPE, SIZE>& operator /=(VecBase<DATA_TYPE, SIZE>& v1, const SCALAR_TYPE& scalar)
{
   for(unsigned i=0;i<SIZE;++i)
   {
      v1[i] /= scalar;
   }
   
   return v1;
}

template<class DATA_TYPE, unsigned SIZE, class SCALAR_TYPE>
VecBase<DATA_TYPE, SIZE> operator /(const VecBase<DATA_TYPE, SIZE>& v1, const SCALAR_TYPE& scalar)
{
   VecBase<DATA_TYPE, SIZE> ret_val(v1);
   ret_val /= scalar;
   return ret_val;
   // return VecBase<DATA_TYPE, SIZE>(v1)( /= scalar;
}


/** Vector math operations */
//@{

/** Compute dot prodcut of v1 and v2
* @return dotproduct of v1 and v2
*/
template<class DATA_TYPE, unsigned SIZE>
DATA_TYPE dot(const Vec<DATA_TYPE, SIZE>& v1, const Vec<DATA_TYPE, SIZE>& v2)
{
   DATA_TYPE ret_val(0);
   for(unsigned i=0;i<SIZE;++i)
   {
      ret_val += (v1[i] * v2[i]);
   }
   return ret_val;
}

/** Get vector length
* @return length of the vector
*/
template<class DATA_TYPE, unsigned SIZE>
DATA_TYPE length(const Vec<DATA_TYPE, SIZE>& v1)
{
   DATA_TYPE ret_val = lengthSquared(v1);
   if (ret_val == 0.0f)
      return 0.0f;
   else
      return Math::sqrt(ret_val);
}

/** Return the squared length of the vector
* This can be used in many calculations instead of length
* to increase speed
*/
template<class DATA_TYPE, unsigned SIZE>
DATA_TYPE lengthSquared(const Vec<DATA_TYPE, SIZE>& v1)
{
   DATA_TYPE ret_val(0);
   for(unsigned i=0;i<SIZE;++i)
   {
      ret_val += (v1[i] * v1[i]);
   }

   return ret_val;
}

/** Normalize a vector
* @post length(v1) == 1.0
* If the vector already has length of 1.0, then nothing is done
*/
template<class DATA_TYPE, unsigned SIZE>
DATA_TYPE normalize(Vec<DATA_TYPE, SIZE>& v1)
{
   DATA_TYPE len = length(v1);

   if(len != 0.0f)
   {
      for(unsigned i=0;i<SIZE;++i)
      {
         v1[i] /= len;
      }      
   }

   return len;
}

/**
 * Determines if the given vector is normalized within the given tolerance. The
 * vector is normalized if its lengthSquared is 1.
 *
 * @param v1      the vector to test
 * @param eps     the epsilon tolerance
 *
 * @return  true if the vector is normalized, false otherwise
 */
template< class DATA_TYPE, unsigned SIZE >
bool isNormalized( const Vec<DATA_TYPE, SIZE>& v1, const DATA_TYPE eps = (DATA_TYPE)0.0001 )
{
   return Math::isEqual( lengthSquared( v1 ), (DATA_TYPE)1.0, eps );
}

/** cross product (return a copy)
*/
template<class DATA_TYPE>
Vec<DATA_TYPE,3> cross(const Vec<DATA_TYPE, 3>& v1, const Vec<DATA_TYPE, 3>& v2)
{
   return Vec<DATA_TYPE,3>( ((v1[Yelt]*v2[Zelt]) - (v1[Zelt]*v2[Yelt])),
                            ((v1[Zelt]*v2[Xelt]) - (v1[Xelt]*v2[Zelt])),
                            ((v1[Xelt]*v2[Yelt]) - (v1[Yelt]*v2[Xelt])) );
}

/** cross product (returns by reference)
*/
template<class DATA_TYPE>
Vec<DATA_TYPE,3>& cross( Vec<DATA_TYPE,3>& result, const Vec<DATA_TYPE, 3>& v1, const Vec<DATA_TYPE, 3>& v2)
{
   result.set( ((v1[Yelt]*v2[Zelt]) - (v1[Zelt]*v2[Yelt])),
               ((v1[Zelt]*v2[Xelt]) - (v1[Xelt]*v2[Zelt])),
               ((v1[Xelt]*v2[Yelt]) - (v1[Yelt]*v2[Xelt])) );
   return result;
}

//@}


// --- VEC comparisons -- //

/** Compare two vecs */
template<class DATA_TYPE, unsigned SIZE>
inline bool operator ==(const VecBase<DATA_TYPE, SIZE>& v1, const VecBase<DATA_TYPE, SIZE>& v2)
{
   for(unsigned i=0;i<SIZE;++i)
   {
      if(v1[i] != v2[i])
      {
         return false;
      }
   }

   return true;

   /*  Would like this
   return(vec[0] == _v[0] &&
          vec[1] == _v[1] &&
          vec[2] == _v[2]);
          */
}

template<class DATA_TYPE, unsigned SIZE>
inline bool operator !=(const VecBase<DATA_TYPE, SIZE>& v1, const VecBase<DATA_TYPE, SIZE>& v2)
{
   return(! (v1 == v2));
}

/** Compare two vectors with a tolerance
* @pre eps must be >= 0
*/
template<class DATA_TYPE, unsigned SIZE>
inline bool isEqual(const VecBase<DATA_TYPE, SIZE>& v1, const VecBase<DATA_TYPE, SIZE>& v2, const DATA_TYPE& eps)
{
   ggtASSERT(eps >= 0);

  for(unsigned i=0;i<SIZE;++i)
  {
     if (fabs(v1[i] - v2[i]) > eps)
        return false;
  }
  return true;
}


};

#endif

