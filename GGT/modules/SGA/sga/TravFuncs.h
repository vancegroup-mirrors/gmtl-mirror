/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: TravFuncs.h,v $
 * Date modified: $Date: 2002-01-18 20:43:10 $
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
#ifndef _SGA_TRAV_FUNCS_H_
#define _SGA_TRAV_FUNCS_H_

// Allow calling of a member function of a class
// to be a function object
template <class _Ret, class _Tp, class _Arg>
class member_func_adapter : public std::unary_function<_Arg,_Ret> {
public:
   explicit member_func_adapter(_Tp* __obj, _Ret (_Tp::*__pf)(_Arg)) : mObj(__obj), _M_f(__pf) {}
   _Ret operator()(_Arg _a) const { return (mObj->*_M_f)(_a); }
private:
   _Tp* mObj;                    // The object to call
   _Ret (_Tp::*_M_f)(_Arg);      // The function of the object to call
};

template <class _Tp, class _Arg>
class member_func_adapter<void, _Tp, _Arg> : public std::unary_function<_Arg,void> {
public:
   explicit member_func_adapter(_Tp* __obj, void (_Tp::*__pf)(_Arg)) : mObj(__obj), _M_f(__pf) {}
   void operator()(_Arg _a) const { (mObj->*_M_f)(_a); }
private:
   _Tp* mObj;                    // The object to call
   void (_Tp::*_M_f)(_Arg);      // The function of the object to call
};

/*
template <class _Ret, class _Tp, class _Arg>
_Ret member_func_adapter<_Ret, _Tp, _Arg>::operator()(_Arg _a) const
{ return (mObj->*_M_f)(_a); }

// Specialize for void (can't return value from void)
template <class _Ret, class _Tp, class _Arg>
void member_func_adapter<void, _Tp, _Arg>::operator()(_Arg _a) const
{ (mObj->*_M_f)(_a); return; }
*/
// --- member_func1 --- //
// Helper function to make the member_func_adapter automagically
template <class _Ret, class _Tp, class _Arg>
inline member_func_adapter<_Ret, _Tp, _Arg> member_func1(_Tp* obj, _Ret (_Tp::*func)(_Arg))
{ return member_func_adapter<_Ret, _Tp, _Arg>(obj, func); }

/*
template <class _Tp>
class mem_fun_t<void, _Tp> : public unary_function<_Tp*,void> {
public:
  explicit mem_fun_t(void (_Tp::*__pf)()) : _M_f(__pf) {}
  void operator()(_Tp* __p) const { (__p->*_M_f)(); }
private:
  void (_Tp::*_M_f)();
};

template <class _Tp>
class const_mem_fun_t<void, _Tp> : public unary_function<const _Tp*,void> {
public:
  explicit const_mem_fun_t(void (_Tp::*__pf)() const) : _M_f(__pf) {}
  void operator()(const _Tp* __p) const { (__p->*_M_f)(); }
private:
  void (_Tp::*_M_f)() const;
};

template <class _Tp>
class mem_fun_ref_t<void, _Tp> : public unary_function<_Tp,void> {
public:
  explicit mem_fun_ref_t(void (_Tp::*__pf)()) : _M_f(__pf) {}
  void operator()(_Tp& __r) const { (__r.*_M_f)(); }
private:
  void (_Tp::*_M_f)();
};

template <class _Tp>
class const_mem_fun_ref_t<void, _Tp> : public unary_function<_Tp,void> {
public:
  explicit const_mem_fun_ref_t(void (_Tp::*__pf)() const) : _M_f(__pf) {}
  void operator()(const _Tp& __r) const { (__r.*_M_f)(); }
private:
  void (_Tp::*_M_f)() const;
};

template <class _Tp, class _Arg>
class mem_fun1_t<void, _Tp, _Arg> : public binary_function<_Tp*,_Arg,void> {
public:
  explicit mem_fun1_t(void (_Tp::*__pf)(_Arg)) : _M_f(__pf) {}
  void operator()(_Tp* __p, _Arg __x) const { (__p->*_M_f)(__x); }
private:
  void (_Tp::*_M_f)(_Arg);
};

template <class _Tp, class _Arg>
class const_mem_fun1_t<void, _Tp, _Arg> 
  : public binary_function<const _Tp*,_Arg,void> {
public:
  explicit const_mem_fun1_t(void (_Tp::*__pf)(_Arg) const) : _M_f(__pf) {}
  void operator()(const _Tp* __p, _Arg __x) const { (__p->*_M_f)(__x); }
private:
  void (_Tp::*_M_f)(_Arg) const;
};

template <class _Tp, class _Arg>
class mem_fun1_ref_t<void, _Tp, _Arg>
  : public binary_function<_Tp,_Arg,void> {
public:
  explicit mem_fun1_ref_t(void (_Tp::*__pf)(_Arg)) : _M_f(__pf) {}
  void operator()(_Tp& __r, _Arg __x) const { (__r.*_M_f)(__x); }
private:
  void (_Tp::*_M_f)(_Arg);
};

template <class _Tp, class _Arg>
class const_mem_fun1_ref_t<void, _Tp, _Arg>
  : public binary_function<_Tp,_Arg,void> {
public:
  explicit const_mem_fun1_ref_t(void (_Tp::*__pf)(_Arg) const) : _M_f(__pf) {}
  void operator()(const _Tp& __r, _Arg __x) const { (__r.*_M_f)(__x); }
private:
  void (_Tp::*_M_f)(_Arg) const;
};

*/



#endif
