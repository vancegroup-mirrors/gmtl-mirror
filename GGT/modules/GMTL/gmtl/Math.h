/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Math.h,v $
 * Date modified: $Date: 2002-02-10 04:38:07 $
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
   int iAbs (int iValue);
   int iCeil (float fValue);
   int iFloor (float fValue);
   int iSign (int iValue);

   float abs (float fValue);
   float aCos (float fValue);
   float aSin (float fValue);
   float aTan (float fValue);
   float aTan2 (float fY, float fX);
   float ceil (float fValue);
   float cos (float fValue);
   float exp (float fValue);
   float floor (float fValue);
   float log (float fValue);
   float pow (float kBase, float kExponent);
   float sign (float fValue);
   float sin (float fValue);
   float sqr (float fValue);
   float sqrt (float fValue);
   float unitRandom ();  // in [0,1]
    /*
    static float symmetricRandom ();  // in [-1,1]
    */

   float deg2Rad(float fVal);
   float rad2Deg(float fVal);

    //static const float PI;       //     = 3.14159265358979323846;
    //static const float PI_2;     //     = 1.57079632679489661923;

   /** @name Mathematical constants */
   //@{
   const float PI = 3.14159265358979323846;
   const float PI_2 = 1.57079632679489661923;
   //@}
};


//----------------------------------------------------------------------------
inline int Math::iAbs (int iValue)
{
    return ( iValue >= 0 ? iValue : -iValue );
}
//----------------------------------------------------------------------------
inline int Math::iCeil (float fValue)
{
    return int(::ceil(fValue));
}
//----------------------------------------------------------------------------
inline int Math::iFloor (float fValue)
{
    return int(::floor(fValue));
}
//----------------------------------------------------------------------------
inline int Math::iSign (int iValue)
{
    return ( iValue > 0 ? +1 : ( iValue < 0 ? -1 : 0 ) );
}
//----------------------------------------------------------------------------
inline float Math::abs (float fValue)
{
    return float(::fabs(fValue));
}
//----------------------------------------------------------------------------
inline float Math::aCos (float fValue)
{
    if ( -1.0 < fValue )
    {
        if ( fValue < 1.0 )
            return float(::acos(fValue));
        else
            return 0.0;
    }
    else
    {
        return Math::PI;
    }
}
//----------------------------------------------------------------------------
inline float Math::aSin (float fValue)
{
    if ( -1.0 < fValue )
    {
        if ( fValue < 1.0 )
            return float(::asin(fValue));
        else
            return -Math::PI_2;
    }
    else
    {
        return Math::PI_2;
    }
}
//----------------------------------------------------------------------------
inline float Math::aTan (float fValue)
{
    return float(::atan(fValue));
}
//----------------------------------------------------------------------------
inline float Math::aTan2 (float fY, float fX)
{
    return float(::atan2(fY,fX));
}
//----------------------------------------------------------------------------
inline float Math::ceil (float fValue)
{
    return float(::ceil(fValue));
}
//----------------------------------------------------------------------------
inline float Math::cos (float fValue)
{
    return float(::cos(fValue));
}
//----------------------------------------------------------------------------
inline float Math::exp (float fValue)
{
    return float(::exp(fValue));
}
//----------------------------------------------------------------------------
inline float Math::floor (float fValue)
{
    return float(::floor(fValue));
}
//----------------------------------------------------------------------------
inline float Math::log (float fValue)
{
    return float(::log(fValue));
}
//----------------------------------------------------------------------------
inline float Math::pow (float fBase, float fExponent)
{
    return float(::pow(fBase,fExponent));
}
//----------------------------------------------------------------------------
inline float Math::sign (float fValue)
{
    if ( fValue > 0.0 )
        return 1.0;

    if ( fValue < 0.0 )
        return -1.0;

    return 0.0;
}
//----------------------------------------------------------------------------
inline float Math::sin (float fValue)
{
    return float(::sin(fValue));
}
//----------------------------------------------------------------------------
inline float Math::sqr (float fValue)
{
    return fValue*fValue;
}
//----------------------------------------------------------------------------
inline float Math::sqrt (float fValue)
{
    return float(::sqrt(fValue));
}

inline float Math::unitRandom ()
{
    //return float(random())/float(RAND_MAX);
   float ret_val;
   ret_val = drand48();
   gfxASSERT((ret_val >= 0.0f) && (ret_val <= 1.0f));
   return drand48();
}

/*
float Math::SymmetricRandom ()
{
    return 2.0*float(rand())/float(RAND_MAX) - 1.0;
}
*/

inline float Math::deg2Rad(float fVal)
{
   return float(fVal*(Math::PI/180.0f));
}

inline float Math::rad2Deg(float fVal)
{
   return float(fVal*(180.0/Math::PI));
}

}

#endif
