/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Vec4.h,v $
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
#ifndef _GMTL_VEC4_H_
#define _GMTL_VEC4_H_

#include <GMTL/gmtlDefines.h>

namespace gmtl
{

class  Vec4
{
public:
   // Constructor
   Vec4();
   Vec4(const float& _x, const float& _y, const float& _z, const float& _w);
   Vec4(const Vec4& rVec);

   // Member access
   inline float&  operator [](const int i);
   inline const float&  operator [](const int i) const;

   // Assignment
   inline Vec4&  operator =(const Vec4& _v);
   inline void set(const float& _x, const float& _y, const float& _z, const float& _w);

   // Comparisons
   inline int operator ==(const Vec4& _v) const;
   inline int operator !=(const Vec4& _v) const;
   inline bool equal(const Vec4& _v, const float& eps=GMTL_VEC_EQUAL_EPSILON) const  {

      for(int i=0;i<4;i++)
      {
         if (fabs(vec[i] - _v[i]) > eps)
            return false;
      }
      return true;
   }


   // Arith ops
   inline Vec4 operator +(const Vec4& _v) const;
   inline Vec4 operator -(const Vec4& _v) const;
   inline Vec4 operator* (const float& scalar) const;
   inline Vec4 operator/ (const float& scalar) const;
   inline Vec4 operator -() const;

   // Arith update ops
   inline Vec4& operator +=(const Vec4& _v);
   inline Vec4& operator -=(const Vec4& _v);
   inline Vec4& operator *=(float _s);
   inline Vec4& operator /=(float _s);

   // Vector operations
   inline float dot(const Vec4&  _v) const;
   inline void normalize();
   inline float lengthSquared() const;
   inline float length() const;

public:
   static const Vec4 ZERO;
   static const Vec4 UNIT_X;
   static const Vec4 UNIT_Y;
   static const Vec4 UNIT_Z;

public:
   float vec[4];
};


inline
Vec4::Vec4()
{ set(0.0, 0.0, 0.0, 0.0);}

inline
Vec4::Vec4(const float& _x, const float& _y, const float& _z, const float& _w)
{ set(_x, _y, _z, _w);}

inline
Vec4::Vec4(const Vec4& rVec)
{
   vec[0] = rVec.vec[0];
   vec[1] = rVec.vec[1];
   vec[2] = rVec.vec[2];
   vec[3] = rVec.vec[3];
}

// Member access
inline float&  Vec4::operator [](const int i)
{
   gfxASSERT((i>=0)&&(i<4));
   return vec[i];
}
inline const float&  Vec4::operator [](const int i) const
{
   gfxASSERT((i>=0)&&(i<4));
   return vec[i];
}

// Assignment
inline Vec4&  Vec4::operator =(const Vec4& _v)
{
   vec[0] = _v[0]; vec[1] = _v[1];
   vec[2] = _v[2]; vec[3] = _v[3];
   return *this;
}

inline void Vec4::set(const float& _x, const float& _y, const float& _z, const float& _w) {
   vec[0] = _x;
   vec[1] = _y;
   vec[2] = _z;
   vec[3] = _w;
}

// Comparisons
inline int Vec4::operator ==(const Vec4& _v) const {
   return(vec[0] == _v[0] &&
          vec[1] == _v[1] &&
          vec[2] == _v[2] &&
          vec[3] == _v[3]);
}

inline int Vec4::operator !=(const Vec4& _v) const
{
   return(vec[0] != _v[0] ||
          vec[1] != _v[1] ||
          vec[2] != _v[2] ||
          vec[3] != _v[3]);
}

// Arith ops

inline Vec4 Vec4::operator +(const Vec4& _v) const {
   return Vec4(vec[0]+_v[0], vec[1]+_v[1], vec[2]+_v[2], vec[3]+_v[3]);
}

inline Vec4 Vec4::operator -(const Vec4& _v) const {
   return Vec4(vec[0]-_v[0], vec[1]-_v[1], vec[2]-_v[2], vec[3]-_v[3]);
}
inline Vec4 Vec4::operator* (const float& scalar) const {
   return Vec4(vec[0]*scalar, vec[1]*scalar, vec[2]*scalar, vec[3]*scalar);
}
inline Vec4 Vec4::operator/ (const float& scalar) const {
   float denom = 1.0f/scalar;
   return Vec4(vec[0]*denom, vec[1]*denom, vec[2]*denom, vec[3]*denom);
}



inline Vec4 Vec4::operator -() const {
   return Vec4(-vec[0], -vec[1], -vec[2], -vec[3]);
}

// Arith update ops
inline Vec4& Vec4::operator +=(const Vec4& _v) {
   vec[0] += _v[0]; vec[1] += _v[1];
   vec[2] += _v[2]; vec[3] += _v[3];
   return *this;
}

inline Vec4& Vec4::operator -=(const Vec4& _v) {
   vec[0] -= _v[0]; vec[1] -= _v[1];
   vec[2] -= _v[2]; vec[3] -= _v[3];
   return *this;
}


inline Vec4& Vec4::operator *=(float _s) {
   vec[0] *= _s; vec[1] *= _s;
   vec[2] *= _s; vec[3] *= _s;
   return *this;
}

inline Vec4& Vec4::operator /=(float _s) {
   _s = 1.0/_s;
   return *this *= _s;
}


inline float Vec4::dot(const Vec4&  _v) const {
   return(vec[0] * _v[0] +
          vec[1] * _v[1] +
          vec[2] * _v[2]);
}


inline void Vec4::normalize()
{
   float len = length();
   vec[0] = vec[0] / len;
   vec[1] = vec[1] / len;
   vec[2] = vec[2] / len;
   vec[3] = vec[3] / len;
}

inline float Vec4::lengthSquared() const
{
   return(vec[0]*vec[0])+
   (vec[1]*vec[1])+
   (vec[2]*vec[2])+
   (vec[3]*vec[3]);


}

inline float Vec4::length() const
{
   float ret_val = lengthSquared();
   if (ret_val == 0.0f)
      return 0.0f;
   else
      return Math::sqrt(ret_val);
}


 /*
 inline Vec4 operator *(float _s, const sgVec4& _v) {
     return Vec4(_v[0]*_s, _v[1]*_s, _v[2]*_s, _v[3]*_s);
 }

 inline Vec4 operator *(const sgVec4& _v, float _s) {
     return Vec4(_v[0]*_s, _v[1]*_s, _v[2]*_s, _v[3]*_s);
 }

 inline Vec4 operator /(const sgVec4& _v, float _s) {
     _s = 1.0f/_s;
     return Vec4(_v[0]*_s, _v[1]*_s, _v[2]*_s, _v[3]*_s);
 }


    // Output operator
 ostream& operator<<(ostream& out, Vec4& _v);

 */

};

#endif
