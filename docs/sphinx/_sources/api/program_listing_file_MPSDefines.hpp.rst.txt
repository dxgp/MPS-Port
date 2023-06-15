
.. _program_listing_file_MPSDefines.hpp:

Program Listing for File MPSDefines.hpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_MPSDefines.hpp>` (``MPSDefines.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   
   #include "../Foundation/NSDefines.hpp"
   
   #define _MPS_EXPORT _NS_EXPORT
   #define _MPS_EXTERN _NS_EXTERN
   #define _MPS_INLINE _NS_INLINE
   #define _MPS_PACKED _NS_PACKED
   
   #define _MPS_CONST(type, name) _NS_CONST(type, name)
   #define _MPS_ENUM(type, name) _NS_ENUM(type, name)
   #define _MPS_OPTIONS(type, name) _NS_OPTIONS(type, name)
   
   #define _MPS_VALIDATE_SIZE(ns, name) _NS_VALIDATE_SIZE(ns, name)
   #define _MPS_VALIDATE_ENUM(ns, name) _NS_VALIDATE_ENUM(ns, name)
   
   
