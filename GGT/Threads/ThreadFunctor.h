#ifndef _GFX_THREAD_FUNCTOR_H_
#define _GFX_THREAD_FUNCTOR_H_

#include <gfxConfig.h>
#include <stdlib.h>

namespace gfx
{

//---------------------------------------------------------------
//: Converts a function into a functor that can be passed to a
//  extern C type function to be called by a thread creation
//  routine.
//!PUBLIC_API:
//---------------------------------------------------------------
class  BaseThreadFunctor
{
public:
    virtual void operator()() = 0;    // Pure virtual
    virtual void operator()(void*) = 0;
    virtual void setArg(void*) = 0;
};

//---------------------------------------------------------------
//: Member functor class.
//!PUBLIC_API:
//---------------------------------------------------------------
template<class T>
class ThreadMemberFunctor : public  BaseThreadFunctor
{
public:
    typedef void (T::* FunPtr)(void*);

    ThreadMemberFunctor(T* theObject, FunPtr func, void* arg = NULL)
    {
    	object = theObject;
    	function = func;
    	argument = arg;
    }

    void
    operator() (void* arg) {
        (object->*function)(arg);
    }

    void
    operator() () {
        (object->*function)(argument);
    }

    void
    setArg (void* arg) {
        argument = arg;
    }

private:
    T*	    object;
    FunPtr  function;
    void*   argument;
};


//---------------------------------------------------------------
//: Nonmember functor class.  Converts a NonMember function into
//+ a functor.
//
//!PUBLIC_API:
//---------------------------------------------------------------
class ThreadNonMemberFunctor : public  BaseThreadFunctor
{
public:
    typedef void(* NonMemFunPtr)(void*);

    //---------------------------------------------------------------
    //: Constructor.
    //---------------------------------------------------------------
    ThreadNonMemberFunctor (NonMemFunPtr f, void* a = NULL) : func(f), argument(a)
    {;}

    virtual void operator() (void* arg) {
        (*func)(arg);
    }

    virtual void operator() () {
        (*func)(argument);
    }

    void setArg (void* arg) {
        argument = arg;
    }

    // private:
    // = Arguments to thread startup.
    NonMemFunPtr func;	// Thread startup function (C++ linkage).
    void* argument;		// Argument to thread startup function.
};

} // namescape gfx

//---------------------------------------------
// This is the actual function that is called.
// It must be extern "C"
//---------------------------------------------
/*
#if defined(VJ_IRIX_SPROC)
extern "C" void ThreadFunctorFunction(void* args);
#elif defined(VJ_OS_Win32)
    unsigned int __stdcall ThreadFunctorFunction(void* args);
#elif defined(VJ_USE_PTHREADS)
#   ifdef _PTHREADS_DRAFT_4
        extern "C" void
#   else
        extern "C" void*
#   endif
        ThreadFunctorFunction (void* args);
#else
    extern "C" void ThreadFunctorFunction(void* args);
#endif	// VJ_IRIX_SPROC
*/

// NSPR thread functor
extern "C" void gfxThreadFunctorFunction(void* args);

#endif	/* _THREAD_FUNCTOR_H_ */
