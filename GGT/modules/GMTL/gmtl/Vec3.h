/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Vec3.h,v $
 * Date modified: $Date: 2002-01-31 00:56:21 $
 * Version:       $Revision: 1.3 $
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
#ifndef _GMTL_VEC3_H_
#define _GMTL_VEC3_H_

#include <iostream>
#include <gmtl/gmtlDefines.h>

namespace gmtl
{

class Vec3
{
public:
   // Constructor
   Vec3();
   Vec3(const float& _x, const float& _y, const float& _z);
   Vec3(const Vec3& rVec);

   // Member access
   inline float&  operator [](const int i);
   inline const float&  operator [](const int i) const;

   // Assignments
   inline Vec3&  operator =(const Vec3& _v);
   inline void set(const float& _x, const float& _y, const float& _z);
   inline void zero();

   // Comparisons
   inline bool operator ==(const Vec3& _v) const;
   inline bool operator !=(const Vec3& _v) const;
   inline bool equal(const Vec3& _v, const float& eps=GMTL_VEC_EQUAL_EPSILON) const;

   // Arithmetic update ops
   inline Vec3& operator +=(const Vec3& _v);
   inline Vec3& operator -=(const Vec3& _v);
   inline Vec3& operator *=(const float& _s);
   inline Vec3& operator /=(float _s);

   // Vector operations
   inline float dot(const Vec3&  _v) const;
   inline float length() const;
   inline float lengthSquared() const;
   inline void normalize();
   inline bool isNormalized() const;
   inline Vec3 cross(const Vec3&  _v) const;

   /**
   * Transform the vec by the full 4x4 matrix.
   * vec = (Mat)(_v)
   * initial w = 1;  At end scale by W to convert back
   */
   //void xformFull(const sgMatrix& _m, const Vec3& _v);

   /*
   * Transform as vector.
   * w initial = 0.0  ==> Translation doesn't effect vector
   * No scale by 1/w at end.... why???
   */
   //void xformVec(const sgMatrix& _m, const Vec3& _v);

   /*
   friend inline Vec3 operator *(const float& _s, const sgVec3&);
   friend inline Vec3 operator *(const sgVec3& _v, const float& _s);
   friend inline Vec3 operator /(const sgVec3& _v, float _s);
   */

public:
   float vec[3];
};

/** @name Unit Vec3 Vectors */
//@{
const Vec3 ZeroVec3 = Vec3(0,0,0);
const Vec3 XUnitVec3 = Vec3(1,0,0);
const Vec3 YUnitVec3 = Vec3(0,1,0);
const Vec3 ZUnitVec3 = Vec3(0,0,1);
//@}

// --------- IMPLS ---------------------- //
inline
Vec3::Vec3()
{ set(0.0, 0.0, 0.0);}

inline
Vec3::Vec3(const float& _x, const float& _y, const float& _z)
{ set(_x, _y, _z);}

inline
Vec3::Vec3(const Vec3& rVec)
{
   vec[0] = rVec.vec[0];
   vec[1] = rVec.vec[1];
   vec[2] = rVec.vec[2];
}

// Member access
inline float&  Vec3::operator [](const int i)
{
   gfxASSERT((i>=0)&&(i<3));
   return vec[i];
}
inline const float&  Vec3::operator [](const int i) const
{
   gfxASSERT((i>=0)&&(i<3));
   return vec[i];
}

// Assignments
inline Vec3&  Vec3::operator =(const Vec3& _v) {
   vec[0] = _v[0];
   vec[1] = _v[1];
   vec[2] = _v[2];
   return *this;
}

/// Set value of Vector
inline void Vec3::set(const float& _x, const float& _y, const float& _z)
{
   vec[0] = _x;
   vec[1] = _y;
   vec[2] = _z;
}

//: Zero out the vector
inline void Vec3::zero()
{
   vec[0] = 0.0f;
   vec[1] = 0.0f;
   vec[2] = 0.0f;
}

// Comparisons
inline bool Vec3::operator ==(const Vec3& _v) const
{
   return(vec[0] == _v[0] &&
          vec[1] == _v[1] &&
          vec[2] == _v[2]);
}

inline bool Vec3::operator !=(const Vec3& _v) const {
   return(vec[0] != _v[0] ||
          vec[1] != _v[1] ||
          vec[2] != _v[2]);
}

inline bool Vec3::equal(const Vec3& _v, const float& eps) const
{

  for(int i=0;i<3;i++)
  {
     if (fabs(vec[i] - _v[i]) > eps)
        return false;
  }
  return true;
}



// Arithmetic update ops
inline Vec3& Vec3::operator +=(const Vec3& _v) {
   vec[0] += _v[0];
   vec[1] += _v[1];
   vec[2] += _v[2];
   return *this;
}

inline Vec3& Vec3::operator -=(const Vec3& _v) {
   vec[0] -= _v[0];
   vec[1] -= _v[1];
   vec[2] -= _v[2];
   return *this;
}

inline Vec3& Vec3::operator *=(const float& _s) {
   vec[0] *= _s;
   vec[1] *= _s;
   vec[2] *= _s;
   return *this;
}

inline Vec3& Vec3::operator /=(float _s) {
   _s = 1.0/_s;
   return *this *= _s;
}


inline float Vec3::dot(const Vec3&  _v) const {
   return(vec[0] * _v.vec[0] +
          vec[1] * _v.vec[1] +
          vec[2] * _v.vec[2]);
}

inline float Vec3::length() const
{
   float retVal = lengthSquared();
   if (retVal == 0.0f)
      return 0.0f;
   else
      return Math::sqrt(retVal);
}

// This returns the length squared.
// This can be used in many computational geometry algorithms
// It does not require the sqrt that length requires
inline float Vec3::lengthSquared() const
{
   return(vec[0]*vec[0])+
   (vec[1]*vec[1])+
   (vec[2]*vec[2]);
}

inline void Vec3::normalize()
{
   float len = length();

   if (len == 0.0f)
   {
      //std::cerr << "Tried to normalize a zero vector" << endl;
   }
   else
   {
      vec[0] = vec[0] / len;
      vec[1] = vec[1] / len;
      vec[2] = vec[2] / len;
   }
}



//: checks if the vector is normalized
inline bool Vec3::isNormalized() const
{
   float len = lengthSquared();
   return GMTL_NEAR(len, 1.0f, 0.001);
}

/// Calculate the cross product of me X _v
inline Vec3 Vec3::cross(const Vec3&  _v) const
{
   return Vec3( ((vec[Yelt]*_v.vec[Zelt]) - (vec[Zelt]*_v.vec[Yelt])),
                ((vec[Zelt]*_v.vec[Xelt]) - (vec[Xelt]*_v.vec[Zelt])),
                ((vec[Xelt]*_v.vec[Yelt]) - (vec[Yelt]*_v.vec[Xelt])) );
}




//ostream& operator<<(ostream& out, sgVec3& _v);


    // Class to hash a sgVec3
    // NOTES: Make sure not to round to long until after multiples.  Otherwise, the coords are too close
    //       Also, the mults are needed to gain seperation and stuff
//struct hash<sgVec3> {
//    size_t operator()(sgVec3 aVec) const { return (aVec.vec[0]*21.0f) + (aVec.vec[1]*777.0f) + (aVec.vec[2]*1221.0f) ; }
//};

    // Class to test pfVec3 for comparison...  needed by set algorithms
/*
class less_sgVec3 {
    public:
   bool operator()(const sgVec3 &x, const sgVec3 &y) const
   {
       if (x[0] < y[0])
      return true;
       else if ((x[0] == y[0]) && (x[1] < y[1]))
      return true;
       else if ((x[0] == y[0]) && (x[1] == y[1]) && (x[2] < y[2]))
      return true;
       else
      return false;
   }
};
*/

};

#endif
