/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatOps.h,v $
 * Date modified: $Date: 2002-02-21 21:37:08 $
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
#ifndef _GMTL_QUAT_H_
#define _GMTL_QUAT_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Quat.h>

namespace gmtl 
{
   /** product of two quaternions (quaternion product)
    *  @post this' = q1 * q2
    *  @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& mult( Quat<DATA_TYPE>& result, const Quat<DATA_TYPE>& q1, const Quat<DATA_TYPE>& q2 )
   {
      // Here is the easy to understand equation: (grassman product)
      // scalar_component = q1.s * q2.s - dot(q1.v, q2.v)
      // vector_component = q2.v * q1.s + q1.v * q2.s + cross(q1.v, q2.v)

      // Here is another version (euclidean product, just FYI)...
      // scalar_component = q1.s * q2.s + dot(q1.v, q2.v)
      // vector_component = q2.v * q1.s - q1.v * q2.s - cross(q1.v, q2.v)

      // Here it is, using vector algebra (grassman product)
      /*
      const float& w1( q1[Welt] ), w2( q2[Welt] );
      Vec3 v1( q1[Xelt], q1[Yelt], q1[Zelt] ), v2( q2[Xelt], q2[Yelt], q2[Zelt] );

      float w = w1 * w2 - v1.dot( v2 );
      Vec3 v = (w1 * v2) + (w2 * v1) + v1.cross( v2 );

      vec[Welt] = w;
      vec[Xelt] = v[0];
      vec[Yelt] = v[1];
      vec[Zelt] = v[2];
      */
            
      // Here is the same, only expanded... (grassman product)
      Quat temporary; // avoid aliasing problems...
      temporary[Xelt] = q1[Welt]*q2[Xelt] + q1[Xelt]*q2[Welt] + q1[Yelt]*q2[Zelt] - q1[Zelt]*q2[Yelt];
      temporary[Yelt] = q1[Welt]*q2[Yelt] + q1[Yelt]*q2[Welt] + q1[Zelt]*q2[Xelt] - q1[Xelt]*q2[Zelt];
      temporary[Zelt] = q1[Welt]*q2[Zelt] + q1[Zelt]*q2[Welt] + q1[Xelt]*q2[Yelt] - q1[Yelt]*q2[Xelt];
      temporary[Welt] = q1[Welt]*q2[Welt] - q1[Xelt]*q2[Xelt] - q1[Yelt]*q2[Yelt] - q1[Zelt]*q2[Zelt];

      // use a temporary, in case q1 or q2 is the same as self.
      result[Xelt] = temporary[Xelt];
      result[Yelt] = temporary[Yelt];
      result[Zelt] = temporary[Zelt];
      result[Welt] = temporary[Welt];

      // don't normalize, because it might not be rotation arithmetic we're doing
      // (only rotation quats have unit length)
      return result;
   }
   
   /** vector scalar multiplication
    * @post result' = [qx*s, qy*s, qz*s, qw*s]
    * @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& mult( Quat<DATA_TYPE>& result, const Quat<DATA_TYPE>& q, DATA_TYPE s )
   {
      result[0] = q[0] * s;
      result[1] = q[1] * s;
      result[2] = q[2] * s;
      result[3] = q[3] * s;
   }
   
   /** quotient of two quaternions
    * @post result = q1 / q2
    * @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& div( Quat<DATA_TYPE>& result, const Quat<DATA_TYPE>& q1, const Quat<DATA_TYPE>& q2 )
   {
      Quat q2_inv( q2 ), r, s;

      // invert the quat
      invert( q2_inv );

      mult( r, q1, q2_inv );
      mult( s, q2_inv, q2_inv );

      float sw_inv = 1.0f / s[Welt];
      result[0] = r[0] * sw_inv;
      result[1] = r[1] * sw_inv;
      result[2] = r[2] * sw_inv;
      result[3] = r[3] * sw_inv;
      return result;
   }

   /** vector addition
    * @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& add( Quat<DATA_TYPE>& result, const Quat<DATA_TYPE>& q1, const Quat<DATA_TYPE>& q2 )
   {
      result[0] = q1[0] + q2[0];
      result[1] = q1[1] + q2[1];
      result[2] = q1[2] + q2[2];
      result[3] = q1[3] + q2[3];
   }

   /** vector subtraction
    *  @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& sub( Quat<DATA_TYPE>& result, const Quat<DATA_TYPE>& q1, const Quat<DATA_TYPE>& q2 )
   {
      result[0] = q1[0] - q2[0];
      result[1] = q1[1] - q2[1];
      result[2] = q1[2] - q2[2];
      result[3] = q1[3] - q2[3];
   }

   /** vector dot product
    *  get the lengthSquared between two quat vectors...
    *  @post result = x1*x2 + y1*y2 + z1*z2 + w1*w2
    *  @see Quat
    */
   template <typename DATA_TYPE>
   DATA_TYPE dot( const Quat<DATA_TYPE>& q1, const Quat<DATA_TYPE>& q2 ) const
   {
      return DATA_TYPE( (q1[0] * q2[0]) + 
                        (q1[1] * q2[1]) + 
                        (q1[2] * q2[2]) + 
                        (q1[3] * q2[3])  );
   }
   
   /** quaternion "norm" (also known as vector length squared)
    *  using this can be faster than using length for some operations...
    *  @post returns the vector length squared
    *  @post result = x*x + y*y + z*z + w*w
    *  @see Quat
    */
   template <typename DATA_TYPE>
   DATA_TYPE lengthSquared( const Quat<DATA_TYPE>& q ) const
   {
      return dot( q, q );
   }
   
   /** quaternion "absolute" (also known as vector length or magnitude)
    *  using this can be faster than using length for some operations...
    *  @post returns the magnitude of the 4D vector.  
    *  @post result = sqrt( lengthSquared( q ) )
    *  @see Quat
    */
   template <typename DATA_TYPE>
   DATA_TYPE length( const Quat<DATA_TYPE>& q ) const
   {
      return Math::sqrt( lengthSquared( q ) );
   } 
   
   /** set self to the normalized quaternion of self.
    *  @pre magnitude should be > 0, otherwise no calculation is done.
    *  @post result' = normalize( result ), where normalize makes length( result ) == 1
    *  @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& normalize( Quat<DATA_TYPE>& result )
   {
      DATA_TYPE l = length( result );
   
      // return if no magnitude (already as normalized as possible)
      if (l < (DATA_TYPE)0.0001) 
         return result;

      DATA_TYPE l_inv = ((DATA_TYPE)1.0) / l;
      result[Xelt] *= l_inv;
      result[Yelt] *= l_inv;
      result[Zelt] *= l_inv;
      result[Welt] *= l_inv;
      
      return result;
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
   template< typename DATA_TYPE >
   bool isNormalized( const Quat<DATA_TYPE>& v1, const DATA_TYPE eps = (DATA_TYPE)0.0001f )
   {
      return Math::isEqual( lengthSquared( q1 ), DATA_TYPE(1), eps );
   }
   
   /** quaternion complex conjugate (when quat is a rotation, this is also the same as the inverse of the rotation).
    *  @post set result to the complex conjugate of result.
    *  @post result'[x,y,z,w] == result[-x,-y,-z,w]
    *  @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& invert( Quat<DATA_TYPE>& result )
   {
      result[Xelt] = -result[Xelt];
      result[Yelt] = -result[Yelt];
      result[Zelt] = -result[Zelt];
      return result;
   }
   
   /** complex exponentiation.
    *  @pre safe to pass self as argument
    *  @post sets self to the exponentiation of quat
    *  @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& exp( Quat<DATA_TYPE>& result )
   {
      DATA_TYPE len1, len2;

      len1 = Math::sqrt( result[Xelt] * result[Xelt] +
                         result[Yelt] * result[Yelt] +
                         result[Zelt] * result[Zelt] );
      if (len1 > (DATA_TYPE)0.0)
         len2 = Math::sin( len1 ) / len1;
      else
         len2 = (DATA_TYPE)1.0;

      result[Xelt] = result[Xelt] * len2;
      result[Yelt] = result[Yelt] * len2;
      result[Zelt] = result[Zelt] * len2;
      result[Welt] = Math::cos( len1 );
      
      return result;
   }

   /** complex logarithm
    *  @post sets self to the log of quat
    *  @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& log( Quat<DATA_TYPE>& result )
   {
      DATA_TYPE length;

      length = Math::sqrt( result[Xelt] * result[Xelt] +
                           result[Yelt] * result[Yelt] +
                           result[Zelt] * result[Zelt] );

      // avoid divide by 0
      if (Math::isEqual( result[Welt], (DATA_TYPE)0.0, (DATA_TYPE)0.00001 ) == false)
         length = Math::atan( length / result[Welt] );
      else
         length = Math::PI_OVER_2;

      result[Welt] = (DATA_TYPE)0.0;
      result[Xelt] = result[Xelt] * length;
      result[Yelt] = result[Yelt] * length;
      result[Zelt] = result[Zelt] * length;
      return result;
   }

   /** spherical linear interpolation between two rotation quaternions.
    *  t is a value between 0 and 1 that interpolates between from and to.
    * @pre no aliasing problems to worry about ("result" can be "from" or "to" param).
    * References:
    * <ul>
    * <li> From Adv Anim and Rendering Tech. Pg 364
    * </ul>
    * @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& slerp( Quat<DATA_TYPE>& result, const DATA_TYPE t, const Quat<DATA_TYPE>& from, const Quat<DATA_TYPE>& to)
   {
      const Quat& p = from; // just an alias to match q
      
      // calc cosine theta
      DATA_TYPE cosom = dot( from, to );

      // adjust signs (if necessary)
      Quat q;
      if (cosom < (DATA_TYPE)0.0)
      {
         cosom = -cosom;
         q.vec[0] = -to.vec[0];   // Reverse all signs
         q.vec[1] = -to.vec[1];
         q.vec[2] = -to.vec[2];
         q.vec[3] = -to.vec[3];
      }
      else
      {
         q = to;
      }

      // Calculate coefficients
      DATA_TYPE sclp, sclq;
      if (((DATA_TYPE)1.0 - cosom) > (DATA_TYPE)0.0001) // 0.0001 -> some epsillon
      {
         // Standard case (slerp)
         DATA_TYPE omega, sinom;
         omega = Math::acos( cosom ); // extract theta from dot product's cos theta
         sinom = Math::sin( omega );
         sclp  = Math::sin( ((DATA_TYPE)1.0 - t) * omega ) / sinom;
         sclq  = Math::sin( t * omega ) / sinom;
      }
      else
      {
         // Very close, do linear interp (because it's faster)
         sclp = (DATA_TYPE)1.0 - t;
         sclq = t;
      }

      result[Xelt] = sclp * p[Xelt] + sclq * q[Xelt];
      result[Yelt] = sclp * p[Yelt] + sclq * q[Yelt];
      result[Zelt] = sclp * p[Zelt] + sclq * q[Zelt];
      result[Welt] = sclp * p[Welt] + sclq * q[Welt];
      return result;
   }
   
   /** linear interpolation between two quaternions.
    *  t is a value between 0 and 1 that interpolates between from and to.
    * @pre no aliasing problems to worry about ("result" can be "from" or "to" param).
    * References:
    * <ul>
    * <li> From Adv Anim and Rendering Tech. Pg 364
    * </ul>
    *  @see Quat
    */
   template <typename DATA_TYPE>
   Quat<DATA_TYPE>& lerp( Quat& result, const DATA_TYPE t, const Quat<DATA_TYPE>& from, const Quat& to)
   {
      // just an alias to match q
      const Quat& p = from; 
      
      // calc cosine theta
      DATA_TYPE cosom = dot( from, to );

      // adjust signs (if necessary)
      Quat q;
      if (cosom < (DATA_TYPE)0.0)
      {
         q.vec[0] = -to.vec[0];   // Reverse all signs
         q.vec[1] = -to.vec[1];
         q.vec[2] = -to.vec[2];
         q.vec[3] = -to.vec[3];
      }
      else
      {
         q = to;
      }

      // do linear interp
      DATA_TYPE sclp, sclq;
      sclp = (DATA_TYPE)1.0 - t;
      sclq = t;

      result[Xelt] = sclp * p[Xelt] + sclq * q[Xelt];
      result[Yelt] = sclp * p[Yelt] + sclq * q[Yelt];
      result[Zelt] = sclp * p[Zelt] + sclq * q[Zelt];
      result[Welt] = sclp * p[Welt] + sclq * q[Welt];
      return result;
   }
   
   /** WARNING: not implemented (do not use) */
   template <typename DATA_TYPE>
   void squad( Quat& result, DATA_TYPE t, const Quat<DATA_TYPE>& q1, const Qua<DATA_TYPE>t& q2, const Quat<DATA_TYPE>& a, const Quat& b ) 
   {
      ggtASSERT( false );
   }

   /** WARNING: not implemented (do not use) */
   void meanTangent( Quat<dataType>& result, const Quat<dataType>& q1, const Quat<dataType>& q2, const Quat<dataType>& q3 )
   {
       ggtASSERT( false );
   }



   //-- COMPARISONS --//

   template <typename DATA_TYPE>
   bool isEqual( const Quat<DATA_TYPE>& q1, const Quat<DATA_TYPE>& q2, DATA_TYPE tol = 0.0 ) 
   {
      return bool( Math::isEqual( q1[0], q2[0], tol ) &&
                   Math::isEqual( q1[1], q2[1], tol ) &&
                   Math::isEqual( q1[2], q2[2], tol ) &&
                   Math::isEqual( q1[3], q2[3], tol )    );
   }
   
}

#endif
