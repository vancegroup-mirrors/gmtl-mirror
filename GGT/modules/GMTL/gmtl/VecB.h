/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecB.h,v $
 * Date modified: $Date: 2004-09-01 15:56:42 $
 * Version:       $Revision: 1.1.2.1 $
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
#ifndef _GMTL_VECB_H_
#define _GMTL_VECB_H_

#include <gmtl/Util/Assert.h>
#include <gmtl/Util/Meta.h>
#include <gmtl/Config.h>
#include <gmtl/Helpers.h>


namespace gmtl
{

namespace meta
{
// Expression templates for vectors
//
// NOTE: These could probably be optimized more in the future

// Concepts:
//
// VectorExpression:
//    types:
//    interface:
//       TYPE eval(unsigned i):  Returns evaluation of expression at elt i

template<typename T>
struct VecArgTraits
{
   typedef T const& ExprRef;
};


/** template to hold argument reference that is a vector. */
template <typename VEC_TYPE>
struct VecArg
{
   typedef typename VEC_TYPE::DataType DataType;
   const VEC_TYPE& mVecArg;

   inline VecArg(const VEC_TYPE& vArg) : mVecArg(vArg) {}
   inline DataType eval(const unsigned i) const
   {  return mVecArg[i]; }
};

template <typename VEC_TYPE>
inline VecArg<VEC_TYPE> makeVecArg(VEC_TYPE vec)
{ return VecArg<VEC_TYPE>(vec); }

/** template to hold a scalar argument. */
template <typename T>
struct ScalarArg
{
   typedef T DataType;

   const T mScalar;

   inline ScalarArg(const T scalar) : mScalar(scalar) {}
   inline T eval(const unsigned i) const
   { return mScalar; }
};

template <typename T>
inline ScalarArg<T> makeScalarArg(T val)
{ return ScalarArg<T>(val); }

// -- Expressions -- //
/** Base expression.  Used for Barton-Nackman style trick.
* It allows other methods to be parameterized for only Expressions instead of every
* type under the sun.
*/
/*
template <typename EXP_TYPE>
struct VecExpr
{
   typedef EXP_TYPE ExpressionType;

   inline const ExpressionType& impl() const
   { return *static_cast<const ExpressionType *> (this); }

   ExpressionType& impl()
   { return *static_cast<ExpressionType*> (this); }
};
*/

/** Binary vector expression.
*/
template <typename EXP1_T, typename EXP2_T, typename OP>
struct VecBinaryExpr //: public VecExpr< VecBinaryExpr<EXP1_T, EXP2_T, OP> >
{
   typedef typename EXP1_T::DataType DataType;

   const EXP1_T Exp1;
   const EXP2_T Exp2;

   inline VecBinaryExpr(const EXP1_T& e1, const EXP2_T& e2) : Exp1(e1), Exp2(e2) {;}
   inline DataType eval(const unsigned i) const
   { return OP::eval(Exp1.eval(i), Exp2.eval(i)); }
};

/** Unary vector expression.
*/
template <typename EXP1_T, typename OP>
struct VecUnaryExpr //: public VecExpr< VecUnaryExpr<EXP1_T, OP> >
{
   typedef typename EXP1_T::DataType DataType;

   const EXP1_T Exp1;

   inline VecUnaryExpr(const EXP1_T& e1) : Exp1(e1) {;}
   inline DataType eval(const unsigned i) const
   { return OP::eval(Exp1.eval(i)); }
};

// --- Operations --- //
struct VecPlusBinary
{
   template <typename T>
   static inline T eval(const T& a1, const T& a2)
   { return a1+a2; }
};


template<typename VEC_TYPE, typename EXP1_T, typename EXP2_T, typename OP>
inline void AssignVec(VEC_TYPE& vec, const VecBinaryExpr<EXP1_T,EXP2_T,OP>& exp)
{
   for(unsigned i=0;i<unsigned(VEC_TYPE::Size);++i)
   { vec[i] = exp.eval(i); }
}

template<typename VEC_TYPE, typename EXP1_T, typename OP>
inline void AssignVec(VEC_TYPE& vec, const VecUnaryExpr<EXP1_T,OP>& exp)
{
   for(unsigned i=0;i<unsigned(VEC_TYPE::Size);++i)
   {  vec[i] = exp.eval(i); }
}


template<typename EXP1_T, typename EXP2_T>
inline VecBinaryExpr<EXP1_T, EXP2_T, VecPlusBinary >
SumVec(const EXP1_T& e1, const EXP2_T& e2)
{
   return VecBinaryExpr<EXP1_T, EXP2_T, VecPlusBinary >(e1, e2);
}

template<typename T, unsigned SIZE>
inline VecBinaryExpr< VecArg<gmtl::Vec<T,SIZE> >, VecArg<gmtl::Vec<T,SIZE> >, VecPlusBinary>
SumVec(const gmtl::Vec<T,SIZE>& v1, const gmtl::Vec<T,SIZE>& v2)
{
   return VecBinaryExpr< VecArg<gmtl::Vec<T,SIZE> >,
                         VecArg<gmtl::Vec<T,SIZE> >,
                         VecPlusBinary>(makeVecArg(v1), makeVecArg(v2));
}

} // meta
} // gmtl

namespace gm = gmtl::meta;

namespace gmtl
{

struct DefaultVecTag
{;};

/**
 * Base type for vector-like objects including Points and Vectors. It is
 * templated on the component datatype as well as the number of components that
 * make it up.
 *
 * @param DATA_TYPE  the datatype to use for the components
 * @param SIZE       the number of components this VecB has
 * @param REP        the representation to use for the vector.  (expression template or default)
 */
template<class DATA_TYPE, unsigned SIZE, typename REP=DefaultVecTag>
class VecB
{
public:
   /// The datatype used for the components of this VecB.
   typedef DATA_TYPE DataType;

   /// The number of components this VecB has.
   enum Params { Size = SIZE };

public:
   /**
    * Default constructor.
    * Does nothing, leaves data alone.
    * This is for performance because this constructor is called by derived class constructors
    * Even when they just want to set the data directly
    */
   VecB()
   {
#ifdef GMTL_COUNT_CONSTRUCT_CALLS
      gmtl::helpers::VecCtrCounterInstance()->inc();
#endif
   }


   /**
    * Makes an exact copy of the given VecB object.
    *
    * @param rVec    the VecB object to copy
    */
   VecB(const VecB<DATA_TYPE, SIZE>& rVec)
   {
#ifdef GMTL_COUNT_CONSTRUCT_CALLS
      gmtl::helpers::VecCtrCounterInstance()->inc();
#endif
      /*
      for(unsigned i=0;i<SIZE;++i)
         mData[i] = rVec.mData[i];
      */
      gmtl::meta::AssignVecUnrolled<SIZE-1, VecB<DATA_TYPE,SIZE> >::func(*this, rVec);
   }


   //@{
   /**
    * Gets the ith component in this VecB.
    *
    * @param i    the zero-based index of the component to access.
    * @pre i < SIZE
    *
    * @return  a reference to the ith component
    */
   inline DATA_TYPE& operator [](const unsigned i)
   {
      gmtlASSERT(i < SIZE);
      //return mData[i];
   }
   inline const DATA_TYPE&  operator [](const unsigned i) const
   {
      gmtlASSERT(i < SIZE);
      //return mData[i];
   }
   //@}

public:
};



/** Partial specialization for default vec impl.
 * This is the one that users see and it has all the data members to use.
 */
template<class DATA_TYPE, unsigned SIZE>
class VecB<DATA_TYPE, SIZE, DefaultVecTag>
{
public:
   /// The datatype used for the components of this VecB.
   typedef DATA_TYPE DataType;

   /// The number of components this VecB has.
   enum Params { Size = SIZE };

public:
   /**
    * Default constructor.
    * Does nothing, leaves data alone.
    * This is for performance because this constructor is called by derived class constructors
    * Even when they just want to set the data directly
    */
   VecB()
   {
#ifdef GMTL_COUNT_CONSTRUCT_CALLS
      gmtl::helpers::VecCtrCounterInstance()->inc();
#endif
   }


   /**
    * Makes an exact copy of the given VecB object.
    *
    * @param rVec    the VecB object to copy
    */
   VecB(const VecB<DATA_TYPE, SIZE>& rVec)
   {
#ifdef GMTL_COUNT_CONSTRUCT_CALLS
      gmtl::helpers::VecCtrCounterInstance()->inc();
#endif
      /*
      for(unsigned i=0;i<SIZE;++i)
         mData[i] = rVec.mData[i];
      */
      gmtl::meta::AssignVecUnrolled<SIZE-1, VecB<DATA_TYPE,SIZE> >::func(*this, rVec);
   }


   //@{
   /**
    * Creates a new VecB initialized to the given values.
    */
   VecB(const DATA_TYPE& val0,const DATA_TYPE& val1)
   {
#ifdef GMTL_COUNT_CONSTRUCT_CALLS
      gmtl::helpers::VecCtrCounterInstance()->inc();
#endif

      // @todo need compile time assert
      gmtlASSERT( SIZE == 2 && "out of bounds element access in VecB" );
      mData[0] = val0; mData[1] = val1;
   }
   VecB(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2)
   {
#ifdef GMTL_COUNT_CONSTRUCT_CALLS
      gmtl::helpers::VecCtrCounterInstance()->inc();
#endif
      // @todo need compile time assert
      gmtlASSERT( SIZE == 3 && "out of bounds element access in VecB" );
      mData[0] = val0;  mData[1] = val1;  mData[2] = val2;
   }
   VecB(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2,const DATA_TYPE& val3)
   {
#ifdef GMTL_COUNT_CONSTRUCT_CALLS
      gmtl::helpers::VecCtrCounterInstance()->inc();
#endif
      // @todo need compile time assert
      gmtlASSERT( SIZE == 4 && "out of bounds element access in VecB" );
      mData[0] = val0;  mData[1] = val1;  mData[2] = val2;  mData[3] = val3;
   }
   //@}

   /**
    * Sets the components in this VecB using the given array.
    *
    * @param dataPtr    the array containing the values to copy
    * @pre dataPtr has at least SIZE elements
    */
   inline void set(const DATA_TYPE* dataPtr)
   {
      gmtl::meta::AssignArrayUnrolled<SIZE-1, DATA_TYPE>::func(&(mData[0]), dataPtr);
   }

   //@{
   /**
    * Sets the components in this VecB to the given values.
    */
   inline void set(const DATA_TYPE& val0)
   { mData[0] = val0; }

   inline void set(const DATA_TYPE& val0,const DATA_TYPE& val1)
   {
      gmtlASSERT( SIZE >= 2 && "out of bounds element access in VecB" );
      mData[0] = val0; mData[1] = val1;
   }
   inline void set(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2)
   {
      gmtlASSERT( SIZE >= 3 && "out of bounds element access in VecB" );
      mData[0] = val0;  mData[1] = val1;  mData[2] = val2;
   }
   inline void set(const DATA_TYPE& val0,const DATA_TYPE& val1,const DATA_TYPE& val2,const DATA_TYPE& val3)
   {
      gmtlASSERT( SIZE >= 4 && "out of bounds element access in VecB" );
      mData[0] = val0;  mData[1] = val1;  mData[2] = val2;  mData[3] = val3;
   }
   //@}

   //@{
   /**
    * Gets the ith component in this VecB.
    *
    * @param i    the zero-based index of the component to access.
    * @pre i < SIZE
    *
    * @return  a reference to the ith component
    */
   inline DATA_TYPE& operator [](const unsigned i)
   {
      gmtlASSERT(i < SIZE);
      return mData[i];
   }
   inline const DATA_TYPE&  operator [](const unsigned i) const
   {
      gmtlASSERT(i < SIZE);
      return mData[i];
   }
   //@}

   //@{
   /**
    * Gets the internal array of the components.
    *
    * @return  a pointer to the component array with length SIZE
    */
   DATA_TYPE* getData()
   { return mData; }
   const DATA_TYPE* getData() const
   { return mData; }
   //@}

public:
   /// The array of components.
   DATA_TYPE mData[SIZE];
};



};

#endif
