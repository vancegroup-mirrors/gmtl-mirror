/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Xforms.h,v $
 * Date modified: $Date: 2002-03-09 23:17:54 $
 * Version:       $Revision: 1.16 $
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
#ifndef _GMTL___XFORMS_H_
#define _GMTL___XFORMS_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Vec.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Convert.h>
#include <gmtl/Generate.h>

namespace gmtl
{
   /** transform a vector by a rotation quaternion.
    * @pre give a vector
    * @post Rv = q P(v) q*
    * @post vector = rotquat * pure_quat_from_vector * rotquat_conj
    * @see game programming gems #1 p199
    * @see shoemake siggraph notes
    * @notes for the implementation, inv and conj should both work for the "q*" in "Rv = q P(v) q*"
    *        but conj is actually faster so we usually choose that.
    */
   template <typename DATA_TYPE>
   inline Vec<DATA_TYPE, 3>& xform( Vec<DATA_TYPE, 3>& result_vec, const Quat<DATA_TYPE>& rot, const Vec<DATA_TYPE, 3>& vector )
   {
      // easiest to write and understand (slowest too)
      //return result_vec = makeVec( rot * makePure( vector ) * makeConj( rot ) );

      // completely hand expanded 
      // (faster by 28% in gcc 2.96 debug mode.)
      // (faster by 35% in gcc 2.96 opt3 mode (78% for doubles))
      Quat<DATA_TYPE> rot_conj( -rot[Xelt], -rot[Yelt], -rot[Zelt], rot[Welt] ); 
      Quat<DATA_TYPE> pure( vector[0], vector[1], vector[2], (DATA_TYPE)0.0 );
      Quat<DATA_TYPE> temp( 
         pure[Welt]*rot_conj[Xelt] + pure[Xelt]*rot_conj[Welt] + pure[Yelt]*rot_conj[Zelt] - pure[Zelt]*rot_conj[Yelt],
         pure[Welt]*rot_conj[Yelt] + pure[Yelt]*rot_conj[Welt] + pure[Zelt]*rot_conj[Xelt] - pure[Xelt]*rot_conj[Zelt],
         pure[Welt]*rot_conj[Zelt] + pure[Zelt]*rot_conj[Welt] + pure[Xelt]*rot_conj[Yelt] - pure[Yelt]*rot_conj[Xelt],
         pure[Welt]*rot_conj[Welt] - pure[Xelt]*rot_conj[Xelt] - pure[Yelt]*rot_conj[Yelt] - pure[Zelt]*rot_conj[Zelt] );
      
      result_vec.set( 
         rot[Welt]*temp[Xelt] + rot[Xelt]*temp[Welt] + rot[Yelt]*temp[Zelt] - rot[Zelt]*temp[Yelt],
         rot[Welt]*temp[Yelt] + rot[Yelt]*temp[Welt] + rot[Zelt]*temp[Xelt] - rot[Xelt]*temp[Zelt],
         rot[Welt]*temp[Zelt] + rot[Zelt]*temp[Welt] + rot[Xelt]*temp[Yelt] - rot[Yelt]*temp[Xelt] );
      return result_vec;
   }

   /** transform a vector by a rotation quaternion.
    * @pre give a vector
    * @post result = quat * vector
    */
   template <typename DATA_TYPE>
   inline Vec<DATA_TYPE, 3> operator*( const Quat<DATA_TYPE>& rot, const Vec<DATA_TYPE, 3>& vector )
   {
      // easiest to write and understand (slowest too)
      //return makeVec( rot * makePure( vector ) * makeConj( rot ) );
      
      // completely hand expanded 
      // (faster by 24% in gcc 2.96 debug mode.)
      // (faster by 29% in gcc 2.96 opt3 mode (74% for doubles))
      Quat<DATA_TYPE> rot_conj( -rot[Xelt], -rot[Yelt], -rot[Zelt], rot[Welt] ); 
      Quat<DATA_TYPE> pure( vector[0], vector[1], vector[2], (DATA_TYPE)0.0 );
      Quat<DATA_TYPE> temp( 
         pure[Welt]*rot_conj[Xelt] + pure[Xelt]*rot_conj[Welt] + pure[Yelt]*rot_conj[Zelt] - pure[Zelt]*rot_conj[Yelt],
         pure[Welt]*rot_conj[Yelt] + pure[Yelt]*rot_conj[Welt] + pure[Zelt]*rot_conj[Xelt] - pure[Xelt]*rot_conj[Zelt],
         pure[Welt]*rot_conj[Zelt] + pure[Zelt]*rot_conj[Welt] + pure[Xelt]*rot_conj[Yelt] - pure[Yelt]*rot_conj[Xelt],
         pure[Welt]*rot_conj[Welt] - pure[Xelt]*rot_conj[Xelt] - pure[Yelt]*rot_conj[Yelt] - pure[Zelt]*rot_conj[Zelt] );

      return Vec<DATA_TYPE, 3>( 
         rot[Welt]*temp[Xelt] + rot[Xelt]*temp[Welt] + rot[Yelt]*temp[Zelt] - rot[Zelt]*temp[Yelt],
         rot[Welt]*temp[Yelt] + rot[Yelt]*temp[Welt] + rot[Zelt]*temp[Xelt] - rot[Xelt]*temp[Zelt],
         rot[Welt]*temp[Zelt] + rot[Zelt]*temp[Welt] + rot[Xelt]*temp[Yelt] - rot[Yelt]*temp[Xelt] );
   }

   
   
   /** xform a vector by a matrix.
    *  Transforms a vector with a matrix, uses multiplication of [m x k] matrix by a [k x 1] matrix (the later also known as a Vector...).
    *  @post This results in a full matrix xform of the vector (assumes you know what you are doing - 
    *  i.e. that you know that the last component of a vector by definition is 0.0, and changing 
    *  this might make the xform different than what you may expect).
    *  @post returns a point same size as the matrix rows...  (v[r][1] = m[r][k] * v[k][1])
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Vec<DATA_TYPE, COLS>& xform( Vec<DATA_TYPE, COLS>& result, const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, COLS>& vector )
   {
      // do a standard [m x k] by [k x n] matrix multiplication (where n == 0).
      
      // reset vec to zero...
      result = Vec<DATA_TYPE, COLS>(); 
         
      for (int iRow = 0; iRow < ROWS; ++iRow)
      for (int iCol = 0; iCol < COLS; ++iCol)
         result[iRow] += matrix( iRow, iCol ) * vector[iCol];
      
      return result;
   }
   
         
   /** matrix * vector xform.
    *  multiplication of [m x k] matrix by a [k x 1] matrix (also known as a Vector...).
    *  @post This results in a full matrix xform of the vector (assumes you know what you are doing - 
    *  i.e. that you know that the last component of a vector by definition is 0.0, and changing 
    *  this might make the xform different that what you may expect).
    *  @post returns a vec same size as the matrix rows...  (v[r][1] = m[r][k] * v[k][1])
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Vec<DATA_TYPE, COLS> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, COLS>& vector )
   {
      // do a standard [m x k] by [k x n] matrix multiplication (where n == 0).
      Vec<DATA_TYPE, COLS> temporary;
      return xform( temporary, matrix, vector );
   }

   
   
   
   /** partially transform a partially specified vector by a matrix, assumes last elt of vector is 0 (the 0 makes it only partially transformed).
    *  Transforms a vector with a matrix, uses multiplication of [m x k] matrix by a [k-1 x 1] matrix (also known as a Vector [with w == 0 for vectors by definition] ).
    *  @post the [k-1 x 1] vector you pass in is treated as a [vector, 0.0]
    *  @post This ends up being a partial xform using only the rotation from the matrix (vector xformed result is untranslated).
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS, unsigned VEC_SIZE>
   inline Vec<DATA_TYPE, VEC_SIZE>& xform( Vec<DATA_TYPE, VEC_SIZE >& result, const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, VEC_SIZE >& vector )
   {
      ggtASSERT( VEC_SIZE == COLS - 1 );
      // do a standard [m x k] by [k x n] matrix multiplication (where n == 0).
      
      // copy the point to the correct size.
      Point<DATA_TYPE, COLS> temp_vector, temp_result;
      for (int x = 0; x < VEC_SIZE; ++x)
         temp_vector[x] = vector[x];
      temp_vector[COLS-1] = (DATA_TYPE)0.0; // by definition of a vector, set the last unspecified elt to 0.0

      // transform it.
      xform( temp_result, matrix, temp_vector );
      
      // convert result back to vec<DATA_TYPE, VEC_SIZE>
      // some matrices will make the W param large even if this is a true vector, 
      // we'll need to redistribute it to the other elts if W param is non-zero
      if (Math::isEqual( temp_result[VEC_SIZE], (DATA_TYPE)0, (DATA_TYPE)0.0001 ) == false)
      {
         DATA_TYPE w_coord_div = DATA_TYPE( 1.0 ) / temp_result[VEC_SIZE];
         for (int x = 0; x < VEC_SIZE; ++x)
            result[x] = temp_result[x] * w_coord_div;
      }
      else
      {
         for (int x = 0; x < VEC_SIZE; ++x)
            result[x] = temp_result[x];
      }
      
      return result;
   }

   /** matrix * partial vector, assumes last elt of vector is 0 (partial transform).
    *  multiplication of [m x k] matrix by a [k-1 x 1] matrix (also known as a Vector [with w == 0 for vectors by definition] ).
    *  @post the [k-1 x 1] vector you pass in is treated as a [vector, 0.0]
    *  @post This ends up being a partial xform using only the rotation from the matrix (vector xformed result is untranslated).
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS, unsigned COLS_MINUS_ONE>
   inline Vec<DATA_TYPE, COLS_MINUS_ONE> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, COLS_MINUS_ONE>& vector )
   {
      Vec<DATA_TYPE, COLS_MINUS_ONE> temporary;
      return xform( temporary, matrix, vector );
   }
   

   
   
   /** transform point by a matrix.
    *  multiplication of [m x k] matrix by a [k x 1] matrix (also known as a Point...).
    *  @post This results in a full matrix xform of the point.
    *  @post returns a point same size as the matrix rows...  (p[r][1] = m[r][k] * p[k][1])
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Point<DATA_TYPE, COLS>& xform( Point<DATA_TYPE, COLS>& result, const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, COLS>& point )
   {
      // do a standard [m x k] by [k x n] matrix multiplication (n == 1).

      // reset point to zero...
      result = Point<DATA_TYPE, COLS>();
      
      for (int iRow = 0; iRow < ROWS; ++iRow)
      for (int iCol = 0; iCol < COLS; ++iCol)
         result[iRow] += matrix( iRow, iCol ) * point[iCol];
      
      return result;
   }   
   
   /** matrix * point.
    *  multiplication of [m x k] matrix by a [k x 1] matrix (also known as a Point...).
    *  @post This results in a full matrix xform of the point.
    *  @post returns a point same size as the matrix rows...  (p[r][1] = m[r][k] * p[k][1])
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Point<DATA_TYPE, COLS> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, COLS>& point )
   {
      Point<DATA_TYPE, COLS> temporary;
      return xform( temporary, matrix, point );
   }

   
   
   
   /** transform a partially specified point by a matrix, assumes last elt of point is 1.
    *  Transforms a point with a matrix, uses multiplication of [m x k] matrix by a [k-1 x 1] matrix (also known as a Point [with w == 1 for points by definition] ).
    *  @post the [k-1 x 1] point you pass in is treated as [point, 1.0]
    *  @post This results in a full matrix xform of the point.
    * @todo we need a PointOps.h operator*=(scalar) function
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS, unsigned PNT_SIZE>
   inline Point<DATA_TYPE, PNT_SIZE>& xform( Point<DATA_TYPE, PNT_SIZE>& result, const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, PNT_SIZE>& point )
   {
      ggtASSERT( PNT_SIZE == COLS - 1 && "The precondition of this method is that the vector size must be one less than the number of columns in the matrix.  eg. if Mat<n,k>, then Vec<k-1>." );

      // copy the point to the correct size.
      Point<DATA_TYPE, PNT_SIZE+1> temp_point, temp_result;
      for (int x = 0; x < PNT_SIZE; ++x)
         temp_point[x] = point[x];
      temp_point[PNT_SIZE] = (DATA_TYPE)1.0; // by definition of a point, set the last unspecified elt to 1.0

      // transform it.
      xform( temp_result, matrix, temp_point );
      
      // convert result back to pnt<DATA_TYPE, PNT_SIZE>
      // some matrices will make the W param large even if this is a true vector, 
      // we'll need to redistribute it to the other elts if W param is non-zero
      if (Math::isEqual( temp_result[PNT_SIZE], (DATA_TYPE)0, (DATA_TYPE)0.0001 ) == false)
      {
         DATA_TYPE w_coord_div = DATA_TYPE( 1.0 ) / temp_result[PNT_SIZE];
         for (int x = 0; x < PNT_SIZE; ++x)
            result[x] = temp_result[x] * w_coord_div;
      }
      else
      {
         for (int x = 0; x < PNT_SIZE; ++x)
            result[x] = temp_result[x];
      }
            
      return result;
   }
         
   /** matrix * partially specified point.
    *  multiplication of [m x k] matrix by a [k-1 x 1] matrix (also known as a Point [with w == 1 for points by definition] ).
    *  @post the [k-1 x 1] vector you pass in is treated as a [point, 1.0]
    *  @post This results in a full matrix xform of the point.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS, unsigned COLS_MINUS_ONE>
   inline Point<DATA_TYPE, COLS_MINUS_ONE> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, COLS_MINUS_ONE>& point )
   {
      Point<DATA_TYPE, COLS_MINUS_ONE> temporary;
      return xform( temporary, matrix, point );
   }
   
   
   
   
   
   
   
   
   // old xform stuff...
/*
// XXX: Assuming that there is no projective portion to the matrix or homogeneous coord
// NOTE: It is a vec, so we don't deal with the translation
Vec3 operator*(const Matrix& mat, const Vec3& vec)
{

   Vec3 ret_vec;
   for(int iRow=0;iRow<3;iRow++)
   {
      ret_vec[iRow] = (vec[0]* (mat[0][iRow]))
                    + (vec[1]* (mat[1][iRow]))
                    + (vec[2]* (mat[2][iRow]));
   }
   return ret_vec;
}

// XXX: Assuming no projective or homogeneous coord to the mat
Point3 operator*(const Matrix& mat, const Point3& point)
{
   Point3 ret_pt;
   for(int iRow=0;iRow<3;iRow++)
   {
      ret_pt[iRow] = (point[0]* (mat[0][iRow]))
                   + (point[1]* (mat[1][iRow]))
                   + (point[2]* (mat[2][iRow]))
                   + (mat[3][iRow]);
   }
   return ret_pt;
}

// Xform an OOB by a matrix
// NOTE: This will NOT work if the matrix has shear or scale
OOBox operator*(const Matrix& mat, const OOBox& box)
{
   OOBox ret_box;

   ret_box.center() = mat * box.center();

   ret_box.axis(0) = mat * ret_box.axis(0);
   ret_box.axis(1) = mat * ret_box.axis(1);
   ret_box.axis(2) = mat * ret_box.axis(2);

   ret_box.halfLen(0) = box.halfLen(0);
   ret_box.halfLen(1) = box.halfLen(1);
   ret_box.halfLen(2) = box.halfLen(2);

   return ret_box;
}
*/

};

#endif
