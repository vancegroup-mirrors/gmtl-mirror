/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Math.h,v $
 * Date modified: $Date: 2002-02-15 21:48:30 $
 * Version:       $Revision: 1.8 $
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
#ifndef _GMTL_MATH_H_
#define _GMTL_MATH_H_

#include <gmtl/gmtlConfig.h>
#include <Util/Assert.h>
#include <math.h>
#include <stdlib.h>

namespace gmtl
{

namespace Math
{
   /** @name Mathematical constants */
   //@{
   const float PI = 3.14159265358979323846; //3.14159265358979323846264338327950288419716939937510;
   const float PI_2 = 1.57079632679489661923;
   const float PI_4 = 0.78539816339744830962;
   //@}

//----------------------------------------------------------------------------
template <typename T>
inline T Math::abs( T iValue )
{
    return T( iValue >= ((T)0) ? iValue : -iValue );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::ceil( T fValue );
inline float Math::ceil( float fValue )
{
    return float( ::ceilf( fValue ) );
}
inline double Math::ceil( double fValue )
{
    return double( ::ceil( fValue ) );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::floor( T fValue ); // why do a floor of int?  shouldn't compile...
inline float Math::floor( float fValue )
{
    return float( ::floorf( fValue ) );
}
inline double Math::floor( double fValue )
{
    return double( ::floor( fValue ) );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::sign( int iValue )
{
    return ( iValue > ((T)0) ? ((T)+1) : ( iValue < ((T)0) ? ((T)-1) : ((T)0) ) );
}
//----------------------------------------------------------------------------
// don't allow non-float types, because their ret val wont be correct
// i.e. with int, the int retval will be rounded up or down.  
//      we'd need a float retval to do it right, but we can't specialize by ret
template <typename T>
inline T Math::aCos( T fValue );
inline float Math::aCos( float fValue )
{
    if ( -1.0f < fValue )
    {
        if ( fValue < 1.0f )
            return float( ::acosf( fValue ) );
        else
            return 0.0f;
    }
    else
    {
        return (float)Math::PI;
    }
}
inline double Math::aCos( double fValue )
{
    if ( -1.0 < fValue )
    {
        if ( fValue < 1.0 )
            return double( ::acos( fValue ) );
        else
            return 0.0;
    }
    else
    {
        return (double)Math::PI;
    }
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::aSin( T fValue );
inline float Math::aSin( float fValue )
{
    if ( -1.0f < fValue )
    {
        if ( fValue < 1.0f )
            return float( ::asinf( fValue ) );
        else
            return (float)-Math::PI_2;
    }
    else
    {
        return (float)Math::PI_2;
    }
}
inline double Math::aSin( double fValue )
{
    if ( -1.0 < fValue )
    {
        if ( fValue < 1.0 )
            return double( ::asin( fValue ) );
        else
            return (double)-Math::PI_2;
    }
    else
    {
        return (double)Math::PI_2;
    }
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::aTan( T fValue );
inline float Math::aTan( float fValue )
{
    return float( ::atanf( fValue ) );
}
inline double Math::aTan( double fValue )
{
    return ::atan( fValue );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::atan2( T fY, T fX );
inline float Math::aTan2( float fY, float fX )
{
    return float( ::atan2f( fY, fX ) );
}
inline double Math::aTan2( double fY, double fX )
{
    return double( ::atan2( fY, fX ) );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::cos( T fValue );
inline float Math::cos( float fValue )
{
    return float( ::cosf( fValue ) );
}
inline double Math::cos( double fValue )
{
    return double( ::cos( fValue ) );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::exp( T fValue );
inline float Math::exp( float fValue )
{
    return float( ::expf( fValue ) );
}
inline double Math::exp( double fValue )
{
    return double( ::exp( fValue ) );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::log( T fValue );
inline double Math::log( double fValue )
{
    return double( ::log( fValue ) );
}
inline float Math::log( float fValue )
{
    return float( ::logf( fValue ) );
}
//----------------------------------------------------------------------------
inline double Math::pow( double fBase, double fExponent)
{
    return double( ::pow( fBase, fExponent ) );
}
inline float Math::pow( float fBase, float fExponent)
{
    return float( ::powf( fBase, fExponent ) );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::sin( T fValue );
inline double Math::sin( double fValue )
{
    return double( ::sin( fValue ) );
}
inline float Math::sin( float fValue )
{
    return float( ::sinf( fValue ) );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::sqr( T fValue )
{
    return T( fValue * fValue );
}
//----------------------------------------------------------------------------
template <typename T>
inline T Math::sqrt( T fValue )
{
    return T( ::sqrtf( ((float)fValue) ) );
}
inline double Math::sqrt( double fValue )
{
    return double( ::sqrt( fValue ) );
}

//----------------------------------------------------------------------------
inline float Math::unitRandom()
{
    //return float(random())/float(RAND_MAX);
   float ret_val;
   ret_val = drand48();
   ggtASSERT((ret_val >= 0.0f) && (ret_val <= 1.0f));
   return drand48();
}

/** return a random number between x1 and x2
 * RETURNS: random number between x1 and x2
 */
inline float rangeRandom( float x1, float x2 )
{
   float r = Math::unitRandom();
   float size = x2 - x1;
   return float( r * size + x1 );
}
   
/*
float Math::SymmetricRandom ()
{
    return 2.0*float(rand())/float(RAND_MAX) - 1.0;
}
*/
//----------------------------------------------------------------------------

inline float Math::deg2Rad( float fVal )
{
   return float( fVal * (float)(Math::PI/180.0) );
}
inline double Math::deg2Rad( double fVal )
{
   return double( fVal * (double)(Math::PI/180.0) );
}

inline float Math::rad2Deg( float fVal )
{
   return float( fVal * (float)(180.0/Math::PI) );
}
inline double Math::rad2Deg( double fVal )
{
   return double( fVal * (double)(180.0/Math::PI) );
}
//----------------------------------------------------------------------------

/** Is almost equal?
 * test for equality within some tolerance...
 * @PRE: tolerance must be >= 0
 */
template <class T>
inline bool isEqual( const T& a, const T& b, const T& tolerance )
{
   ggtASSERT( tolerance >= (T)0 );
   return bool( Math::abs( a - b ) <= tolerance );
}
//----------------------------------------------------------------------------
/** cut off the digits after the decimal place */
template <class T>
inline T trunc( T val )
{
   return T( (val < ((T)0)) ? Math::ceil( val ) : Math::floor( val ) );
}
/** round to nearest integer */
template <class T>
inline T round( T p )
{
   return T( Math::floor( p + (T)0.5 ) );
}
//----------------------------------------------------------------------------
/** Linear Interpolation between number [a] and [b]
 * use double or float only...
 */
template <class T, typename U>
inline void lerp( T& result, const U& lerp, const T& a, const T& b )
{
    T size = b - a;
    result = ((U)a) + (((U)size) * lerp);
}

//----------------------------------------------------------------------------
/** min returns the minimum of 2 values */
template <class T>
inline T Min( const T& x, const T& y )
{
   return ( x > y ) ? y : x;
}
/** min returns the minimum of 3 values */
template <class T>
inline T Min( const T& x, const T& y, const T& z )
{
   return Math::Min( Math::Min( x, y ), z );
}
/** min returns the minimum of 4 values */
template <class T>
inline T Min( const T& w, const T& x, const T& y, const T& z )
{
   return Math::Min( Math::Min( w, x ), Math::Min( y, z ) );
}

/** max returns the maximum of 2 values */
template <class T>
inline T Max( const T& x, const T& y )
{
   return ( x > y ) ? x : y;
}
/** max returns the maximum of 3 values */
template <class T>
inline T Max( const T& x, const T& y, const T& z )
{
   return Math::Max( Math::Max( x, y ), z );
}
/** max returns the maximum of 4 values */
template <class T>
inline T Max( const T& w, const T& x, const T& y, const T& z )
{
   return Math::Max( Math::Max( w, x ), Math::Max( y, z ) );
}
//----------------------------------------------------------------------------
template <class T>
inline void swap( T& a, T& b )
{
   T a_temp;
   a_temp = a; a = b; b = a_temp;
}
//----------------------------------------------------------------------------
/** Compute the factorial.
 * give - an object who's type has operator++, operator=, operator<=, and operator*= defined.
 *        it should be a single valued scalar type such as an int, float, double etc....
 * NOTE: This could be faster with a lookup table, but then wouldn't work templated : kevin
 */
template<class T>
inline T factorial(T rhs)
{
   T lhs = (T)1;

   for( T x = (T)1; x <= rhs; ++x )
   {
      lhs *= x;
   }

   return lhs;
}
//----------------------------------------------------------------------------

} // end namespace Math 
} // end namespace gmtl

#endif
