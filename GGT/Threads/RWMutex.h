#ifndef _GFX_RWMutex_h_
#define _GFX_RWMutex_h_

#include <gfxConfig.h>
#include <nspr.h>

 namespace gfx {

//----------------------------------------------
// RWMutex
//
// Purpose:
//:    RWMutex wrapper
//
// Author:
//	   Allen Bierbaum
//-----------------------------------------------
//!PUBLIC_API:
class RWMutex
{
public:
    RWMutex () : mRWLock(NULL), mIsLocked(false)
    {
      mRWLock = PR_NewRWLock(PR_RWLOCK_RANK_NONE, "UnNamed");
    }

    ~RWMutex(void)
    {
      PR_DestroyRWLock(mRWLock);
    }

    //---------------------------------------------------------
    //: Lock the mutex.
    //
    //! RETURNS:  1 - Acquired
    //! RETURNS: -1 - Error
    //---------------------------------------------------------
    bool acquire()
    {
        return acquireWrite();
    }

    //----------------------------------------------------------
    //: Acquire a read mutex.
    //----------------------------------------------------------
    bool acquireRead(void)
    {
       PR_RWLock_Rlock(mRWLock);
       mIsLocked = true;
       return true;
    }

    //----------------------------------------------------------
    //: Acquire a write mutex.
    //----------------------------------------------------------
    bool acquireWrite(void)
    {
       PR_RWLock_Wlock(mRWLock);
       mIsLocked = true;
       return true;
    }

    //---------------------------------------------------------
    //: Release the mutex.
    //
    //! RETURNS:  0 - Success
    //! RETURNS: -1 - Error
    //---------------------------------------------------------
    bool release(void)
    {
       mIsLocked = false;
       PR_RWLock_Unlock(mRWLock);
       return true;
    }

    //------------------------------------------------------
    //:	Test the current lock status.
    //
    //! RETURNS: 0 - Not locked
    //! RETURNS: 1 - Locked
    //------------------------------------------------------
    bool test()
    {
        return mIsLocked;
    }

protected:
    PRRWLock* mRWLock;
    bool      mIsLocked;

    // = Prevent assignment and initialization.
    void operator= (const RWMutex &) {}
    RWMutex (const RWMutex &) {}
};

 }

#endif
