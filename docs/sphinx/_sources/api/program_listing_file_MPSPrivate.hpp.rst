
.. _program_listing_file_MPSPrivate.hpp:

Program Listing for File MPSPrivate.hpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_MPSPrivate.hpp>` (``MPSPrivate.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   
   #include "MPSDefines.hpp"
   #include <objc/runtime.h>
   
   #define _MPS_PRIVATE_CLS( symbol )                 ( Private::Class::s_k ## symbol )
   #define _MPS_PRIVATE_SEL( accessor )                 ( Private::Selector::s_k ## accessor )
   
   #if defined( MPS_PRIVATE_IMPLEMENTATION )
   
   #define _MPS_PRIVATE_VISIBILITY                     __attribute__( ( visibility( "default" ) ) )
   #define _MPS_PRIVATE_IMPORT                       __attribute__( ( weak_import ) )
   
   #ifdef __OBJC__
   #define  _MPS_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   ( ( __bridge void* ) objc_lookUpClass( # symbol ) )
   #define _MPS_PRIVATE_OBJC_GET_PROTOCOL( symbol )  ( ( __bridge void* ) objc_getProtocol( # symbol ) )
   #else
   #define  _MPS_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   objc_lookUpClass( # symbol )
   #define _MPS_PRIVATE_OBJC_GET_PROTOCOL( symbol )  objc_getProtocol( # symbol )
   
   #endif // __OBJC__
   
   #define _MPS_PRIVATE_DEF_CLS( symbol )  void*   s_k ## symbol   _MPS_PRIVATE_VISIBILITY = _MPS_PRIVATE_OBJC_LOOKUP_CLASS( symbol )
   #define _MPS_PRIVATE_DEF_PRO(symbol) void* s_k ## symbol _MPS_PRIVATE_VISIBILITY = _MPS_PRIVATE_OBJC_GET_PROTOCOL(symbol)
   #define _MPS_PRIVATE_DEF_SEL( accessor, symbol )     SEL     s_k ## accessor     _MPS_PRIVATE_VISIBILITY = sel_registerName( symbol )
   
   #include <dlfcn.h>
   #define MPS_DEF_FUNC( name,signature ) \
       using Fn##name = signature; \
       Fn##name name = reinterpret_cast< Fn##name >( dlsym( RTLD_DEFAULT, #name) )
   
   namespace MPS::Private
   {
       template <typename _Type>
       inline _Type const LoadSymbol(const char* pSymbol){
           const _Type* pAddress = static_cast<_Type*>(dlsym(RTLD_DEFAULT, pSymbol));
           return pAddress ? *pAddress : nullptr;
       }
   } // MPS::Private
   
   #define _MPS_PRIVATE_DEF_STR(type,symbol)       \
       _MPS_EXTERN type const MPS##symbol _MPS_PRIVATE_IMPORT; \
       type const MPS::symbol = (nullptr!=&MPS##symbol)?MPS##symbol : nullptr
   #define _MPS_PRIVATE_DEF_CONST(type, symbol)    \
       _MPS_EXTERN type const MPS##symbol _MPS_PRIVATE_IMPORT; \
       type const MPS::symbol = (nullptr!=&MPS##symbol)?MPS##symbol : nullptr
   #define _MPS_PRIVATE_DEF_WEAK_CONST(type,symbol)    \
       _MPS_EXTERN type const MPS##symbol; \
       type const MPS::symbol = Private::LoadSymbol<type>("MPS" #symbol)
   
   #else
   #define _MPS_PRIVATE_DEF_CLS(symbol) extern void* s_k##symbol
   #define _MPS_PRIVATE_DEF_PRO(symbol) extern void* s_k##symbol
   #define _MPS_PRIVATE_DEF_SEL(accessor, symbol) extern SEL s_k##accessor
   #define _MPS_PRIVATE_DEF_STR(type,symbol) extern type const MPS::symbol
   #define _MPS_PRIVATE_DEF_CONST(type,symbol) extern type const MPS::symbol
   #define _MPS_PRIVATE_DEF_WEAK_CONST(type,symbol) extern type const MTL::symbol
   
   #endif // MPS_PRIVATE_IMPLEMENTATION
   
   namespace MPS
   {
       namespace Private
       {
           namespace Class
           {
   
           }
       }
   }
   
   namespace MPS
   {
       namespace Private
       {
           namespace Protocol
           {
   
           }
       }
   }
   
   namespace MPS
   {
       namespace Private
       {
           namespace Selector
           {
               _MPS_PRIVATE_DEF_SEL(beginScope, "beginScope");
               _MPS_PRIVATE_DEF_SEL(endScope, "endScope");
           }
       }
   }
   
   
   
   
   
