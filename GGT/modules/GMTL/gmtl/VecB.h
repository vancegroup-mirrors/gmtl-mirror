/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecB.h,v $
 * Date modified: $Date: 2004-10-30 18:24:33 $
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
#ifndef _GMTL_VECB_H_
#define _GMTL_VECB_H_

#include <gmtl/Defines.h>
#include <gmtl/Util/Assert.h>
#ifndef GMTL_NO_METAPROG
#include <gmtl/Util/Meta.h>
#endif
#include <gmtl/Config.h>
#include <gmtl/Helpers.h>


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
protected:
   const REP  expRep;      // The expression rep

public:
   /// The datatype used for the components of this VecB.
   typedef DATA_TYPE DataType;

   /// The number of components this VecB has.
   enum Params { Size = SIZE };

public:
   VecB()
   {;}

   VecB(const REP& rep)
      : expRep(rep)
   {;}


   /** Return the value at given location. */
   inline DATA_TYPE operator [](const unsigned i)
   {
      gmtlASSERT(i < SIZE);
      return expRep[i];
   }
   inline const DATA_TYPE  operator [](const unsigned i) const
   {
      gmtlASSERT(i < SIZE);
      return expRep[i];
   }
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
   typedef VecB<DATA_TYPE, SIZE, DefaultVecTag> VecType;

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
#ifdef GMTL_NO_METAPROG
      for(unsigned i=0;i<SIZE;++i)
         mData[i] = rVec.mData[i];
#else
      gmtl::meta::AssignVecUnrolled<SIZE-1, VecB<DATA_TYPE,SIZE> >::func(*this, rVec);
#endif
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

   /** Assign from another of same type. */
   inline VecType& operator=(const VecType&  rhs)
   {
      for(unsigned i=0;i<SIZE;++i)
      {
         mData[i] = rhs[i];
      }
      return *this;
   }

   /** Assign from different rep. */
   template<typename REP2>
   inline VecType& operator=(const VecB<DATA_TYPE,SIZE,REP2>& rhs)
   {
      for(unsigned i=0;i<SIZE;++i)
      {
         mData[i] = rhs[i];
      }
      return *this;
   }

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


/** template to hold a scalar argument. */
template <typename T>
struct ScalarArg
{
   typedef T DataType;

   const T mScalar;

   inline ScalarArg(const T scalar) : mScalar(scalar) {}
   inline T operator[](const unsigned i) const
   { return mScalar; }
};

template <typename T>
inline ScalarArg<T> makeScalarArg(T val)
{ return ScalarArg<T>(val); }

// --- TRAITS --- //
/** Traits class for expression template parameters.
* NOTE: These types are VERY important to the performance of the code.
*    They allow the compiler to optimize (ie. eliminate) much code.
*/
template<typename T>
struct ExprTraits
{
   typedef T const& ExprRef;     // Refer using a constant reference
};

template<typename T, unsigned SIZE>
struct ExprTraits< VecB<T, SIZE, ScalarArg<T> > >
{
   typedef VecB<T,SIZE,ScalarArg<T> > ExprRef;
};

// -- Expressions -- //
/** Binary vector expression.
*
* Stores the two vector expressions to process.
*/
template <typename EXP1_T, typename EXP2_T, typename OP>
struct VecBinaryExpr
{
   typedef typename EXP1_T::DataType DataType;

   typename ExprTraits<EXP1_T>::ExprRef Exp1;
   typename ExprTraits<EXP2_T>::ExprRef Exp2;

   inline VecBinaryExpr(const EXP1_T& e1, const EXP2_T& e2) : Exp1(e1), Exp2(e2) {;}
   inline DataType operator[](const unsigned i) const
   { return OP::eval(Exp1[i], Exp2[i]); }
};

/** Unary vector expression.
* Holds the vector expression and unary operation to apply to it.
*/
template <typename EXP1_T, typename OP>
struct VecUnaryExpr
{
   typedef typename EXP1_T::DataType DataType;

   typename ExprTraits<EXP1_T>::ExprRef Exp1;

   inline VecUnaryExpr(const EXP1_T& e1) : Exp1(e1) {;}
   inline DataType operator[](const unsigned i) const
   { return OP::eval(Exp1[i]); }
};

// --- Operations --- //
/* Binary operations to add two vector expressions. */
struct VecPlusBinary
{
   template <typename T>
   static inline T eval(const T& a1, const T& a2)
   { return a1+a2; }
};

template<typename T, unsigned SIZE, typename R1, typename R2>
inline VecB<T,SIZE, VecBinaryExpr<VecB<T,SIZE,R1>, VecB<T,SIZE,R2>, VecPlusBinary> >
sum(const VecB<T,SIZE,R1>& v1, const VecB<T,SIZE,R2>& v2)
{
   return VecB<T,SIZE,
               VecBinaryExpr<VecB<T,SIZE,R1>,
                             VecB<T,SIZE,R2>,
                             VecPlusBinary> >( VecBinaryExpr<VecB<T,SIZE,R1>,
                                                             VecB<T,SIZE,R2>,
                                                             VecPlusBinary>(v1,v2) );
}


template<typename T, unsigned SIZE, typename R1>
inline VecB<T,SIZE, VecBinaryExpr<VecB<T,SIZE,R1>, VecB<T,SIZE,ScalarArg<T> >, VecPlusBinary> >
sum(const VecB<T,SIZE,R1>& v1, const T& arg)
{
   return VecB<T,SIZE,
               VecBinaryExpr<VecB<T,SIZE,R1>,
                             VecB<T,SIZE,ScalarArg<T> >,
                             VecPlusBinary> >( VecBinaryExpr<VecB<T,SIZE,R1>,
                                                             VecB<T,SIZE,ScalarArg<T> >,
                                                             VecPlusBinary>(v1,ScalarArg<T>(arg)) );
}


} // meta

template<typename T, unsigned SIZE, typename R1, typename R2>
inline VecB<T,SIZE, meta::VecBinaryExpr<VecB<T,SIZE,R1>, VecB<T,SIZE,R2>, meta::VecPlusBinary> >
operator+(const VecB<T,SIZE,R1>& v1, const VecB<T,SIZE,R2>& v2)
{
   return VecB<T,SIZE,
               meta::VecBinaryExpr<VecB<T,SIZE,R1>,
                                   VecB<T,SIZE,R2>,
                                   meta::VecPlusBinary> >( meta::VecBinaryExpr<VecB<T,SIZE,R1>,
                                                                               VecB<T,SIZE,R2>,
                                                                               meta::VecPlusBinary>(v1,v2) );
}


} // gmtl

namespace gm = gmtl::meta;

#endif
