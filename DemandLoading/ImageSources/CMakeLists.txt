#
# Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

include(BuildConfig)

otk_add_library( ImageSources STATIC
  src/DeviceConstantImage.cpp
  src/DeviceConstantImageKernels.cu
  src/DeviceMandelbrotImage.cpp
  src/DeviceMandelbrotImageKernels.cu
  src/ImageSources.cpp
  )
set_property(TARGET ImageSources PROPERTY FOLDER DemandLoading)

add_library(OptiXToolkit::ImageSources ALIAS ImageSources)

target_sources(ImageSources
  PUBLIC 
  FILE_SET HEADERS 
  BASE_DIRS include
  FILES
  include/OptiXToolkit/ImageSources/DeviceConstantImage.h
  include/OptiXToolkit/ImageSources/DeviceConstantImageParams.h
  include/OptiXToolkit/ImageSources/DeviceMandelbrotImage.h
  include/OptiXToolkit/ImageSources/DeviceMandelbrotParams.h
  include/OptiXToolkit/ImageSources/ImageSources.h
  include/OptiXToolkit/ImageSources/MultiCheckerImage.h
)

target_include_directories( ImageSources
  PUBLIC
  ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
  PRIVATE
  src
  )

target_link_libraries( ImageSources
  PRIVATE
  OptiXToolkit::ImageSource
  OptiXToolkit::Util
)

set_target_properties(ImageSources PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
