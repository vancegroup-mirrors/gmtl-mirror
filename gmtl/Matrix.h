/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Matrix.h,v $
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
#ifndef _GMTL_MATRIX_H_
#define _GMTL_MATRIX_H_

#include <gmtl/gmtlDefines.h>
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
      { gfxASSERT(i<4); return &mMat[i][0];}
   inline const float*  operator[]( unsigned i ) const
      { gfxASSERT(i<4); return &mMat[i][0];}
   inline float&        operator()( const unsigned& row, const unsigned& column )
      { gfxASSERT((row<4)&&(column<4)); return mMat[column][row];}
   inline const float&  operator()( const unsigned& row, const unsigned& column ) const
      { gfxASSERT((row<4)&&(column<4)); return mMat[column][row];}
   // Return pointer to first element of the given column
   inline float* column(unsigned i)
      { gfxASSERT((i<4)); return &mMat[i][0]; }


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

#endif
