#ifndef _COND_VAR_
#define _COND_VAR_

#include <gfxConfig.h>
#include <nspr.h>

namespace gfx {

/*
  FROM: NSPR 2.0 documentation

Condition variables are always monitored. The relevant operations on
conditions are always performed from within the monitor. They are
used to communicate changes in the state of the monitored data
(though still preserving the monitored invariant). Condition variables allow
one or more threads to wait for a predetermined condition to exist,
and they allow another thread to notify them when the condition occurs.
Condition variables themselves do not carry the semantics of the state change,
but simply provide a mechanism for indicating that
something has changed. It is the programmer's responsibility to associate
a condition with the state of the data.

A thread may be designed to wait for a particular situation to exist
in some monitored data. Since the nature of the situation is not an
attribute of the condition, the program must test that itself. Since
this testing involves the monitored data, it must be done from within the
monitor. The wait operation atomically exits the monitor and blocks the
calling thread in a waiting condition state. When the thread is
resumed after the wait, it will have reentered the monitor, making
operations on the data safe.

There is a subtle interaction between the thread(s) waiting on a condition
and those notifying it. The notification must take place within a
monitor--the same monitor that protects the data being manipulated by
the notifier. In pseudo code, the sequence looks like this:

lock->acquire;          // enter(monitor);
... manipulate the monitored data
condvar->notify()       // notify(condition);
lock->release();        // exit(monitor);

Notifications to a condition do not accumulate. Nor is it required that any thread be waiting on a condition when the notification occurs.
The design of the code that waits on a condition must take these facts into account. Therefore, the pseudo code for the waiting thread
might look like this:

lock->acquire();        // enter(monitor)
while (!expression) wait(condition);
... manipulate monitored data
lock->release();        // exit(monitor);
*/

// Condition variable wrapper
class CondVar {
public:
    // -----------------------------------------------------------------------
    //: Constructor for CondPosix class.
    //
    //! PRE: None.
    //! POST: The condition variable is intialized, and the mutex variable
    //+       associated with it is defined.  These two steps must be done
    //+       before any other member functions can use them.
    // -----------------------------------------------------------------------
    CondVar ()
    {
       mCondLock = PR_NewLock();
       mCondVar = PR_NewCondVar(mCondLock);
    }

    // -----------------------------------------------------------------------
    //: Destructor for CondVar class.
    //
    //! PRE: None.
    //! POST: The condition variable is destroyed.
    // -----------------------------------------------------------------------
    ~CondVar(void)
    {
        PR_DestroyCondVar(mCondVar);
        PR_DestroyLock(mCondLock);
    }

    // -----------------------------------------------------------------------
    //: Block on a condition.
    //
    //! PRE: The mutex variable associated with the condition variable must
    //+      be locked.
    //! POST: The condition variable is locked.  If it was previously
    //+       locked, the caller blocks until signaled.
    //
    //! RETURNS:  true - Successful completion
    //! RETURNS:  false - Error
    // -----------------------------------------------------------------------
    bool
    wait ()
    {
        // If not locked ...
        /*
        if ( mIsLocked == false )
        {
            std::cerr << "CondVar::wait: INCORRECT USAGE: Mutex was not "
                      << "locked when wait invoked!!!\n";
            return false;
        }
        */

        // The mutex variable must be locked when passed to
        // pthread_cond_wait().
        PRStatus ret_status = PR_WaitCondVar(mCondVar, PR_INTERVAL_NO_TIMEOUT);
        if(ret_status == PR_SUCCESS)
           return true;
        else
           return false;
    }

    // -----------------------------------------------------------------------
    //: Notify a thread waiting on the condition variable.
    //
    //! PRE: The condition variable must be locked.
    //! POST: The condition variable is unlocked, and a signal is sent to a
    //+       thread waiting on it.
    //
    //! RETURNS:  true - Successful completion
    //! RETURNS:  false - Error
    // -----------------------------------------------------------------------
    inline bool
    notify (void)
    {
       // If not locked ...
        if ( mIsLocked == false )
        {
            std::cerr << "CondVar::wait: INCORRECT USAGE: Mutex was not "
                      << "locked when wait invoked!!!\n";
            return false;
        }

       // ASSERT:  We have been locked
        PRStatus ret_status = PR_NotifyCondVar(mCondVar);
        if(ret_status == PR_SUCCESS)
           return true;
        else
           return false;
    }

    // -----------------------------------------------------------------------
    //: Notify all waiting threads.
    //
    //! PRE: The mutex variable associated with the condition variable
    //+      should be locked.
    //! POST: The condition variable is unlocked, and all waiting threads
    //+       are signaled of this event.
    //
    //! RETURNS:  true - Successful completion
    //! RETURNS: -1 - Error
    // -----------------------------------------------------------------------
    inline int
    notifyAll (void) {
        // ASSERT:  We have been locked

        // If not locked ...
        if ( mIsLocked == false) {
            std::cerr << "CondVar::broadcast: Mutex was not locked when "
                      << "broadcast called!!!\n";
        }

        // ASSERT:  We have been locked
        PRStatus ret_status = PR_NotifyAllCondVar(mCondVar);
        if(ret_status == PR_SUCCESS)
           return true;
        else
           return false;
   }

    // -----------------------------------------------------------------------
    //: Acquire a lock on the mutex variable associated with the condition
    //+ variable.
    //
    //! PRE: None.
    //! POST: A lock is acquired on the mutex variable associated with the
    //+      condition variable.  If a lock is acquired, the caller controls
    //+      the mutex variable.  If it was previously locked, the caller
    //+      blocks until it is unlocked.
    //
    //! RETURNS:  true - Successful completion
    //! RETURNS:  false - Error
    // -----------------------------------------------------------------------
    inline bool
    acquire (void)
    {
        PR_Lock(mCondLock);
        mIsLocked = true;
        return true;
    }

    // -----------------------------------------------------------------------
    //: Release the lock on the mutex variable associated with the condition
    //+ variable.
    //
    //! PRE: None.
    //! POST: The lock held by the caller on the mutex variable is released.
    // -----------------------------------------------------------------------
    inline bool
    release (void)
    {
       mIsLocked = false;
       PR_Unlock(mCondLock);
       return true;
    }

private:
    PRCondVar*	   mCondVar;	//: Condition variable
    PRLock*	      mCondLock;	//: A default mutex variable
    bool          mIsLocked;  //: Is the cond var currently locked

    // = Prevent assignment and initialization.
    void operator= (const CondVar&) {}
    CondVar (const CondVar &c) {}
};

}

#endif
