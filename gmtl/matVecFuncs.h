/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: matVecFuncs.h,v $
 * Date modified: $Date: 2002-01-18 20:43:12 $
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
#ifndef _GMTL_MAT_VEC_FUNCS_H_
#define _GMTL_MAT_VEC_FUNCS_H_

#include <GMTL/gmtlDefines.h>
#include <GMTL/Matrix.h>
#include <GMTL/Vec3.h>
#include <GMTL/Vec4.h>

namespace gmtl
{

   //////////////////////////////////////////////////////////////
   //                VEC3 OPS
   //////////////////////////////////////////////////////////////
// Arithmetic ops	
inline Vec3 operator+ (const Vec3& v1, const Vec3& v2)
{
   return Vec3(v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]);
}

inline Vec3 operator- (const Vec3& v1, const Vec3& v2)
{
   return Vec3(v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]);
}

inline Vec3 operator* (const Vec3& v1, const float scalar)
{
   return Vec3(v1[0]*scalar, v1[1]*scalar, v1[2]*scalar);
}
inline Vec3 operator* (const float scalar, const Vec3& v1)
{
   return v1*scalar;
}
inline Vec3 operator/ (const Vec3& v1, const float scalar)
{
   return Vec3(v1[0]/scalar, v1[1]/scalar, v1[2]/scalar);
}

inline Vec3 operator -(const Vec3& v1)
{
   return Vec3(-v1[0], -v1[1], -v1[2]);
}




// Make a matrix from the given axis and angle
// NOTE: Matrix will be orothonormal
// From: 3d game engine design
/*
Matrix makeAxisAngle (const Vec3& rotAxis, float rotDegrees)
{
   Matrix ret_mat;
   ret_mat.makeIdent();
   float rot_rad = Math::deg2Rad(rotDegrees);

   float fCos = Math::cos(fRadians);
   float fSin = Math::sin(fRadians);
   float fOneMinusCos = 1.0-fCos;
   float fX2 = rkAxis.x*rkAxis.x;
   float fY2 = rkAxis.y*rkAxis.y;
   float fZ2 = rkAxis.z*rkAxis.z;
   float fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
   float fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
   float fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
   float fXSin = rkAxis.x*fSin;
   float fYSin = rkAxis.y*fSin;
   float fZSin = rkAxis.z*fSin;

   ret_mat[0][0] = fX2*fOneMinusCos+fCos;   ret_mat[0][1] = fXYM-fZSin;            ret_mat[0][2] = fXZM+fYSin;
   ret_mat[1][0] = fXYM+fZSin;              ret_mat[1][1] = fY2*fOneMinusCos+fCos; ret_mat[1][2] = fYZM-fXSin;
   ret_mat[2][0] = fXZM-fYSin;              ret_mat[2][1] = fYZM+fXSin;            ret_mat[2][2] = fZ2*fOneMinusCos+fCos;

   return ret_mat;
}
*/

/*
XXX: Need to finish and test these functions --^
void getAxisAngle (const Matrix& mat, Vec3& rkAxis, float& rfRadians)
{
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

    MgcReal fTrace = m_aafEntry[0][0] + m_aafEntry[1][1] + m_aafEntry[2][2];
    MgcReal fCos = 0.5*(fTrace-1.0);
    rfRadians = MgcMath::ACos(fCos);  // in [0,PI]

    if ( rfRadians > 0.0 )
    {
        if ( rfRadians < MgcMath::PI )
        {
            rkAxis.x = m_aafEntry[2][1]-m_aafEntry[1][2];
            rkAxis.y = m_aafEntry[0][2]-m_aafEntry[2][0];
            rkAxis.z = m_aafEntry[1][0]-m_aafEntry[0][1];
            rkAxis.Unitize();
        }
        else
        {
            // angle is PI
            float fHalfInverse;
            if ( m_aafEntry[0][0] >= m_aafEntry[1][1] )
            {
                // r00 >= r11
                if ( m_aafEntry[0][0] >= m_aafEntry[2][2] )
                {
                    // r00 is maximum diagonal term
                    rkAxis.x = 0.5*MgcMath::Sqrt(m_aafEntry[0][0] -
                        m_aafEntry[1][1] - m_aafEntry[2][2] + 1.0);
                    fHalfInverse = 0.5/rkAxis.x;
                    rkAxis.y = fHalfInverse*m_aafEntry[0][1];
                    rkAxis.z = fHalfInverse*m_aafEntry[0][2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis.z = 0.5*MgcMath::Sqrt(m_aafEntry[2][2] -
                        m_aafEntry[0][0] - m_aafEntry[1][1] + 1.0);
                    fHalfInverse = 0.5/rkAxis.z;
                    rkAxis.x = fHalfInverse*m_aafEntry[0][2];
                    rkAxis.y = fHalfInverse*m_aafEntry[1][2];
                }
            }
            else
            {
                // r11 > r00
                if ( m_aafEntry[1][1] >= m_aafEntry[2][2] )
                {
                    // r11 is maximum diagonal term
                    rkAxis.y = 0.5*MgcMath::Sqrt(m_aafEntry[1][1] -
                        m_aafEntry[0][0] - m_aafEntry[2][2] + 1.0);
                    fHalfInverse  = 0.5/rkAxis.y;
                    rkAxis.x = fHalfInverse*m_aafEntry[0][1];
                    rkAxis.z = fHalfInverse*m_aafEntry[1][2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis.z = 0.5*MgcMath::Sqrt(m_aafEntry[2][2] -
                        m_aafEntry[0][0] - m_aafEntry[1][1] + 1.0);
                    fHalfInverse = 0.5/rkAxis.z;
                    rkAxis.x = fHalfInverse*m_aafEntry[0][2];
                    rkAxis.y = fHalfInverse*m_aafEntry[1][2];
                }
            }
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        rkAxis.x = 1.0;
        rkAxis.y = 0.0;
        rkAxis.z = 0.0;
    }
}
*/



/*
Matrix::Matrix(vjCoord coord)
{
   makeXYZEuler(coord.orient[0], coord.orient[1], coord.orient[2]);
   setTrans(coord.pos[0], coord.pos[1], coord.pos[2]);
}
*/

/*
void Matrix::preTrans(float _x, float _y, float _z, Matrix&  _m)
{
    Matrix transMat;
    transMat.makeTrans(_x, _y, _z);
    transMat.postMult(_m);
    *this = transMat;
}

//: Pre translate a matrix
//!POST: mat' = trans(_x,_y,_z) * _m
void Matrix::preTrans(Vec3& _trans, Matrix&  _m)
{ preTrans(_trans.vec[0], _trans.vec[1], _trans.vec[2], _m); }


    /// mat = _m * trans(_x,_y,_z)
void Matrix::postTrans(const Matrix&  _m, float _x, float _y, float _z)
{
    Matrix transMat;
    transMat.makeTrans(_x, _y, _z);
    transMat.preMult(_m);
    *this = transMat;
}

//!POST: mat' = _m * trans(_x,_y,_z)
void Matrix::postTrans(const Matrix&  _m, Vec3& _trans)
{ postTrans(_m, _trans.vec[0], _trans.vec[1], _trans.vec[2]); }

void Matrix::preRot(const float& _degrees, const Vec3& axis, Matrix&  _m)
{
    Matrix rotMat;
    rotMat.makeRot(_degrees, axis);
    rotMat.postMult(_m);
    *this = rotMat;
}

void Matrix::postRot(const Matrix&  _m, const float& _degrees, const Vec3& axis)
{
    Matrix rotMat;
    rotMat.makeRot(_degrees, axis);
    rotMat.preMult(_m);
    *this = rotMat;
}

void Matrix::preXYZEuler(float x, float y, float z, Matrix& _m)
{
    Matrix rotMat;
    rotMat.makeXYZEuler(x, y, z);
    rotMat.postMult(_m);
    *this = rotMat;
}

void Matrix::postXYZEuler(Matrix& _m, float x, float y, float z)
{
    Matrix rotMat;
    rotMat.makeXYZEuler(x, y, z);
    rotMat.preMult(_m);
    *this = rotMat;
}

    /// mat = scale(_xs,_ys,_zs) * _m;
void Matrix::preScale(float _xs, float _ys, float _zs, Matrix&  _m)
{
    Matrix scaleMat;
    scaleMat.makeScale(_xs, _ys, _zs);
    scaleMat.postMult(_m);
    *this = scaleMat;
}
    /// mat = _m * scale(_xs,_ys,_zs)
void Matrix::postScale(const Matrix&  _m, float _xs, float _ys, float _zs)
{
    Matrix scaleMat;
    scaleMat.makeScale(_xs, _ys, _zs);
    scaleMat.preMult(_m);
    *this = scaleMat;
}

inline Matrix operator *(float _s, const Matrix& _m) {
    Matrix dst; dst.scale(_s, _m); return dst;
}

inline Matrix operator *(const Matrix& _m, float _s) {
    Matrix dst; dst.scale(_s, _m); return dst;
}

inline Matrix operator /(const Matrix& _m, float _s) {
    Matrix dst; dst.scale(1.0f/_s, _m); return dst;
}

    // Matrix Multiplication of A:(nxl) B:(lxm) ==> C:(nxm)
    //   Cij = Sum(k=1,l) (Aik)(Bkj)
    /// mat = mat * m
    // NOTE: All accesses in the function are using the C/C++ indexing method
void Matrix::postMult(const Matrix&  _m)
{
    Matrix prevMat = *this;     // May be sloooow!!!
    zero();

    for(int i=0;i<4;i++)
   for(int j=0;j<4;j++)
       for(int k=0;k<4;k++)
      mMat[j][i] += ( prevMat.mMat[k][i] * _m.mMat[j][k]);
}

    // mat = m * mat
void Matrix::preMult(const Matrix&  _m)
{
    Matrix prevMat = *this;     // May be sloooow!!!
    zero();

    for(int i=0;i<4;i++)
   for(int j=0;j<4;j++)
       for(int k=0;k<4;k++)
      mMat[i][j] += ( prevMat.mMat[i][k] * _m.mMat[k][j]);;
}
*/

// From Watt & Watt
/*
void    Matrix::makeQuaternion(float* q)
{
   float wx, wy, wz, xx, yy, yz, xy, xz, zz, xs, ys, zs;
   //float s;

   //s = 2.0f/(q[VJ_X]*q[VJ_X] + q[VJ_Y]*q[VJ_Y] + q[VJ_Z]*q[VJ_Z] + q[VJ_W]*q[VJ_W]);

   xs = q[VJ_X] + q[VJ_X];    ys = q[VJ_Y] + q[VJ_Y];    zs = q[VJ_Z] + q[VJ_Z];
   xx = q[VJ_X] * xs;   xy = q[VJ_X] * ys;   xz = q[VJ_X] * zs;
   yy = q[VJ_Y] * ys;   yz = q[VJ_Y] * zs;   zz = q[VJ_Z] * zs;
   wx = q[VJ_W] * xs;   wy = q[VJ_W] * ys;   wz = q[VJ_W] * zs;

   mMat[0][0] = 1.0 - (yy+zz);
    mMat[0][1] = xy+wz;
    mMat[0][2] = xz-wy;
    mMat[0][3] = 0.0;

    mMat[1][0] = xy-wz;
    mMat[1][1] = 1.0 - (xx+zz);
    mMat[1][2] = yz+wx;
    mMat[1][3] = 0.0;

    mMat[2][0] = xz+wy;
    mMat[2][1] = yz-wx;
    mMat[2][2] = 1.0 - (xx+yy);
    mMat[2][3] = 0.0;

    mMat[3][0] = 0.0;
    mMat[3][1] = 0.0;
    mMat[3][2] = 0.0;
    mMat[3][3] = 1.0;
}

void Matrix::makeQuaternion(vjQuat& q)
{makeQuaternion(q.vec);}
*/

};

#endif


