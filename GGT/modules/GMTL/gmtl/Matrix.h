/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Matrix.h,v $
 * Date modified: $Date: 2002-05-17 20:01:30 $
 * Version:       $Revision: 1.18 $
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

namespace gmtl
{

/**
 * Matrix: 4x4 Matrix class (OpenGL ordering)
 *
 * C/C++ uses matrices in row major order.  In other words the access
 * indices look like: mat[row][col] <br>
 * (0,0) (0,1) (0,2) (0,3)   <=== Array      <br>
 * (1,0) (1,1) (1,2) (1,3)   <=== Array      <br>
 * (2,0) (2,1) (2,2) (2,3)   <=== Array      <br>
 * (3,0) (3,1) (3,2) (3,3)   <=== Array      <br>
 * <br>
 * OpenGL ordering specifies that the matrix has to be column major in memory,
 * so we need to access it more like: <br>
 *    NOTE: The given indexes are what the cells have to be called in C/C++
 *          notation.  Since we are putting the columns into memory
 *          back-to-back.        <br>
 * (0,0) (1,0) (2,0) (3,0)       <br>
 * (0,1) (1,1) (2,1) (3,1)       <br>
 * (0,2) (1,2) (2,2) (3,2)       <br>
 * (0,3) (1,3) (2,3) (3,3)       <br>
 *   ^     ^     ^     ^         <br>
 *   ====================== Arrays     <br>
 *
 * So basically OpenGL ordering is the Transpose of the way C++ accesses the array
 * @addtogroup Types
 */
template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
class Matrix
{
public:
   /** use this to declare single value types of the same type as this matrix.
    */
   typedef DATA_TYPE DataType;
   enum
   {
      Rows = ROWS, Cols = COLS
   };

   /** describes the xforms that this matrix has been through. */
   enum XformState
   {
      IDENTITY = 1,
      ORTHOGONAL = 2,
      ORTHONORMAL = 4,
      AFFINE = 8,
      FULL = 16,
      XFORM_ERROR = 32 // error bit
   };

   /** Default Constructor (Identity constructor) */
   Matrix()
   {
      /** @todo mp */
      for (unsigned int r = 0; r < ROWS; ++r)
      for (unsigned int c = 0; c < COLS; ++c)
         this->operator()( r, c ) = (DATA_TYPE)0.0;

      /** @todo mp */
      for (unsigned int x = 0; x < Math::Min( COLS, ROWS ); ++x)
         this->operator()( x, x ) = (DATA_TYPE)1.0;

      /** @todo Set initial state to IDENTITY and test other stuff */
      mState = FULL;
   };

   /** copy constructor */
   Matrix( const Matrix<DATA_TYPE, ROWS, COLS>& matrix )
   {
      this->set( matrix.getData() );
      mState = matrix.mState;
   }

   /** element wise setter for 2x2.
    *  @todo needs mp!!
    */
   void set( DATA_TYPE v00, DATA_TYPE v01,
             DATA_TYPE v10, DATA_TYPE v11 )
   {
      gmtlASSERT( ROWS == 2 && COLS == 2 ); // could be at compile time...
      mData[0] = v00;
      mData[1] = v10;
      mData[2] = v01;
      mData[3] = v11;
      mState = FULL;
   }

   /** element wise setter for 2x3.
    * @todo needs mp!!
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12  )
   {
      gmtlASSERT( ROWS == 2 && COLS == 3 ); // could be at compile time...
      mData[0] = v00;
      mData[1] = v10;
      mData[2] = v01;
      mData[3] = v11;
      mData[4] = v02;
      mData[5] = v12;
      mState = FULL;
   }

   /** element wise setter for 3x3.
    * @todo needs mp!!
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12,
             DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22)
   {
      gmtlASSERT( ROWS == 3 && COLS == 3 ); // could be at compile time...
      mData[0] = v00;
      mData[1] = v10;
      mData[2] = v20;

      mData[3] = v01;
      mData[4] = v11;
      mData[5] = v21;

      mData[6] = v02;
      mData[7] = v12;
      mData[8] = v22;
      mState = FULL;
   }

   /** element wise setter for 3x4.
    * @todo needs mp!!  currently no way for a 4x3, ....
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02, DATA_TYPE v03,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12, DATA_TYPE v13,
             DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22, DATA_TYPE v23)
   {
      gmtlASSERT( ROWS == 3 && COLS == 4 );// could be compile time...
      mData[0] = v00;
      mData[1] = v10;
      mData[2] = v20;
      mData[3] = v01;
      mData[4] = v11;
      mData[5] = v21;
      mData[6] = v02;
      mData[7] = v12;
      mData[8] = v22;

      // right row
      mData[9]  = v03;
      mData[10] = v13;
      mData[11] = v23;
      mState = FULL;
   }

   /** element wise setter for 4x4.
    * @todo needs mp!!  currently no way for a 4x3, ....
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02, DATA_TYPE v03,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12, DATA_TYPE v13,
             DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22, DATA_TYPE v23,
             DATA_TYPE v30, DATA_TYPE v31, DATA_TYPE v32, DATA_TYPE v33 )
   {
      gmtlASSERT( ROWS == 4 && COLS == 4 );// could be compile time...
      mData[0]  = v00;
      mData[1]  = v10;
      mData[2]  = v20;
      mData[4]  = v01;
      mData[5]  = v11;
      mData[6]  = v21;
      mData[8]  = v02;
      mData[9]  = v12;
      mData[10] = v22;

      // right row
      mData[12] = v03;
      mData[13] = v13;
      mData[14] = v23;

      // bottom row
      mData[3]  = v30;
      mData[7]  = v31;
      mData[11] = v32;
      mData[15] = v33;
      mState = FULL;
   }

   /** comma operator
    *  @todo implement this!
    */
   //void operator,()( DATA_TYPE b ) {}

   /** set the matrix to the given data.
    *  This function is useful to copy matrix data from another math library.
    *
    * <h3> "Example (to a matrix using an external math library):" </h3>
    * \code
    *    pfMatrix other_matrix;
    *    other_matrix.setRot( 90, 1, 0, 0 );
    *
    *    gmtl::Matrix44f mat;
    *    mat.set( other_matrix.getFloatPtr() );
    * \endcode
    *
    *  WARNING: this isn't really safe, size and datatype are not enforced by
    *           the compiler.
    * @pre data is in the native format of the gmtl::Matrix class, if not,
    *      then you might be able to use the setTranspose function.
    * @pre i.e. in a 4x4 data[0-3] is the 1st column, data[4-7] is 2nd, etc...
    */
   void set( const DATA_TYPE* data )
   {
      /** @todo mp */
      for (unsigned int x = 0; x < ROWS * COLS; ++x)
         mData[x] = data[x];
      mState = FULL;
   }

   /** set the matrix to the transpose of the given data.
    * normally set() takes raw matrix data in column by column order,
    * this function allows you to pass in row by row data.
    *
    * Normally you'll use this function if you want to use a float array
    * to init the matrix (see code example).
    *
    * <h3> "Example (to set a [15 -4 20] translation using float array):" </h3>
    * \code
    *    float data[] = { 1, 0, 0, 15,
    *                     0, 1, 0, -4,
    *                     0, 0, 1, 20,
    *                     0, 0, 0, 1   };
    *    gmtl::Matrix44f mat;
    *    mat.setTranspose( data );
    * \endcode
    *
    *  WARNING: this isn't really safe, size and datatype are not enforced by
    *           the compiler.
    * @pre ptr is in the transpose of the native format of the Matrix class
    * @pre i.e. in a 4x4 data[0-3] is the 1st row, data[4-7] is 2nd, etc...
    */
   void setTranspose( const DATA_TYPE* data )
   {
      /** @todo metaprog */
      for (unsigned int r = 0; r < ROWS; ++r)
      for (unsigned int c = 0; c < COLS; ++c)
         this->operator()( r, c ) = data[(r * COLS) + c];
      mState = FULL;
   }

   /** access [row, col] in the matrix */
   DATA_TYPE& operator()( const unsigned row, const unsigned column )
   {
      gmtlASSERT( (row < ROWS) && (column < COLS) );
      return mData[column*ROWS + row];
   }

   /** access [row, col] in the matrix (const version) */
   const DATA_TYPE&  operator()( const unsigned row, const unsigned column ) const
   {
      gmtlASSERT( (row < ROWS) && (column < COLS) );
      return mData[column*ROWS + row];
   }

   /** bracket operator */
   DATA_TYPE& operator[]( const unsigned i )
   {
      gmtlASSERT( i < (ROWS*COLS) );
      return mData[i];
   }

   /** bracket operator */
   const DATA_TYPE& operator[]( const unsigned i ) const
   {
      gmtlASSERT( i < (ROWS*COLS) );
      return mData[i];
   }

   /** Get a DATA_TYPE pointer to the matrix data
    * RETVAL: Returns a ptr to the head of the matrix data
    */
   const DATA_TYPE*  getData() const { return (DATA_TYPE*)mData; }

   bool isError()
   {
      return mState & XFORM_ERROR;
   }
   void setError()
   {
      mState |= XFORM_ERROR;
   }

public:
   /** Column major.  In other words {Column1, Column2, Column3, Column4} in memory
    * access element mData[column][row]
    */
   DATA_TYPE mData[COLS*ROWS];

   /** describes what xforms are in this matrix */
   char mState;
};

typedef Matrix<float, 2, 2> Matrix22f;
typedef Matrix<double, 2, 2> Matrix22d;
typedef Matrix<float, 2, 3> Matrix23f;
typedef Matrix<double, 2, 3> Matrix23d;
typedef Matrix<float, 3, 3> Matrix33f;
typedef Matrix<double, 3, 3> Matrix33d;
typedef Matrix<float, 3, 4> Matrix34f;
typedef Matrix<double, 3, 4> Matrix34d;
typedef Matrix<float, 4, 4> Matrix44f;
typedef Matrix<double, 4, 4> Matrix44d;

/** 32bit floating point 2x2 identity matrix */
const Matrix22f MAT_IDENTITY22F = Matrix22f();

/** 64bit floating point 2x2 identity matrix */
const Matrix22d MAT_IDENTITY22D = Matrix22d();

/** 32bit floating point 2x2 identity matrix */
const Matrix23f MAT_IDENTITY23F = Matrix23f();

/** 64bit floating point 2x2 identity matrix */
const Matrix23d MAT_IDENTITY23D = Matrix23d();

/** 32bit floating point 3x3 identity matrix */
const Matrix33f MAT_IDENTITY33F = Matrix33f();

/** 64bit floating point 3x3 identity matrix */
const Matrix33d MAT_IDENTITY33D = Matrix33d();

/** 32bit floating point 3x4 identity matrix */
const Matrix34f MAT_IDENTITY34F = Matrix34f();

/** 64bit floating point 3x4 identity matrix */
const Matrix34d MAT_IDENTITY34D = Matrix34d();

/** 32bit floating point 4x4 identity matrix */
const Matrix44f MAT_IDENTITY44F = Matrix44f();

/** 64bit floating point 4x4 identity matrix */
const Matrix44d MAT_IDENTITY44D = Matrix44d();


} // end namespace gmtl



#endif
