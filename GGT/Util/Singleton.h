#ifndef _SINGLETON_TEMPLATE_H_
#define _SINGLETON_TEMPLATE_H_

#include <gfxConfig.h>
#include <Threads/Mutex.h>
#include <Threads/Guard.h>
#include <iostream>

//
// Double checked locking version
//

///*
#define SingletonHeader(TYPE) \
public:                                        \
   static TYPE* instance(void)                 \
   {                                           \
      if(_instance == NULL)                    \
      {                                        \
         Guard<Mutex> guard(_inst_lock);   \
         if (_instance == NULL)                \
         { _instance = new TYPE; }             \
      }                                        \
      return _instance;                        \
   }                                           \
private:                                       \
   static Mutex _inst_lock;                  \
   static TYPE* _instance

#define SingletonHeaderWithInitFunc(TYPE, INIT_FUNC_NAME) \
public:                                        \
   static TYPE* instance(void)                 \
   {                                           \
      if(_instance == NULL)                    \
      {                                        \
         Guard<Mutex> guard(_inst_lock);   \
         if (_instance == NULL)                \
         {                                     \
            _instance = new TYPE;              \
            _instance->INIT_FUNC_NAME();       \
         }                                     \
      }                                        \
      return _instance;                        \
   }                                           \
private:                                       \
   static Mutex _inst_lock;                  \
   static TYPE* _instance


#define SingletonImp(TYPE) \
            TYPE* TYPE::_instance = NULL; \
            Mutex  TYPE::_inst_lock
//*/

//
// Non-locking version
//
/*
#define SingletonHeader(TYPE) \
public:                                        \
   static TYPE* instance(void)                 \
   {                                           \
      if (_instance == NULL)                   \
      {                                        \
         std::cout << "Creating instance of: TYPE" << std::endl; \
         _instance = new TYPE;                 \
      }                                        \
      return _instance;                        \
   }                                           \
private:                                       \
   static TYPE* _instance

#define SingletonHeaderWithInitFunc(TYPE, INIT_FUNC_NAME) \
public:                                        \
   static TYPE* instance(void)                 \
   {                                           \
      if (_instance == NULL)                   \
      {                                        \
         std::cout << "Creating instance of: TYPE" << std::endl; \
         _instance = new TYPE;                 \
         _instance->INIT_FUNC_NAME();          \
      }                                        \
      return _instance;                        \
   }                                           \
private:                                       \
   static TYPE* _instance

#define SingletonImp(TYPE) \
            TYPE* TYPE::_instance = NULL
*/

#endif
