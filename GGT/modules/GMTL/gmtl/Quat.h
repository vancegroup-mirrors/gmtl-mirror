/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Quat.h,v $
 * Date modified: $Date: 2002-01-18 20:43:11 $
 * Version:       $Revision: 1.1.1.1 $
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

#include <GMTL/gmtlDefines.h>
#include <GMTL/Matrix.h>
#include <GMTL/Vec3.h>
#include <GMTL/Vec4.h>

namespace gmtl {

#define SG_QUAT_EPSILON	    0.00001f

/**
 * Quat: Class to encapsulate quaternion behaviors.
 *
 * Note: The code for most of these routines was taken from the the folling sources.
 *
 * Advanced Animation and Rendering Techniques: pp363-365
 * Quaternion Calculus for Animation,  Ken Shoemake SIGGRAPH course notes 1989
 * Animating Rotation with Quaternion Curves,  Ken Shoemake
 *		SIGGRAPH Proceedings Vol 19, Number 3, 1985
 *
 */
class Quat
{
public:
   static const Quat ZERO;
   static const Quat IDENTITY;
   static const float EPSILON;

public:
   // --- Constructors --- //
   Quat( const float x = 0.0f, const float y = 0.0f, const float z = 0.0f,
           const float w = 1.0f)
   { set(x, y, z, w);}

   void set(const float x, const float y, const float z, const float w)
   { vec[Xelt] = x; vec[Yelt] = y; vec[Zelt] = z; vec[Welt] = w;}

   void makeQuat(const Matrix& mat);
   void getMat(Matrix& mat) const;

   void getAxisAngle(float& angle, Vec3& axis) const;
   void makeAxisAngle(const float angle, const Vec3& axis);

   void makeAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis);
   void getAxes(Vec3& xAxis, Vec3& yAxis, Vec3& zAxis) const;


   inline Quat operator=(const Quat& rQuat);
   inline Quat operator+(const Quat& rQuat);
   inline Quat operator-(const Quat& rQuat);
   /// quat = q1 * q2
   inline Quat operator* (const Quat& rQuat);
   inline Quat operator* (float scalar) const;

   float& operator[](const unsigned int i)
   { return vec[i]; }
   const float& operator[](const unsigned int i) const
   { return vec[i]; }

   // -x,-y,-z,-w
   inline Quat operator- () const;

// -x,-y,-z,w
   inline Quat conj() const;
   inline float dot (const Quat& rQuat) const;
   inline float norm () const;

   // NOTE: I don't know if this is legal to do... :(
   inline void normalize();

   // Note: Should check for Multiples as well
   inline bool equal(const Quat& _q, const float& eps = 0.001) const;

public:
   Quat inverse() const;
   Quat exp () const;
   Quat log () const;

public:
   // Order x, y, z, w
   float    vec[4];
};


Quat slerp(float t, const Quat& p, const Quat& q, int extraSpins=0);
Quat squad(float _t, const Quat& _q1, const Quat& _q2, const Quat& _a, const Quat& _b);
inline Quat operator* (float scalar, const Quat& rQuat)
{
    return Quat(scalar*rQuat[Xelt], scalar*rQuat[Yelt], scalar*rQuat[Zelt], scalar*rQuat[Welt]);
}


// Inlines
inline Quat Quat::operator=(const Quat& rQuat)
{
   vec[Xelt] = rQuat.vec[Xelt];
   vec[Yelt] = rQuat.vec[Yelt];
   vec[Zelt] = rQuat.vec[Zelt];
   vec[Xelt] = rQuat.vec[Welt];
   return *this;
}

inline Quat Quat::operator+(const Quat& rQuat)
{
   return Quat(vec[Xelt] + rQuat.vec[Xelt],
               vec[Yelt] + rQuat.vec[Yelt],
               vec[Zelt] + rQuat.vec[Zelt],
               vec[Xelt] + rQuat.vec[Welt]);
}

inline Quat Quat::operator-(const Quat& rQuat)
{
   return Quat(vec[Xelt] - rQuat.vec[Xelt],
               vec[Yelt] - rQuat.vec[Yelt],
               vec[Zelt] - rQuat.vec[Zelt],
               vec[Xelt] - rQuat.vec[Welt]);
}

/// quat = q1 * q2
inline Quat Quat::operator* (const Quat& rQuat)
{
   return Quat
   (
   vec[Welt]*rQuat[Xelt] + vec[Xelt]*rQuat[Welt] + vec[Zelt]*rQuat[Yelt] - vec[Yelt]*rQuat[Zelt],
   vec[Welt]*rQuat[Yelt] + vec[Yelt]*rQuat[Welt] + vec[Xelt]*rQuat[Zelt] - vec[Zelt]*rQuat[Xelt],
   vec[Welt]*rQuat[Zelt] + vec[Zelt]*rQuat[Welt] + vec[Yelt]*rQuat[Xelt] - vec[Xelt]*rQuat[Yelt],
   vec[Welt]*rQuat[Welt] - vec[Xelt]*rQuat[Xelt] - vec[Yelt]*rQuat[Yelt] - vec[Zelt]*rQuat[Zelt]
   );
}

inline Quat Quat::operator* (float scalar) const
{
   return Quat(scalar*vec[Xelt],scalar*vec[Yelt],scalar*vec[Zelt],scalar*vec[Welt]);
}

inline Quat Quat::operator- () const
{
   return Quat(-vec[Xelt], -vec[Yelt], -vec[Zelt], -vec[Welt]);
}

inline Quat Quat::conj() const
{
   return Quat(-vec[Xelt], -vec[Yelt], -vec[Zelt], vec[Welt]);
}

inline float Quat::dot (const Quat& rQuat) const
{
   return vec[Welt]*rQuat[Welt] + vec[Xelt]*rQuat[Xelt] + vec[Yelt]*rQuat[Yelt] + vec[Zelt]*rQuat[Zelt];
}

inline float Quat::norm () const
{
   return vec[Welt]*vec[Welt] + vec[Xelt]*vec[Xelt] + vec[Yelt]*vec[Yelt] + vec[Zelt]*vec[Zelt];
}

inline void Quat::normalize()
{
   float len = Math::sqrt(norm());
   vec[0] = vec[0]/len;
   vec[1] = vec[1]/len;
   vec[2] = vec[2]/len;
   vec[3] = vec[3]/len;
}

inline bool Quat::equal(const Quat& _q, const float& eps) const
   {

     for(int i=0;i<4;i++)
     {
        if (fabs(vec[i] - _q[i]) > eps)
           return false;
     }
     return true;
   }

};    // End: namespace gmtl

#endif

