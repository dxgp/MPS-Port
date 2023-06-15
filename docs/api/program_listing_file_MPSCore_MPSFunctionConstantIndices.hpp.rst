
.. _program_listing_file_MPSCore_MPSFunctionConstantIndices.hpp:

Program Listing for File MPSFunctionConstantIndices.hpp
=======================================================

|exhale_lsh| :ref:`Return to documentation for file <file_MPSCore_MPSFunctionConstantIndices.hpp>` (``MPSCore/MPSFunctionConstantIndices.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   
   namespace MPS{
       #define MPSDeviceCapsIndex                            127                     // unavailable to user
       #define MPSFunctionConstantIndex                      (MPSDeviceCapsIndex-1)  // unavailable to user
       #define MPSBatchSizeIndex                             (MPSDeviceCapsIndex-2)  // unavailable to user
       #define MPSUserConstantIndex                          (MPSDeviceCapsIndex-3)  // unavailable to user
       #define MPSNDArrayConstantIndex                       (MPSDeviceCapsIndex-4)  // unavailable to user
       #define MPSFunctionConstantIndexReserved              (MPSDeviceCapsIndex-5)  // unavailable to user
       #define MPSUserAvailableFunctionConstantStartIndex    (MPSDeviceCapsIndex-8)  // first index availble to user
   }
   
