/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Quat.h,v $
 * Date modified: $Date: 2002-02-10 04:45:24 $
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
#ifndef _GMTL_QUAT_H_
#define _GMTL_QUAT_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Matrix.h>
#include <gmtl/Vec3.h>
#include <gmtl/Vec4.h>

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
   /*
   static const Quat ZERO;
   static const Quat IDENTITY;
   static const float EPSILON;
   */

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

const Quat ZeroQuat = Quat(0.0,0.0,0.0,0.0);
const Quat IdentQuat = Quat(0.0,0.0,0.0,1.0);
const float EpsilonQuat = 1e-03;


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

void Quat::makeQuat(const Matrix& mat)
{
   float trace, root;

   trace = mat[0][0] + mat[1][1] + mat[2][2];

   if (trace > 0.0)
   {
      // |w| > 1/2, may as well chose w > 1/2
      root = sqrt(trace + 1.0);     // 2w
      vec[Welt] = root*0.5;
      root = 0.5/root;              // 1/(4w)

      vec[Xelt] = (mat[1][2] - mat[2][1])*root;
      vec[Yelt] = (mat[2][0] - mat[0][2])*root;
      vec[Zelt] = (mat[0][1] - mat[1][0])*root;
   }
   else
   {
      // |w| <= 1/2
      static int nxt[3] = { Yelt, Zelt, Xelt };
      int i = Xelt;
      if (mat[Yelt][Yelt] > mat[Xelt][Xelt])
         i = Yelt;
      if (mat[Zelt][Zelt] > mat[i][i])
         i = Zelt;

      int j = nxt[i];
      int k = nxt[j];

      root = Math::sqrt(mat[i][i] - (mat[j][j] + mat[k][k]) + 1.0f);

      vec[i] = root*0.5;
      root = 0.5f/root;
      vec[Welt] = (mat[j][k] - mat[k][j])*root;
      vec[j] = (mat[i][j] + mat[j][i])*root;
      vec[k] = (mat[i][k] + mat[k][i])*root;
   }

   normalize();

   ggtASSERT(GMTL_NEAR(norm(),1.0f,0.01) && "setMat(..) returned a non-unit quaternion");
}

void Quat::getMat(Matrix& mat) const
{
   ggtASSERT(GMTL_NEAR(norm(),1.0f,0.01) && "getMat(..) is trying to use a non-unit quaternion");

   float Tx  = 2.0*vec[Xelt];
   float Ty  = 2.0*vec[Yelt];
   float Tz  = 2.0*vec[Zelt];
   float Twx = Tx*vec[Welt];
   float Twy = Ty*vec[Welt];
   float Twz = Tz*vec[Welt];
   float Txx = Tx*vec[Xelt];
   float Txy = Ty*vec[Xelt];
   float Txz = Tz*vec[Xelt];
   float Tyy = Ty*vec[Yelt];
   float Tyz = Tz*vec[Yelt];
   float Tzz = Tz*vec[Zelt];

   mat[0][0] = 1.0-(Tyy+Tzz);  mat[1][0] = Txy-Twz;        mat[2][0] = Txz+Twy;
   mat[0][1] = Txy+Twz;        mat[1][1] = 1.0-(Txx+Tzz);  mat[2][1] = Tyz-Twx;
   mat[0][2] = Txz-Twy;        mat[1][2] = Tyz+Twx;        mat[2][2] = 1.0-(Txx+Tyy);

}


void Quat::getAxisAngle(float& angle, Vec3& axis) const
{
   // The quaternion representing the rotation is
   //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

   float sqr_length = vec[Xelt]*vec[Xelt]
                      + vec[Yelt]*vec[Yelt]
                      + vec[Zelt]*vec[Zelt];

   if ( sqr_length > 0.0 )
   {
      angle = 2.0*Math::aCos(vec[Welt]);
      float inv_len = 1.0/Math::sqrt(sqr_length);
      axis[Xelt] = vec[Xelt] * inv_len;
      axis[Yelt] = vec[Yelt] * inv_len;
      axis[Zelt] = vec[Zelt] * inv_len;
   }
   else
   {
      // angle is 0 (mod 2*pi), so any axis will do
      angle = 0.0;
      axis.set(1.0, 0.0, 0.0);
   }
}

void Quat::makeAxisAngle(const float angle, const Vec3& axis)
{
   // assert:  axis[] is unit length
   //
   // The quaternion representing the rotation is
   //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
   ggtASSERT(GMTL_NEAR(axis.lengthSquared(),1.0f,0.00001f));

   float half_angle = 0.5*angle;
   float sin_val = Math::sin(half_angle);
   vec[Welt] = Math::cos(half_angle);
   vec[Xelt] = sin_val*axis[Xelt];
   vec[Yelt] = sin_val*axis[Yelt];
   vec[Zelt] = sin_val*axis[Zelt];
}


void Quat::makeAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis)
{
   ggtASSERT((xAxis.isNormalized()) && (yAxis.isNormalized()) && (zAxis.isNormalized()) && "Called with non-normal axis");
#ifdef GMTL_DEBUG
   Vec3 cross;
   cross = xAxis.cross(yAxis);
   cross.normalize();
   ggtASSERT( cross.equal(zAxis,0.01) && "Not an orthogonal set of axes");
#endif

   Matrix rot_mat;
   rot_mat.makeAxes(xAxis, yAxis, zAxis);
   this->makeQuat(rot_mat);
}

void Quat::getAxes(Vec3& xAxis, Vec3& yAxis, Vec3& zAxis) const
{
   Matrix rot_mat;
   this->getMat(rot_mat);
   rot_mat.getAxes(xAxis, yAxis, zAxis);
}


Quat Quat::inverse() const
{
   float len = norm();
   float inv_len;

   if (len >= 0.0f)
   {
      inv_len = 1.0f/len;
      return Quat(-vec[Xelt]*inv_len,
                  -vec[Yelt]*inv_len,
                  -vec[Zelt]*inv_len,
                  vec[Welt]*inv_len);
   }
   else
      return Quat(0.0f, 0.0f, 0.0f, 0.0f);
}


Quat Quat::exp () const
{
    // If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

    float angle = Math::sqrt(vec[Xelt]*vec[Xelt]
                      + vec[Yelt]*vec[Yelt]
                      + vec[Zelt]*vec[Zelt]);
    float fSin = Math::sin(angle);

    Quat result;
    result[Welt] = Math::cos(angle);

    if ( Math::abs(fSin) >= EpsilonQuat )
    {
        float coeff = fSin/angle;
        result[Xelt] = coeff*vec[Xelt];
        result[Yelt] = coeff*vec[Yelt];
        result[Zelt] = coeff*vec[Zelt];
    }
    else
    {
        result[Xelt] = vec[Xelt];
        result[Yelt] = vec[Yelt];
        result[Zelt] = vec[Zelt];
    }

    return result;
}

Quat Quat::log () const
{
    // If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
    // sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

    Quat result;
    result[Welt] = 0.0;

    if ( Math::abs(vec[Welt]) < 1.0 )
    {
        float angle = Math::aCos(vec[Welt]);
        float fSin = Math::sin(angle);
        if ( Math::abs(fSin) >= EpsilonQuat)
        {
            float coeff = angle/fSin;
            result[Xelt] = coeff*vec[Xelt];
        result[Yelt] = coeff*vec[Yelt];
        result[Zelt] = coeff*vec[Zelt];
            return result;
        }
    }

    result[Xelt] = vec[Xelt];
    result[Yelt] = vec[Yelt];
    result[Zelt] = vec[Zelt];

    return result;
}


// Mathmatical functions


Quat slerp(float t, const Quat& pQuat, const Quat& qQuat, int extraSpins)
{
   float fCos = pQuat.dot(qQuat);
   float fAngle = Math::aCos(fCos);

   if ( Math::abs(fAngle) < EpsilonQuat)
      return pQuat;

   float fSin = Math::sin(fAngle);
   float fPhase = Math::PI * extraSpins * t;
   float fInvSin = 1.0/fSin;
   float fCoeff0 = Math::sin((1.0-t)*fAngle - fPhase)*fInvSin;
   float fCoeff1 = Math::sin(t*fAngle + fPhase)*fInvSin;
   return (fCoeff0*pQuat) + (fCoeff1*qQuat);
}

Quat squad(float _t, const Quat& _q1, const Quat& _q2, const Quat& _a, const Quat& _b)
{
   float fSlerpT = 2.0*_t * (1.0-_t);
   Quat kSlerpP = slerp(_t,_q1,_q2);
   Quat kSlerpQ = slerp(_t,_a,_b);
   return slerp(fSlerpT,kSlerpP,kSlerpQ);
}


};    // End: namespace gmtl

#endif

