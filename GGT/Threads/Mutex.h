#ifndef _GFX_MUTEX_H_
#define _GFX_MUTEX_H_

//----------------------------------------------
// Mutex
//
// Purpose:
//    Defines a mutex wrapper.
//    Try to make everything inline so that we get
//    maximum performance.
//
// Author:
//	   Allen Bierbaum
//
// Date:
//    Sept 12, 2000
//-----------------------------------------------
#include <nspr.h>

namespace gfx {

class Mutex
{
public:
   Mutex() : mLock(NULL), mCurrentlyLocked(false)
    {
        mLock = PR_NewLock();
    }

    ~Mutex(void)
    {
       PR_DestroyLock(mLock);
    }

    //---------------------------------------------------------
    //: Lock the mutex.
    //
    //! RETURNS:  true - Acquired
    //! RETURNS: false - Error
    //---------------------------------------------------------
    bool acquire()
    {
        PR_Lock(mLock);
        mCurrentlyLocked = true;
        return true;
    }

    //---------------------------------------------------------
    //: Release the mutex.
    //
    //! RETURNS:  true - Success
    //! RETURNS:  false - Error
    //---------------------------------------------------------
    bool release()
    {
       mCurrentlyLocked = false;
       PR_Unlock(mLock);
       return true;
    }

    //------------------------------------------------------
    //: Test the current lock status.
    //
    //! RETURNS: true - Not locked
    //! RETURNS: false - Locked
    //------------------------------------------------------
    bool test() const
    {
        return mCurrentlyLocked;
    }

protected:
    PRLock* mLock;
    bool    mCurrentlyLocked;

    // = Prevent assignment and initialization.
    void operator= (const  Mutex &) {}
     Mutex (const  Mutex &) {}
};

}

#endif	/* _GFX_MUTEX_H_ */
