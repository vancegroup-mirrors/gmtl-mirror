/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Matrix.h,v $
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
#ifndef _GMTL_MATRIX_H_
#define _GMTL_MATRIX_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Vec3.h>

namespace gmtl
{

//-----------------------------------------------------------------------------
//: Matrix: 4x4 Matrix class (OpenGL ordering)
//
// C/C++ uses matrices in row major order.  In other words the access
// indices look like: mat[row][col] <br>
// (0,0) (0,1) (0,2) (0,3)   <=== Array      <br>
// (1,0) (1,1) (1,2) (1,3)   <=== Array      <br>
// (2,0) (2,1) (2,2) (2,3)   <=== Array      <br>
// (3,0) (3,1) (3,2) (3,3)   <=== Array      <br>
// <br>
// OpenGL ordering specifies that the matrix has to be column major in memory,
// so we need to access it more like: <br>
//    NOTE: The given indexes are what the cells have to be called in C/C++
//          notation.  Since we are putting the columns into memory
//          back-to-back.        <br>
// (0,0) (1,0) (2,0) (3,0)       <br>
// (0,1) (1,1) (2,1) (3,1)       <br>
// (0,2) (1,2) (2,2) (3,2)       <br>
// (0,3) (1,3) (2,3) (3,3)       <br>
//   ^     ^     ^     ^         <br>
//   ====================== Arrays     <br>
//
// So basically OpenGL ordering is the Transpose of the way C++ accesses the array
//-----------------------------------------------------------------------------
class Matrix
{
public:
   // ----- CONSTRUCTION --- //
   //: Default Constructor (Identity constructor)
   Matrix() { makeIdent(); };

   //: Constructor: Specify each element
   Matrix(float a00, float a01, float a02, float a03,
            float a10, float a11, float a12, float a13,
            float a20, float a21, float a22, float a23,
            float a30, float a31, float a32, float a33)
   {
      mMat[0][0] = a00; mMat[1][0] = a01; mMat[2][0] = a02; mMat[3][0] = a03;
      mMat[0][1] = a10; mMat[1][1] = a11; mMat[2][1] = a12; mMat[3][1] = a13;
      mMat[0][2] = a10; mMat[1][2] = a21; mMat[2][2] = a22; mMat[3][2] = a23;
      mMat[0][3] = a30; mMat[1][3] = a31; mMat[2][3] = a32; mMat[3][3] = a33;
   }

   //: copy constructor
   Matrix( const Matrix& matrix )
   {
      this->set( matrix.floatPtr());
   }

   // ----- MEMBER ACCESS ---- //
   // Access operators
   inline float*        operator[]( unsigned i )
      { ggtASSERT(i<4); return &mMat[i][0];}
   inline const float*  operator[]( unsigned i ) const
      { ggtASSERT(i<4); return &mMat[i][0];}
   inline float&        operator()( const unsigned& row, const unsigned& column )
      { ggtASSERT((row<4)&&(column<4)); return mMat[column][row];}
   inline const float&  operator()( const unsigned& row, const unsigned& column ) const
      { ggtASSERT((row<4)&&(column<4)); return mMat[column][row];}
   // Return pointer to first element of the given column
   inline float* column(unsigned i)
      { ggtASSERT((i<4)); return &mMat[i][0]; }


   //: Get a float pointer to the matrix data
   //!RETVAL: Returns a ptr to the head of the matrix data
   inline float*        floatPtr() { return (float*)mMat;}
   inline const float*  floatPtr() const { return (float*)mMat;}

   // --- ASSIGNMENT AND COMPARISON --- //
   // Assignment operators
   Matrix  operator=( const Matrix&  _m )
   {
      this->set( _m.floatPtr() );
      return *this;
   }

   int operator==( const Matrix&  _m ) const
   {
      return ((mMat[0][0] == _m[0][0]) && (mMat[0][1] == _m[0][1]) && (mMat[0][2] == _m[0][2]) && (mMat[0][3] == _m[0][3]) &&
              (mMat[1][0] == _m[1][0]) && (mMat[1][1] == _m[1][1]) && (mMat[1][2] == _m[1][2]) && (mMat[1][3] == _m[1][3]) &&
              (mMat[2][0] == _m[2][0]) && (mMat[2][1] == _m[2][1]) && (mMat[2][2] == _m[2][2]) && (mMat[2][3] == _m[2][3]) &&
              (mMat[3][0] == _m[3][0]) && (mMat[3][1] == _m[3][1]) && (mMat[3][2] == _m[3][2]) && (mMat[3][3] == _m[3][3]));
   }

   int operator!=( const Matrix&  _m ) const
   {
      return ((mMat[0][0] != _m[0][0]) || (mMat[0][1] != _m[0][1]) || (mMat[0][2] != _m[0][2]) || (mMat[0][3] != _m[0][3]) ||
              (mMat[1][0] != _m[1][0]) || (mMat[1][1] != _m[1][1]) || (mMat[1][2] != _m[1][2]) || (mMat[1][3] != _m[1][3]) ||
              (mMat[2][0] != _m[2][0]) || (mMat[2][1] != _m[2][1]) || (mMat[2][2] != _m[2][2]) || (mMat[2][3] != _m[2][3]) ||
              (mMat[3][0] != _m[3][0]) || (mMat[3][1] != _m[3][1]) || (mMat[3][2] != _m[3][2]) || (mMat[3][3] != _m[3][3]));
   }
    //: Compare matrix for equality with epsilon value
   //
   bool equal(const Matrix&  _m, const float& eps=GMTL_MAT_EQUAL_EPSILON) const  {

      for(int iCol=0;iCol<4;iCol++)
      {
         for(int jRow=0;jRow<4;jRow++)
         {
            if (fabs(mMat[iCol][jRow] - _m[iCol][jRow]) > eps)
               return false;
         }
      }
      return true;
   }


   //: Set from a memory region
   //! PRE: m refers to an array of 16 floats
   //! POST: this' = *m
   void    set(const float *m) {
      memcpy(mMat, m, sizeof(float) * 16);
   }

   //: Set matrix elementwise
   //!POST: this' is set to pass args
   //!ARGS: a00 - Upper left
   //!ARGS: a33 - Lower left
   void set(float a00, float a01, float a02, float a03,
            float a10, float a11, float a12, float a13,
            float a20, float a21, float a22, float a23,
            float a30, float a31, float a32, float a33)
   {
      mMat[0][0] = a00; mMat[1][0] = a01; mMat[2][0] = a02; mMat[3][0] = a03;
      mMat[0][1] = a10; mMat[1][1] = a11; mMat[2][1] = a12; mMat[3][1] = a13;
      mMat[0][2] = a20; mMat[1][2] = a21; mMat[2][2] = a22; mMat[3][2] = a23;
      mMat[0][3] = a30; mMat[1][3] = a31; mMat[2][3] = a32; mMat[3][3] = a33;
   }

   // ----- ARITHMETIC OPERATIONS ---- //

   // NOTE: return by val is better performing (C++ 11.6)
   Matrix operator* (const Matrix& rmat) const
   {
      Matrix ret_mat;

      for(int iRow=0;iRow<4;iRow++)
         for(int jCol=0;jCol<4;jCol++)
            ret_mat[jCol][iRow] = (mMat[0][iRow] * rmat.mMat[jCol][0]) + (mMat[1][iRow] * rmat.mMat[jCol][1])
                                + (mMat[2][iRow] * rmat.mMat[jCol][2]) + (mMat[3][iRow] * rmat.mMat[jCol][3]);
      return ret_mat;
   }

   //: addition
   Matrix operator+( const Matrix&  _m ) const
   {
      Matrix ret_mat;

      for (int n=0;n<4;n++)
         for (int m=0;m<4;m++)
            ret_mat[n][m] = (mMat[n][m] + _m.mMat[n][m]);

      return ret_mat;
   }

   //: subtraction
   Matrix operator-(const Matrix&  _m) const
   {
      Matrix ret_mat;

      for (int n=0;n<4;n++)
         for (int m=0;m<4;m++)
            ret_mat[n][m] = (mMat[n][m] - _m.mMat[n][m]);

      return ret_mat;
   }

   Matrix operator*=( const Matrix&  _m )
   {
      (*this) = (*this) * _m;;
      return *this;
   }

   Matrix operator*=(float _s)
   {
      for (int i=0; i<4; i++)
         for (int j=0; j<4; j++)
            mMat[i][j] *= _s;

      return *this;
   }


   // ------ UTILITY FUNCTIONS ----- //

   //: Create Identity Matrix
   void makeIdent()
   {
      mMat[0][0]=1.0f; mMat[1][0]=0.0f; mMat[2][0]=0.0f; mMat[3][0]=0.0f;
      mMat[0][1]=0.0f; mMat[1][1]=1.0f; mMat[2][1]=0.0f; mMat[3][1]=0.0f;
      mMat[0][2]=0.0f; mMat[1][2]=0.0f; mMat[2][2]=1.0f; mMat[3][2]=0.0f;
      mMat[0][3]=0.0f; mMat[1][3]=0.0f; mMat[2][3]=0.0f; mMat[3][3]=1.0f;
   }

   //: Zero out the matrix
   void zero()
   {
      mMat[0][0]=0.0f; mMat[1][0]=0.0f; mMat[2][0]=0.0f; mMat[3][0]=0.0f;
      mMat[0][1]=0.0f; mMat[1][1]=0.0f; mMat[2][1]=0.0f; mMat[3][1]=0.0f;
      mMat[0][2]=0.0f; mMat[1][2]=0.0f; mMat[2][2]=0.0f; mMat[3][2]=0.0f;
      mMat[0][3]=0.0f; mMat[1][3]=0.0f; mMat[2][3]=0.0f; mMat[3][3]=0.0f;
   }

   // ---- EULER ANGLE CONVERSIONS --- //
   //: Make XYZEuler matrix
   //!ARGS: rotX - Rotation about the x-axis
   //!ARGS: rotY - Rotation about the y-axis
   //!ARGS: rotZ - Rotation about the z-axis
   //
   //!POST: mat = rX*rY*rZ
   void makeXYZEuler(float xRot, float yRot, float zRot);
   void getXYZEuler(float& xRot, float& yRot, float& zRot) const;

   //: Make ZYX Euler matrix
   //!ARGS: rotZ - Rotation about the z-axis
   //!ARGS: rotY - Rotation about the y-axis
   //!ARGS: rotX - Rotation about the x-axis
   //!POST: mat = rZ*rY*rX
   void makeZYXEuler(float zRot, float yRot, float xRot);
   void getZYXEuler(float& zRot, float& yRot, float& xRot) const;

   //!POST: mat = rZ*rX*rY
   void makeZXYEuler( float zRot, float xRot, float yRot );
   void getZXYEuler( float& zRot, float& xRot, float& yRot ) const;

   // Get rotation around axis
   //!POST:  returned value is from -180 to 180, where 0 is none
   float    getYRot() const;
   float    getXRot() const;
   float    getZRot() const;

   //: Make a matrix using direction cosines
   //
   //!ARGS: secXAxis - The x-axis of the secondary coord system in terms of the first
   //+      secYAxis - The y-axis of the secondary coord system in terms of the first
   //+      secZAxis - The z-axis of the secondary coord system in terms of the first
   //
   //!PRE: The axis must be normalized
   //!POST: mat = direction cosine matrix
   //!NOTE: Based on "Virtual Reality Sytems" pg. 26
   //+      The matrix created is able to transform a pt in the first coord
   //+      system to the second coord system. Ps = sMf*Pf
   void     makeDirCos( Vec3 secXAxis, Vec3 secYAxis, Vec3 secZAxis );

   void makeAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis);
   void getAxes(Vec3& xAxis, Vec3& yAxis, Vec3& zAxis) const;


   //: Make rotation matrix around _axis
   //!ARGS: _degrees - Number of degrees to rotate
   //+      _axis - The axis to rotate around
   void makeRot(float _degrees, Vec3 _axis);

   //: Make translation matrix
   //!POST: mat = matrix with only the new translation
   void makeTrans(float _x, float _y, float _z);
   void makeTrans(const Vec3& trans);

   //: Sets given translation to current matrix
   //!POST: mat = old(mat) with the tranlation portion set to the parameters
   void setTrans(float _x, float _y, float _z);
   void setTrans(const Vec3& trans);

   //: Get the translation portion of the matrix
   //!POST: _x, _y, and _z contain the translation portion of the matrix
   void getTrans(float& _x, float& _y, float& _z) const;
   Vec3 getTrans() const;

   //: Make scale matrix
   void makeScale(float _x, float _y, float _z);

   //: Clamps the values of the matrix to zero
   //!POST: Any values in matrix < GMTL_EPSILON are set to 0.0f
   void zeroClamp()
   {
      for(int i=0;i<4;i++)
         for(int j=0;j<4;j++)
            mMat[i][j] = GMTL_ZERO_CLAMP(mMat[i][j]);
   }


public:
   //: return the transposition of the matrix
   Matrix transpose() const
   {
      Matrix ret_transpose;
      for (int i=0; i<4; i++)
         for (int j=0; j<4; j++)
            ret_transpose[i][j] = mMat[j][i];

      return ret_transpose;
   }

   //: Find inverse of a matrix
   //!POST: mat = inverse(_m)
   //! RETURNS: 1 - Success
   bool invert(Matrix& _m);

//public:
   //static const Matrix IDENT;

public:
   // Column major.  In other words {Column1, Column2, Column3, Column4} in memory
   // Access element mMat[column][row]
   float mMat[4][4];
};

const Matrix IdentMatrix = Matrix();   // Defaults to making ident matrix

};

// ------------ Implementations ---------- ///

namespace gmtl
{
   /*
   const Matrix Matrix::IDENT(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);
                              */

// Clamp an angle to zero if it is close
static inline void zeroClampAngle(float& angle)
{
   if(fabs(angle) < 1e-6)
      angle = 0.0f;
}


void Matrix::makeXYZEuler(float xRot, float yRot, float zRot)
{
   float sx = sin(Math::deg2Rad(xRot));  float cx = cos(Math::deg2Rad(xRot));
   float sy = sin(Math::deg2Rad(yRot));  float cy = cos(Math::deg2Rad(yRot));
   float sz = sin(Math::deg2Rad(zRot));  float cz = cos(Math::deg2Rad(zRot));

   // Derived by simply multiplying out the matrices by hand
   // X*Y*Z
   mMat[0][0] = cy*cz;              mMat[1][0] = -cy*sz;              mMat[2][0] = sy;      mMat[3][0] = 0.0f;
   mMat[0][1] = sx*sy*cz + cx*sz;   mMat[1][1] = -sx*sy*sz + cx*cz;   mMat[2][1] = -sx*cy;  mMat[3][1] = 0.0f;
   mMat[0][2] = -cx*sy*cz + sx*sz;  mMat[1][2] = cx*sy*sz + sx*cz;    mMat[2][2] = cx*cy;   mMat[3][2] = 0.0f;
   mMat[0][3] = 0.0f;               mMat[1][3] = 0.0f;                mMat[2][3] = 0.0f;    mMat[3][3] = 1.0f;

   zeroClamp();     // Clamp ~ zero values
}

void Matrix::getXYZEuler(float& xRot, float& yRot, float& zRot) const
{
   float cz;

   zRot = atan2f(-mMat[1][0], mMat[0][0]);     // -(-cy*sz)/(cy*cz) - cy falls out
   xRot = atan2f(-mMat[2][1], mMat[2][2]);     // -(sx*cy)/(cx*cy) - cy falls out
   cz = cos(zRot);
   yRot = atan2f(mMat[2][0], mMat[0][0]/cz);   // (sy)/((cy*cz)/cz)

   xRot = Math::rad2Deg(xRot);
   yRot = Math::rad2Deg(yRot);
   zRot = Math::rad2Deg(zRot);
}

// ------------------------------------------------------------------- //

void Matrix::makeZYXEuler(float zRot, float yRot, float xRot)
{
   float sx = sin(Math::deg2Rad(xRot));  float cx = cos(Math::deg2Rad(xRot));
   float sy = sin(Math::deg2Rad(yRot));  float cy = cos(Math::deg2Rad(yRot));
   float sz = sin(Math::deg2Rad(zRot));  float cz = cos(Math::deg2Rad(zRot));

   // Derived by simply multiplying out the matrices by hand
   // Z*Y*Z
   mMat[0][0] = cy*cz;      mMat[1][0] = -cx*sz + sx*sy*cz;   mMat[2][0] = sx*sz + cx*sy*cz;    mMat[3][0] = 0.0f;
   mMat[0][1] = cy*sz;      mMat[1][1] = cx*cz + sx*sy*sz;    mMat[2][1] = -sx*cz + cx*sy*sz;   mMat[3][1] = 0.0f;
   mMat[0][2] = -sy;        mMat[1][2] = sx*cy;               mMat[2][2] = cx*cy;               mMat[3][2] = 0.0f;
   mMat[0][3] = 0.0f;       mMat[1][3] = 0.0f;                mMat[2][3] = 0.0f;                mMat[3][3] = 1.0f;

   zeroClamp();     // Clamp ~ zero values
}

void Matrix::getZYXEuler(float& zRot, float& yRot, float& xRot) const
{
   float sx;

   zRot = atan2f(mMat[0][1], mMat[0][0]);      // (cy*sz)/(cy*cz) - cy falls out
   xRot = atan2f(mMat[1][2], mMat[2][2]);      // (sx*cy)/(cx*cy) - cy falls out
   sx = sinf(xRot);
   yRot = atan2f(-mMat[0][2],(mMat[1][2]/sx) );   // -(-sy)/((sx*cy)/sx)

   xRot = Math::rad2Deg(xRot);
   yRot = Math::rad2Deg(yRot);
   zRot = Math::rad2Deg(zRot);
}

// -------------------------------------------------------------- //

void Matrix::makeZXYEuler(float zRot, float xRot, float yRot)
{
   float sx = sin(Math::deg2Rad(xRot));  float cx = cos(Math::deg2Rad(xRot));
   float sy = sin(Math::deg2Rad(yRot));  float cy = cos(Math::deg2Rad(yRot));
   float sz = sin(Math::deg2Rad(zRot));  float cz = cos(Math::deg2Rad(zRot));

   // Derived by simply multiplying out the matrices by hand
   // Z*X*Y
   mMat[0][0] = cy*cz - sx*sy*sz;    mMat[1][0] = -cx*sz;     mMat[2][0] = sy*cz + sx*cy*sz;    mMat[3][0] = 0.0f;
   mMat[0][1] = cy*sz + sx*sy*cz;    mMat[1][1] = cx*cz;      mMat[2][1] = sy*sz - sx*cy*cz;    mMat[3][1] = 0.0f;
   mMat[0][2] = -cx*sy;              mMat[1][2] = sx;         mMat[2][2] = cx*cy;               mMat[3][2] = 0.0f;
   mMat[0][3] = 0.0f;                mMat[1][3] = 0.0f;       mMat[2][3] = 0.0f;               mMat[3][3] = 1.0f;

   zeroClamp();     // Clamp ~ zero values
}

//: extract the yaw information from the matrix
//  returned value is from -180 to 180, where 0 is none
// Rotation around Y axis
float Matrix::getYRot() const
{
   /*
   const vjVec3 forwardPoint( 0, 0, -1 );       // -Z
   const vjVec3 originPoint( 0, 0, 0 );
   vjVec3 endPoint, startPoint;
   endPoint.xformFull( *this, forwardPoint );
   startPoint.xformFull( *this, originPoint );
   vjVec3 directionVector = endPoint - startPoint;

   // constrain the direction to x/z plane only
   directionVector[VJ_Y] = 0.0f;                   // Eliminate Y value
   directionVector.normalize();
   float y_rot = Math::rad2Deg( acosf(directionVector.dot( forwardPoint )) );
   vjVec3 whichSide = forwardPoint.cross(directionVector);
   if (whichSide[VJ_Y] < 0.0f)   // If dir vector to "right" (negative) side of forward
      y_rot = -y_rot;

   return y_rot;
   */
   return 0.0f;
}

//: extract the pitch information from the matrix
//  returned value is from -180 to 180, where 0 none
// Rotation around X axis
float Matrix::getXRot() const
{
   /*
   const vjVec3 forwardPoint( 0, 0, -1 );    // -Z
   const vjVec3 originPoint( 0, 0, 0 );
   vjVec3 endPoint, startPoint;
   endPoint.xformFull( *this, forwardPoint );
   startPoint.xformFull( *this, originPoint );
   vjVec3 directionVector = endPoint - startPoint;

   // constrain the direction to y/z plane only
   directionVector[VJ_X] = 0.0f;                // Eliminate X value
   directionVector.normalize();
   float x_rot = Math::rad2Deg( acosf(directionVector.dot( forwardPoint )) );
   vjVec3 whichSide = forwardPoint.cross(directionVector);
   if (whichSide[VJ_X] < 0.0f)      // If dir vector to "bottom" (negative) side of forward
      x_rot = -x_rot;

   return x_rot;
   */
   return 0.0f;
}

//: extract the roll information from the matrix
//  returned value is from -180 to 180, where 0 is no roll
// Rotation around Z axis
float Matrix::getZRot() const
{
   /*
   const vjVec3 up_point( 0, 1, 0 );          // straight up (+Y)
   const vjVec3 origin_point( 0, 0, 0 );
   vjVec3 end_point, start_point;
   end_point.xformFull( *this, up_point );
   start_point.xformFull( *this, origin_point );
   vjVec3 direction_vector = end_point - start_point;

   // constrain the direction to x/y plane only
   direction_vector[VJ_Z] = 0.0f;                    // Eliminate Z component
   direction_vector.normalize();
   float z_rot = Math::rad2Deg( acosf(direction_vector.dot( up_point )) );
   vjVec3 which_side = up_point.cross(direction_vector);
   if (which_side[VJ_Z] < 0.0f)                          // If dirVec it to right (neg side) of up_point
      z_rot = -z_rot;

   return z_rot;
   */
   return 0.0f;
}

void Matrix::getZXYEuler(float& zRot, float& xRot, float& yRot) const
{
   // Extract the rotation directly fromt he matrix
   float x_angle;
   float y_angle;
   float z_angle;
   float cos_y, sin_y;
   float cos_x, sin_x;
   float cos_z, sin_z;

   sin_x = mMat[1][2];
   x_angle = asinf(sin_x);     // Get x angle
   cos_x = cos(x_angle);
   zeroClampAngle(cos_x);          // Clamp it to get a good test

   // Check if cos_x = Zero
   if(cos_x != 0.0f)     // ASSERT: cos_x != 0
   {
         // Get y Angle
      cos_y = mMat[2][2]/cos_x;
      sin_y = -mMat[0][2]/cos_x;
      y_angle = atan2(cos_y, sin_y);

         // Get z Angle
      cos_z = mMat[1][1]/cos_x;
      sin_z = -mMat[1][0]/cos_x;
      z_angle = atan2(cos_z, sin_z);
   }
   else
   {
      // Arbitrarily set z_angle = 0
      z_angle = 0;

         // Get y Angle
      cos_y = mMat[0][0];
      sin_y = mMat[0][1];
      y_angle = atan2(cos_y, sin_y);
   }

   xRot = Math::rad2Deg(x_angle);
   yRot = Math::rad2Deg(y_angle);
   zRot = Math::rad2Deg(z_angle);
}

// --------------------------------------------------------------------------- //

void Matrix::makeDirCos(Vec3 secXAxis, Vec3 secYAxis, Vec3 secZAxis)
{
//   vjASSERT(secXAxis.isNormalized());
//   vjASSERT(secYAxis.isNormalized());
//   vjASSERT(secZAxis.isNormalized());

   float Xa, Xb, Xy;    // Direction cosines of the secondary x-axis
   float Ya, Yb, Yy;    // Direction cosines of the secondary y-axis
   float Za, Zb, Zy;    // Direction cosines of the secondary z-axis

   Vec3 xAxis(1,0,0), yAxis(0,1,0), zAxis(0,0,1);   // The base axis to use

   Xa = secXAxis.dot(xAxis);  Xb = secXAxis.dot(yAxis);  Xy = secXAxis.dot(zAxis);
   Ya = secYAxis.dot(xAxis);  Yb = secYAxis.dot(yAxis);  Yy = secYAxis.dot(zAxis);
   Za = secZAxis.dot(xAxis);  Zb = secZAxis.dot(yAxis);  Zy = secZAxis.dot(zAxis);

   // Set the matrix correctly
   set(Xa, Xb, Xy, 0,
       Ya, Yb, Yy, 0,
       Za, Zb, Zy, 0,
       0,  0,  0, 1);
}

void Matrix::makeAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis)
{
   makeIdent();

   mMat[0][0] = xAxis[0];
   mMat[0][1] = xAxis[1];
   mMat[0][2] = xAxis[2];

   mMat[1][0] = yAxis[0];
   mMat[1][1] = yAxis[1];
   mMat[1][2] = yAxis[2];

   mMat[2][0] = zAxis[0];
   mMat[2][1] = zAxis[1];
   mMat[2][2] = zAxis[2];
}

void Matrix::getAxes(Vec3& xAxis, Vec3& yAxis, Vec3& zAxis) const
{
   xAxis[0] = mMat[0][0];
   xAxis[1] = mMat[0][1];
   xAxis[2] = mMat[0][2];

   yAxis[0] = mMat[1][0];
   yAxis[1] = mMat[1][1];
   yAxis[2] = mMat[1][2];

   zAxis[0] = mMat[2][0];
   zAxis[1] = mMat[2][1];
   zAxis[2] = mMat[2][2];
}


void  Matrix::makeRot(float _degrees, Vec3 _axis)
{
    _axis.normalize();  // NOTE: This could be eliminated by passing normalized
             //       vector.  This could be by ref to make even faster
    // GGI: pg 466
    float s = sin(Math::deg2Rad(_degrees));
    float c = cos(Math::deg2Rad(_degrees));
    float t = 1-c;
    float x = _axis[0];
    float y = _axis[1];
    float z = _axis[2];

    /*
    mat[0][0] = (t*x*x)+c;     mat[1][0] = (t*x*y)+(s*z); mat[2][0] = (t*x*z)-(s*y); mat[3][0] = 0.0f;
    mat[0][1] = (t*x*y)-(s*z); mat[1][1] = (t*y*y)+c;     mat[2][1] = (t*y*z)+(s*x); mat[3][1] = 0.0f;
    mat[0][2] = (t*x*z)+(s*y); mat[1][2] = (t*y*z)-(s*x); mat[2][2] = (t*z*z)+c;     mat[3][2] = 0.0f;
    mat[0][3] = 0.0f;          mat[1][3] = 0.0f;          mat[2][3] = 0.0f;          mat[3][3] = 1.0f;
    */

    /* From: Introduction to robotic.  Craig.  Pg. 52 */
    mMat[0][0] = (t*x*x)+c;     mMat[1][0] = (t*x*y)-(s*z); mMat[2][0] = (t*x*z)+(s*y); mMat[3][0] = 0.0f;
    mMat[0][1] = (t*x*y)+(s*z); mMat[1][1] = (t*y*y)+c;     mMat[2][1] = (t*y*z)-(s*x); mMat[3][1] = 0.0f;
    mMat[0][2] = (t*x*z)-(s*y); mMat[1][2] = (t*y*z)+(s*x); mMat[2][2] = (t*z*z)+c;     mMat[3][2] = 0.0f;
    mMat[0][3] = 0.0f;          mMat[1][3] = 0.0f;          mMat[2][3] = 0.0f;          mMat[3][3] = 1.0f;

    zeroClamp();     // Clamp ~ zero values
}


void  Matrix::makeTrans(float _x, float _y, float _z)
{
   makeIdent();
   mMat[3][0] = _x;
   mMat[3][1] = _y;
   mMat[3][2] = _z;
}

void Matrix::makeTrans(const Vec3& trans)
{ makeTrans(trans[0],trans[1],trans[2]); }

void Matrix::setTrans(float _x, float _y, float _z)
{
   mMat[3][0] = _x;
   mMat[3][1] = _y;
   mMat[3][2] = _z;
}

void Matrix::setTrans(const Vec3& trans)
{ setTrans(trans[0],trans[1],trans[2]); }


void Matrix::getTrans(float& _x, float& _y, float& _z) const
{
   _x = mMat[3][0];
   _y = mMat[3][1];
   _z = mMat[3][2];
}

Vec3 Matrix::getTrans() const
{
   Vec3 trans;;
   getTrans(trans[0],trans[1],trans[2]);
   return trans;
}

void  Matrix::makeScale(float _x, float _y, float _z)
{
    makeIdent();
    mMat[0][0] = _x;
    mMat[1][1] = _y;
    mMat[2][2] = _z;
}


/*---------------------------------------------------------------------------*
 | mat_inv: Compute the inverse of a n x n matrix, using the maximum pivot   |
 |          strategy.  n <= MAX1.                                            |
 *---------------------------------------------------------------------------*

   Parameters:
       a        a n x n square matrix
       b        inverse of input a.
       n        dimenstion of matrix a.
*/
//void mat_inv( a, b, n )
//double  a[], b[];
//int     n;

    /// Set mat = inverse(_m)
bool Matrix::invert(Matrix& _m)

{
        float*  a = _m.floatPtr();
   float*  b = floatPtr();

   int   n = 4;
   //int      is, js;      // Was never referenced
   int     i, j, k;
        int     r[ 4], c[ 4], row[ 4], col[ 4];
        float  m[ 4][ 4*2], pivot, max_m, tmp_m, fac;


        /* Initialization */
        for ( i = 0; i < n; i ++ )
        {
                r[ i] = c[ i] = 0;
                row[ i] = col[ i] = 0;
        }

        /* Set working matrix */
        for ( i = 0; i < n; i++ )
        {
                for ( j = 0; j < n; j++ )
                {
                        m[ i][ j] = a[ i * n + j];
                        m[ i][ j + n] = ( i == j ) ? 1.0 : 0.0 ;
                }
        }

        /* Begin of loop */
        for ( k = 0; k < n; k++ )
        {
                /* Choosing the pivot */
                for ( i = 0, max_m = 0; i < n; i++ )
                {
                        if ( row[ i]  )      continue;
                        for ( j = 0; j < n; j++ )
                        {
                                if ( col[ j] )          continue;
                                tmp_m = fabs( m[ i][ j]);
                                if ( tmp_m > max_m)
                                {
                                        max_m = tmp_m;
                                        r[ k] = i;
                                        c[ k] = j;
                                }
                        }
                }
                row[ r[k] ] = col[ c[k] ] = 1;
                pivot = m[ r[ k] ][ c[ k] ];


                if ( fabs( pivot) <= 1e-20)
                {
                        std::cerr << "*** pivot = %f in mat_inv. ***\n";
                        //exit( 0);
         return false;
                }

                /* Normalization */
                for ( j = 0; j < 2*n; j++ )
                {
                        if ( j == c[ k] )
                                m[ r[ k]][ j] = 1.0;
                        else
                                m[ r[ k]][ j] /= pivot;
                }

                /* Reduction */
                for ( i = 0; i < n; i++ )
                {
                        if ( i == r[ k] )
                                continue;

                        for ( j=0, fac = m[ i][ c[k]]; j < 2*n; j++ )
                        {
                                if ( j == c[ k] )
                                        m[ i][ j] = 0.0;
                                else
                                        m[ i][ j] -= fac * m[ r[k]][ j];
                        }
                }
        }

        /* Assign invers to a matrix */
        for ( i = 0; i < n; i++ )
                for ( j = 0; j < n; j++ )
                        row[ i] = ( c[ j] == i ) ? r[ j] : row[ i];

        for ( i = 0; i < n; i++ )
                for ( j = 0; j < n; j++ )
                        b[ i * n +  j] = m[ row[ i]][ j + n];

   return true;   // It worked
}

}



#endif
