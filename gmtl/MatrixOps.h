/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixOps.h,v $
 * Date modified: $Date: 2002-06-06 00:28:00 $
 * Version:       $Revision: 1.26 $
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
#ifndef _GMTL_MATRIXOPS_H_
#define _GMTL_MATRIXOPS_H_

#include <iostream>         // for std::cerr
#include <algorithm>        // needed for std::swap
#include <gmtl/Matrix.h>
#include <gmtl/Math.h>
#include <gmtl/Vec.h>

namespace gmtl
{
/** @ingroup Ops
 * @name Matrix Operations
 * @{
 */

   /** Make identity matrix out the matrix.
    * make sure every elt is 0.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& identity( Matrix<DATA_TYPE, ROWS, COLS>& result )
   {
      if(result.mState != Matrix<DATA_TYPE, ROWS, COLS>::IDENTITY)   // if not already ident
      {
         // TODO: mp
         for (unsigned int r = 0; r < ROWS; ++r)
         for (unsigned int c = 0; c < COLS; ++c)
            result( r, c ) = (DATA_TYPE)0.0;

         // TODO: mp
         for (unsigned int x = 0; x < Math::Min( COLS, ROWS ); ++x)
            result( x, x ) = (DATA_TYPE)1.0;

//         result.mState = Matrix<DATA_TYPE, ROWS, COLS>::IDENTITY;
         result.mState = Matrix<DATA_TYPE, ROWS, COLS>::FULL;
      }

      return result;
   }


   /** zero out the matrix.
    * make sure every elt is 0.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& zero( Matrix<DATA_TYPE, ROWS, COLS>& result )
   {
      if (result.mState == Matrix<DATA_TYPE, ROWS, COLS>::IDENTITY)
      {
         for (unsigned int x = 0; x < Math::Min( ROWS, COLS ); ++x)
         {
            result( x, x ) = (DATA_TYPE)0;
         }
      }
      else
      {
         for (unsigned int x = 0; x < ROWS*COLS; ++x)
         {
            result[x] = (DATA_TYPE)0;
         }
      }
      return result;
   }


   /** matrix multiply.
    *  @PRE: if lhs is m x p, and rhs is p x n, then result is m x n (mult func undefined otherwise)
    *  @POST: returns a m x n matrix
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned INTERNAL, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& mult( Matrix<DATA_TYPE, ROWS, COLS>& result,
                 const Matrix<DATA_TYPE, ROWS, INTERNAL>& lhs,
                 const Matrix<DATA_TYPE, INTERNAL, COLS>& rhs )
   {
      Matrix<DATA_TYPE, ROWS, COLS> ret_mat; // prevent aliasing
      zero( ret_mat );

      // p. 150 Numerical Analysis (second ed.)
      // if A is m x p, and B is p x n, then AB is m x n
      // (AB)ij  =  [k = 1 to p] (a)ik (b)kj     (where:  1 <= i <= m, 1 <= j <= n)
      for (unsigned int i = 0; i < ROWS; ++i)           // 1 <= i <= m
      for (unsigned int j = 0; j < COLS; ++j)           // 1 <= j <= n
      for (unsigned int k = 0; k < INTERNAL; ++k)       // [k = 1 to p]
         ret_mat( i, j ) += lhs( i, k ) * rhs( k, j );

      return result = ret_mat;
   }

   /** matrix * matrix.
    *  @PRE: if lhs is m x p, and rhs is p x n, then result is m x n (mult func undefined otherwise)
    *  @POST: returns a m x n matrix == lhs * rhs
    *  returns a temporary, is slower.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned INTERNAL, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS> operator*( const Matrix<DATA_TYPE, ROWS, INTERNAL>& lhs,
                                                   const Matrix<DATA_TYPE, INTERNAL, COLS>& rhs )
   {
      Matrix<DATA_TYPE, ROWS, COLS> temporary;
      return mult( temporary, lhs, rhs );
   }

   /** matrix subtraction (algebraic operation for matrix).
    *  @PRE: if lhs is m x n, and rhs is m x n, then result is m x n (mult func undefined otherwise)
    *  @POST: returns a m x n matrix
    *  TODO: <B>enforce the sizes with templates...</b>
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& sub( Matrix<DATA_TYPE, ROWS, COLS>& result,
                 const Matrix<DATA_TYPE, ROWS, COLS>& lhs,
                 const Matrix<DATA_TYPE, ROWS, COLS>& rhs )
   {
      // p. 150 Numerical Analysis (second ed.)
      // if A is m x n, and B is m x n, then AB is m x n
      // (A - B)ij  = (a)ij - (b)ij     (where:  1 <= i <= m, 1 <= j <= n)
      for (unsigned int i = 0; i < ROWS; ++i)           // 1 <= i <= m
      for (unsigned int j = 0; j < COLS; ++j)           // 1 <= j <= n
         result( i, j ) = lhs( i, j ) - rhs( i, j );

      return result;
   }

   /** matrix addition (algebraic operation for matrix).
    *  @PRE: if lhs is m x n, and rhs is m x n, then result is m x n (mult func undefined otherwise)
    *  @POST: returns a m x n matrix
    *  TODO: <B>enforce the sizes with templates...</b>
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& add( Matrix<DATA_TYPE, ROWS, COLS>& result,
                 const Matrix<DATA_TYPE, ROWS, COLS>& lhs,
                 const Matrix<DATA_TYPE, ROWS, COLS>& rhs )
   {
      // p. 150 Numerical Analysis (second ed.)
      // if A is m x n, and B is m x n, then AB is m x n
      // (A - B)ij  = (a)ij + (b)ij     (where:  1 <= i <= m, 1 <= j <= n)
      for (unsigned int i = 0; i < ROWS; ++i)           // 1 <= i <= m
      for (unsigned int j = 0; j < COLS; ++j)           // 1 <= j <= n
         result( i, j ) = lhs( i, j ) + rhs( i, j );

      return result;
   }

   /** matrix postmultiply.
    * @PRE: args must both be n x n (this function is undefined otherwise)
    * @POST: result' = result * operand
    */
   template <typename DATA_TYPE, unsigned SIZE>
   inline Matrix<DATA_TYPE, SIZE, SIZE>& postMult( Matrix<DATA_TYPE, SIZE, SIZE>& result,
                                                     const Matrix<DATA_TYPE, SIZE, SIZE>& operand )
   {
      return mult( result, result, operand );
   }

   /** matrix preMultiply.
    * @PRE: args must both be n x n (this function is undefined otherwise)
    * @POST: result' = operand * result
    */
   template <typename DATA_TYPE, unsigned SIZE>
   inline Matrix<DATA_TYPE, SIZE, SIZE>& preMult( Matrix<DATA_TYPE, SIZE, SIZE>& result,
                                                  const Matrix<DATA_TYPE, SIZE, SIZE>& operand )
   {
      return mult( result, operand, result );
   }

   /** matrix postmult (operator*=).
    * does a postmult on the matrix.
    * @PRE: args must both be n x n (this function is undefined otherwise)
    * @POST: result' = result * operand
    */
   template <typename DATA_TYPE, unsigned SIZE>
   inline Matrix<DATA_TYPE, SIZE, SIZE>& operator*=( Matrix<DATA_TYPE, SIZE, SIZE>& result,
                                                     const Matrix<DATA_TYPE, SIZE, SIZE>& operand )
   {
      return postMult( result, operand );
   }

   /** matrix scalar mult.
    *  mult each elt in a matrix by a scalar value.
    *  @POST: result = mat * scalar
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& mult( Matrix<DATA_TYPE, ROWS, COLS>& result, const Matrix<DATA_TYPE, ROWS, COLS>& mat, float scalar )
   {
      for (unsigned i = 0; i < ROWS * COLS; ++i)
         result[i] = mat[i] * scalar;
      return result;
   }

   /** matrix scalar mult.
    * mult each elt in a matrix by a scalar value.
    *  @POST: result *= scalar
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& mult( Matrix<DATA_TYPE, ROWS, COLS>& result, DATA_TYPE scalar )
   {
      for (unsigned i = 0; i < ROWS * COLS; ++i)
         result[i] *= scalar;
      return result;
   }

   /** matrix scalar mult (operator*=).
    * multiply matrix elements by a scalar
    * @POST: result *= scalar
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& operator*=( Matrix<DATA_TYPE, ROWS, COLS>& result, DATA_TYPE scalar )
   {
      return mult( result, scalar );
   }

   /** matrix transpose in place.
    *  @PRE:  needs to be an N x N matrix
    *  @POST: flip along diagonal
    */
   template <typename DATA_TYPE, unsigned SIZE>
   Matrix<DATA_TYPE, SIZE, SIZE>& transpose( Matrix<DATA_TYPE, SIZE, SIZE>& result )
   {
      // p. 27 game programming gems #1
      for (unsigned c = 0; c < SIZE; ++c)
         for (unsigned r = c + 1; r < SIZE; ++r)
            std::swap( result( r, c ), result( c, r ) );

      return result;
   }

   /** matrix transpose from one type to another (i.e. 3x4 to 4x3)
    *  @PRE:  source needs to be an M x N matrix, while dest needs to be N x M
    *  @POST: flip along diagonal
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   Matrix<DATA_TYPE, ROWS, COLS>& transpose( Matrix<DATA_TYPE, ROWS, COLS>& result, const Matrix<DATA_TYPE, COLS, ROWS>& source )
   {
      // in case result is == source... :(
      Matrix<DATA_TYPE, COLS, ROWS> temp = source;

      // p. 149 Numerical Analysis (second ed.)
      for (unsigned i = 0; i < ROWS; ++i)
      {
         for (unsigned j = 0; j < COLS; ++j)
         {
            result( i, j ) = temp( j, i );
         }
      }

      return result;
   }


   /** full matrix inversion.
    *  Check for error with Matrix::isError().
    * @POST: result' = inv( result )
    * @POST: If inversion failed, then error bit is set within the Matrix.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& invertFull( Matrix<DATA_TYPE, ROWS, COLS>& result, const Matrix<DATA_TYPE, ROWS, COLS>& src )
   {
      /*---------------------------------------------------------------------------*
       | mat_inv: Compute the inverse of a n x n matrix, using the maximum pivot   |
       |          strategy.  n <= MAX1.                                            |
       *---------------------------------------------------------------------------*

         Parameters:
             a        a n x n square matrix
             b        inverse of input a.
             n        dimenstion of matrix a.
      */

      const DATA_TYPE* a = src.getData();
      DATA_TYPE* b = result.mData;

      int   n = 4;
      int    i, j, k;
      int    r[ 4], c[ 4], row[ 4], col[ 4];
      DATA_TYPE  m[ 4][ 4*2], pivot, max_m, tmp_m, fac;

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
            m[ i][ j + n] = ( i == j ) ? (DATA_TYPE)1.0 : (DATA_TYPE)0.0 ;
         }
      }

      /* Begin of loop */
      for ( k = 0; k < n; k++ )
      {
         /* Choosing the pivot */
         for ( i = 0, max_m = 0; i < n; i++ )
         {
            if ( row[ i]  )
               continue;
            for ( j = 0; j < n; j++ )
            {
               if ( col[ j] )
                  continue;
               tmp_m = gmtl::Math::abs( m[ i][ j]);
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


         if ( gmtl::Math::abs( pivot) <= 1e-20)
         {
            std::cerr << "*** pivot = %f in mat_inv. ***\n";
            result.setError();
            return result;
         }

         /* Normalization */
         for ( j = 0; j < 2*n; j++ )
         {
            if ( j == c[ k] )
               m[ r[ k]][ j] = (DATA_TYPE)1.0;
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
                  m[ i][ j] = (DATA_TYPE)0.0;
               else
                  m[ i][ j] -= fac * m[ r[k]][ j];
            }
         }
      }

      /* Assign inverse to a matrix */
      for ( i = 0; i < n; i++ )
         for ( j = 0; j < n; j++ )
            row[ i] = ( c[ j] == i ) ? r[ j] : row[ i];

      for ( i = 0; i < n; i++ )
         for ( j = 0; j < n; j++ )
            b[ i * n +  j] = m[ row[ i]][ j + n];

      // It worked
      return result;
   }

   /** smart matrix inversion.
    *  Does matrix inversion by intelligently selecting what type of inversion to use depending
    *  on the types of operations your Matrix has been through.
    *
    *  5 types of inversion: FULL, AFFINE, ORTHONORMAL, ORTHOGONAL, IDENTITY.
    *
    *  Check for error with Matrix::isError().
    * @POST: result' = inv( result )
    * @POST: If inversion failed, then error bit is set within the Matrix.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& invert( Matrix<DATA_TYPE, ROWS, COLS>& result, const Matrix<DATA_TYPE, ROWS, COLS>& src )
   {
      if (src.mState == Matrix<DATA_TYPE, ROWS, COLS>::IDENTITY )
         return result = src;
      else
         return invertFull( result, src );
   }

   /** smart matrix inversion (in place)
    *  Does matrix inversion by intelligently selecting what type of inversion to use depending
    *  on the types of operations your Matrix has been through.
    *
    *  5 types of inversion: FULL, AFFINE, ORTHONORMAL, ORTHOGONAL, IDENTITY.
    *
    *  Check for error with Matrix::isError().
    * @POST: result' = inv( result )
    * @POST: If inversion failed, then error bit is set within the Matrix.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline Matrix<DATA_TYPE, ROWS, COLS>& invert( Matrix<DATA_TYPE, ROWS, COLS>& result )
   {
      return invert( result, result );
   }

/** @} */

/** @ingroup Compare 
 * @name Matrix Comparitors
 * @{
 */

   /** Compare two mats */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline bool operator==( const Matrix<DATA_TYPE, ROWS, COLS>& lhs, const Matrix<DATA_TYPE, ROWS, COLS>& rhs )
   {
      for (unsigned int i = 0; i < ROWS*COLS; ++i)
      {
         if (lhs[i] != rhs[i])
         {
            return false;
         }
      }

      return true;

      /*  Would like this
      return( lhs[0] == rhs[0] &&
              lhs[1] == rhs[1] &&
              lhs[2] == rhs[2] );
      */
   }

   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline bool operator!=( const Matrix<DATA_TYPE, ROWS, COLS>& lhs, const Matrix<DATA_TYPE, ROWS, COLS>& rhs )
   {
      return bool( !(lhs == rhs) );
   }

   /** Compare two vectors with a tolerance
   * @pre eps must be >= 0
   */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   inline bool isEqual( const Matrix<DATA_TYPE, ROWS, COLS>& lhs, const Matrix<DATA_TYPE, ROWS, COLS>& rhs, const DATA_TYPE& eps = (DATA_TYPE)0 )
   {
      gmtlASSERT( eps >= (DATA_TYPE)0 );

      for (unsigned int i = 0; i < ROWS*COLS; ++i)
      {
         if (!Math::isEqual( lhs[i], rhs[i], eps ))
            return false;
      }
      return true;
   }
/** @} */

} // end of namespace gmtl

#endif
