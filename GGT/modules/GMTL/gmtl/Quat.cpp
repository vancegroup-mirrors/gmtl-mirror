/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Quat.cpp,v $
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
#include <Util/Assert.h>
#include <gmtl/Quat.h>

namespace gmtl
{

   /*
   const Quat Quat::ZERO(0.0,0.0,0.0,0.0);
   const Quat Quat::IDENTITY(0.0,0.0,0.0,1.0);
   const float Quat::EPSILON(1e-03);
   */

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

   gfxASSERT(GMTL_NEAR(norm(),1.0f,0.01) && "setMat(..) returned a non-unit quaternion");
}

void Quat::getMat(Matrix& mat) const
{
   gfxASSERT(GMTL_NEAR(norm(),1.0f,0.01) && "getMat(..) is trying to use a non-unit quaternion");

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
   gfxASSERT(GMTL_NEAR(axis.lengthSquared(),1.0f,0.00001f));

   float half_angle = 0.5*angle;
   float sin_val = Math::sin(half_angle);
   vec[Welt] = Math::cos(half_angle);
   vec[Xelt] = sin_val*axis[Xelt];
   vec[Yelt] = sin_val*axis[Yelt];
   vec[Zelt] = sin_val*axis[Zelt];
}


void Quat::makeAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis)
{
   gfxASSERT((xAxis.isNormalized()) && (yAxis.isNormalized()) && (zAxis.isNormalized()) && "Called with non-normal axis");
#ifdef GFX_DEBUG
   Vec3 cross;
   cross = xAxis.cross(yAxis);
   cross.normalize();
   gfxASSERT( cross.equal(zAxis,0.01) && "Not an orthogonal set of axes");
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

    if ( Math::abs(fSin) >= Quat::EPSILON )
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
        if ( Math::abs(fSin) >= Quat::EPSILON )
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

   if ( Math::abs(fAngle) < Quat::EPSILON )
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

};
